/* This file is tc-h8500.h
   Copyright (C) 1993, 95, 1997 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */


#define TC_H8500

#define TARGET_BYTES_BIG_ENDIAN 1

/* This macro translates between an internal fix and an coff reloc type */
#define TC_COFF_FIX2RTYPE(fixP) tc_coff_fix2rtype(fixP)

#define BFD_ARCH bfd_arch_h8500
#define COFF_MAGIC 0x8500
#define TC_COUNT_RELOC(x) ((x)->fx_addsy||(x)->fx_subsy)
#define IGNORE_NONSTANDARD_ESCAPES

#define TC_RELOC_MANGLE(s,a,b,c) tc_reloc_mangle(a,b,c)

#define DO_NOT_STRIP 0
#define LISTING_HEADER "Hitachi H8/500 GAS "
#define NEED_FX_R_TYPE 1
#define RELOC_32 1234

#define TC_START_LABEL(ch, ptr)  (ch == ':' && start_label(ptr))
#define TC_COFF_SIZEMACHDEP(frag) tc_coff_sizemachdep(frag)

#define md_operand(x)

extern struct relax_type md_relax_table[];
#define TC_GENERIC_RELAX_TABLE md_relax_table

/* end of tc-h8500.h */
