/* Definitions for hosting on WIN32, for GDB.
   Copyright 1991, 1992 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef XM_H
#define XM_H

#define HOST_BYTE_ORDER LITTLE_ENDIAN
#include "fopen-bin.h"
#include <stdlib.h>

/* Define this lseek(n) != nth byte of file */
/*#define LSEEK_NOT_LINEAR */

#define CANT_FORK

/* way scary...
 * 
 * defs.h defines QUIT as:
 * #define QUIT { \
 *   if (quit_flag) quit (); \
 *   if (interactive_hook) interactive_hook (); \
 *     PROGRESS (1); \
 *   }
 *       
 * pollquit calls win32pollquit to catch <cntl-c> in win32 msg queue.
 * Sh's interp.c calls win32pollquit (defined in gui.cpp), then control_c().
 * Normally go32 uses pollquit (defined in utils.c), but interp.c calls keyht 
 * directly.
 * Might be safest to write a keyht for Win32 which either checks the msg 
 * queue if called from a windows app, or stdin if a console app.
 * Eg., if _WINGDB, check msg queue; if IN_SIMULATOR, check stdin.
 * 
 * Redefine to poll until exception handler installed.
 * Then, can use defs.h's QUIT.
 */
#ifdef QUIT
#undef QUIT
#define FIX_QUIT "FIXME"
#define FIX_QUIT "overriding redefinition of QUIT"
#endif 
#define QUIT  { pollquit(); }

#define GDBINIT_FILENAME "gdb.ini"

#define R_OK 1
#define SIGQUIT 5
#define SIGTRAP 6
#define SIGHUP  7

#define HAVE_STRING

#define DIRNAME_SEPARATOR ';'
#define SLASH_P(X) ((X)=='/' || (X)=='\\')
#define SLASH_CHAR '\\'
#define SLASH_STRING "\\"
#define ROOTED_P(X) ((SLASH_P(X[0])) || (X[1]== ':'))

#define WINGDB


#define HAVE_STRING_H
#define HAVE_STDDEF_H
#define HAVE_STDLIB_H
#define HAVE_TIME_H
#define USE_BINARY_FOPEN
#define FCLOSE_PROVIDED
#define GETENV_PROVIDED
#define MALLOC_INCOMPATIBLE
#ifndef __cplusplus
void free();
#endif

/* older releases ( <= 96q3 ) require __WIN32__ to be defined
 * and don't build if __STDC__ is 1.
 * Newer releases don't define __WIN32__ and allow __STD__ to be 1
 */
/* resetting */
#define __STDC__ 1

void gdbwin_command (const char *);
int win32pollquit(void);
void pollquit(void);
int close(int);	/* callback returns the result of close as int */


#include <sys/stat.h>
/* stats.h defines _stat but not stat if __STDC__ */
#define fstat    _fstat
#define stat     _stat
#include <fcntl.h>

#endif /*XM_H*/
