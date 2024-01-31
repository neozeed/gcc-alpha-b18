/* fork.cc

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include "winsup.h"
#include "dll_init.h"

extern "C" struct _reent reent_data;



/* Timeout to wait for child to start, parent to init child, etc.  */
/* FIXME: Once things stabilize, bump up to a few minutes.  */
#define FORK_WAIT_TIMEOUT (120 * 1000)     /* 120 seconds */

/* Error return code from WaitForSingleObject.  */
#define WAIT_ERROR_RC 0xffffffff

#define parent_subproc_ready	myself->subproc_ready
#define parent_forker_finished	myself->forker_finished


extern char _data_start__;
extern char _data_end__;
extern char _bss_start__;
extern char _bss_end__;
#define dll_data_start &_data_start__
#define dll_data_end &_data_end__
#define dll_bss_start &_bss_start__
#define dll_bss_end &_bss_end__

#ifdef __alpha
extern "C" 
{
 int getsp();
 int GetpeOffset(char *module,int *bs,int *be,
		int *ds,int *de,int *ls,int *le);
}
#endif

/* Initialize the fork mechanism.  */

static NO_COPY SECURITY_ATTRIBUTES sa;

void
fork_init ()
{
  sa.nLength = sizeof (sa);
  sa.lpSecurityDescriptor = get_null_sd ();
  sa.bInheritHandle = 1;
}

#if 0
void
print_checksum (int idx, register void *low, register void *high)
{
  int pi;
  register  int sum = 0;
  small_printf ("CK %d %x %x ", idx, low, high);

  for (int *pi = (int *)low; pi < (int *)high; pi++)
    {
      sum += *pi;
    }
  small_printf ("%x\n", sum);
}
#endif

/* Copy memory from parent to child.
   The result is a boolean indicating success.  */

static int
fork_copy (HANDLE child, void *low, void *high, int)
{
  DWORD done;
  int res;

  debug_printf ("child handle %d, low %p, high %p\n",
		child, low, high);

  int lump = 1024 * 64;
  for (char *p = (char *) low; p < (char *) high; p += lump)
    {
      DWORD todo = MIN ((char *)high - p, lump);

      res = WriteProcessMemory (child, p, p, todo, &done);
      if (!res || todo != done)
	{
	  if (!res)
	    __seterrno ();
	  /* This happens when it shouldn't so there's a bug in our fork
	     implementation somewhere.  Print a message on the console to
	     call people's attention to the failure until we get it
	     straightened out.  */
	  small_printf ("failed, %p..%p, res is %d, done is %d\n",
			low, high, res, done);
	  /* Call debug_printf as well to make sure message gets in log
	     file if there is one.  */
	  debug_printf ("failed\n");
	  return 0;
	}
    }

#if 0
  print_checksum (idx, low, high);
#endif
  debug_printf ("done\n");
  return 1;
}

static void *
stack_dummy (int here)
{
  return &here;
}

/* Main guts of fork implementation.
   The result is the standard result of fork.  */
