/* Configuration for GNU compiler for processor running OpenNT
   Copyright (C) 1993, 1995 Free Software Foundation, Inc.
   Donn Terry, Softway Systems, Inc,
   from code
      Contributed by Douglas B. Rupp (drupp@cs.washington.edu)

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include <stdlib.h>

#ifndef USG
#define USG 1
#endif

#ifndef ONLY_INT_FIELDS
#define ONLY_INT_FIELDS 1
#endif

#ifndef USE_PROTOTYPES
#define USE_PROTOTYPES 1
#endif

#ifndef HAVE_PUTENV
#define HAVE_PUTENV 1
#endif

#ifndef HAVE_VPRINTF
#define HAVE_VPRINTF 1
#endif

#ifndef HAVE_STRERROR
#define HAVE_STRERROR 1
#endif

#ifndef HAVE_SYS_TIME_H
#define HAVE_SYS_TIME_H 1
#endif

#ifndef TIME_WITH_SYS_TIME
#define TIME_WITH_SYS_TIME 1
#endif

#ifndef HAVE_UNISTD_H
#define HAVE_UNISTD_H 1
#endif

#ifndef HAVE_FCNTL_H
#define HAVE_FCNTL_H 1
#endif

#ifndef STDC_HEADERS
#define STDC_HEADERS 1
#endif

#ifndef NO_SYS_FILE_H
#define NO_SYS_FILE_H 1
#endif

#ifndef HAVE_CRLF
#define HAVE_CRLF 1
#endif

/* If not compiled with GNU C, use the portable alloca.  */
#ifndef __GNUC__
#define USE_C_ALLOCA 1
#endif

#define DONT_DECLARE_SYS_SIGLIST 1  /* signal.h already does */
#define NO_SYS_SIGLIST 1


/* Improve abort information */
#if !defined (__GNUC__) || __GNUC_MINOR__ <= 5
#define __PRETTY_FUNCTION__  ((char*)0)
#endif

#undef abort
#define abort()         gcc_abort (__FILE__, __LINE__, __PRETTY_FUNCTION__)
extern void gcc_abort (const char *, int, const char *);
