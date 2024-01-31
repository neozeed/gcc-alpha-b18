/* syscalls.cc: syscalls

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <sys/stat.h>
#include <sys/vfs.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <sys/socket.h>

#include "winsup.h"

/* Table to map Windows error codes to Errno values.  */
/* FIXME: Doing things this way is a little slow.  It's trivial to change
   this into a big case statement if necessary.  Left as is for now. */

static const struct
  {
    int w;		 /* windows version of error */
    const char *s;	 /* text of windows version */
    int e;		 /* errno version of error */
  }
errmap[] =
{
  /* ??? Some of these choices are arbitrary.  */
  { ERROR_INVALID_FUNCTION, "ERROR_INVALID_FUNCTION", EBADRQC  },
  { ERROR_FILE_NOT_FOUND, "ERROR_FILE_NOT_FOUND", ENOENT  },
  { ERROR_PATH_NOT_FOUND, "ERROR_PATH_NOT_FOUND", ENOENT  },
  { ERROR_TOO_MANY_OPEN_FILES, "ERROR_TOO_MANY_OPEN_FILES", EMFILE  },
  { ERROR_ACCESS_DENIED, "ERROR_ACCESS_DENIED", EACCES  },
  { ERROR_INVALID_HANDLE, "ERROR_INVALID_HANDLE", EBADF  },
  { ERROR_NOT_ENOUGH_MEMORY, "ERROR_NOT_ENOUGH_MEMORY", ENOMEM  },
  { ERROR_INVALID_DATA, "ERROR_INVALID_DATA", EINVAL  },
  { ERROR_OUTOFMEMORY, "ERROR_OUTOFMEMORY", ENOMEM  },
  { ERROR_INVALID_DRIVE, "ERROR_INVALID_DRIVE", ENODEV  },
  { ERROR_NOT_SAME_DEVICE, "ERROR_NOT_SAME_DEVICE", EXDEV  },
  { ERROR_NO_MORE_FILES, "ERROR_NO_MORE_FILES", ENMFILE  },
  { ERROR_WRITE_PROTECT, "ERROR_WRITE_PROTECT", EROFS  },
  { ERROR_BAD_UNIT, "ERROR_BAD_UNIT", ENODEV  },
  { ERROR_SHARING_VIOLATION, "ERROR_SHARING_VIOLATION", EACCES  },
  { ERROR_LOCK_VIOLATION, "ERROR_LOCK_VIOLATION", EACCES  },
  { ERROR_SHARING_BUFFER_EXCEEDED, "ERROR_SHARING_BUFFER_EXCEEDED", ENOLCK  },
  { ERROR_HANDLE_EOF, "ERROR_HANDLE_EOF", ENODATA  },
  { ERROR_HANDLE_DISK_FULL, "ERROR_HANDLE_DISK_FULL", ENOSPC  },
  { ERROR_NOT_SUPPORTED, "ERROR_NOT_SUPPORTED", ENOSYS  },
  { ERROR_REM_NOT_LIST, "ERROR_REM_NOT_LIST", ENONET  },
  { ERROR_DUP_NAME, "ERROR_DUP_NAME", ENOTUNIQ  },
  { ERROR_BAD_NETPATH, "ERROR_BAD_NETPATH", ENXIO  },
  { ERROR_FILE_EXISTS, "ERROR_FILE_EXISTS", EEXIST  },
  { ERROR_CANNOT_MAKE, "ERROR_CANNOT_MAKE", EPERM  },
  { ERROR_INVALID_PARAMETER, "ERROR_INVALID_PARAMETER", EINVAL  },
  { ERROR_NO_PROC_SLOTS, "ERROR_NO_PROC_SLOTS", EAGAIN  },
  { ERROR_BROKEN_PIPE, "ERROR_BROKEN_PIPE", EPIPE  },
  { ERROR_OPEN_FAILED, "ERROR_OPEN_FAILED", EIO  },
  { ERROR_NO_MORE_SEARCH_HANDLES, "ERROR_NO_MORE_SEARCH_HANDLES", ENFILE  },
  { ERROR_CALL_NOT_IMPLEMENTED, "ERROR_CALL_NOT_IMPLEMENTED", ENOSYS  },
  { ERROR_INVALID_NAME, "ERROR_INVALID_NAME", ENOENT  },
  { ERROR_WAIT_NO_CHILDREN, "ERROR_WAIT_NO_CHILDREN", ECHILD  },
  { ERROR_CHILD_NOT_COMPLETE, "ERROR_CHILD_NOT_COMPLETE", EBUSY  },
  { ERROR_DIR_NOT_EMPTY, "ERROR_DIR_NOT_EMPTY", ENOTEMPTY  },
  { ERROR_SIGNAL_REFUSED, "ERROR_SIGNAL_REFUSED", EIO  },
  { ERROR_BAD_PATHNAME, "ERROR_BAD_PATHNAME", EINVAL  },
  { ERROR_SIGNAL_PENDING, "ERROR_SIGNAL_PENDING", EBUSY  },
  { ERROR_MAX_THRDS_REACHED, "ERROR_MAX_THRDS_REACHED", EAGAIN  },
  { ERROR_BUSY, "ERROR_BUSY", EBUSY  },
  { ERROR_ALREADY_EXISTS, "ERROR_ALREADY_EXISTS", EEXIST  },
  { ERROR_NO_SIGNAL_SENT, "ERROR_NO_SIGNAL_SENT", EIO  },
  { ERROR_FILENAME_EXCED_RANGE, "ERROR_FILENAME_EXCED_RANGE", EINVAL  },
  { ERROR_META_EXPANSION_TOO_LONG, "ERROR_META_EXPANSION_TOO_LONG", EINVAL  },
  { ERROR_INVALID_SIGNAL_NUMBER, "ERROR_INVALID_SIGNAL_NUMBER", EINVAL  },
  { ERROR_THREAD_1_INACTIVE, "ERROR_THREAD_1_INACTIVE", EINVAL  },
  { ERROR_BAD_PIPE, "ERROR_BAD_PIPE", EINVAL  },
  { ERROR_PIPE_BUSY, "ERROR_PIPE_BUSY", EBUSY  },
  { ERROR_NO_DATA, "ERROR_NO_DATA", EPIPE  },
  { ERROR_PIPE_NOT_CONNECTED, "ERROR_PIPE_NOT_CONNECTED", ECOMM  },
  { ERROR_MORE_DATA, "ERROR_MORE_DATA", EAGAIN  },
  { ERROR_DIRECTORY, "ERROR_DIRECTORY", EISDIR  },
  { ERROR_PIPE_CONNECTED, "ERROR_PIPE_CONNECTED", EBUSY  },
  { ERROR_PIPE_LISTENING, "ERROR_PIPE_LISTENING", ECOMM  },
  { ERROR_NO_TOKEN, "ERROR_NO_TOKEN", EINVAL  },
  { ERROR_PROCESS_ABORTED, "ERROR_PROCESS_ABORTED", EFAULT  },
  { ERROR_BAD_DEVICE, "ERROR_BAD_DEVICE", ENODEV  },
  { ERROR_BAD_USERNAME, "ERROR_BAD_USERNAME", EINVAL  },
  { ERROR_NOT_CONNECTED, "ERROR_NOT_CONNECTED", ENOLINK  },
  { ERROR_OPEN_FILES, "ERROR_OPEN_FILES", EAGAIN  },
  { ERROR_ACTIVE_CONNECTIONS, "ERROR_ACTIVE_CONNECTIONS", EAGAIN  },
  { ERROR_DEVICE_IN_USE, "ERROR_DEVICE_IN_USE", EAGAIN  },
  { ERROR_INVALID_AT_INTERRUPT_TIME, "ERROR_INVALID_AT_INTERRUPT_TIME", EINTR},
  { ERROR_IO_DEVICE, "ERROR_IO_DEVICE", EIO },
};

