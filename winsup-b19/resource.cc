/* resource.cc: getrusage () and friends.

   Copyright 1996, 1997, 1998 Cygnus Solutions.

   Written by Steve Chamberlain (sac@cygnus.com), Doug Evans (dje@cygnus.com),
   Geoffrey Noer (noer@cygnus.com) of Cygnus Support.
   Rewritten by Sergey S. Okhapkin (sos@prospect.com.ru)

This file is part of Cygwin32.

This software is a copyrighted work licensed under the terms of the
Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
details. */

#include "winsup.h"

/* add timeval values */
static void
add_timeval (struct timeval *tv1, struct timeval *tv2)
{
  tv1->tv_sec += tv2->tv_sec;
  tv1->tv_usec += tv2->tv_usec;
  if (tv1->tv_usec >= 1000000)
    {
      tv1->tv_usec -= 1000000;
      tv1->tv_sec++;
    }
}

/* add rusage values of r2 to r1 */
void
add_rusage (struct rusage *r1, struct rusage *r2)
{
  add_timeval (&r1->ru_utime, &r2->ru_utime);
  add_timeval (&r1->ru_stime, &r2->ru_stime);
  r1->ru_maxrss += r2->ru_maxrss;   
  r1->ru_ixrss += r2->ru_ixrss;   
  r1->ru_idrss += r2->ru_idrss;   
  r1->ru_isrss += r2->ru_isrss;   
  r1->ru_minflt += r2->ru_minflt;  
  r1->ru_majflt += r2->ru_majflt;  
  r1->ru_nswap += r2->ru_nswap;   
  r1->ru_inblock += r2->ru_inblock; 
  r1->ru_oublock += r2->ru_oublock; 
  r1->ru_msgsnd += r2->ru_msgsnd;  
  r1->ru_msgrcv += r2->ru_msgrcv;  
  r1->ru_nsignals += r2->ru_nsignals;
  r1->ru_nvcsw += r2->ru_nvcsw;   
  r1->ru_nivcsw += r2->ru_nivcsw;  
}

/* FIXME: what about other fields? */
void
fill_rusage (struct rusage *r, HANDLE h)
{
  FILETIME creation = {0,0};
  FILETIME exit = {0,0};
  FILETIME kernel = {0,0};
  FILETIME user = {0,0};

  struct timeval tv;

  GetProcessTimes (h, &creation, &exit, &kernel, &user);
  totimeval (&tv, &kernel, 0, 0);
  add_timeval (&r->ru_stime, &tv);
  totimeval (&tv, &user, 0, 0);
  add_timeval (&r->ru_utime, &tv);
}

extern "C"
int
getrusage (int intwho, struct rusage *rusage)
{
  int res = 0;
  struct rusage r;

  if (intwho == RUSAGE_SELF)
    {
      memset (&r, 0, sizeof (r));
      fill_rusage (&r, GetCurrentProcess ());
      *rusage = r;
    }
  else if (intwho == RUSAGE_CHILDREN)
    *rusage = myself->rusage_children;
  else
    {
      set_errno (EINVAL);
      res = -1;
    }

  syscall_printf ("%d = getrusage (%d, 0x%x)\n", res, intwho, rusage);
  return res;
}
