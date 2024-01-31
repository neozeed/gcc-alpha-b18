/* Operating system specific defines to be used when targeting GCC for
   OpenNT
   Copyright (C) 1994, 1995 Free Software Foundation, Inc.
   Donn Terry, Softway Systems, Inc. (donn@softway.com)
   Modified from code
      Contributed by Douglas B. Rupp (drupp@cs.washington.edu).

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

#define TARGET_MEM_FUNCTIONS

#undef LINK_SPEC
#define LINK_SPEC "-stack 0x400000,0x10000 %{g}"

#undef STANDARD_EXEC_PREFIX
#define STANDARD_EXEC_PREFIX ""

#undef STANDARD_STARTFILE_PREFIX
#define STANDARD_STARTFILE_PREFIX ""

#undef TOOLDIR_BASE_PREFIX
#define TOOLDIR_BASE_PREFIX ""

#undef STDC_VALUE
#define STDC_VALUE 0