/* Queue a file for deletion when the next close () is done.  */
struct file_queue
{
  struct file_queue *next;
  /* The name is recorded in malloc space.  */
  char *name;
  /* Not currently used.  */
  int fd;
};

/* seterrno: standards? */
/* Set `errno' based on GetLastError (). */
extern "C"
void
seterrno (const char *file, int line)
{
  int i;
  int why = GetLastError ();

  why &= 0xff;

  for (i = 0; errmap[i].w != 0; ++i)
    if (why == errmap[i].w)
      break;

  if (errmap[i].w != 0)
    {
      if (strace() &((_STRACE_SYSCALL)|1))
	strace_printf ("%s:%d seterrno: %d (%s) -> %d\n", 
		      file, line,why, errmap[i].s, errmap[i].e);
      set_errno (errmap[i].e);
    }
  else
    {
      if (strace() &((_STRACE_SYSCALL)|1)) \
	strace_printf ("%s:%d seterrno: unknown error %d!!\n", file, line, why);
      set_errno (EACCES);
    }
}

/* Close all files and process any queued deletions.
   Lots of unix style applications will open a tmp file, unlink it,
   but never call close.  This function is called by _exit to
   ensure we don't leave any such files lying around.  */
extern "C"
void
close_all_files (void)
{
  for (int i = 0; i < getdtablesize(); i++)
    if (myself->hmap[i].is_open ())
      _close (i);

  s->delqueue.process_queue ();
}

/* Return whether the directory of a file is writable.  Return 1 if it
   is.  Otherwise, return 0, and set errno appropriately.  */

static int
writable_directory (const char *file)
{
  char *dir = strdup (file);
  if (dir == NULL)
    {
      set_errno (ENOMEM);
      return 0;
    }

  const char *usedir;
  char *slash = strrchr (dir, '\\');
  if (slash == NULL)
    usedir = ".";
  else
    {
      *slash = '\0';
      usedir = dir;
    }

  int acc = access (usedir, W_OK);

  free (dir);

  return acc == 0;
}

extern "C"
int
_unlink (const char *ourname)
{
  int res;

  path_conv win32_name (ourname, 0);
  
  if (win32_name.error)
    {
      set_errno (win32_name.error);
      res = -1;
      goto done;
    }

  syscall_printf ("_unlink (%s)\n", win32_name.get_win32 ());

  /* Windows won't check the directory mode, so we do that ourselves.  */
  if (! writable_directory (win32_name.get_win32 ()))
    {
      syscall_printf ("-1 = unlink (%s)\n", ourname);
      return -1;
    }

  if (!DeleteFileA (win32_name.get_win32 ()))
    {
      res = GetLastError ();

      /* if access denied, chmod to be writable in case it is not
	 and try again */
      /* FIXME!!! Should check whether ourname is directory or file
	 and only try again if permissions are not sufficient */
      if (res == ERROR_ACCESS_DENIED)
        {
	  /* chmod ourname to be writable here */
          res = chmod (ourname, 0777);

	  if (DeleteFileA (win32_name.get_win32 ()))
	    {
              res = GetLastError ();
	      syscall_printf ("%d = unlink (%s)\n", res, ourname);
	      return 0;
	    }

	  res = GetLastError ();
        }

      /* If we get ERROR_SHARING_VIOLATION, the file may still be open -
	 Windows NT doesn't support deleting a file while it's open.  */
      if (res == ERROR_SHARING_VIOLATION
	  || res == ERROR_ACCESS_DENIED)
	{
	  s->delqueue.queue_file (win32_name.get_win32 ());
	  res = 0;
	}
      else
	{
	  __seterrno ();
	  res = -1;
	}
    }
  else
    res = 0;

done:
  syscall_printf ("%d = unlink (%s)\n", res, ourname);
  return res;
}

extern "C"
pid_t 
_getpid ()
{
  return myself->pid;
}

/* getppid: POSIX 4.1.1.1 */
extern "C"
pid_t
getppid () 
{
  return myself->ppid;
}

/* setsid: POSIX 4.3.2.1 */
extern "C"
pid_t 
setsid (void)
{
  /* FIXME: for now */
  myself->ctty = -1;
  myself->sid = _getpid ();
  myself->pgid = _getpid ();
  return _getpid ();
}

extern "C"
ssize_t
_read (int fd, void *ptr, size_t len)
{
  int res = -1;

  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
    }
  else 
    {
      /* Could block, so let user know we at least got here.  */
      syscall_printf ("read (%d, 0x%x, %d)\n", fd, ptr, len);
      if (myself->hmap[fd].h->get_flags () & (O_NONBLOCK | O_NDELAY))
	{
	  /* Check for data existance */
	  fd_set fds;
	  struct timeval tv = {0, 0};

	  FD_ZERO (&fds);
	  FD_SET (fd, &fds);
	  if (cygwin32_select(fd+1, &fds, NULL, NULL, &tv) == 0)
	    {
	      syscall_printf ("nothing to read\n");
	      set_errno (EAGAIN);
	      return -1;
	    }
	}
      myself->process_state |= PID_TTYIN;
      res = myself->hmap[fd].h->read (ptr, len);
      myself->process_state &= ~PID_TTYIN;
      syscall_printf ("%d = read (%d, 0x%x, %d)\n", res, fd, ptr, len);
    }

  return (ssize_t)res;
}

extern "C"
ssize_t
_write (int fd, const void *ptr, size_t len)
{
  int res = -1;

  if (NOT_OPEN_FD(fd))
    {
      set_errno (EBADF);
      goto done;
    }

  /* Could block, so let user know we at least got here.  */
  if (fd == 1 || fd == 2)
    {
      paranoid_printf ("write (%d, 0x%x, %d)\n", fd, ptr, len);
    }
  else
    {
      syscall_printf  ("write (%d, 0x%x, %d)\n", fd, ptr, len);
    }

  myself->process_state |= PID_TTYOU;
  res = myself->hmap[fd].h->write (ptr, len);
  myself->process_state &= ~PID_TTYOU;

done:
  if (fd == 1 || fd == 2) 
    {
      paranoid_printf ("%d = write (%d, 0x%x, %d)\n", res, fd, ptr, len);
    }
  else 
    {
      syscall_printf ("%d = write (%d, 0x%x, %d)\n", res, fd, ptr, len);
    }

  return (ssize_t)res;
}

