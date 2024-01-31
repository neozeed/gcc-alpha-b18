/* fcntl.cc: fcntl syscall

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include <fcntl.h>
#include <stdarg.h>
#include "winsup.h"

extern "C"
int
_fcntl (int fd, int cmd,...)
{
  va_list args;
  int arg = 0;
  int res;

  if (NOT_OPEN_FD (fd))
    {
      set_errno (EBADF);
      res = -1;
      goto done;
    }

  switch (cmd)
    {
    case F_DUPFD:
      va_start (args, cmd);
      arg = va_arg (args,int);
      va_end (args);
      res = dup2 (fd, myself->hmap.find_unused_handle (arg));
      goto done;

    case F_GETFD:
      res = myself->hmap[fd].h->get_close_on_exec() ? FD_CLOEXEC : 0;
      goto done;

    case F_SETFD:
      va_start (args, cmd);
      arg = va_arg (args, int);
      va_end (args);
      myself->hmap[fd].h->set_close_on_exec(arg);
      res = 0;
      goto done;
#if 0
      if (arg == FD_CLOEXEC)
	{
/* Don't delete this.  Keep it around for reference.  */
#if 0
	  HANDLE new;
	  if (CHILD_P ())
	    {
	      if (!DuplicateHandle (GetCurrentProcess (),
			__myself->hmap[fd].handle,
				    GetCurrentProcess (), &new,
				    0, 0,
			(DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS)))
		{
		  /* Ugh.  We've lost the original handle.  */
		  _STRACE (0, ("DuplicateHandle for FD_CLOEXEC failed!\n"));
		  __seterrno ();
		  res = -1;
		  goto done;
		}
	      __myself->hmap[fd].handle = new;
	    }
#endif
	  myself->hmap[fd].h->set_close_on_exec(1);

	  res = 0;
	  goto done;
	}
#endif
      break;

    case F_GETFL:
      {
        res = myself->hmap[fd].h->get_flags ();
        goto done;
      }
    case F_SETFL:
      {
	int temp = 0;

	va_start (args, cmd);
	arg = va_arg (args, int);
	va_end (args);

        if (arg & O_RDONLY)
          temp |= GENERIC_READ;
        if (arg & O_WRONLY)
          temp |= GENERIC_WRITE;

	syscall_printf ("fcntl (%d, F_SETFL, %d);\n", arg);

 	myself->hmap[fd].h->set_access (temp);
 	myself->hmap[fd].h->set_flags (arg);

	res = 0;
	goto done;
      }

    case F_GETLK:
    case F_SETLK:
    case F_SETLKW:
      {
        struct flock *fl;
        va_start (args, cmd);
        fl = va_arg (args,struct flock *);
        va_end (args);
        res = myself->hmap[fd].h->lock(cmd, fl);
        goto done;
      }
    default:
      set_errno (EINVAL);
      res = -1;
      goto done;
    }

  set_errno (ENOSYS);
  res = -1;

 done:
  syscall_printf ("%d = fcntl (%d, %d, %d)\n", res, fd, cmd, arg);
  return res;
}