static int
cygwin_fork_helper1 (void *proc_data_start, void *proc_data_end,
		     void *proc_bss_start, void *proc_bss_end)
{
  int res;
  DWORD rc;
  sigset_t oldmask, forkmask;
  void *stack_here;
  int x;
  hinfo *child_hinfo = 0;
  char **load_dll = 0;



  /* Calculate how much of stack to copy to child */
  stack_here = stack_dummy (0);

  sigfillset (&forkmask);

  if (ISSTATE(myself, PID_SPLIT_HEAP))
    {
      small_printf ("The heap has been split, CYGWIN can't fork this process.\n");
      small_printf ("Increase the heap_chunk_size in the registry and try again.\n");
      set_errno (ENOMEM);
      syscall_printf ("-1 = fork (), split heap\n");
      return -1;
    }

  /* Don't start the fork until we have the lock.  */
  rc = lock_pinfo_for_update (FORK_WAIT_TIMEOUT);
  switch (rc)
    {
    case WAIT_ERROR_RC:
      small_printf ("fork parent: WaitForSingleObject (mutex) failed, win32 error %d\n",
		    GetLastError ());
      set_errno (EAGAIN);
      syscall_printf ("-1 = fork (), wait failed\n");
      return -1;
    case WAIT_TIMEOUT:
      small_printf ("fork parent: WaitForSingleObject (mutex) timed out\n");
      set_errno (EAGAIN);
      syscall_printf ("-1 = fork (), wait timed out\n");
      return -1;
    default:
      debug_printf ("%d = WaitForSingleObject (...)\n", rc);
      break;
    }

  pinfo *child = s->p.allocate_pid ();

  if (!child)
    {
      set_errno (EAGAIN);
      syscall_printf ("-1 = fork (), process table full\n");
      unlock_pinfo ();
      return -1;
    }

  /* Block all signals while in a fork */
  sigprocmask (SIG_SETMASK, &forkmask, &oldmask);

  /*
   * We need to save this allocated pointer as the child
   * will be changing it, plus we need to delete [] it later.
   */
  child_hinfo = child->hmap.vec;

  /* This will help some of the confusion.  */
  fflush (stdout);

  debug_printf ("parent pid is %d, child pid is %d\n",
		myself->pid, child->pid);

  HANDLE subproc_ready = CreateEvent (&sa, TRUE, FALSE, NULL);
  HANDLE forker_finished = CreateEvent (&sa, TRUE, FALSE, NULL);

  /* If we didn't obtain all the resources we need to fork, allow the program
     to continue, but record the fact that fork won't work.  */
  if (forker_finished == NULL || subproc_ready == NULL)
    {
      system_printf ("fork_init: unable to allocate fork() resources.\n");
      system_printf ("fork_init: fork() disabled.\n");
      return -1;
    }

  /* Initialize things that are done later in dll_crt0_1 that aren't done
     for the forkee.  */
  child->reent_save = reent_data;
  child->progname = myself->progname;

  /* Copy all the handles we need in the child.  */
  myself->hmap.dup_for_fork (&child->hmap);

  PROCESS_INFORMATION pi = {0};

  STARTUPINFO si = {0};
  si.cb = sizeof (STARTUPINFO);

  int c_flags = GetPriorityClass (GetCurrentProcess ()) | CREATE_SUSPENDED; 

  /* If we don't have a console, then don't create a console for the
     child either.  */
  HANDLE console_handle = CreateFileA ("CONOUT$", GENERIC_WRITE,
				       FILE_SHARE_WRITE, NULL,
				       OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
				       NULL);
  if (console_handle != INVALID_HANDLE_VALUE
      && console_handle != 0)
    CloseHandle (console_handle);
  else
    c_flags |= DETACHED_PROCESS;

  syscall_printf ("CreateProcessA (%s, %s,0,0,1,%x, 0,0,%p,%p)\n",
		  myself->progname, myself->progname, c_flags, &si, &pi);

  subproc_init ();
  rc = CreateProcessA (myself->progname, /* image to run */
		       myself->progname, /* what we send in arg0 */
		       0,		  /* process security attrs */
		       0,		  /* thread security attrs */
		       TRUE,		  /* inherit handles from parent */
		       c_flags,
		       NULL,		  /* environment filled in later */
		       0,		  /* use current drive/directory */
		       &si,
		       &pi);

  if (!rc)
    {
      __seterrno ();
      syscall_printf ("-1 = fork(), CreateProcessA failed\n");
      child->process_state = PID_NOT_IN_USE;
      delete [] child_hinfo;
      unlock_pinfo ();
      sigprocmask (SIG_SETMASK, &oldmask, NULL);
      CloseHandle(subproc_ready);
      CloseHandle(forker_finished);
      subproc_ready = forker_finished = NULL;
      return -1;
    }

  debug_printf ("about to call setjmp\n");
  x = setjmp (child->restore);
  debug_printf ("setjmp returned %d\n", x);

  if (x == 0)
    {
      /* Parent.  */

      dump_jmp_buf (child->restore);

#if 0 /* for debugging */
      s->base[0][0] = proc_data_start;
      s->base[0][1] = proc_data_end;
      s->base[1][0] = proc_bss_start;
      s->base[1][1] = proc_bss_end;
      s->base[2][0] = u->base;
      s->base[2][1] = u->ptr;
      s->base[3][0] = &x;
      s->base[3][1] = u->initial_sp; 
#endif 

      /* Tell the child it's being forked and its pid.
	 Remember, *u gets copied to the child's address space.  */
      u->forkee = child->pid;

      /* Fill in fields in the child's process table entry.  */
      child->ppid = myself->pid;
      child->hProcess = pi.hProcess;
      child->dwProcessId = pi.dwProcessId;
      child->uid = myself->uid;
      child->gid = myself->gid;
      child->pgid = myself->pgid;
      child->sid = myself->sid;
      child->ctty = myself->ctty;
      child->umask = myself->umask;
      child->sigs = myself->sigs;
      sigfillset (&(child->sig_mask));
      child->strace_mask = myself->strace_mask;
      child->forker_finished = forker_finished;
      child->subproc_ready = subproc_ready;
      if (number_of_sockets)
        child->process_state |= PID_SOCKETS_USED;
      child->process_state |= PID_INITIALIZING |
			      (myself->process_state & PID_USETTY);
      set_child_mmap_ptr (child);

      /* Initialize the child's .data and .bss.  */
      rc = fork_copy (pi.hProcess, (char *) proc_data_start,
		      (char *) proc_data_end, 0);
      if (rc)
	rc = fork_copy (pi.hProcess, (char *) proc_bss_start,
			(char *) proc_bss_end, 1);

      if (! rc)
	{
	  small_printf ("fork_helper: copy of data/bss failed\n");
	  set_errno (EAGAIN);
	  syscall_printf ("-1 = fork(), data/bss copy failed\n");
	  TerminateProcess (child->hProcess, 1);
	  u->forkee = 0;
          goto cleanup;
	}

      u->forkee = 0;

      /* Start thread, and wait for it to initialize itself.  */
      rc = ResumeThread (pi.hThread);
      if (rc != 1)
	{
	  /* Can't resume the thread.  Not sure why this would happen unless
	     there's a bug in the system.  Things seem to be working OK now
	     though, so flag this with EAGAIN, but print a message on the
	     console.  */
	  small_printf ("fork_helper: ResumeThread failed, rc = %d\n", rc);
	  set_errno (EAGAIN);
	  syscall_printf ("-1 = fork(), ResumeThread failed\n");
	  TerminateProcess (child->hProcess, 1);
          goto cleanup;
	}
      debug_printf ("child started\n");

      /* We don't want to wait forever here.  If there's a problem somewhere
	 it'll hang the entire system (since all forks are mutex'd).  If we
	 time out, set errno = EAGAIN and hope the app tries again.  */

      /* We also add child->hProcess to the wait. If the child fails
         to initialize (eg. because of a missing dll). Then this
         handle will become signalled. This stops a *looong* timeout wait.
      */
      HANDLE wait_array[2];
      wait_array[0] = child->hProcess;
      wait_array[1] = subproc_ready;
      rc = WaitForMultipleObjects (2, wait_array, FALSE, FORK_WAIT_TIMEOUT);

      if (rc == WAIT_ERROR_RC || rc == WAIT_TIMEOUT)
	{
	  if (rc == WAIT_ERROR_RC)
	    small_printf ("fork_helper: WaitForMultipleObjects failed, win32 error %d\n",
			  GetLastError ());
	  else
	    small_printf ("fork_helper: WaitForMultipleObjects timed out\n");
	  set_errno (EAGAIN);
	  syscall_printf ("-1 = fork(), WaitForMultipleObjects failed\n");
	  TerminateProcess (child->hProcess, 1);
          goto cleanup;
	}
      else if (rc == WAIT_OBJECT_0)
        {
          /* Child died. Clean up and exit. */
          DWORD errcode;
          GetExitCodeProcess (child->hProcess, &errcode);
	  /* Fix me.  This is not enough.  The fork should not be considered
	   * to have failed if the process was essentially killed by a signal.
	   */
	  if (errcode != STATUS_CONTROL_C_EXIT)
	    small_printf ("fork_helper: child died before initialization with win32 error %x\n", errcode);
	  set_errno (EAGAIN);
          syscall_printf ("Child died before subproc_ready signalled\n");
          goto cleanup;
	}
      SuspendThread (pi.hThread);
      ResetEvent( subproc_ready );

      /* Initialize cygwin.dll data/bss in a child process */
      /* Note: variables marked as NO_COPY will not be copied! */
#ifndef __alpha
      if (rc)
	rc = fork_copy (pi.hProcess, dll_bss_start, dll_bss_end, 10);
      if (rc)
	rc = fork_copy (pi.hProcess, dll_data_start, dll_data_end, 11);
#else

{
	int bs,be,ds,de,ls,le;	
	if (GetpeOffset("cygwinb19",&bs,&be,&ds,&de,&ls,&le)==-1) {
		small_printf("Unable to get peoffsets\n");
 		TerminateProcess (pi.hProcess, 1);
  		set_errno (EAGAIN);
		goto cleanup;
	}

	if (rc)
	  rc = fork_copy (pi.hProcess, (void *)ds,(void *)de, 10);
	if (rc) /* Ms linker groups .data & .bss sections together */
	  if (bs>0)
	    rc = fork_copy (pi.hProcess, (void *)bs, (void *)be, 11);

}


#endif

      /* check if forkee must reload dlopened dlls 	*/
      /* we have to:					*/
      /* 1) create a list with dlls names		*/
      /* 2) let the child reload these dlls		*/
      /* 3) write memory of these dlls in child		*/

      if (DllList::the().forkeeMustReloadDlls() &&
	 DllList::the().numberOfOpenedDlls() != 0)
      {
	load_dll = new char*[ DllList::the().numberOfOpenedDlls() + 1 ];
	int index = 0;
	DO_LOADED_DLL_NAMES(name)
	{
	  if (name)
	    load_dll[index++] = strdup (name);
	}
	DONE;
	load_dll[index] = 0;
	
	/* Now copy memory of load_dll (contains is in heap copied later) */
        debug_printf ("copying load=%x\n", load_dll);
	rc = fork_copy (child->hProcess, &load_dll,
                             (char *) &load_dll + sizeof (load_dll), 0);
	if (!rc)
	  small_printf ("copy of &load_dll failed\n");
      }
      
      /* Now fill in the stack and heap - this has to be done after 
	 the child is started.  */
      rc = fork_copy (child->hProcess, u->base, u->ptr, 2);
      if (rc)
#ifdef __alpha
	rc = fork_copy (child->hProcess, (void *)getsp(), u->initial_sp, 3);
#else
	rc = fork_copy (child->hProcess, stack_here, u->initial_sp, 3);
#endif
      if (! rc)
	{
	  small_printf ("fork_helper: copy of stack/heap failed\n");
	  set_errno (EAGAIN);
	  syscall_printf ("-1 = fork(), stack/heap copy failed\n");
	  TerminateProcess (child->hProcess, 1);
          goto cleanup;
	}


      /* Now fill data/bss of linked dll */
      DO_LINKED_DLL(p)
      {
        debug_printf ("copying data/bss of a linked dll\n");
	rc = fork_copy (child->hProcess, p->data_start, p->data_end, 0);
	if (rc)
	  rc = fork_copy (child->hProcess, p->bss_start, p->bss_end, 0);
	
	if (!rc)
	  small_printf ("copy of data/bss failed for a linked dll\n");
      }
      DONE;

      /* child reload dlls & then write their data and bss */
      if (load_dll != 0)
      {
	/* Start thread, and wait for it to reload dlls.  */
	SetEvent (forker_finished);
	ResetEvent (subproc_ready);
	rc = ResumeThread (pi.hThread);
	if (rc != 1)
	{
	  /* Can't resume the thread.  Not sure why this would happen unless */
	  /* there's a bug in the system.  Things seem to be working OK now  */
	  /* though, so flag this with EAGAIN, but print a message on the    */
	  /* console.  							     */
	  small_printf ("ResumeThread failed, rc = %d\n", rc);
	  set_errno (EAGAIN);
	  syscall_printf ("-1 = fork(), ResumeThread failed\n");
	  TerminateProcess (child->hProcess, 1);
          goto cleanup;
	}
	
	/* We don't want to wait forever here.If there's a problem somewhere */
	/* it'll hang the entire system (since all forks are mutex'd). If we */
	/* time out, set errno = EAGAIN and hope the app tries again.        */
	
	/* We also add child->hProcess to the wait. If the child fails       */
	/* to initialize (eg. because of a missing dll). Then this           */
	/* handle will become signalled. This stops a *looong* timeout wait. */

	HANDLE wait_array[2];
	wait_array[0] = child->hProcess;
	wait_array[1] = subproc_ready;
	rc = WaitForMultipleObjects (2, wait_array, FALSE, FORK_WAIT_TIMEOUT);
	if (rc == WAIT_ERROR_RC || rc == WAIT_TIMEOUT)
	{
	  if (rc == WAIT_ERROR_RC)
	    small_printf ("fork_helper: WaitForMultipleObjects failed, win32 error %d\n",
			  GetLastError ());
	  else
	    small_printf ("fork_helper: WaitForMultipleObjects timed out\n");
	  set_errno (EAGAIN);
	  syscall_printf ("-1 = fork(), WaitForMultipleObjects failed\n");
	  TerminateProcess (child->hProcess, 1);
          goto cleanup;
	}
	else if (rc == WAIT_OBJECT_0)
        {
          /* Child died. Clean up and exit. */
          DWORD errcode;
          GetExitCodeProcess (child->hProcess, &errcode);
	  small_printf ("fork_helper: child died before initialization with win32 error %d\n", errcode);
	  set_errno (EAGAIN);
          syscall_printf ("fork_helper: Child died before forkee_stopped signalled\n");
          goto cleanup;
	}
	SuspendThread (pi.hThread);
	ResetEvent( subproc_ready );

	/* release memory */
	rc = 0;
	char *ptr = load_dll[rc++];
	while (ptr)
	{
	  free (ptr);
	  ptr = load_dll[rc++];
	}
	delete []load_dll;
	load_dll = 0;

	/* then write memory of reloaded dlls */
	DO_LOADED_DLL(p)
	{
          debug_printf ("copying data/bss for a loaded dll\n");
	  rc = fork_copy (child->hProcess, p->data_start, p->data_end, 0 );
	  if (rc)
	    rc = fork_copy (child->hProcess, p->bss_start, p->bss_end, 0 );
	  
	  if (!rc)
	    small_printf ("fork_helper: copy of data/bss failed for a loaded dll\n");
	}
	DONE;
      }
      
      CloseHandle (subproc_ready);
      subproc_ready = NULL;
      /*
       * Now we have started the child we can get rid of the
       * childs fd table from our address space.
       */
      delete [] child_hinfo;
      /* Start the child up again.  */
      unlock_pinfo ();
      proc_register (child);

      SetEvent (forker_finished);
      CloseHandle (forker_finished);
      forker_finished = NULL;

      ResumeThread (pi.hThread);
      CloseHandle (pi.hThread);
      pi.hThread = NULL;

      res = child->pid;
    }
  else
    {
      /* We arrive here via a longjmp from "crt0".  */
      debug_printf ("child is running %d\n", x);
      (void) stack_dummy (0);		// Just to make sure

      myself->start_time = time (NULL);

      debug_printf ("fork child: self %p, pid %d, ppid %d\n",
		    myself, x, myself ? myself->ppid : -1);
      reent_data = myself->reent_save;

      /* Signals are blocked initially.  Eventually oldmask will be
	 filled in by the parent with the mask active at the time of
	 the fork.  This will be setup later. */

      /* With the current malloc implementation, we can not handle
         calls to malloc until after the parent has copied the malloc
         state over to us.  That means that although we are about to
         enable signal handling, we will fail if the signal handler
         calls malloc.  POSIX.1 does not permit a signal handler to
         call malloc, so we may be able to get away with this.  */

      /* Initialize signal/process handling */
      sigproc_init ();

      /* reset load_dll */
      load_dll = 0;

      ResetEvent( parent_forker_finished );
      /* Tell our parent we've started.  */
      if (!SetEvent (parent_subproc_ready))
	{
	  small_printf ("fork child: SetEvent failed, error %d\n",
			GetLastError ());
	  ExitProcess (1);
	}


      for (int i = 0; i < 2; i++)
	{
	  int werr;

	/* Wait for the parent to fill in our stack and heap.
	   Don't wait forever here.  If our parent dies we don't want to clog
	   the system.  If the wait fails, we really can't continue so exit.  */
	  int rc = WaitForSingleObject (parent_forker_finished,
					FORK_WAIT_TIMEOUT);
	  switch (rc)
	    {
	    case WAIT_TIMEOUT:
	      small_printf ("child: WFSO timed out\n");
	      ExitProcess (1);
	      break;
	    case WAIT_ERROR_RC:
	      werr = GetLastError ();
	      if (werr == ERROR_INVALID_HANDLE)
		  continue;	// Windows 95 sometimes returns this when
				  // WaitForSingleObject is resumed
	      debug_printf ("child: i = %d, WFSO failed, error %d\n",
			    i, werr);
	      ExitProcess (1);
	      break;
	    default:
	      i = 3;
	      break;
	    }
	}


      DllList::the().forkeeStartLoadedDlls();
      /* reload dlls if necessary */
      if (load_dll != 0)
      {
	rc = 0;
	char* ptr = load_dll[rc++];

	while (ptr)
	{
	  HANDLE res;
          debug_printf ("reloading library %s\n", ptr );
	  if ((res = LoadLibrary (ptr)) == 0)
	    small_printf ("fork child: can't reload library %s\n", ptr);
	  else
	    debug_printf ("library loaded %x\n", res);
	  free (ptr);
	  ptr = load_dll[rc++];
	}
	delete []load_dll;

	/* Tell our parent we've started.  */
	ResetEvent (parent_forker_finished);
	SetEvent (parent_subproc_ready);
	
	/* Wait for the parent to fill loaded dlls data */
	/* Don't wait forever here. If our parent dies we don't want to clog */
	/* the system.  If the wait fails, we really can't continue so exit. */
	int rc = WaitForSingleObject (parent_forker_finished, FORK_WAIT_TIMEOUT);
	switch (rc)
	{
	case WAIT_ERROR_RC:
	  small_printf ("fork child: WaitForSingleObject failed, win32 error %d\n",
			GetLastError ());
	  ExitProcess (1);
	case WAIT_TIMEOUT:
	  small_printf ("fork child: WaitForSingleObject timed out\n");
	  ExitProcess (1);
	default:
	  break;
	}
      }

      DllList::the().forkeeEndLoadedDlls ();

      (void) CloseHandle (parent_subproc_ready);
      (void) CloseHandle (parent_forker_finished);
      parent_forker_finished = parent_subproc_ready = NULL;

      /* connect to tty */
      tty_init ();

      if (recreate_mmaps_after_fork (myself->mmap_ptr))
        {
          small_printf ("fork child: recreate_mmaps_after_fork_failed\n");
          ExitProcess (1);
        }

      /* Initialize winsock if neccessary */
      if (ISSTATE(myself, PID_SOCKETS_USED))
        winsock_init ();

#if 0
      print_checksum (4, s->base[0][0], s->base[0][1]);
      print_checksum (5, s->base[1][0], s->base[1][1]);
      print_checksum (6, s->base[2][0], s->base[2][1]);
      print_checksum (7, s->base[3][0], s->base[3][1]);
#endif

      res = 0;
    }

  sigprocmask (SIG_SETMASK, &oldmask, NULL);
  syscall_printf ("%d = fork()\n", res);
  return res;

/* Common cleanup code for failure cases */
cleanup:
  /* Remember to de-allocate the fd table. */
  delete [] child_hinfo;
  child->process_state = PID_NOT_IN_USE;
  unlock_pinfo ();
  if (pi.hProcess)
    CloseHandle (pi.hProcess);
  if (pi.hThread)
    CloseHandle (pi.hThread);
  if (subproc_ready)
    CloseHandle (subproc_ready);
  if (forker_finished)
    CloseHandle (forker_finished);
  if (load_dll)
    {
      rc = 0;
      char* ptr = load_dll[rc++];
      while (ptr)
        {
          free (ptr);
          ptr = load_dll[rc++];
	}
      delete []load_dll;
    }
  forker_finished = subproc_ready = child->hProcess = NULL;
  sigprocmask (SIG_SETMASK, &oldmask, NULL);
  return -1;
}