/*
 * FIXME - should really move this interface into fhandler, and implement
 * write in terms of it. There are devices in Win32 that could do this with
 * overlapped I/O much more efficiently - we should eventually use
 * these.
 */

extern "C"
ssize_t
writev (int fd, const struct iovec *iov, int iovcnt)
{
  int i;
  ssize_t len, total;
  char *base;

  if (iovcnt < 1 || iovcnt > IOV_MAX)
    {
      set_errno (EINVAL);
      return -1;
    }

  /* Ensure that the sum of the iov_len values is less than
     SSIZE_MAX (per spec), if so, we must fail with no output (per spec).
  */
  total = 0;
  for (i = 0; i < iovcnt; ++i)
    {
    total += iov[i].iov_len;
    if (total > SSIZE_MAX)
      {
      set_errno (EINVAL);
      return -1;
      }
    }
  /* Now write the data */
  for (i = 0, total = 0; i < iovcnt; i++, iov++)
    {
      len = iov->iov_len;
      base = iov->iov_base;
      while (len > 0)
	{
	  register int nbytes;
	  nbytes = write (fd, base, len);
	  if (nbytes < 0 && total == 0)
	    return -1;
	  if (nbytes <= 0)
	    return total;
	  len -= nbytes;
	  total += nbytes;
	  base += nbytes;
	}
    }
  return total;
}

/*
 * FIXME - should really move this interface into fhandler, and implement
 * read in terms of it. There are devices in Win32 that could do this with
 * overlapped I/O much more efficiently - we should eventually use
 * these.
 */

extern "C"
ssize_t
readv (int fd, const struct iovec *iov, int iovcnt)
{
  int i;
  ssize_t len, total;
  char *base;

  for (i = 0, total = 0; i < iovcnt; i++, iov++)
    {
      len = iov->iov_len;
      base = iov->iov_base;
      while (len > 0)
	{
	  register int nbytes;
	  nbytes = read (fd, base, len);
	  if (nbytes < 0 && total == 0)
	    return -1;
	  if (nbytes <= 0)
	    return total;
	  len -= nbytes;
	  total += nbytes;
	  base += nbytes;
	}
    }
  return total;
}

extern "C"
int
_open (const char *unix_path, int flags, mode_t mode)
{
  int fd;
  int res = -1;

  pinfo *p = myself;

  syscall_printf ("open (%s, 0x%x)\n", unix_path, flags);

  fd = p->hmap.find_unused_handle (0);
  
  if (fd < 0)
    {
      set_errno (ENMFILE);
      goto done;
    }

  p->hmap.build_fhandler (unix_path, fd, NULL);
  
  if (! p->hmap[fd].h->open (unix_path, flags, (mode & 0777) & ~myself->umask))
    {
      p->hmap.release (fd);
    }
  else
    res = fd;
  
done:
  syscall_printf ("%d = open (%s, 0x%x)\n", res, unix_path, flags);
  return res;
}

extern "C"
off_t
_lseek (int fd, off_t pos, int dir)
{
  off_t res;

  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
      res = -1;
    }
  else
    {
      res = myself->hmap[fd].h->lseek (pos, dir);
    }
  syscall_printf ("%d = lseek (%d, %d, %d)\n", res, fd, pos, dir);

  return res;
}

extern "C"
int
_close (int fd)
{
  int res;

  syscall_printf ("close (%d)\n", fd);
  
  if (NOT_OPEN_FD(fd))
    {
      debug_printf ("handle %d not open\n", fd);
      set_errno (EBADF);
      res = -1;
    }
  else
    {
      res = myself->hmap[fd].h->close ();
      myself->hmap.release (fd);
    }
  syscall_printf ("%d = close (%d)\n", res, fd);
  s->delqueue.process_queue ();

  return res;
}

extern "C"
int
isatty (int fd)
{
  int res;

  if (NOT_OPEN_FD (fd))
    {
      syscall_printf ("0 = isatty (%d)\n", fd);
      return 0;
    }
  
  res = myself->hmap[fd].h->is_tty ();
  syscall_printf ("%d = isatty (%d)\n", res, fd);
  return res;
}

/* Under NT, try to make a hard link using backup API.  If that
   fails or we are Win 95, just copy the file.  
   FIXME: This function requires some thought.
*/

extern "C"
int
_link (const char *a, const char *b)
{
  int res = -1;
  path_conv real_a (a, 0);

  if (real_a.error)
    {
      set_errno (real_a.error);
      syscall_printf ("-1 = link (%s, %s)\n", a, b);
      return -1;
    }

  path_conv real_b (b, 0);

  if (real_b.error)
    {
      set_errno (real_b.error);
      syscall_printf ("-1 = link (%s, %s)\n", a, b);
      return -1;
    }
  
  /* Try to make hard link first on Windows NT */
  if (get_os_type () == winNT)
    {
      HANDLE hFileSource;

      WIN32_STREAM_ID StreamId;
      DWORD dwBytesWritten;
      LPVOID lpContext;
      DWORD cbPathLen;
      DWORD StreamSize;
      WCHAR wbuf[MAX_PATH];
      char buf[MAX_PATH];

      BOOL bSuccess;

      hFileSource = CreateFile (
        real_a.get_win32 (),
        FILE_WRITE_ATTRIBUTES,
        FILE_SHARE_READ | FILE_SHARE_WRITE /*| FILE_SHARE_DELETE*/,
        NULL, // sa
        OPEN_EXISTING,
        0,
        NULL
        );

      if (hFileSource == INVALID_HANDLE_VALUE)
	{
	  syscall_printf ("cannot open source %d\n", GetLastError ());
	  goto docopy;
	}

      lpContext = NULL;
      conv_to_full_win32_path (real_b.get_win32 (), buf);
      OemToCharW (buf, wbuf);
      cbPathLen = (strlen (buf) + 1) * sizeof (WCHAR);

      StreamId.dwStreamId = BACKUP_LINK;
      StreamId.dwStreamAttributes = 0;
      StreamId.dwStreamNameSize = 0;
      StreamId.Size.HighPart = 0;
      StreamId.Size.LowPart = cbPathLen;

      StreamSize = sizeof (WIN32_STREAM_ID) - sizeof (WCHAR**) +
                                            StreamId.dwStreamNameSize;

      /* Write the WIN32_STREAM_ID */
      bSuccess = BackupWrite (
        hFileSource,
        (LPBYTE) &StreamId,  // buffer to write
        StreamSize,         // number of bytes to write
        &dwBytesWritten,
        FALSE,              // don't abort yet
        FALSE,              // don't process security
        &lpContext);

      if (bSuccess)
	{
          /* write the buffer containing the path */
	  /* FIXME: BackupWrite sometimes traps if linkname is invalid.
	     Need to handle. */
          bSuccess = BackupWrite (
                hFileSource,
                (LPBYTE) wbuf,   // buffer to write
                cbPathLen,          // number of bytes to write
                &dwBytesWritten,
                FALSE,              // don't abort yet
                FALSE,              // don't process security
                &lpContext
                );

	  if (!bSuccess)
	    syscall_printf ("cannot write linkname %d\n", GetLastError ());

          /* Free context */
          BackupWrite (
            hFileSource,
            NULL,               // buffer to write
            0,                  // number of bytes to write
            &dwBytesWritten,
            TRUE,               // abort
            FALSE,              // don't process security
            &lpContext
            );
        }
      else
	syscall_printf ("cannot write streamId %d\n", GetLastError ());

      CloseHandle (hFileSource);

      if (!bSuccess)
	goto docopy;

      res = 0;
      goto done;
    }
docopy:
  /* do this with a copy */
  if (CopyFileA (real_a.get_win32 (), real_b.get_win32 (), 1))
    res = 0;
  else
    __seterrno ();

done:  
  syscall_printf ("%d = link (%s, %s)\n", res, a, b);
  return res;
}

