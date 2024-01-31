/* spawn.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <process.h>
#include <sys/wait.h>
#include "winsup.h"
#include "paths.h"

/* Add .exe to PROG if not already present and see if that exists.
   If not, return PROG (converted from posix to win32 rules if necessary).
   The result is always BUF.

   If REPORT_FAILURE_P is zero, then if PROG.exe isn't found, return PROG.
   If REPORT_FAILURE_P is non-zero, NULL is returned if neither PROG.exe
   nor PROG exist.  */

static const char *
perhaps_suffix (const char *prog, char *buf, int report_failure_p)
{
  int attr;
  char temp [MAX_PATH];

  strcpy (temp, prog);

check_again:
  int l = strlen (temp);

  strcpy (buf, path_conv (temp).get_win32 ());
  int l2 = strlen (buf);

  /* If .exe not already present, add it and try that.  */
  if (l < 5 || strcasecmp (prog + l - 4, ".exe"))
    {
      strcat (buf, ".exe");
      attr = GetFileAttributesA (buf);
      if (attr > 0)
        {
          if (attr & FILE_ATTRIBUTE_SYSTEM)
            {
              /* funny case - prog.exe is a symlink. Resolve it */
              strcpy (temp, buf);
              goto check_again;
            }
          if (!(attr & FILE_ATTRIBUTE_DIRECTORY))
	    return buf;
        }
    }

  /* .exe not found */
  buf[l2] = 0;
  if (report_failure_p)
    {
      attr = GetFileAttributesA (buf);
      if (attr > 0 && !(attr & FILE_ATTRIBUTE_DIRECTORY))
	return buf;
      return NULL;
    }
  return buf;
}

static const char *
find_exec_1 (const char *name, char *buf)
{
  char tmp[MAX_PATH];

  if (strchr (name, '/') || strchr (name, '\\'))
    return perhaps_suffix (name, buf, 0);

  if (isalpha (name[0]) && name[1] == ':')
    return perhaps_suffix (name, buf, 0);

  const char *path = getenv ("PATH");
  if (!path)
    return perhaps_suffix (name, buf, 0);

  /* Win32 systems always check . first, but PATH may not be set up to
     do this.  FIXME: This can be simplified, but leave til later.  */
  if (perhaps_suffix (name, buf, 1) != NULL)
    return buf;

  /* Rather than force the issue of what the path delimiter should be,
     we do this:  If a ';' is present in the path list use ';', otherwise
     if the first path begins with <letter>: (in which case it can be the
     only element since if it wasn't a ';' would be present) use ';',
     otherwise use ':'.  */
  const char path_delim = posix_path_list_p (path) ? ':' : ';';

  debug_printf ("path_delim = %c, PATH = %s\n", path_delim, path);

  while (*path)
    {
      char *d = tmp;

      while (*path && *path != path_delim)
	*d++ = *path++;
      /* An empty path means the current directory, but we've already
	 tried that.  */
      if (d != tmp)
	{
	  *d++ = '/';
	  strcpy (d, name);

	  debug_printf ("trying %s\n", tmp);

	  if (perhaps_suffix (tmp, buf, 1) != NULL)
	    return buf;
	}

      if (*path == path_delim)
	path++;			/* skip over delim */
    }

  /* That didn't work.  Give up and return NAME.  We've already looked in
     the current directory.  */
  strcpy (buf, path_conv (name).get_win32 ());
  return buf;
}

/* Find executable NAME, maybe by appending .exe to it.
   NAME.exe is preferred if it is found.
   $PATH is used if NAME has no directory elements.
   The result is always BUF.
   This function exists to simplify the calling of debug_printf around
   find_exec_1.  */

const char *
find_exec (const char *name, char *buf)
{
  debug_printf ("find_exec (%s)\n", name);
  const char *res = find_exec_1 (name, buf);
  debug_printf ("%s = find_exec (%s)\n", res, name);
  return res;
}

/* Utility for spawn_guts.  */

