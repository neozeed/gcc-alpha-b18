/* Configuration for GNU compiler for processor running Windows NT 3.x.
   Copyright (C) 1993, 1995 Free Software Foundation, Inc.
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

#ifndef ALMOST_STDC
#define ALMOST_STDC
#endif

#ifndef HAVE_STRERROR
#define HAVE_STRERROR
#endif

#define NO_SYS_FILE_H 1
#define NO_SYS_SIGLIST 1
#define bcmp(a,b,c) memcmp (a,b,c)
#define bcopy(a,b,c) memcpy (b,a,c)
#define bzero(a,b) memset (a,0,b)
#define index  strchr
#define rindex strrchr
#define kill(a,b) raise(b)

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

//#define OBJECT_SUFFIX ".obj"
#define EXECUTABLE_SUFFIX ".exe"

#define PATH_SEPARATOR ';'
#define DIR_SEPARATOR '\\'

#define S_IRUSR 0000400
#define S_IWUSR 0000200
#define S_IXUSR 0000100
#define S_IRGRP 0000040
#define S_IWGRP 0000020
#define S_IXGRP 0000010
#define S_IROTH 0000004
#define S_IWOTH 0000002
#define S_IXOTH 0000001
#define S_IRWXU S_IRUSR | S_IWUSR | S_IXUSR
#define S_ISREG(m) (((m)&S_IFMT) == S_IFREG)
#define S_ISDIR(m) (((m)&S_IFMT) == S_IFDIR)