/* mkdir: POSIX 5.4.1.1 */
extern "C"
int
mkdir (const char *dir, mode_t mode)
{
  int res = -1;

  path_conv real_dir (dir, 0);
  
  if (real_dir.error)
    {
      set_errno (real_dir.error);
      goto done;
    }

  if (! writable_directory (real_dir.get_win32 ()))
    goto done;

  if (CreateDirectoryA (real_dir.get_win32 (), 0))
    res = 0;
  else
    __seterrno ();
  
done:
  syscall_printf ("%d = mkdir (%s, %d)\n", res, dir, mode);
  return res;
}

/* rmdir: POSIX 5.5.2.1 */
extern "C"
int
rmdir (const char *dir)
{
  int res = -1;

  path_conv real_dir (dir, 0);
  
  if (real_dir.error)
    {
      set_errno (real_dir.error);
      goto done;
    }

  if (RemoveDirectoryA (real_dir.get_win32 ()))
    res = 0;
  else
    __seterrno ();
  
done:
  syscall_printf ("%d = rmdir (%s)\n", res, dir);
  return res;
}

static BOOL
rel2abssd (PSECURITY_DESCRIPTOR psd_rel, PSECURITY_DESCRIPTOR psd_abs,
		DWORD abslen)
{
  static char dacl_buf[1024];
  static char sacl_buf[1024];
  static char ownr_buf[1024];
  static char grp_buf[1024];
  DWORD dacl_len = 1024;
  DWORD sacl_len = 1024;
  DWORD ownr_len = 1024;
  DWORD grp_len = 1024;

  BOOL res = MakeAbsoluteSD (psd_rel, psd_abs, &abslen, (PACL) dacl_buf, &dacl_len,
                   (PACL) sacl_buf, &sacl_len, (PSID) ownr_buf, &ownr_len,
                   (PSID) grp_buf, &grp_len);

  syscall_printf ("%d = rel2abssd (...);\n", res);
  return res;
}