static HANDLE
handle (int n, int direction)
{
  hinfo &h = myself->hmap[n];

  if (!h.is_open ())
    return INVALID_HANDLE_VALUE;
  if (h.h->get_close_on_exec ())
    return INVALID_HANDLE_VALUE;
  if (direction == 0)
    return h.h->get_input_handle ();
  return h.h->get_output_handle ();
}

/* Cover function for CreateProcess.

   This function is used by both the routines that search $PATH and those
   that do not.  This should work out ok as according to the documentation,
   CreateProcess only searches $PATH if PROG has no directory elements.

   Spawning doesn't fit well with Posix's fork/exec (one can argue the merits
   of either but that's beside the point).  If we're exec'ing we want to
   record the child pid for fork.  If we're spawn'ing we don't want to do
   this.  It is up to the caller to handle both cases.

   The result is the process id.  The handle of the created process is
   stored in H.
*/

HANDLE NO_COPY hExeced;
DWORD NO_COPY exec_exit;

int
spawn_guts (HANDLE hToken, const char * prog_arg, const char *const *argv,
	    const char *const envp[], int pid, int mode)
{
  int i;
  char *copy;
  BOOL rc;
  int argc;

  hExeced = NULL;

  if (prog_arg == 0)
    {
      syscall_printf ("prog_arg is 0\n");
      set_errno(EINVAL);
      return -1;
    }

  syscall_printf ("spawn_guts (%s)\n", prog_arg);

  if (argv == 0)
    {
      syscall_printf ("argv is 0\n");
      set_errno(EINVAL);
      return (-1);
    }

  /* CreateProcess takes one long string that is the command line (sigh).
     We need to quote any argument that has whitespace or embedded "'s.  */
  {
    int clen, last_clen;

    /* See how much space we need.  Note that "'s are doubled. */
    clen = 0;
    if (argv[0] == 0)
      {
	/* Hmm - nasty - no prog name, - fill one up for us */
	small_printf ("spawn_guts: NO ARG0 !!\n");
	char **tmp;
	tmp = (char **) &argv[0];
	*tmp = (char *) prog_arg;
      }
    for (argc = 0; argv[argc]; argc++)
      {
        int needquote = 0;
        const char *s;
	/* Zero length args need quotes. */
	if (!argv[argc][0])
	  needquote = 1;

        for (s = argv[argc];  *s; s++)
          {
	    if (*s == '"')
	      clen++;
            if (*s == ' ' || *s == '\t' || *s == '"')
	      needquote = 1;
            clen++;
          }
        if (needquote)
	  clen += 2;		/* space for quotes */
        clen++;			/* space for separating space */
      }

    if ((copy = (char *) alloca (clen + 1)) == NULL)
      {
        syscall_printf ("couldn't allocate %d characters\n", clen + 1);
	set_errno (ENAMETOOLONG);
	return -1;
      }
    syscall_printf ("total arg length %d, copy %p\n", clen, copy);
    last_clen = clen + 1;
    clen = 0;

    for (i = 0, argc--; i <= argc; i++) 
      {
        int needquote = 0;
        const char *s;

	/* Extra space after `in' intentional.  */
        syscall_printf ("argv[%d] in  `%s'\n", i, argv[i]);

	if (!argv[i][0])
	  needquote = 1;

        for (s = argv[i]; *s; s++) 
	  if (*s == ' ' || *s == '\t' || *s == '"') 
	    needquote = 1;

        if (needquote) 
	  copy[clen++] = '"';

        for (s = argv[i]; *s; s++) 
          {
            if (*s=='"')
	      copy[clen++] = '"';
            copy[clen++] = *s;
          }

        if (needquote)  
	  copy[clen++] = '"'; 
        copy[clen++] = (i == argc) ? '\0' : ' ';
        syscall_printf ("argv[%d] out `%s'\n", i, argv[i]);
      }
    if (clen > last_clen)
      system_printf ("spawn_guts: Hey! clen %d, last_clen %d\n", clen, last_clen);
  }

  /* And dup all the things we want to copy across */
  /* FIXME: This doesn't dup anything.  What it does do is close files
     with close-on-exec set.  That doesn't seem right though, what if the
     exec fails?  */
  if (mode == _P_OVERLAY) /* Real exec */
    myself->init_from_exec ();

  /* We have to translate PATH, etc. back so a dos image can grok them.  */

check_again:

  char real_path[MAX_PATH];
  const char *saved_prog_arg = prog_arg;

  if (perhaps_suffix (prog_arg, real_path, 1) == NULL)
    {
      set_errno (ENOENT);
      return -1;
    }

  /* Check if it's a script.  */

  SECURITY_ATTRIBUTES sa;  
  sa.nLength = sizeof (sa);
  sa.lpSecurityDescriptor = 0;
  sa.bInheritHandle = FALSE;

  HANDLE hnd = CreateFileA (real_path, 
			    GENERIC_READ,
			    FILE_SHARE_READ | FILE_SHARE_WRITE,
			    &sa,
			    OPEN_EXISTING,
			    FILE_ATTRIBUTE_NORMAL,
			    0);
  if (hnd == INVALID_HANDLE_VALUE)
    {
      __seterrno ();
      return -1;
    }

  DWORD done;
  char magic[2];

  char buf[2 * MAX_PATH + 1];
  buf[0] = buf[1] = buf[2] = buf[sizeof(buf) - 1] = '\0';
  if (! ReadFile (hnd, buf, sizeof (buf) - 1, &done, 0))
    {
      CloseHandle (hnd);
      __seterrno ();
      return -1;
    }

  CloseHandle (hnd);

  if (buf[0] != 'M' || buf[1] != 'Z')
    {
      debug_printf ("%s is a script\n", prog_arg);

      char *ptr, *pgm, *arg1;

      if (buf[0] != '#' || buf[1] != '!')
        {
          strcpy (buf, "sh");         /* shell script without magic */
	  pgm = buf;
	  ptr = arg1 = buf + 2;
        }
      else
	{
	  pgm = buf + 2;
	  pgm += strspn(pgm, " \t");
	  for (ptr = pgm, arg1 = NULL;
	       *ptr && *ptr != '\r' && *ptr != '\n';
	       ptr++)
	    if (!arg1 && (*ptr == ' ' || *ptr == '\t'))
	      {
		*ptr = '\0';
		do
		  arg1 = ++ptr;
		while (*ptr && (*ptr == ' ' || *ptr == '\t'));
		ptr--;
	      }

	    
	  *ptr = '\0';
	  if (arg1 == NULL)
	    arg1 = ptr;
	}

      prog_arg = (char *) alloca (MAX_PATH);
      /* pointers:
       * pgm	interpreter name
       * arg1	optional string
       * ptr	end of string
       */ 
      find_exec (pgm, (char *) prog_arg);
      char *f = (char *) alloca (strlen (copy) + strlen (prog_arg) +
                                strlen (real_path) + (ptr - arg1) + 7);
      strcpy (f, prog_arg);
      if (ptr == arg1)
	strcat (f, " ");
      else
        {
          strcat (f, " \"");
          strcat (f, arg1);
	  strcat (f, "\" ");
        }

      /* If script had absolute path, add it to script name now!
       * This is necessary if script has been found via PATH.
       * For example, /usr/local/bin/tkman started as "tkman":
       * #!/usr/local/bin/wish -f
       * ...
       * We should run /usr/local/bin/wish -f /usr/local/bin/tkman,
       * but not /usr/local/bin/wish -f tkman!
       * We don't modify anything, if script has qulified path.
       */
      if (saved_prog_arg[0] == '/' && copy[0] != '/')
        {
          debug_printf ("getting path of %s\n", saved_prog_arg);
          split_path (saved_prog_arg, strchr(f, '\0'), buf);
          debug_printf ("path is %s\n", ptr);
          strcat (f, "/");
        }
      strcat (f, copy);
      copy = f;

      debug_printf ("prog_arg is %s\n", prog_arg);
      debug_printf ("copy is now %s\n", copy);
      goto check_again;
    }

  PROCESS_INFORMATION pi = {0};

  STARTUPINFO si = {0};
  si.lpReserved = NULL;
  si.lpDesktop = NULL;
  si.dwFlags = STARTF_USESTDHANDLES;
  si.hStdInput = handle (0, 0); /* Get input handle */
  si.hStdOutput = handle (1, 1); /* Get output handle */
  si.hStdError = handle (2, 1); /* Get output handle */
  si.cb = sizeof (si);

  /* Pass fd table to a child */

  int len = myself->hmap.linearize_fd_array (0, 0);
  if (len == -1)
    {
      system_printf ("create_shared_fd_table: FATAL error in linearize_fd_array\n");
      return -1;
    }
  int titlelen = 1 + (old_title && mode == _P_OVERLAY ? strlen (old_title) : 0);
  si.cbReserved2 = len + titlelen + sizeof(int);
  si.lpReserved2 = (unsigned char *) alloca (si.cbReserved2);
  
  memset (si.lpReserved2, 0, sizeof(int));	// Fool microsoft startup
  LPBYTE resrv = si.lpReserved2 + sizeof(int);
  if (myself->hmap.linearize_fd_array (resrv, len) < 0)
    {
      system_printf ("create_shared_fd_table : FATAL error in second linearize_fd_array\n");
      return -1;
    }

  if (titlelen > 1)
    strcpy ((char *) resrv + len, old_title);
  else
    resrv[len] = '\0';

  /* We print the translated program and arguments here so the user can see
     what was done to it.  */
  syscall_printf ("spawn_guts (%s, %s)\n", real_path, copy);

  int flags = CREATE_SUSPENDED | GetPriorityClass (GetCurrentProcess ());

  if (mode == _P_DETACH)
    flags |= DETACHED_PROCESS;
  else
    {
      /* If we don't have a console, then don't create a console for
	 the child either.  */
      HANDLE console_handle = CreateFileA ("CONOUT$", GENERIC_WRITE,
					   FILE_SHARE_WRITE, NULL,
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL, NULL);
      if (console_handle != INVALID_HANDLE_VALUE
	  && console_handle != 0)
	CloseHandle (console_handle);
      else
	flags |= DETACHED_PROCESS;
    }

  HANDLE spr;
  if (mode == _P_OVERLAY)
    {
      sa.bInheritHandle = TRUE;
      sa.lpSecurityDescriptor = get_null_sd ();
      spr = myself->subproc_ready = CreateEvent(&sa, TRUE, FALSE, NULL);
    }

  /* Build windows style environment list */
  char *envblock = winenv (envp);

  if (hToken)
    {
      /* allow the child to interact with our window station/desktop */
      HANDLE hwst, hdsk;
      SECURITY_INFORMATION dsi = DACL_SECURITY_INFORMATION;
      DWORD n;
      char wstname[1024];
      char dskname[1024];

      hwst = GetProcessWindowStation();
      SetUserObjectSecurity(hwst, &dsi, get_null_sd ());
      GetUserObjectInformation(hwst, UOI_NAME, wstname, 1024, &n);
      hdsk = GetThreadDesktop(GetCurrentThreadId());
      SetUserObjectSecurity(hdsk, &dsi, get_null_sd ());
      GetUserObjectInformation(hdsk, UOI_NAME, dskname, 1024, &n);
      strcat (wstname, "\\");
      strcat (wstname, dskname);
      si.lpDesktop = wstname;
      /* force the new process to reread /etc/passwd and /etc/group */
      myself->uid = USHRT_MAX;
      rc = CreateProcessAsUser (hToken,
		       real_path,	/* image name - with full path */
		       copy,	/* what was passed to exec */
		       0,	/* process security attrs */
		       0,	/* thread security attrs */
		       TRUE,	/* inherit handles from parent */
		       flags,
		       envblock,/* environment */
		       0,	/* use current drive/directory */
		       &si,
		       &pi);
    }
  else
    rc = CreateProcessA (real_path,	/* image name - with full path */
		       copy,	/* what was passed to exec */
		       0,	/* process security attrs */
		       0,	/* thread security attrs */
		       TRUE,	/* inherit handles from parent */
		       flags,
		       envblock,/* environment */
		       0,	/* use current drive/directory */
		       &si,
		       &pi);

  free (envblock);

  /* Set errno now so that debugging messages from it appear before our
     final debugging message [this is a general rule for debugging
     messages].  */
  if (!rc)
    __seterrno ();

  /* We print the original program name here so the user can see that too.  */
  syscall_printf ("%d = spawn_guts (%s, %s)\n",
		  rc ? pi.dwProcessId : (unsigned int) -1,
		  prog_arg, copy);

  if (!rc)
    {
      CloseHandle (spr);
      myself->subproc_ready = NULL;
      return -1;
    }

  if (mode == _P_OVERLAY)
    {
      hExeced = pi.hProcess;
      /* Set up child's signal handlers */
      for (int i = 0; i < NSIG; i++)
        if (myself->sigs[i].sa_handler != SIG_IGN)
          {
            myself->sigs[i].sa_handler = SIG_DFL;
            myself->sigs[i].sa_mask = 0;
          }

      if (number_of_sockets)
        myself->process_state |= PID_SOCKETS_USED;
      else
        myself->process_state &= ~PID_SOCKETS_USED;

      close_all_files ();
      myself->process_state |= PID_EXECED;
      myself->dwSpawnedProcessId = pi.dwProcessId;
      strcpy (myself->progname, real_path);
      proc_terminate ();
    }
  else
    {
      pinfo *child = procinfo(pid);
      child->dwProcessId = pi.dwProcessId;
      child->hProcess = pi.hProcess;
      child->process_state |= PID_INITIALIZING;
      proc_register (child);
      /* Set up child's signal handlers */
      for (int i = 0; i < NSIG; i++)
        if (myself->sigs[i].sa_handler != SIG_IGN)
          {
            child->sigs[i].sa_handler = SIG_DFL;
            child->sigs[i].sa_mask = 0;
          }
        else
          child->sigs[i].sa_handler = SIG_DFL;

      if (number_of_sockets)
        child->process_state |= PID_SOCKETS_USED;
      child->dwSpawnedProcessId = pi.dwProcessId;
      sigproc_printf ("spawned windows pid %d\n", pi.dwProcessId);
    }

  /* Start the child running */
  ResumeThread (pi.hThread);
  CloseHandle (pi.hThread);

  if (hToken)
    CloseHandle (hToken);

  DWORD res;

  if (mode == _P_OVERLAY)
    {
      BOOL exited;
      HANDLE waitbuf[3] = {pi.hProcess, signal_arrived, spr};
      int nwait = 3;

      SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_HIGHEST);
      res = 0;
      DWORD timeout = INFINITE;
      exec_exit = 1;
      exited = FALSE;
  waitfor:
      switch (WaitForMultipleObjects (nwait, waitbuf, FALSE, timeout))
	{
	case WAIT_TIMEOUT:
	  syscall_printf ("WFMO timed out after signal\n");
	  if (WaitForSingleObject (pi.hProcess, 0) != WAIT_OBJECT_0)
	    {
	      sigproc_printf ("subprocess still alive after signal\n");
	      res = exec_exit;
	    }
	  else
	    {
	      sigproc_printf ("subprocess exited after signal\n");
	case WAIT_OBJECT_0:
	      sigproc_printf ("subprocess exited\n");
	      if (!GetExitCodeProcess (pi.hProcess, &res))
		res = exec_exit;
	      exited = TRUE;
	     }
	  if (nwait > 2 && WaitForSingleObject (spr, 1) == WAIT_OBJECT_0)
	    res |= EXIT_REPARENTING;
	  else if (!(res & EXIT_REPARENTING))
	    {
	      (void) myself->hmap.de_linearize_fd_array (resrv);
	      close_all_files ();
	    }
	  break;
	case WAIT_OBJECT_0 + 1:
	  ResetEvent (signal_arrived);
	  sigproc_printf ("signal arrived\n");
	  timeout = 10;
	  goto waitfor;
	case WAIT_OBJECT_0 + 2:
	  res = EXIT_REPARENTING;
	  CloseHandle (myself->subproc_ready);
	  if (!myself->parent_alive)
	    {
	      nwait = 2;
	      goto waitfor;
	    }
	  break;
	case WAIT_FAILED:
	  system_printf ("spawn_guts wait failed: handle = %x, pid =%d, winpid = %d\n",
			 pi.hProcess, myself->pid, myself->dwProcessId);
	  set_errno (ECHILD);
	  return -1;
	}

      CloseHandle (spr);

      sigproc_printf ("res = %x\n", res);

      if (res & EXIT_REPARENTING)
	{
	  /* Try to reparent child process.
	   * Make handles to child available to parent process and exit with
	   * EXIT_REPARENTING status. Wait() syscall in parent will then wait
	   * for newly created child.
	   */
	  lock_pinfo_for_update (INFINITE);
	  if (alive_parent (myself))
            {
	      pinfo  *parent = procinfo (myself->ppid);
	      sigproc_printf ("parent = %x\n", parent);
	      HANDLE hP = OpenProcess (PROCESS_ALL_ACCESS, 0,
				       parent->dwProcessId);
              sigproc_printf ("parent's handle = %d\n", hP);
	      res = 0;
	      if (hP)
                {
	          res = DuplicateHandle (GetCurrentProcess (), pi.hProcess,
					hP, &myself->hProcess, 0, FALSE,
					DUPLICATE_SAME_ACCESS);
                  sigproc_printf ("Dup hP %d\n", res);
		}
	      if (!res)
		{
		  system_printf ("Reparent failed\n");
		  system_printf ("my dwProcessId = %d, myself->dwProcessId = %d\n", GetCurrentProcessId(), myself->dwProcessId);
		  system_printf ("myself->process_state %x\n", myself->process_state);
		  system_printf ("myself->hProcess %x\n", myself->hProcess);
		}
	      unlock_pinfo ();
	      res = EXIT_REPARENTING;
	      CloseHandle (hExeced);
	      hExeced = NULL;
	    }
        }
      else if (exited)
	{
	  CloseHandle (hExeced);
	  hExeced = NULL; // stop do_exit from attempting to terminate subproc
	}

      do_exit (res | EXIT_NOCLOSEALL);
    }

  if (mode == _P_WAIT)
    {
      waitpid (pid, (int *) &res, 0);
    }
  else if (mode == _P_DETACH)
    {
      /* Lose all memory of this child. */
      res = 0;
    }
  else if ((mode == _P_NOWAIT) || (mode == _P_NOWAITO))
    {
      res = pid;
    }

  return (int) res;
}

