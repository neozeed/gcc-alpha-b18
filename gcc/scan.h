/* scan.h - Utility declarations for scan-decls and fix-header programs.
   Copyright (C) 1993 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include <stdio.h>

typedef struct sstring
{
  char *base;
  char *ptr;
  char *limit;
} sstring;

#define INIT_SSTRING(STR) ((STR)->base = 0, (STR)->ptr = 0, (STR)->limit = 0)
#define FREE_SSTRING(STR) do { if ((STR)->base) free (STR)->base; } while(0)
#define SSTRING_PUT(STR, C) do {\
  if ((STR)->limit <= (STR)->ptr) make_sstring_space (STR, 1); \
  *(STR)->ptr++ = (C); } while (0)
#define SSTRING_LENGTH(STR) ((STR)->ptr - (STR)->base)
#define MAKE_SSTRING_SPACE(STR, COUNT) \
  if ((STR)->limit - (STR)->ptr < (COUNT)) make_sstring_space (STR, COUNT);

#ifndef _PARAMS
#if defined(__STDC__) || defined(__cplusplus)
#define _PARAMS(args) args
#else
#define _PARAMS(args) ()
#endif
#endif

struct partial_proto;
struct fn_decl
{
  char *fname;
  char *rtype;
  char *params;
  struct partial_proto *partial;
};

extern int lineno;
extern void sstring_append _PARAMS((sstring *, sstring *));
extern void make_sstring_space _PARAMS((sstring *, int));
extern int skip_spaces _PARAMS((FILE *, int));
extern int scan_ident _PARAMS((FILE *, sstring *, int));
extern int scan_string _PARAMS((FILE *, sstring *, int));
extern int read_upto _PARAMS((FILE *, sstring *, int));
extern char *xmalloc _PARAMS((unsigned));
extern char *xrealloc _PARAMS((char *, unsigned));
extern unsigned long hash _PARAMS((const char *));

/* get_token is a simple C lexer. */
#define IDENTIFIER_TOKEN 300
#define CHAR_TOKEN 301
#define STRING_TOKEN 302
#define INT_TOKEN 303
extern int get_token _PARAMS ((FILE *, sstring *));

/* Current file and line numer, taking #-directives into account */
extern int source_lineno;
extern sstring source_filename;
/* Current physical line number */
extern int lineno;