static BOOL
set_process_privileges ()
{
  HANDLE hProcess = OpenProcess (PROCESS_ALL_ACCESS, TRUE,
					GetCurrentProcessId ());
  HANDLE hToken;
  LUID privilege;
  TOKEN_PRIVILEGES *new_priv;
    
  if (!OpenProcessToken (hProcess, TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
      CloseHandle (hProcess);
      return FALSE;
    }
    
  if (!LookupPrivilegeValue (NULL, SE_RESTORE_NAME, &privilege))
    {
      CloseHandle (hProcess);
      CloseHandle (hToken);
      return FALSE;
    }
    
  new_priv = (TOKEN_PRIVILEGES *) malloc (sizeof (TOKEN_PRIVILEGES) +
					2 * sizeof (LUID_AND_ATTRIBUTES));
  new_priv->PrivilegeCount = 2;
  new_priv->Privileges[0].Luid = privilege;
  new_priv->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  if (!LookupPrivilegeValue (NULL, SE_BACKUP_NAME, &privilege))
    {
      CloseHandle (hProcess);
      CloseHandle (hToken);
      return FALSE;
    }

  new_priv->Privileges[1].Luid = privilege;
  new_priv->Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;
    
  if (!AdjustTokenPrivileges (hToken, FALSE, new_priv, 0, NULL, NULL))
    {
      CloseHandle (hProcess);
      CloseHandle (hToken);
      free (new_priv);
      return FALSE;
    }
    
  free (new_priv);
  CloseHandle (hProcess);
  CloseHandle (hToken);

  syscall_printf ("TRUE = set_process_privileges ();\n");
  return TRUE;
}

/* chown: POSIX 5.6.5.1 */    
/*
 * chown() is only implemented for Windows NT.  Under other operating
 * systems, it is only a stub that always returns zero.
 *
 * Note: the SetFileSecurity API in NT can only set the current
 * user as file owner so we have to use the Backup API instead.
 */
extern "C"
int
chown (const char * name, uid_t uid, gid_t gid)
{
  if (get_os_type () == winNT)	// real chown only works on NT
    {
      char sid_name_buffer[1024];  // FIXME: do the buffs have to be this big?
      char sid_group_buffer[1024];
      DWORD sid_len;
      WIN32_STREAM_ID header;
      HANDLE hFile;
      DWORD bytes_read = 0;
      LPVOID context = NULL;
      PSID psid_name = (PSID) sid_name_buffer;
      PSID psid_group = (PSID) sid_group_buffer;
      char domain_name[100];
      DWORD domname_len;
      char username[UNLEN + 1];
      char groupname[UNLEN + 1];
      SID_NAME_USE acc_type;
      struct passwd user, *pw_ptr;
      struct group group, *gr_ptr ;

      /* converting user and group id to names */
      if ((pw_ptr = getpwuid (uid)) == NULL)
        {
	  /* We didn't find the user id in /etc/passwd.  See if it
             refers to us, for convenience when there is no
             /etc/passwd file.  */
	  char userbuf[UNLEN + 1];
	  DWORD ulen;

	  sid_len = 1024;
	  domname_len = 100;
	  ulen = UNLEN + 1;
	  if (GetUserName (userbuf, &ulen))
	    {
	      if (! LookupAccountName (NULL, username, psid_name, &sid_len,
				       domain_name, &domname_len, &acc_type))
		{
		  if (GetLastError () == ERROR_NONE_MAPPED)
		    {
		      /* There is no mapping from user names to
                         security identifiers, so there isn't much we
                         can do.  */
                      syscall_printf ("0 = chown (%s,...) (no mapping)\n",
				      name);
		      return 0;
		    }
		  __seterrno ();
		  return -1;
		}
	      if (uid == get_id_from_sid (psid_name))
		strcpy (username, userbuf);
	      else
		{
		  set_errno (EINVAL);
		  return -1;
		}
	    }
	  else
	    {
	      set_errno (EINVAL);
	      return -1;
	    }
        }

      strcpy (username, pw_ptr->pw_name);            
        
      if ((gr_ptr = getgrgid (gid)) == NULL)
        {
          set_errno (EINVAL);
          return -1;
        }

      strcpy (groupname, gr_ptr->gr_name);
            
      /* we need Win32 path names because of usage of Win32 API functions */
      path_conv win32_path (name);
        
      if (win32_path.error)
        {
          set_errno (win32_path.error);
          return -1;
        }
        
      /* open the file for read */
      hFile = CreateFile (win32_path.get_win32 (), GENERIC_READ, 
                           FILE_SHARE_READ | FILE_SHARE_WRITE,
                           NULL, OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
                           NULL);
                              
      if (hFile == INVALID_HANDLE_VALUE)
        {
          __seterrno ();
          return -1;
        }

      /* step through the backup streams and search for the security data */
      while (BackupRead (hFile, (LPBYTE) &header, sizeof (header) -
              sizeof (header.cStreamName), &bytes_read, FALSE, TRUE, &context))
        {
          if (header.dwStreamId == BACKUP_SECURITY_DATA)
            {
              DWORD datasize = header.Size.LowPart + header.dwStreamNameSize;
              char b[datasize + 100];  // add space for new information
              PSECURITY_DESCRIPTOR psd =
                         (PSECURITY_DESCRIPTOR) &b[header.dwStreamNameSize];
                
              if (!BackupRead (hFile, (LPBYTE) b, datasize, &bytes_read,
                       FALSE, TRUE, &context))
                {
                  __seterrno ();
                  BackupRead (hFile, NULL, 0, &bytes_read, TRUE, TRUE, &context);
                  CloseHandle (hFile);
                  return -1;
                }
            
              if (IsValidSecurityDescriptor (psd))
                {
                  /* data is valid security descriptor */
                    
                  char abs_buf[1024];
                  PSECURITY_DESCRIPTOR abs_psd = (PSECURITY_DESCRIPTOR) abs_buf;
                  DWORD bytes_written;
                   
                  /* terminate read process */
                  BackupRead (hFile, NULL, 0, &bytes_read, TRUE, TRUE, &context);
                  CloseHandle (hFile);
                   
                  /* get sid for the new user */
                  sid_len = 1024;
                  domname_len = 100;
                  if (!LookupAccountName (NULL, username, psid_name,
                            &sid_len, domain_name, &domname_len, &acc_type))
                    {
                      __seterrno ();
                      syscall_printf ("0 = chown (%s,...);\n", name);
                      return 0;
                    }
       
                  if (!IsValidSid (psid_name))
                    {
                      __seterrno ();
                      return -1;
                    }
                   
                  /* convert security descriptor to absolute format */
                  if (!rel2abssd (psd, abs_psd, 1024))
                    {
                      __seterrno ();
                      return -1;
                    }
                   
                  /* set new owner information */
                  if (!SetSecurityDescriptorOwner (abs_psd, psid_name, TRUE))
                    {
                        __seterrno ();
                        return -1;
                    }
                   
                  /* restore buffer size information */
                  sid_len = 1024;
                  domname_len = 100;
         
                  /* get sid for new group */
                  if (!LookupAccountName (NULL, groupname, psid_group,
                          &sid_len, domain_name, &domname_len, &acc_type))
                    {
                      __seterrno ();
                      return -1;
                    }
                   
                  /* set new group info */
                  if (!SetSecurityDescriptorGroup (abs_psd, psid_group, TRUE))
                    {
                      __seterrno ();
                      return -1;
                    }
                   
                  datasize = sizeof (b);
                    
                  /* convert security descriptor to self-relative format */
                  if (!MakeSelfRelativeSD (abs_psd, psd, &datasize))
                    {
                      __seterrno ();
                      return -1;
                    }
       
                  /* set new size of security descriptor */
                  header.Size.LowPart = GetSecurityDescriptorLength (psd);
                  header.dwStreamAttributes = STREAM_CONTAINS_SECURITY;
                  context = NULL;
                   
                  if (!set_process_privileges ())
                    {
                      set_errno (EACCES);
                      return -1;
                    }
                   
                  SECURITY_ATTRIBUTES sa;
                  sa.nLength = sizeof (sa);
                  sa.lpSecurityDescriptor = psd;
                  sa.bInheritHandle = TRUE;
                   
                  /* open the file again for write owner and dac */
                  hFile = CreateFile (win32_path.get_win32 (),
                             GENERIC_READ | GENERIC_WRITE |
                             WRITE_OWNER | WRITE_DAC,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             &sa,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
                             NULL);
                              
                  if (hFile == INVALID_HANDLE_VALUE)
                    {
                      __seterrno ();
                      return -1;
                    }
                    
                  context = NULL;
                  bytes_written = 0;
                    
                  /* write new security info header */
                  if (!BackupWrite (hFile, (LPBYTE) &header,
                           sizeof (WIN32_STREAM_ID) - sizeof (header.cStreamName),
                           &bytes_written, FALSE, TRUE, &context))
                    {
                      __seterrno ();
                      CloseHandle (hFile);
                      return -1;
                    }

                  /* write new security descriptor */
                  if (!BackupWrite (hFile, (LPBYTE) b,
                            header.Size.LowPart + header.dwStreamNameSize,
                            &bytes_written, FALSE, TRUE, &context))
                    {
                      __seterrno ();
                      BackupWrite (hFile, NULL, 0, &bytes_written, TRUE,
                                                          TRUE, &context);
                      CloseHandle (hFile);
                      return -1;
                    }
                    
                  /* terminate the restore process */
                  BackupWrite (hFile, NULL, 0, &bytes_written, TRUE,
                                                           TRUE, &context);
                  CloseHandle (hFile);
                  syscall_printf ("0 = chown (%s,...);\n", name);
                  return 0;
                }
              else
                {
                  /* security descriptor data is invalid,
                   * this should not happen
                   */
                     
                  CloseHandle (hFile);
                  set_errno (EINVAL);
                  return -1;
                }
            }
          else
            {
              DWORD low_seek = 0;
              DWORD high_seek = 0;

              if (!BackupSeek (hFile, header.Size.LowPart, header.Size.HighPart, 
                       &low_seek, &high_seek, &context))
                break;
            }
        }
        
        /* no security data found - all remains unchanged */
        CloseHandle (hFile);
        syscall_printf ("0 = chown (%s,...);\n", name);
        return 0;
    }

  /* chown() returns zero (and does nothing) under other operating systems
     such as Windows 95 */

  syscall_printf ("0 = chown (%s,...);\n", name);
  return 0;
}

/* umask: POSIX 5.3.3.1 */
extern "C"
mode_t 
umask (mode_t mask)
{
  mode_t oldmask;

  oldmask = myself->umask;
  myself->umask = mask & 0777;
  return oldmask;
}

/* chmod: POSIX 5.6.4.1 */
extern "C"
int
chmod (const char *path, mode_t mode)
{
  int res = -1;

  path_conv win32_path (path);

  if (win32_path.error)
    {
      set_errno (win32_path.error);
      goto done;
    }

  int now;

  set_file_attribute (win32_path.get_win32 (), mode);

  if ((now = GetFileAttributesA (win32_path.get_win32 ())) == -1)
    {
      __seterrno ();
    }
  else
    {
      /* if the mode we want has any write bits set, we can't
	 be read only. */
      if (mode & STD_WBITS)
	{
	  now &= ~FILE_ATTRIBUTE_READONLY;
	}
      else
	{
	  now |= FILE_ATTRIBUTE_READONLY;
	}
      if (S_ISLNK (mode))
	{
	  now |= FILE_ATTRIBUTE_SYSTEM;
	}

      if (SetFileAttributesA (win32_path.get_win32 (), now))
	res = 0;
      else
	__seterrno ();
    }

done:
  syscall_printf ("%d = chmod (%s, 0x%x)\n", res, path, mode);
  return res;
}

/* fchmod: Provided by SVR4 and 4.3+BSD, not part of POSIX.1 */

extern "C"
int
fchmod (int fd, mode_t mode)
{
  if (NOT_OPEN_FD (fd))
    {
      syscall_printf ("-1 = fchmod (%d, 0%o)\n", fd, mode);
      set_errno (EBADF);
      return -1;
    }

  const char *path = myself->hmap[fd].h->get_name ();

  if (path == NULL)
    {
      syscall_printf ("-1 = fchmod (%d, 0%o) (no name)\n", fd, mode);
      set_errno (ENOSYS);
      return -1;
    }

  syscall_printf ("fchmod (%d, 0%o): calling chmod (%s, 0%o)\n",
		  fd, mode, path, mode);
  return chmod (path, mode);
}

/* Some programs rely on st_dev/st_ino being unique for each file.
   Hash the path name and hope for the best.  The hash arg is not
   always initialized to zero since readdir needs to compute the
   dirent ino_t based on a combination of the hash of the directory
   done during the opendir call and the hash or the filename within
   the directory.  FIXME: Not bullet-proof. */
/* Cygwin32 internal */
extern "C"
unsigned long
hash_path_name (unsigned long hash, const char *name)
{
  /* Build up hash.  Ignore single trailing slash or /a/b/ != /a/b */
  while (*name != '\0' && (*name != '\\' || name[1] != '\0'))
    {
      hash += *name + (*name << 17);
      hash ^= hash >> 2;
      name++;
    }
  return hash;
}

/* Cygwin32 internal */
static int
num_entries (const char *win32_name)
{
  WIN32_FIND_DATA buf;
  HANDLE handle;
  char buf1[MAX_PATH];
  int count = 0;

  strcpy (buf1, win32_name);
  int len = strlen (buf1);
  if (len == 0 || buf1[len - 1] == '/')
    strcat (buf1, "*");
  else
    strcat (buf1, "/*"); 	/* */

  handle = FindFirstFileA (buf1, &buf);

  if (handle == INVALID_HANDLE_VALUE)
    return 0;
  count ++;
  while (FindNextFileA (handle, &buf))
    {
      count ++;
    }
  FindClose (handle);
  return count;
}

/* get_os_type: Return type of Win32 operating system being run. */
/* Cygwin32 internal */
extern "C"
os_type
get_os_type () 
{
  DWORD version = GetVersion ();

  if (version < 0x80000000)
    return winNT;
  else if ((version & 0x80000000) && (version & 0xff) > 3)
    return win95;
  else
    return win32s;
}

extern "C"
int
_fstat (int fd, struct stat *buf)
{
  int r;

  if (NOT_OPEN_FD (fd))
    {
      syscall_printf ("-1 = fstat (%d, 0x%x)\n", fd, buf);
      set_errno (EBADF);
      r = -1;
    }
  else
    {
      r = myself->hmap[fd].h->fstat (buf);
      syscall_printf ("%d = fstat (%d, %x)\n", r,fd,buf);
    }

  return r;
}

/* fsync: XPG3 */
extern "C"
int
fsync (int fd)
{
  if (NOT_OPEN_FD (fd))
    {
      syscall_printf ("-1 = fsync (%d)\n", fd);
      set_errno (EBADF);
      return -1;
    }

  HANDLE h = myself->hmap[fd].h->get_handle ();

  if (FlushFileBuffers (h) == 0)
    {
      __seterrno ();
      return -1;
    }
  return 0;
}

/* sync: standards? */
extern "C"
int
sync ()
{
  return 0;
}

/* Cygwin32 internal */
static int
_stat_worker (const char *caller, const char *name, struct stat *buf,
	      int nofollow)
{
  int res = -1;
  int atts, len;
  char tmp[MAX_PATH];
  const char *win32_name;

  debug_printf ("%s (%s, %p)\n", caller, name, buf);
  
  path_conv real_path (name, !nofollow);
  if (real_path.error)
    {
      set_errno (real_path.error);
      goto done;
    }

  memset (buf, 0, sizeof (struct stat));

  win32_name = real_path.get_win32 ();
  atts = GetFileAttributesA (win32_name);

  /* If we can't find the name, try again with a .exe suffix
     [but only if not already present].  */
  /* FIXME: Doing this is of dubious merit.  */
  if (atts == -1
      && ((len = strlen (win32_name)) < 5
	  || strcasecmp (win32_name + len - 4, ".exe")))
    {
      debug_printf ("trying with .exe suffix\n");
      strcpy (tmp, win32_name);
      strcat (tmp, ".exe");
      win32_name = tmp;
      atts = GetFileAttributesA (tmp);
    }
  if (atts == -1)
    {
      /* probably a raw device, try fstat */
      win32_name = name;
      goto fstat;
    }

  debug_printf ("%d = GetFileAttributesA (%s)\n", atts, win32_name);
  if (atts & FILE_ATTRIBUTE_DIRECTORY)
    {
      WIN32_FIND_DATA wfd;
      HANDLE handle;
      /* hmm, the number of links to a directory includes the 
	 number of entries in the directory, since all the things
	 in the directory point to it */
      buf->st_nlink += num_entries (win32_name);
      buf->st_dev = 42;
      buf->st_ino = hash_path_name (0, real_path.get_win32 ());
      buf->st_mode = S_IFDIR | STD_RBITS | STD_XBITS;
      if ((atts & FILE_ATTRIBUTE_READONLY) == 0)
	buf->st_mode |= STD_WBITS;
      buf->st_uid = get_file_owner (real_path.get_win32 ());
      buf->st_gid = get_file_group (real_path.get_win32 ());
      if ((handle = FindFirstFile (real_path.get_win32(), &wfd)) != INVALID_HANDLE_VALUE)
	{
	  buf->st_atime   = to_time_t (&wfd.ftLastAccessTime);
	  buf->st_mtime   = to_time_t (&wfd.ftLastWriteTime);
	  buf->st_ctime   = to_time_t (&wfd.ftCreationTime);
	  buf->st_size    = wfd.nFileSizeLow;
	  buf->st_blksize = S_BLKSIZE;
	  buf->st_blocks  = (buf->st_size + S_BLKSIZE-1) / S_BLKSIZE;
	  FindClose (handle);
	}
      res = 0;
    }
  else
    {
fstat:
      int h = _open (win32_name,
		     O_RDONLY | O_BINARY | (nofollow ? O_NOSYMLINK : 0),
		     0);
      if (h >= 0)
	{
	  res = _fstat (h, buf);
	  _close (h);
	}
    }
  
 done:
  syscall_printf ("%d = %s (%s, %p)\n", res, caller, name, buf);
  return res;
}

extern "C"
int
_stat (const char *name, struct stat *buf)
{
  return (_stat_worker ("stat", name, buf, 0));
}

/* lstat: Provided by SVR4 and 4.3+BSD, POSIX? */
extern "C"
int
lstat (const char *name, struct stat *buf)
{
  return (_stat_worker ("lstat", name, buf, 1));
}

extern "C"
int
access (const char *fn, int flags)
{
  struct stat s;
  
  if (stat (fn, &s))
    return -1;
  if (flags & W_OK)
    {
      if (s.st_mode & S_IWRITE)
	return 0;

      /* can't write to the file */
      set_errno (EACCES);
      return -1;
    }
  return 0;
}

extern "C"
int
_rename (const char *oldpath, const char *newpath)
{
  int res = 0;

  path_conv real_old (oldpath, 0);

  if (real_old.error)
    {
      set_errno (real_old.error);
      syscall_printf ("-1 = rename (%s, %s)\n", oldpath, newpath);
      return -1;
    }
  
  path_conv real_new (newpath, 0);

  if (real_new.error)
    {
      set_errno (real_new.error);
      syscall_printf ("-1 = rename (%s, %s)\n", oldpath, newpath);
      return -1;
    }

  if (! writable_directory (real_old.get_win32 ())
      || ! writable_directory (real_new.get_win32 ()))
    {
      syscall_printf ("-1 = rename (%s, %s)\n", oldpath, newpath);
      return -1;
    }

  int oldatts = GetFileAttributesA (real_old.get_win32 ());
  int newatts = GetFileAttributesA (real_new.get_win32 ());

  if (oldatts == -1) /* file to move doesn't exist */
    {
       syscall_printf ("file to move doesn't exist\n");
       return (-1);
    }

  if (newatts != -1 && newatts & FILE_ATTRIBUTE_READONLY)
    {
      /* Destination file exists and is read only, change that or else
	 the rename won't work. */
      SetFileAttributesA (real_new.get_win32 (), newatts & ~ FILE_ATTRIBUTE_READONLY);
    }

  /* First make sure we have the permissions */
  if (!MoveFileEx (real_old.get_win32 (), real_new.get_win32 (), MOVEFILE_REPLACE_EXISTING))
    {
      res = -1;

      /* !!! fixme, check for windows version before trying this.. */
      if (GetLastError () == ERROR_CALL_NOT_IMPLEMENTED)
	{
	  /* How sad, we must be on win95, try it the stupid way */
	  syscall_printf ("try win95 hack\n");
	  for (;;)
 	    {
	      if (MoveFile (real_old.get_win32 (), real_new.get_win32 ()))
 		{
		  res = 0;
		  break;
		}
	      
	      if (GetLastError () != ERROR_ALREADY_EXISTS)
                {
                  syscall_printf ("%s already_exists\n", real_new.get_win32 ());
                  break;
                }
 	      
	      if (!DeleteFileA (real_new.get_win32 ()) &&
		  GetLastError () != ERROR_FILE_NOT_FOUND)
                {
	          syscall_printf ("deleting %s to be paranoid\n", real_new.get_win32 ());
 	          break;
                }
	    }
	}
      if (res)
	__seterrno ();
    }

  if (res == 0)
    {
      /* make the new file have the permissions of the old one */
      SetFileAttributesA (real_new.get_win32 (), oldatts);
    }

  syscall_printf ("%d = rename (%s, %s)\n", res, real_old.get_win32 (), real_new.get_win32 ());

  return res;
}

extern "C"
int
system (const char *cmdstring)
{
  pid_t pid;
  int res;
  const char* command[4];

  if (cmdstring == (const char *) NULL)
        return 1;

  command[0] = "sh";
  command[1] = "-c";
  command[2] = cmdstring;
  command[3] = (const char *) NULL;

  if ((res = spawnvp (_P_WAIT, "sh", command)) == -1)
    {
      // when exec fails, return value should be as if shell
      // executed exit (127)
      res = 127;
    }

  return res;
}

static int dtable_size = NOFILE_INIT;

/* setdtablesize() may only be called internally from
   hinfo::de_linearize_fd_array() and hinfo_vec::find_unused_handle.
*/
extern "C"
void
setdtablesize (int size)
{
  dtable_size = size;
}

extern "C"
int
getdtablesize ()
{
  return dtable_size;
}

extern "C"
int
gethostname (char *name, size_t len)
{
  DWORD local_len = len;

  if (!GetComputerNameA (name, &local_len))
    {
      __seterrno ();
      return -1;
    }

  return 0;
}

extern "C"
size_t
getpagesize ()
{
  return sysconf (_SC_PAGESIZE);
}

/* FIXME: not all values are correct... */
extern "C"
long int
fpathconf (int fd, int v)
{
  switch (v)
    {
    case _PC_LINK_MAX:
      return _POSIX_LINK_MAX;
    case _PC_MAX_CANON:
    case _PC_MAX_INPUT:
      if (isatty (fd))
        return _POSIX_MAX_CANON;
      else
        {
          set_errno (EBADF);
          return -1;
        }
    case _PC_NAME_MAX:
    case _PC_PATH_MAX:
      return PATH_MAX;
    case _PC_PIPE_BUF:
      return 4096;
    case _PC_CHOWN_RESTRICTED:
    case _PC_NO_TRUNC:
      return -1;
    case _PC_VDISABLE:
      if (isatty (fd))
        return -1;
      else
        {
          set_errno (EBADF);
          return -1;
        }
    default:
      set_errno (EINVAL);
      return -1;
    }
}

extern "C"
long int
pathconf (char *file, int v) 
{
  switch (v)
    {
    case _PC_PATH_MAX:
      return PATH_MAX - strlen (file);
    case _PC_NAME_MAX:
      return PATH_MAX;
    case _PC_LINK_MAX:
      return _POSIX_LINK_MAX;
    case _PC_MAX_CANON:
    case _PC_MAX_INPUT:
        return _POSIX_MAX_CANON;
    case _PC_PIPE_BUF:
      return 4096;
    case _PC_CHOWN_RESTRICTED:
    case _PC_NO_TRUNC:
      return -1;
    case _PC_VDISABLE:
        return -1;
    default:
      set_errno (EINVAL);
      return -1;
    }
}

extern "C"
char *
ctermid (char *s)
{
  static NO_COPY char buf[16];
  if (s == NULL)
    s = buf;
  if (NOTSTATE(myself, PID_USETTY) || myself->ctty == -1)
    strcpy (s, "/dev/con");
  else
    sprintf (s, "/dev/tty%d", myself->ctty);
  return s;
}

extern "C"
char *
ttyname (int fd)
{
  if (NOT_OPEN_FD (fd) || !myself->hmap[fd].h->is_tty ())
    {
      return 0;
    }
  return (char *)(myself->hmap[fd].h->ttyname ());
}

/* Set a file descriptor into text or binary mode, returning the
   previous mode.  */

extern "C"
int
setmode (int fd, int mode)
{
  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
      return -1;
    }
  if (mode != O_BINARY  && mode != O_TEXT)
    {
      set_errno (EINVAL);
      return -1;
    }

  fhandler_base *p = myself->hmap[fd].h;

  /* Note that we have no way to indicate the case that writes are
     binary but not reads, or vice-versa.  These cases can arise when
     using the tty or console interface.  People using those
     interfaces should not use setmode.  */

  int res;
  if (p->get_w_binary () && p->get_r_binary ())
    res = O_BINARY;
  else
    res = O_TEXT;

  if (mode & O_BINARY) 
    {
      p->set_w_binary (1);
      p->set_r_binary (1);
    }
  else 
    {
      p->set_w_binary (0);
      p->set_r_binary (0);
    }

  return res;
}

