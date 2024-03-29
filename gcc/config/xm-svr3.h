/* Configuration for GNU C-compiler for hosts running System V Release 3
   Copyright (C) 1991, 1993 Free Software Foundation, Inc.

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

#define bcopy(src,dst,len) memcpy ((dst),(src),(len))
#define bzero(dst,len) memset ((dst),0,(len))
#define bcmp(left,right,len) memcmp ((left),(right),(len))

#define rindex strrchr
#define index strchr

#define USG
#define HAVE_VPRINTF

#ifndef SVR3
#define SVR3
#endif