/* This hack uses setjmp/longjmp to ensure that the parent's
   registers are all available in the child. We could use
   GetThreadContext/SetThreadContext instead, but I'm sure this
   is much faster. */

static int
__fork ()
{
  jmp_buf b;
  int r;

  if ((r = setjmp (b)) != 0)
    {
      r = r == -2 ? -1 : r == -1 ? 0 : r;
      return r;
    }

  r = cygwin_fork_helper1 (u->data_start, u->data_end,
				 u->bss_start, u->bss_end);

  /* Must convert result to get it through setjmp ok.  */
  longjmp (b, r == -1 ? -2 : r == 0 ? -1 : r);
}

/* Utility to dump a setjmp buf.  */

void
dump_jmp_buf (jmp_buf buf)
{
#ifdef __i386__
  debug_printf ("eax 0x%x, ebx 0x%x, ecx 0x%x, edx 0x%x\n",
		buf[0], buf[1], buf[2], buf[3]);
  debug_printf ("esi 0x%x, edi 0x%x, ebp 0x%x, esp 0x%x\n",
		buf[4], buf[5], buf[6], buf[7]);
  short *s = (short *) &buf[9];
  debug_printf ("es 0x%x, fs 0x%x, gs 0x%x, ss 0x%x\n",
		s[0], s[1], s[2], s[3]);
  debug_printf ("eip: 0x%x\n", buf[8]);
#endif
}

extern "C"
int
vfork () 
{
  return fork ();
}

extern "C"
int
fork ()
{
  /* FIXME: Was there a real reason for this?  */
  alloca (100);

  int r = __fork ();
  return r;
}
