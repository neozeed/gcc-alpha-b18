/* Return time used so far, in microseconds.
   Copyright (C) 1994 Free Software Foundation, Inc.

This file is part of the libiberty library.
Libiberty is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

Libiberty is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with libiberty; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "ansidecl.h"
#include "libiberty.h"

/* There are several ways to get elapsed execution time; unfortunately no
   single way is available for all host systems, nor are there reliable
   ways to find out which way is correct for a given host. */

#include <time.h>

/* These should go away when libiberty uses autoconf. */

#if defined(__sun__) && !defined(__svr4__)
#define HAVE_GETRUSAGE
#endif

#ifdef HAVE_SYSCONF
#define HAVE_TIMES
#endif

#ifdef HAVE_GETRUSAGE
#include <sys/time.h>
#include <sys/resource.h>
#endif

#ifdef HAVE_TIMES
#ifndef NO_SYS_PARAM_H
#include <sys/param.h>
#endif
#include <sys/times.h>
#endif

/* This is a fallback; if wrong, it will likely make obviously wrong
   results. */

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1
#endif

long
get_run_time ()
{
#ifdef HAVE_GETRUSAGE
  struct rusage rusage;

  getrusage (0, &rusage);
  return (rusage.ru_utime.tv_sec * 1000000 + rusage.ru_utime.tv_usec
	  + rusage.ru_stime.tv_sec * 1000000 + rusage.ru_stime.tv_usec);
#else /* ! HAVE_GETRUSAGE */
#ifdef HAVE_TIMES
  struct tms tms;

  times (&tms);
  return (tms.tms_utime + tms.tms_stime) * (1000000 / HZ);
#else /* ! HAVE_TIMES */
  /* Fall back on clock and hope it's correctly implemented. */
  const long clocks_per_sec = CLOCKS_PER_SEC;
  if (clocks_per_sec <= 1000000)
    return clock () * (1000000 / clocks_per_sec);
  else
    return clock () / clocks_per_sec;
#endif  /* HAVE_TIMES */
#endif  /* HAVE_GETRUSAGE */
}