/* ftruncate: Provided by SVR4 and 4.3+BSD.  Not part of POSIX.1 or XPG3 */
extern "C"
int
ftruncate (int fd, off_t length) 
{
  int res = -1;

  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
    }
  else
    {
      HANDLE h =myself->hmap[fd].h->get_handle ();
      off_t prev_loc;

      if (h)
	{
	  /* remember curr file pointer location */
          prev_loc = myself->hmap[fd].h->lseek (0, SEEK_CUR);

	  myself->hmap[fd].h->lseek (length, SEEK_SET);
	  if (!SetEndOfFile (h))
	    {
	      __seterrno ();
	    }
	  else
	    res = 0;

          /* restore original file pointer location */
          myself->hmap[fd].h->lseek (prev_loc, 0);
	}
    }
  syscall_printf ("%d = ftruncate (%d, %d); \n", res, fd, length);

  return res;
}

/* truncate: Provided by SVR4 and 4.3+BSD.  Not part of POSIX.1 or XPG3 */
/* FIXME: untested */
extern "C"
int
truncate (const char *pathname, off_t length)
{
  int fd;
  int res = -1;

  fd = open (pathname, O_RDWR);
   
  if (fd == -1)
    {
      set_errno (EBADF);
    }
  else
    {
      res = ftruncate (fd, length);
      close (fd);
    }
  syscall_printf ("%d = truncate (%s, %d); \n", res, pathname, length);

  return res;
}

