/* Macro defintions for i386, running SCO Unix System V/386 3.2.
   Copyright (C) 1989 Free Software Foundation, Inc.

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

/* In 3.2v4 <sys/user.h> requires on <sys/dir.h>.  */
#include <sys/types.h>
#include <sys/dir.h>

#include "i386/xm-i386v.h"

/* Apparently there is inconsistency among various System V's about what
   the name of this field is.  */
#define U_FPSTATE(u) u.u_fps.u_fpstate

/* SCO 3.2v2 and later have job control.  */
/* SCO 3.2v4 I know has termios; I'm not sure about earlier versions.
   GDB does not currently support the termio/job control combination.  */
#undef HAVE_TERMIO
#define HAVE_TERMIOS

/* SCO's assembler doesn't grok dollar signs in identifiers.
   So we use dots instead.  This item must be coordinated with G++. */
#undef CPLUS_MARKER
#define CPLUS_MARKER '.'

/* Use setpgid instead of setpgrp on SCO */
#define NEED_POSIX_SETPGID
