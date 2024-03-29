/* CYGNUS LOCAL: Entire file.  */

/* Definitions of target machine for GNU compiler.
   NEC VR5000 version.
   Copyright (c) 1996 Cygnus Support Inc.

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

#define MIPS_CPU_STRING_DEFAULT "VR5000"

#define MULTILIB_DEFAULTS { "EB" }

/* We use the MIPS EABI by default.  */
#define MIPS_ABI_DEFAULT ABI_EABI

#include "mips/elf64.h"
#include "mips/abi64.h"

#undef CPP_PREDEFINES
#define CPP_PREDEFINES "-Dmips -DMIPSEB -DR5000 -D_mips -D_MIPSEB -D_R5000"

#undef SUBTARGET_CPP_SIZE_SPEC
#define SUBTARGET_CPP_SIZE_SPEC "\
-D__SIZE_TYPE__=long\\ unsigned\\ int -D__PTRDIFF_TYPE__=long\\ int"

#undef SUBTARGET_CPP_SPEC
#define SUBTARGET_CPP_SPEC "\
%{!mips1:%{!mips2:-U__mips -D__mips=3 -D__mips64}}\
%{!mabi=32: %{!mabi=n32: %{!mabi=64: -D__mips_eabi}}}"

#undef MIPS_ISA_DEFAULT
#define MIPS_ISA_DEFAULT 4
