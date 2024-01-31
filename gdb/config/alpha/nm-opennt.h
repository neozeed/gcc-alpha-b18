/* Native definitions for alpha running OpenNT
   Copyright (C) 1995 Free Software Foundation, Inc.

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

#define GET_LONGJMP_TARGET(ADDR) get_longjmp_target(ADDR)
extern int
get_longjmp_target PARAMS ((CORE_ADDR *));

/* ptrace register ``addresses'' are absolute.  */

#define U_REGS_OFFSET 0

/* NB: On OpenNT, we can step a breakpoint */

#if 0
/* Support for shared libraries.  */

#include "solib.h"
#endif 

#define FLOAT_INFO { extern i386_float_info (); \
						  alpha_float_info (); }

#define USE_PROC_FS

/* submodes of USE_PROC_FS */
#define PROCFS_USE_READ_WRITE
#define HAVE_MULTIPLE_PROC_FDS
#define UNIXWARE
#define HAVE_PSTATUS_T
#define HAVE_NO_PRRUN_T
#define HAVE_STRUCT_LWP
#define LOSING_POLL   /* ??? TEMPORARY */

#define ATTACH_DETACH

/* It's ALMOST coff; bfd does the same thing */
#define COFF_WITH_PE
#define COFF_IMAGE_WITH_PE
