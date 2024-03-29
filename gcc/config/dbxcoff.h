/* Definitions needed when using stabs embedded in COFF sections.
   Copyright (C) 1996 Free Software Foundation, Inc.

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

/* This file may be included by any COFF target which wishes to
   support -gstabs generating stabs in sections, as produced by gas
   and understood by gdb.  */

/* Output DBX (stabs) debugging information if doing -gstabs.  */

#undef DBX_DEBUGGING_INFO
#define DBX_DEBUGGING_INFO

/* Generate SDB debugging information by default. */

#ifndef PREFERRED_DEBUGGING_TYPE
#define PREFERRED_DEBUGGING_TYPE SDB_DEBUG
#endif

/* Be function-relative for block and source line stab directives.  */

#undef DBX_BLOCKS_FUNCTION_RELATIVE
#define DBX_BLOCKS_FUNCTION_RELATIVE 1

/* but, to make this work, functions must appear prior to line info.  */

#undef DBX_FUNCTION_FIRST
#define DBX_FUNCTION_FIRST

/* Generate a blank trailing N_SO to mark the end of the .o file, since
   we can't depend upon the linker to mark .o file boundaries with
   embedded stabs.  */

#undef DBX_OUTPUT_MAIN_SOURCE_FILE_END
#define DBX_OUTPUT_MAIN_SOURCE_FILE_END(FILE, FILENAME)			\
  fprintf (FILE,							\
	   "\t.text\n\t.stabs \"\",%d,0,0,Letext\nLetext:\n", N_SO)

/* Like block addresses, stabs line numbers are relative to the
   current function.  */

#undef ASM_OUTPUT_SOURCE_LINE
#define ASM_OUTPUT_SOURCE_LINE(FILE, LINE)			\
{ if (write_symbols == SDB_DEBUG) {				\
    fprintf ((FILE), "\t.ln\t%d\n",				\
	     ((sdb_begin_function_line > -1)			\
	      ? (LINE) - sdb_begin_function_line : 1));		\
  } else if (write_symbols == DBX_DEBUG) {			\
    static int sym_lineno = 1;					\
    fprintf (FILE, ".stabn 68,0,%d,.LM%d-",			\
	     LINE, sym_lineno);					\
    assemble_name (FILE,					\
		   XSTR (XEXP (DECL_RTL (current_function_decl), 0), 0)); \
    fprintf (FILE, "\n.LM%d:\n", sym_lineno);			\
    sym_lineno += 1;						\
  } }

/* When generating stabs debugging, use N_BINCL entries.  */

#undef DBX_USE_BINCL
#define DBX_USE_BINCL

/* There is no limit to the length of stabs strings.  */

#ifndef DBX_CONTIN_LENGTH
#define DBX_CONTIN_LENGTH 0
#endif
