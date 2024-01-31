/* Configuration for GNU C-compiler for hosting on Windows NT.
   using a unix style C library.
   Copyright (C) 1995, 1996, 1997 Free Software Foundation, Inc.

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
Boston, MA 02111-1307, USA. */


/* #defines that need visibility everywhere.  */
#define	FALSE	0
#define	TRUE	1

/* This describes the machine the compiler is hosted on.  */
#define	HOST_BITS_PER_CHAR	8
#define	HOST_BITS_PER_SHORT	16
#define	HOST_BITS_PER_INT	32
#define	HOST_BITS_PER_LONG	64
#define HOST_BITS_PER_LONGLONG  64


/* target machine dependencies.
   tm.h is a symbolic link to the actual target specific file.   */
#include "tm.h"


/* Arguments to use with `exit'.  */
#define	SUCCESS_EXIT_CODE	0
#define	FATAL_EXIT_CODE		33

#if 0
/* If not compiled with GNU C, use the builtin alloca.  */
#if !defined(__GNUC__) && !defined(_WIN32) 
#include <alloca.h>
#else
extern void *alloca ();
#endif

/* The host compiler has problems with enum bitfields since it makes
   them signed so we can't fit all our codes in.  */

#ifndef __GNUC__
#define ONLY_INT_FIELDS
#endif

/* Declare some functions needed for this machine.  We don't want to
   include these in the sources since other machines might define them
   differently.  */

extern void *malloc (), *realloc (), *calloc ();

#ifndef inhibit_libc
#include "string.h"
#endif


/* Define if you have the bsearch function.  */
#define HAVE_BSEARCH 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the strtoul function.  */
#define HAVE_STRTOUL 1

/* Define if you have the <stddef.h> header file.  */
#define HAVE_STDDEF_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <strings.h> header file.  */
#define HAVE_STRINGS_H 1

/* Define if you have the <sys/varargs.h> header file.  */
/* #undef HAVE_SYS_VARARGS_H */

/* Define if you have the <time.h> header file.  */
#define HAVE_TIME_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <varargs.h> header file.  */
#define HAVE_VARARGS_H 1

#include <stdlib.h>

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

#ifndef HAVE_CRLF
#define HAVE_CRLF 1
#endif

/* If not compiled with GNU C, use the portable alloca.  */
#ifndef __GNUC__
#define USE_C_ALLOCA 1
#endif

#define DONT_DECLARE_SYS_SIGLIST 1  /* signal.h already does */
#define NO_SYS_SIGLIST 1

#endif

/* Improve abort information */
#if !defined (__GNUC__) || __GNUC_MINOR__ <= 5
#define __PRETTY_FUNCTION__  ((char*)0)
#endif
#undef abort
#define abort()         gcc_abort (__FILE__, __LINE__, __PRETTY_FUNCTION__)

////////////////////////////////////////////////////////////////////////
#undef HOST_BITS_PER_LONG
#define	HOST_BITS_PER_LONG	32

#ifdef __GNUC__
#define HOST_WIDE_INT long long
#else
#define HOST_WIDE_INT __int64
#endif
#define HOST_BITS_PER_WIDE_INT 64


#define NO_STAB_H
#define HAVE_STRERROR
#define HAVE_FILE_H
#define PATH_SEPARATOR ';'
#define EXECUTABLE_SUFFIX ".exe"
#define P_WAIT _P_WAIT

/* Even though we support "/", allow "\" since everybody tests both.  */
#define DIR_SEPARATOR '\\'

