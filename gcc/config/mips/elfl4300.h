/* Definitions of target machine for GNU compiler.
   NEC VR4300 little-endian version.
   Copyright (c) 1995 Cygnus Support Inc.

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
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#define MIPS_CPU_STRING_DEFAULT "VR4300"

#define MULTILIB_DEFAULTS { "EL" }

#include "mips/elfl64.h"

#undef CPP_PREDEFINES
#define CPP_PREDEFINES "-Dmips -DMIPSEL -DR4300 -D_mips -D_MIPSEL -D_R4300"
