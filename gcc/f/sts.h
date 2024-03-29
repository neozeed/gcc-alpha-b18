/* sts.h -- Private #include File (module.h template V1.0)
   Copyright (C) 1995 Free Software Foundation, Inc.
   Contributed by James Craig Burley (burley@gnu.ai.mit.edu).

This file is part of GNU Fortran.

GNU Fortran is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Fortran is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Fortran; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

   Owning Modules:
      sts.c

   Modifications:
*/

/* Allow multiple inclusion to work. */

#ifndef _H_f_sts
#define _H_f_sts

/* Simple definitions and enumerations. */


/* Typedefs. */

typedef struct _ffests_ *ffests;
typedef struct _ffests_ ffestsHolder;
typedef unsigned long int ffestsLength;

/* Include files needed by this one. */

#include "malloc.h"

/* Structure definitions. */

struct _ffests_
  {
    char *text_;
    mallocPool pool_;
    ffestsLength len_;
    ffestsLength max_;
  };

/* Global objects accessed by users of this module. */


/* Declare functions with prototypes. */

void ffests_kill (ffests s);
void ffests_new (ffests s, mallocPool pool, ffestsLength size);
void ffests_printf_1D (ffests s, char *ctl, long arg1);
void ffests_printf_1U (ffests s, char *ctl, unsigned long arg1);
void ffests_printf_1s (ffests s, char *ctl, char *arg1);
void ffests_printf_2Us (ffests s, char *ctl, unsigned long arg1,
			char *arg2);
void ffests_putc (ffests s, char c);
void ffests_puts (ffests s, char *string);
void ffests_puttext (ffests s, char *text, ffestsLength length);

/* Define macros. */

#define ffests_init_0()
#define ffests_init_1()
#define ffests_init_2()
#define ffests_init_3()
#define ffests_init_4()
#define ffests_length(s) ((s)->len_)
#define ffests_terminate_0()
#define ffests_terminate_1()
#define ffests_terminate_2()
#define ffests_terminate_3()
#define ffests_terminate_4()
#define ffests_text(s) ((s)->text_)

/* End of #include file. */

#endif