extern "C"
int
cwait (int *result, int pid, int)
{
  return waitpid (pid, result, 0);
}

/*
 * Helper function for spawn runtime calls.
 * Doesn't search the path.
 */

int
_spawnve (int mode, const char *path, const char *const *argv,
						const char *const *envp)
{
  pinfo *child;
  int ret;

  syscall_printf ("_spawnve (%s, %s, %x)\n", path, argv[0], envp);

  switch (mode)
    {
      case _P_OVERLAY:
        /* We do not pass _P_SEARCH_PATH here. execve doesn't search PATH.*/
        /* Just act as an exec if _P_OVERLAY set. */
        spawn_guts (NULL, path, argv, envp, myself->pid, mode);
        /* Errno should be set by spawn_guts.  */
        ret = -1;
        break;
      case _P_NOWAIT:
      case _P_NOWAITO:
      case _P_WAIT:
      case _P_DETACH:
        lock_pinfo_for_update (INFINITE);
        child = s->p.allocate_pid ();
        if (!child)
          {
            set_errno (EAGAIN);
            syscall_printf ("-1 = spawnve (), process table full\n");
            unlock_pinfo ();
            return -1;
          }
        strcpy (child->progname, path);
        child->ppid = myself->pid;
        child->uid = myself->uid;
        child->gid = myself->gid;
        child->pgid = myself->pgid;
        child->sid = myself->sid;
        child->ctty = myself->ctty;
        child->umask = myself->umask;
	child->process_state |= PID_INITIALIZING;
        unlock_pinfo ();
	subproc_init ();
        ret = spawn_guts (NULL, path, argv, envp, child->pid, mode);
        if (ret == -1)
          child->process_state = PID_NOT_IN_USE;
        break;
      default:
        set_errno (EINVAL);
        ret = -1;
        break;
    }
  return ret;
}

