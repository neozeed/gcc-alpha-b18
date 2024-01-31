/* This is file TIME.H */

/* Define the structures used by the gettimeofday() syscall. */

/*
** Copyright (C) 1991 DJ Delorie, 24 Kirsten Ave, Rochester NH 03867-2954
**
** This file is distributed under the terms listed in the document
** "copying.dj", available from DJ Delorie at the address above.
** A copy of "copying.dj" should accompany this file; if not, a copy
** should be available from where this file was obtained.  This file
** may not be distributed without a verbatim copy of "copying.dj".
**
** This file is distributed WITHOUT ANY WARRANTY; without even the implied
** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef _SYS_TIME_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _SYS_TIME_H_

#ifndef _GNU_H_WINDOWS32_SOCKETS
struct timeval {
  long tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};
#endif

/* Cygwin32 needs itimer headers */
#ifdef __CYGWIN32__
#define ITIMER_REAL     0
#define ITIMER_VIRTUAL  1
#define ITIMER_PROF     2

struct  itimerval {
  struct  timeval it_interval;
  struct  timeval it_value;
};
#endif /* __CYGWIN32__ */

#ifdef __cplusplus
}
#endif
#endif