extern "C"
long
get_osfhandle (int fd)
{
  long res = -1;

  if (NOT_OPEN_FD (fd))
    {
      set_errno ( EBADF);
    }
  else
    {
      res = (long) myself->hmap[fd].h->get_handle ();
    }
  syscall_printf ("%d = get_osfhandle(%d); \n", res, fd);

  return res;
}

extern "C"
int
statfs (const char *fname, struct statfs *sfs)
{
  char full_path[MAX_PATH];
  int err;

  if (!sfs)
    {
      set_errno (EFAULT);
      return -1;
    }
  conv_to_full_win32_path (fname, full_path);

  /* Possible choices:
   * d:... -> d:/
   * \\server\share... -> \\server\share\
   * else current drive.
   */
  char *root=full_path;

  if (full_path[1] == ':')
    strcpy (full_path + 2, "\\");
  else if (full_path[0] == '\\' && full_path[1] == '\\')
    {
      char *cp = full_path + 2;
      while (*cp && *cp != '\\')
        cp++;
      if (!*cp)
	{
          set_errno (ENOTDIR);
          return -1;
        }
      cp++;
      while (*cp && *cp != '\\')
        cp++;
      strcpy (cp, "\\");
    }
  else
    root = NULL;

  syscall_printf ("statfs %s \n", root);

  DWORD spc, bps, freec, totalc;

  if (!GetDiskFreeSpace (root, &spc, &bps, &freec, &totalc))
    {
      __seterrno ();
      return -1;
    }

  DWORD vsn, maxlen, flags;

  if (!GetVolumeInformation (root, NULL, 0, &vsn, &maxlen, &flags, NULL, 0))
    {
      __seterrno ();
      return -1;
    }
  sfs->f_type = flags;
  sfs->f_bsize = spc*bps;
  sfs->f_blocks = totalc;
  sfs->f_bfree = sfs->f_bavail = freec;
  sfs->f_files = -1;
  sfs->f_ffree = -1;
  sfs->f_fsid = vsn;
  sfs->f_namelen = maxlen;
  return 0;
}