/*
 * spawn functions as implemented in the MS runtime library.
 * Most of these based on (and copied from) newlib/libc/posix/execXX.c
 */

extern "C"
int
spawnl (int mode, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
      argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  va_end (args);

  return _spawnve (mode, path, (char * const  *) argv, *u->envptr);
}

extern "C"
int
spawnle (int mode, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char * const *envp;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
    argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  envp = va_arg (args, const char * const *);
  va_end (args);

  return _spawnve(mode, path, (char * const *) argv, (char * const *) envp);
}

extern "C"
int
spawnlp (int mode, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
      argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  va_end (args);

  return spawnvpe (mode, path, (char * const *) argv, *u->envptr);
}

extern "C"
int
spawnlpe (int mode, const char *path, const char *arg0, ...)
{
  int i;
  va_list args;
  const char * const *envp;
  const char *argv[256];

  va_start (args, arg0);
  argv[0] = arg0;
  i = 1;

  do
    argv[i] = va_arg (args, const char *);
  while (argv[i++] != NULL);

  envp = va_arg (args, const char * const *);
  va_end (args);

  return spawnvpe (mode, path, (char * const *) argv, envp);
}

extern "C"
int
spawnv (int mode, const char *path, const char * const *argv)
{
  return _spawnve (mode, path, argv, *u->envptr);
}

