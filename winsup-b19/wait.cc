/* wait.cc: Posix wait routines.  

   Copyright 1996, 1997, 1998 Cygnus Solutions.

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"
#include "sys/wait.h"
#include <stdlib.h>

/* This is called _wait and not wait because the real wait is defined
   in libc/syscalls/syswait.c.  It calls us.  */

pid_t
_wait (int *status)
{
  return wait4 (-1, status, 0, NULL);
}

pid_t
waitpid (pid_t intpid, int *status, int options)
{
  return wait4 (intpid, status, options, NULL);
}

pid_t
wait3 (int *status, int options, struct rusage *r)
{
  return wait4 (-1, status, options, r);
}

/* Wait for any child to complete.
 * Note: this is not thread safe.  Use of wait in multiple threads will
 * not work correctly.
 */

pid_t
wait4 (int intpid, int *status, int options, struct rusage *r)
{
  int rc;
  waitq *w;
  HANDLE waitfor;

 if (options & ~(WNOHANG | WUNTRACED))
    {
      set_errno (EINVAL);
      return -1;
    }

  if (r)
    memset (r, 0, sizeof (*r));

  if ((w = (waitq *)TlsGetValue(waitq_storage)) == NULL)
    {
      w = (waitq *)malloc(sizeof(*w));
      TlsSetValue(waitq_storage, (LPVOID)w);
      memset(w, 0, sizeof(*w));
    }

  w->pid = intpid;
  w->options = options;
  w->rusage = r;
  sigproc_printf("calling proc_subproc, pid = %d, options = %d\n",
	       w->pid, w->options);
  if (!proc_subproc(PROC_WAIT, (DWORD)w))
    {
      set_errno(ENOSYS);
      paranoid_printf ("proc_subproc returned 0\n");
      rc = -1;
      goto done;
    }

  if ((waitfor = w->ev) == NULL)
    goto nochildren;

  rc = WaitForSingleObject (waitfor, INFINITE);

  sigproc_printf ("%d = WaitForSingleObject (...)\n", rc);

  if (w->ev == NULL)
    {
    nochildren:
      /* found no children */
      set_errno (ECHILD);
      rc = -1;
      goto done;
    }

  if (w->status == -1)
    {
      set_errno (EINTR);
      rc = -1;
    }
  else if (rc != WAIT_OBJECT_0)
    {
      /* We shouldn't set errno to any random value if we can help it.
	 See the Posix manual for a list of valid values for `errno'.  */
      set_errno (EINVAL);
      rc = -1;
    }
  else if ((rc = w->pid) != 0 && status)
    *status = w->status;

done:
  sigproc_printf ("%d, %p(%d), %d = %d\n", intpid, status, w->status,
		  options, rc);
  w->status = -1;
  if (rc < 0)
    sigproc_printf("*** errno = %d\n", get_errno());
  return rc;
}