extern "C"
int
fstatfs (int fd, struct statfs *sfs)
{
  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
      return -1;
    }
  fhandler_disk_file *f = (fhandler_disk_file *) myself->hmap.vec[fd].h;
  return statfs (f->get_name (), sfs);
}

/* setpgid: POSIX 4.3.3.1 */
extern "C"
int
setpgid (pid_t pid, pid_t pgid)
{
  if (pid == 0)
    pid = getpid ();
  if (pgid == 0)
    pgid = pid;

  if (pgid < 0)
    {
      set_errno (EINVAL);
      return -1;
    }
  pinfo *p = procinfo (pid);
  if (p == 0)
    {
      set_errno (ESRCH);
      return -1;
    }
  /* A process may only change the process group of itself and its children */
  if (p == myself || p->ppid == myself->pid)
    {
      p->pgid = pgid;
      return 0;
    }
  else
    {
      set_errno (EPERM);
      return -1;
    }
}

extern "C"
pid_t
getpgid (pid_t pid)
{
  if (pid == 0)
    pid = getpid ();

  pinfo *p = procinfo (pid);
  if (p == 0)
    {
      set_errno (ESRCH);
      return -1;
    }
  return p->pgid;
}

extern "C"
int
setpgrp (void)
{
  return setpgid (0, 0);
}

extern "C"
pid_t
getpgrp (void)
{
  return getpgid (0);
}

extern "C"
char *
ptsname (int fd)
{
  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
      return 0;
    }
  return (char *)(myself->hmap[fd].h->ptsname ());
}

extern "C"
int
regfree ()
{
  return 0;
}

/* mknod was the call to create directories before the introduction
   of mkdir in 4.2BSD and SVR3.  Use of mknod required superuser privs
   so the mkdir command had to be setuid root.
   Although mknod hasn't been implemented yet, some GNU tools (e.g. the
   fileutils) assume its existence so we must provide a stub that always
   fails. */
extern "C"
int
mknod ()
{
  set_errno (ENOSYS);
  return -1;
}

/* setgid: POSIX 4.2.2.1 */
/* FIXME: unimplemented! */
extern "C"
int
setgid (gid_t a)
{
  set_errno (ENOSYS);
  return 0;
}

/* setuid: POSIX 4.2.2.1 */
/* FIXME: unimplemented! */
extern "C"
int
setuid (uid_t b)
{
  set_errno (ENOSYS);
  return 0;
}

/* seteuid: standards? */
extern "C"
int
seteuid (uid_t c)
{
  set_errno (ENOSYS);
  return 0;
}

/* setegid: from System V.  */
extern "C"
int
setegid (gid_t a)
{
  set_errno (ENOSYS);
  return 0;
}

/* chroot: privileged Unix system call.  */
extern "C"
int
chroot (const char *path)
{
  set_errno (ENOSYS);
  return -1;
}