extern "C"
int
spawnve (int mode, const char *path, char * const *argv, const char * const *envp)
{
  return _spawnve (mode, path, argv, envp);
}

extern "C"
int
spawnvp (int mode, const char *path, const char * const *argv)
{
  return spawnvpe (mode, path, argv, *u->envptr);
}

static NO_COPY char path_delim;
#define PATH_DELIM path_delim

/*
 * Copy string, until c or <nul> is encountered.
 * NUL-terminate the destination string (s1).
 */

static char *
strccpy (char *s1, char *s2, char c)
{
  char *dest = s1;

  while (*s2 && *s2 != c)
    *s1++ = *s2++;
  *s1 = 0;

  return dest;
}

extern "C"
int
spawnvpe (int mode, const char *file, const char * const *argv, const char * const *envp)
{
  char *path = getenv ("PATH");
  char buf[MAXNAMLEN];
  int ret;

  /* If $PATH doesn't exist, just pass FILE on unchanged.  */
  if (!path)
    return _spawnve (mode, file, argv, envp);

  /* If FILE contains a directory, don't search $PATH.  */
  if (strchr (file, '/') || strchr (file, '\\'))
    return _spawnve (mode, file, argv, envp);

  /* If a drive letter is passed, the path is still an absolute one.
     Technically this isn't true, but cygwin32 is currently defined so
     that it is.  */
  if ((isalpha (file[0]) && file[1] == ':') || file[0] == '\\')
    return _spawnve (mode, file, argv, envp);

  path_delim = posix_path_list_p (path) ? ':' : ';';

  while (*path)
    {
      strccpy (buf, path, PATH_DELIM);
      /* An empty entry means the current directory.  */
      if (*buf != 0)
	strcat (buf, "/");
      strcat (buf, file);
      ret = _spawnve (mode, buf, argv, envp);
      if (ret == -1 && get_errno() != ENOENT)
	return -1;
      if(ret != -1)
	return ret;
      while (*path && *path != PATH_DELIM)
	path++;
      if (*path == PATH_DELIM)
	path++;			/* skip over delim */
    }

  return -1;
}
