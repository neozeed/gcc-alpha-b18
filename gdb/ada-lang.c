/* Ada language support routines for GDB, the GNU debugger.  Copyright
   1992, 1993, 1994, 1997 Free Software Foundation, Inc.

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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* NOTE: For the moment, there is a good deal of stuff here that ought to be
   elsewhere (e.g., in symtab.c, eval.c, or values.c).  For the
   moment, I am putting them here while I am developing the Ada stuff
   in order to keep it together,  with the intention of integrating it
   all into the proper places in GDB when it becomes part of the
   mainstream. */ 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "demangle.h"
#include "defs.h"
#include "symtab.h"
#include "gdbtypes.h"
#include "expression.h"
#include "parser-defs.h"
#include "language.h"
#include "c-lang.h"
#include "inferior.h"
#include "symfile.h"
#include "objfiles.h"
#include "ada-lang.h"

struct cleanup* unresolved_names;

static void
emit_char PARAMS ((int, GDB_FILE *, int));

static void
ada_printchar PARAMS ((int, GDB_FILE *));

static void
ada_printstr PARAMS ((GDB_FILE *, char *, unsigned int, int));

static struct type *
ada_create_fundamental_type PARAMS ((struct objfile *, int));

static void
modify_general_field PARAMS ((char *, LONGEST, int, int));

static struct type*
desc_base_type PARAMS ((struct type*));

static struct type*
desc_bounds_type PARAMS ((struct type*));

static value_ptr
desc_bounds PARAMS ((value_ptr));

static int
desc_bounds_bitpos PARAMS ((struct type*));

static int
desc_bounds_bitsize PARAMS ((struct type*));

static struct type*
desc_data_type PARAMS ((struct type*));

static value_ptr
desc_data PARAMS ((value_ptr));

static int
desc_data_bitpos PARAMS ((struct type*));

static int
desc_data_bitsize PARAMS ((struct type*));

static value_ptr
desc_one_bound PARAMS ((value_ptr, int, int));

static int
desc_bound_bitpos PARAMS ((struct type*, int, int));

static int
desc_bound_bitsize PARAMS ((struct type*, int, int));

static struct type* 
desc_index_type PARAMS ((struct type*, int));

static int
desc_arity PARAMS ((struct type*));

static int
ada_type_match PARAMS ((struct type*, struct type*, int));

static int
ada_args_match PARAMS ((struct symbol*, value_ptr*, int));

static value_ptr
place_on_stack PARAMS ((value_ptr, CORE_ADDR*));

static value_ptr
convert_actual PARAMS ((value_ptr, struct type*, CORE_ADDR*));

static value_ptr
make_array_descriptor PARAMS ((struct type*, value_ptr, CORE_ADDR*));

static void 
ada_add_block_symbols PARAMS ((struct block*, const char*, namespace_enum));

static void
fill_in_ada_prototype PARAMS ((struct symbol*));

static int
is_nonfunction PARAMS ((struct symbol**, int));

static void
add_defn_to_vec PARAMS ((struct symbol*, struct block*));

static struct partial_symbol *
ada_lookup_partial_symbol PARAMS ((struct partial_symtab*, const char*, int,
				   namespace_enum namespace));

static struct symtab*
symtab_for_sym PARAMS ((struct symbol*));

static int
ada_msymbol_matches_name PARAMS ((struct minimal_symbol*, const char*));

static value_ptr
ada_resolve_subexp PARAMS ((struct expression**, int*, int));

static void
replace_operator_with_call PARAMS ((struct expression**, int, int, int,
				    struct symbol*, struct block*));

static int
possible_user_operator_p PARAMS ((enum exp_opcode, value_ptr*));

static const char*
ada_op_name PARAMS ((enum exp_opcode));

static int
numeric_type_p PARAMS ((struct type*));

static int
integer_type_p PARAMS ((struct type*));

static int
scalar_type_p PARAMS ((struct type*));

static int
discrete_type_p PARAMS ((struct type*));

static int
nearest_to_line PARAMS ((struct symtabs_and_lines, int));

static char*
extended_canonical_line_spec PARAMS ((struct symtab_and_line, const char*));

static value_ptr
evaluate_subexp PARAMS ((struct type*, struct expression*, int*, enum noside));

static value_ptr
evaluate_subexp_type PARAMS ((struct expression*, int*));

/* Table of Ada operators and their GNAT-mangled names.  Last entry is pair 
   of NULLs. */

const struct ada_opname_map ada_opname_table[] =
{
  { "Oadd", "\"+\"", BINOP_ADD },
  { "Osubtract", "\"-\"", BINOP_SUB },
  { "Omultiply", "\"*\"", BINOP_MUL },
  { "Odivide", "\"/\"", BINOP_DIV },
  { "Omod", "\"mod\"", BINOP_MOD },
  { "Orem", "\"rem\"", BINOP_REM },
  { "Oexpon", "\"**\"", BINOP_EXP },
  { "Olt", "\"<\"", BINOP_LESS },
  { "Ole", "\"<=\"", BINOP_LEQ },
  { "Ogt", "\">\"", BINOP_GTR },
  { "Oge", "\">=\"", BINOP_GEQ },
  { "Oeq", "\"=\"", BINOP_EQUAL },
  { "One", "\"/=\"", BINOP_NOTEQUAL },
  { "Oand", "\"and\"", BINOP_BITWISE_AND },
  { "Oor", "\"or\"", BINOP_BITWISE_IOR },
  { "Oxor", "\"xor\"", BINOP_BITWISE_XOR },
  { "Oconcat", "\"&\"", BINOP_CONCAT },
  { "Oabs", "\"abs\"", UNOP_ABS },
  { "Onot", "\"not\"", UNOP_LOGICAL_NOT },
  { "Oadd", "\"+\"", UNOP_PLUS },
  { "Osubtract", "\"-\"", UNOP_NEG },
  { NULL, NULL }
};

/* Given a guess, LANG, as to the initial language, return an updated */
/* guess, assuming that the partial symbol table containing `main' is */
/* MAIN_PST. */
enum language
ada_update_initial_language (lang, main_pst)
     enum language lang;
     struct partial_symtab* main_pst;
{
  if (main_pst != NULL && main_pst -> filename != NULL
      && STREQ (main_pst -> filename + strlen (main_pst -> filename) - 2, ".c")
      && STREQN (main_pst -> filename, "b_", 2))
    {
      int i;
      char* main_name = 
	(char*) alloca (strlen (main_pst -> filename + 2) + sizeof("_ada_"));
      strcpy (main_name, "_ada_");
      strcat (main_name, main_pst -> filename + 2);
      main_name[strlen (main_name) - 2] = '\000';

      if (lookup_minimal_symbol (main_name, (const char*) NULL,
				 (struct objfile*) NULL) != NULL)
	return language_ada;

#ifdef VMS
      for (i = 0; main_name[i]; i += 1)
	main_name[i] = toupper (main_name[i]);

      if (lookup_minimal_symbol (main_name, (const char*) NULL,
				 (struct objfile*) NULL)
	  != NULL)
	return language_ada;
#endif

    }

  return lang;
}
      


/* Print the character C on STREAM as part of the contents of a literal
   string whose delimiter is QUOTER.  Note that that format for printing
   characters and strings is language specific. */

static void
emit_char (c, stream, quoter)
     int c;
     GDB_FILE *stream;
     int quoter;
{

  c &= 0xFF;			/* Avoid sign bit follies */

  if (PRINT_LITERAL_FORM (c))
    {
      if (c == '\\' || c == quoter)
	{
	  fputs_filtered ("\\", stream);
	}
      fprintf_filtered (stream, "%c", c);
    }
  else
    {
      switch (c)
	{
	case '\n':
	  fputs_filtered ("\\n", stream);
	  break;
	case '\b':
	  fputs_filtered ("\\b", stream);
	  break;
	case '\t':
	  fputs_filtered ("\\t", stream);
	  break;
	case '\f':
	  fputs_filtered ("\\f", stream);
	  break;
	case '\r':
	  fputs_filtered ("\\r", stream);
	  break;
	case '\033':
	  fputs_filtered ("\\e", stream);
	  break;
	case '\007':
	  fputs_filtered ("\\a", stream);
	  break;
	default:
	  fprintf_filtered (stream, "\\%.3o", (unsigned int) c);
	  break;
	}
    }
}


static void
ada_printchar (c, stream)
     int c;
     GDB_FILE *stream;
{
  fputs_filtered ("'", stream);
  emit_char (c, stream, '\'');
  fputs_filtered ("'", stream);
}

/* Print the character string STRING, printing at most LENGTH characters.
   Printing stops early if the number hits print_max; repeat counts
   are printed as appropriate.  Print ellipses at the end if we
   had to stop before printing LENGTH characters, or if FORCE_ELLIPSES.  */

static void
ada_printstr (stream, string, length, force_ellipses)
     GDB_FILE *stream;
     char *string;
     unsigned int length;
     int force_ellipses;
{
  unsigned int i;
  unsigned int things_printed = 0;
  int in_quotes = 0;
  int need_comma = 0;
  extern int inspect_it;
  extern int repeat_count_threshold;
  extern int print_max;

  if (length == 0)
    {
      fputs_filtered ("\"\"", stream);
      return;
    }

  for (i = 0; i < length && things_printed < print_max; ++i)
    {
      /* Position of the character we are examining
	 to see whether it is repeated.  */
      unsigned int rep1;
      /* Number of repetitions we have detected so far.  */
      unsigned int reps;

      QUIT;

      if (need_comma)
	{
	  fputs_filtered (", ", stream);
	  need_comma = 0;
	}

      rep1 = i + 1;
      reps = 1;
      while (rep1 < length && string[rep1] == string[i])
	{
	  rep1 += 1;
	  reps += 1;
	}

      if (reps > repeat_count_threshold)
	{
	  if (in_quotes)
	    {
	      if (inspect_it)
		fputs_filtered ("\\\", ", stream);
	      else
		fputs_filtered ("\", ", stream);
	      in_quotes = 0;
	    }
	  ada_printchar (string[i], stream);
	  fprintf_filtered (stream, " <repeats %u times>", reps);
	  i = rep1 - 1;
	  things_printed += repeat_count_threshold;
	  need_comma = 1;
	}
      else
	{
	  if (!in_quotes)
	    {
	      if (inspect_it)
		fputs_filtered ("\\\"", stream);
	      else
		fputs_filtered ("\"", stream);
	      in_quotes = 1;
	    }
	  emit_char (string[i], stream, '"');
	  ++things_printed;
	}
    }

  /* Terminate the quotes if necessary.  */
  if (in_quotes)
    {
      if (inspect_it)
	fputs_filtered ("\\\"", stream);
      else
	fputs_filtered ("\"", stream);
    }

  if (force_ellipses || i < length)
    fputs_filtered ("...", stream);
}

/* Create a fundamental Ada type using default reasonable for the current
   target machine.

   Some object/debugging file formats (DWARF version 1, COFF, etc) do not
   define fundamental types such as "int" or "double".  Others (stabs or
   DWARF version 2, etc) do define fundamental types.  For the formats which
   don't provide fundamental types, gdb can create such types using this
   function.

   FIXME:  Some compilers distinguish explicitly signed integral types
   (signed short, signed int, signed long) from "regular" integral types
   (short, int, long) in the debugging information.  There is some dis-
   agreement as to how useful this feature is.  In particular, gcc does
   not support this.  Also, only some debugging formats allow the
   distinction to be passed on to a debugger.  For now, we always just
   use "short", "int", or "long" as the type name, for both the implicit
   and explicitly signed types.  This also makes life easier for the
   gdb test suite since we don't have to account for the differences
   in output depending upon what the compiler and debugging format
   support.  We will probably have to re-examine the issue when gdb
   starts taking it's fundamental type information directly from the
   debugging information supplied by the compiler.  fnf@cygnus.com */

static struct type *
ada_create_fundamental_type (objfile, typeid)
     struct objfile *objfile;
     int typeid;
{
  struct type *type = NULL;

  switch (typeid)
    {
      default:
	/* FIXME:  For now, if we are asked to produce a type not in this
	   language, create the equivalent of a C integer type with the
	   name "<?type?>".  When all the dust settles from the type
	   reconstruction work, this should probably become an error. */
	type = init_type (TYPE_CODE_INT,
			  TARGET_INT_BIT / TARGET_CHAR_BIT,
			  0, "<?type?>", objfile);
        warning ("internal error: no Ada fundamental type %d", typeid);
	break;
      case FT_VOID:
	type = init_type (TYPE_CODE_VOID,
			  TARGET_CHAR_BIT / TARGET_CHAR_BIT,
			  0, "void", objfile);
	break;
      case FT_CHAR:
	type = init_type (TYPE_CODE_INT,
			  TARGET_CHAR_BIT / TARGET_CHAR_BIT,
			  0, "character", objfile);
	break;
      case FT_SIGNED_CHAR:
	type = init_type (TYPE_CODE_INT,
			  TARGET_CHAR_BIT / TARGET_CHAR_BIT,
			  0, "signed char", objfile);
	break;
      case FT_UNSIGNED_CHAR:
	type = init_type (TYPE_CODE_INT,
			  TARGET_CHAR_BIT / TARGET_CHAR_BIT,
			  TYPE_FLAG_UNSIGNED, "unsigned char", objfile);
	break;
      case FT_SHORT:
	type = init_type (TYPE_CODE_INT,
			  TARGET_SHORT_BIT / TARGET_CHAR_BIT,
			  0, "short_integer", objfile);
	break;
      case FT_SIGNED_SHORT:
	type = init_type (TYPE_CODE_INT,
			  TARGET_SHORT_BIT / TARGET_CHAR_BIT,
			  0, "short_integer", objfile);	
	break;
      case FT_UNSIGNED_SHORT:
	type = init_type (TYPE_CODE_INT,
			  TARGET_SHORT_BIT / TARGET_CHAR_BIT,
			  TYPE_FLAG_UNSIGNED, "unsigned short", objfile);
	break;
      case FT_INTEGER:
	type = init_type (TYPE_CODE_INT,
			  TARGET_INT_BIT / TARGET_CHAR_BIT,
			  0, "integer", objfile);
	break;
      case FT_SIGNED_INTEGER:
	type = init_type (TYPE_CODE_INT,
			  TARGET_INT_BIT / TARGET_CHAR_BIT,
			  0, "integer", objfile); /* FIXME -fnf */
	break;
      case FT_UNSIGNED_INTEGER:
	type = init_type (TYPE_CODE_INT,
			  TARGET_INT_BIT / TARGET_CHAR_BIT,
			  TYPE_FLAG_UNSIGNED, "unsigned int", objfile);
	break;
      case FT_LONG:
	type = init_type (TYPE_CODE_INT,
			  TARGET_LONG_BIT / TARGET_CHAR_BIT,
			  0, "long_integer", objfile);
	break;
      case FT_SIGNED_LONG:
	type = init_type (TYPE_CODE_INT,
			  TARGET_LONG_BIT / TARGET_CHAR_BIT,
			  0, "long_integer", objfile);
	break;
      case FT_UNSIGNED_LONG:
	type = init_type (TYPE_CODE_INT,
			  TARGET_LONG_BIT / TARGET_CHAR_BIT,
			  TYPE_FLAG_UNSIGNED, "unsigned long", objfile);
	break;
      case FT_LONG_LONG:
	type = init_type (TYPE_CODE_INT,
			  TARGET_LONG_LONG_BIT / TARGET_CHAR_BIT,
			  0, "long_long_integer", objfile);
	break;
      case FT_SIGNED_LONG_LONG:
	type = init_type (TYPE_CODE_INT,
			  TARGET_LONG_LONG_BIT / TARGET_CHAR_BIT,
			  0, "long_long_integer", objfile);
	break;
      case FT_UNSIGNED_LONG_LONG:
	type = init_type (TYPE_CODE_INT,
			  TARGET_LONG_LONG_BIT / TARGET_CHAR_BIT,
			  TYPE_FLAG_UNSIGNED, "unsigned long long", objfile);
	break;
      case FT_FLOAT:
	type = init_type (TYPE_CODE_FLT,
			  TARGET_FLOAT_BIT / TARGET_CHAR_BIT,
			  0, "float", objfile);
	break;
      case FT_DBL_PREC_FLOAT:
	type = init_type (TYPE_CODE_FLT,
			  TARGET_DOUBLE_BIT / TARGET_CHAR_BIT,
			  0, "long_float", objfile);
	break;
      case FT_EXT_PREC_FLOAT:
	type = init_type (TYPE_CODE_FLT,
			  TARGET_LONG_DOUBLE_BIT / TARGET_CHAR_BIT,
			  0, "long_long_float", objfile);
	break;
      }
  return (type);
}


/* Dummy name returned by ada_demangle to indicate that a symbol is
   not supposed to be visible to users. */
char* SUPPRESS_SYMBOL_MARK = " ";

/* True if STR is SUPPRESS_SYMBOL_MARK */
static int
is_suppress_mark (str) 
     const char* str;
{
  return str != NULL && str[0] == ' ';
}

/* Demangle: 
     1. Discard final __{DIGIT}+ or ${DIGIT}+
     2. Convert other instances of embedded "__" to `.'.
     3. Discard leading _ada_.
     4. Convert operator names to the appropriate quoted symbols.
     5. Remove everything after first ___ if it is followed by 
        'X'.
     6. Return special marker (SUPPRESS_SYMBOL_MARK) for symbols that
     should be suppressed.
   The resulting string is valid until the next call of ada_demangle.
  */

static char* demangling_buffer = NULL;
static int demangling_buffer_size = 0;

char *
ada_demangle (mangled)
     const char* mangled;
{
  int i, j;
  int len0;
  const char* p;
  char* demangled;
  int at_start_name;
  int changed;
  
  changed = 0;

  if (STREQN (mangled, "_ada_", 5))
    {
      mangled += 5;
      changed = 1;
    }

  if (mangled[0] == '_')
    return SUPPRESS_SYMBOL_MARK;

  p = strstr (mangled, "___");
  if (p == NULL)
    len0 = strlen (mangled);
  else 
    {
      if (p[3] == 'X')
	{
	  len0 = p - mangled;
	  changed = 1;
	}
      else
	return SUPPRESS_SYMBOL_MARK;
    }

  /* Make demangled big enough for possible expansion by operator name. */
  if (demangling_buffer_size < 2*len0)
    {
      demangling_buffer_size = 2*len0 + 32;
      demangling_buffer = xrealloc (demangling_buffer, demangling_buffer_size);
    }
  demangled = demangling_buffer;

  if (isdigit (mangled[len0 - 1])) {
    for (i = len0-2; i >= 0 && isdigit (mangled[i]); i -= 1)
      ;
    if (i > 1 && mangled[i] == '_' && mangled[i-1] == '_')
      {
	len0 = i - 1;
	changed = 1;
      }
    else if (mangled[i] == '$')
      {
	len0 = i;
	changed = 1;
      }
  }

  for (i = 0, j = 0; i < len0 && ! isalpha (mangled[i]); i += 1, j += 1)
    demangled[j] = mangled[i];

  at_start_name = 1;
  while (i < len0)
    {
      if (at_start_name && mangled[i] == 'O')
	{
	  int k;
	  for (k = 0; ada_opname_table[k].mangled != NULL; k += 1)
	    {
	      int op_len = strlen (ada_opname_table[k].mangled); 
	      if (STREQN (ada_opname_table[k].mangled+1, mangled+i+1, op_len-1)
		  && ! isalnum (mangled[i + op_len]))
		{
		  strcpy (demangled + j, ada_opname_table[k].demangled);
		  at_start_name = 0;
		  changed = 1;
		  i += op_len;
		  j += strlen (ada_opname_table[k].demangled);
		  break;
		}
	    }
	  if (ada_opname_table[k].mangled != NULL)
	    continue;
	}
      at_start_name = 0;

      if (i < len0-2 && mangled[i] == '_' && mangled[i+1] == '_') 
	{
	  demangled[j] = '.';
	  changed = at_start_name = 1;
	  i += 2; j += 1;
	}
      else
	{
	  demangled[j] = mangled[i];
	  i += 1;  j += 1;
	}
    }
  demangled[j] = '\000';

  for (i = 0; demangled[i] != '\0'; i += 1)
    if (isupper (demangled[i]) || demangled[i] == ' ')
      return SUPPRESS_SYMBOL_MARK;

  if (! changed)
    return NULL;
  else
    return demangled;
}

/* Returns non-zero iff sym_name matches name ignoring case, or if a 
   suffix of sym_name that immediately follows a '.' matches name, 
   ignoring case.   Also returns 0 if either argument is NULL. */

int
ada_match_name (sym_name, name)
     const char* sym_name;
     const char* name;
{
  if (sym_name == NULL || name == NULL)
    return 0;
  else
    {
      int len_sym = strlen (sym_name);
      int len_name = strlen (name);
      
      return ((len_name == len_sym 
	       || (len_name < len_sym-1
		   && sym_name[len_sym-len_name-1] == '.'))
	      && strcasecmp (name, sym_name + len_sym - len_name) == 0);
    }
}

/* True (non-zero) iff in Ada mode, the symbol SYM should be
   suppressed in info listings. */

int
ada_suppress_symbol_printing (sym)
     struct symbol *sym;
{
  if (SYMBOL_NAMESPACE (sym) == STRUCT_NAMESPACE)
    return 1;
  else if (SYMBOL_LANGUAGE (sym) == language_ada)
    return 
      SYMBOL_ADA_DEMANGLED_NAME (sym) != NULL 
	 && is_suppress_mark (SYMBOL_ADA_DEMANGLED_NAME (sym));
  else
    return is_suppress_mark (ada_demangle (SYMBOL_SOURCE_NAME (sym)));
}




/* Names of MAX_ADA_DIMENS bounds in P_BOUNDS fields of 
   array descriptors.  */

static char* bound_name[] = {
  "LB0", "UB0", "LB1", "UB1", "LB2", "UB2", "LB3", "UB3", 
  "LB4", "UB4", "LB5", "UB5", "LB6", "UB6", "LB7", "UB7"
};

/* Maximum number of array dimensions we are prepared to handle.  */

#define MAX_ADA_DIMENS (sizeof(bound_name) / (2*sizeof(char*)))

/* Like modify_field, but allows bitpos > wordlength. */

static void
modify_general_field (addr, fieldval, bitpos, bitsize)
     char *addr;
     LONGEST fieldval;
     int bitpos, bitsize;
{
  modify_field (addr + sizeof (LONGEST) * bitpos / (8 * sizeof (LONGEST)), 
		fieldval, bitpos % (8 * sizeof (LONGEST)), 
		bitsize);
}


/* The desc_* routines return primitive portions of array descriptors 
   (fat pointers). */

/* The descriptor or array type, if any, indicated by TYPE; removes
   level of indirection, if needed. */

static struct type*
desc_base_type (type)
     struct type* type;
{
  if (type != NULL && TYPE_CODE (type) == TYPE_CODE_PTR)
    return TYPE_TARGET_TYPE (type);
  else
    return type;
}

/* If TYPE is the type of an array descriptor (fat pointer) or a 
/* pointer to one, the type of its bounds data; otherwise, NULL. */

static struct type*
desc_bounds_type (type)
     struct type* type;
{
  struct type* r;

  type = desc_base_type (type);

  if (type != NULL && TYPE_CODE (type) == TYPE_CODE_STRUCT)
    {
      r = lookup_struct_elt_type (type, "P_BOUNDS", 1);
      if (r != NULL)
	return TYPE_TARGET_TYPE (r);
    }
  return NULL;
}

/* If ARR is an array descriptor (fat pointer), a pointer to its 
   bounds data.   Otherwise NULL. */

static value_ptr
desc_bounds (arr)
     value_ptr arr;
{
  if (desc_bounds_type (VALUE_TYPE (arr)) != NULL)
    return value_struct_elt (&arr, NULL, "P_BOUNDS", NULL, 
			     "Bad GNAT array descriptor");
  return NULL;
}

/* If TYPE is the type of an array-descriptor (fat pointer), the bit */
/* position of the field containing the address of the bounds data. */

static int
desc_bounds_bitpos (type)
     struct type* type;
{
  return TYPE_FIELD_BITPOS (desc_base_type (type), 1);
}

/* If TYPE is the type of an array-descriptor (fat pointer), the bit */
/* size of the field containing the address of the bounds data. */

static int
desc_bounds_bitsize (type)
     struct type* type;
{
  type = desc_base_type (type);

  if (TYPE_FIELD_BITSIZE (type, 1) > 0) 
    return TYPE_FIELD_BITSIZE (type, 1);
  else
    return 8 * TYPE_LENGTH (TYPE_FIELD_TYPE (type, 1));
}


/* If TYPE is the type of an array descriptor (fat pointer) or a 
   pointer to one, the type of its array data (a
   pointer-to-array-with-no-bounds type); otherwise,  NULL.  Use
   ada_type_of_array to get an array type with bounds data. */

static struct type*
desc_data_type (type)
     struct type* type;
{
  type = desc_base_type (type);

  if (type != NULL && TYPE_CODE (type) == TYPE_CODE_STRUCT)
    return lookup_struct_elt_type (type, "P_ARRAY", 1);
  else
    return NULL;
}

/* If ARR is an array descriptor (fat pointer), a pointer to its array
   data.  */

static value_ptr
desc_data (arr)
     value_ptr arr;
{
  if (desc_data_type (VALUE_TYPE (arr)) != NULL)
    return value_struct_elt (&arr, NULL, "P_ARRAY", NULL, 
			     "Bad GNAT array descriptor");
  return NULL;
}


/* If TYPE is the type of an array-descriptor (fat pointer), the bit */
/* position of the field containing the address of the data. */

static int
desc_data_bitpos (type)
     struct type* type;
{
  return TYPE_FIELD_BITPOS (desc_base_type (type), 0);
}

/* If TYPE is the type of an array-descriptor (fat pointer), the bit */
/* size of the field containing the address of the data. */

static int
desc_data_bitsize (type)
     struct type* type;
{
  type = desc_base_type (type);

  if (TYPE_FIELD_BITSIZE (type, 0) > 0)
    return TYPE_FIELD_BITSIZE (type, 0);
  else 
    return 8 * TYPE_LENGTH (TYPE_FIELD_TYPE (type, 0));
}


/* If BOUNDS is an array-bounds structure (or pointer to one), return 
   the Ith lower bound stored in it, if WHICH is 0, and the Ith upper
   bound, if WHICH is 1.  The first bound is I=1. */

static value_ptr
desc_one_bound (bounds, i, which)
     value_ptr bounds;
     int i;
     int which;
{
  return value_struct_elt (&bounds, NULL, bound_name[2*i+which-2], NULL,
			   "Bad GNAT array descriptor bounds");
}

/* If BOUNDS is an array-bounds structure type, return the bit position
   of the Ith lower bound stored in it, if WHICH is 0, and the Ith upper
   bound, if WHICH is 1.  The first bound is I=1. */

static int
desc_bound_bitpos (type, i, which)
     struct type* type;
     int i;
     int which;
{
  return TYPE_FIELD_BITPOS (desc_base_type (type), 2*i+which-2);
}

/* If BOUNDS is an array-bounds structure type, return the bit field size
   of the Ith lower bound stored in it, if WHICH is 0, and the Ith upper
   bound, if WHICH is 1.  The first bound is I=1. */

static int
desc_bound_bitsize (type, i, which)
     struct type* type;
     int i;
     int which;
{
  type = desc_base_type (type);

  if (TYPE_FIELD_BITSIZE (type, 2*i+which-2) > 0)
    return TYPE_FIELD_BITSIZE (type, 2*i+which-2);
  else 
    return 8 * TYPE_LENGTH (TYPE_FIELD_TYPE (type, 2*i+which-2));
}

/* If TYPE is the type of an array-bounds structure, the type of its */
/* Ith bound (numbering from 1). Otherwise, NULL. */ 

static struct type* 
desc_index_type (type, i)
     struct type* type;
     int i;
{
  type = desc_base_type (type);

  if (TYPE_CODE (type) == TYPE_CODE_STRUCT)
    return lookup_struct_elt_type (type, bound_name[2*i-2], 1);
  else 
    return NULL;
}

/* The number of index positions in the array-bounds type TYPE.  0 */
/* if TYPE is NULL. */

static int
desc_arity (type)
     struct type* type;
{
  type = desc_base_type (type);

  if (type != NULL)
    return TYPE_NFIELDS (type) / 2;
  return 0;
}


/* Non-zero iff type is a simple array type (or pointer to one). */

int
ada_is_simple_array (type)
     struct type* type;
{
  return (TYPE_CODE (type) == TYPE_CODE_ARRAY
	  || (TYPE_CODE (type) == TYPE_CODE_PTR
	      && TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_ARRAY));
}

/* Non-zero iff type belongs to a GNAT array descriptor. */

int
ada_is_array_descriptor (type)
     struct type* type;
{
  struct type *data_type = desc_data_type (type);

  return 
    data_type != NULL
    && TYPE_CODE (data_type) == TYPE_CODE_PTR
    && TYPE_TARGET_TYPE (data_type) != NULL
    && TYPE_CODE (TYPE_TARGET_TYPE (data_type)) == TYPE_CODE_ARRAY
    && desc_bounds_type (type) != NULL 
    && desc_arity (type) > 0;
}

/* Non-zero iff type is a partially mal-formed GNAT array
   descriptor.  (FIXME: This is to compensate for some problems with 
   debugging output from GNAT.  Re-examine periodically to see if it
   is still needed. */

int
ada_is_bogus_array_descriptor (type)
     struct type *type;
{
  return 
    type != NULL
    && TYPE_CODE (type) == TYPE_CODE_STRUCT
    && (lookup_struct_elt_type (type, "P_BOUNDS", 1) != NULL
	|| lookup_struct_elt_type (type, "P_ARRAY", 1) != NULL)
    && ! ada_is_array_descriptor (type);
}


/* If ARR has a record type in the form of a standard GNAT array descriptor, 
   returns the type of the array data described---specifically, a 
   pointer-to-array type.  If BOUNDS is non-zero, the bounds data are filled 
   in from the descriptor; otherwise, they are left unspecified.  The
   result is simply the type of ARR if ARR is not a descriptor.  The
   result is good until next cleanup. */

struct type*
ada_type_of_array (arr, bounds)
     value_ptr arr;
     int bounds;
{
  if (! ada_is_array_descriptor (VALUE_TYPE (arr)))
    return VALUE_TYPE (arr);
  
  if (! bounds)
    return TYPE_TARGET_TYPE (desc_data_type (VALUE_TYPE (arr)));
  else
    {
      struct type* elt_type;
      int arity;
      struct type* range;
      struct type* array_type;
      struct type* array_ptr_type;
      value_ptr descriptor, temp, low, high;

      elt_type = ada_array_element_type (VALUE_TYPE (arr));
      arity = ada_array_arity (VALUE_TYPE (arr));

      if (elt_type == NULL || arity == 0) 
	return VALUE_TYPE (arr);

      descriptor = desc_bounds (arr);
      while (arity > 0) {
	low = desc_one_bound (descriptor, arity, 0);
	high = desc_one_bound (descriptor, arity, 1);
	arity -= 1;
	range = alloc_type (NULL);
	array_type = alloc_type (NULL);
	make_cleanup (free, range);
	make_cleanup (free, array_type);

	create_range_type (range, VALUE_TYPE (low), 
			   (int) value_as_long (low), 
			   (int) value_as_long (high));
	elt_type = create_array_type (array_type, elt_type, range);
      }

      array_ptr_type = alloc_type (NULL);
      make_cleanup (free, array_ptr_type);
      return make_pointer_type (elt_type, &array_ptr_type);
    }
}

/* If ARR has a record type in the form of a standard GNAT array descriptor, 
   returns a value_ptr to a pointer to the array data described, cast as 
   a pointer-to-array type with the appropriate bounds.   The resulting 
   value is good to next cleanup.  Simply returns ARR if it is not of 
   the right form. */

value_ptr
ada_coerce_to_simple_array_ptr (arr)
     value_ptr arr;
{
  if (ada_is_array_descriptor (VALUE_TYPE (arr)))
    return value_cast (ada_type_of_array (arr, 1), desc_data (arr));
  else
    return arr;
}

/* If ARR has a record type in the form of a standard GNAT array descriptor, 
   returns a (pointer to) the array data described, cast as an array type 
   with the appropriate bounds.   The resulting value is good to next 
   cleanup.  Simply returns ARR if it is not of the right form. */

value_ptr
ada_coerce_to_simple_array (arr)
     value_ptr arr;
{
  if (ada_is_array_descriptor (VALUE_TYPE (arr)))
    return value_ind (ada_coerce_to_simple_array_ptr (arr));
  else 
    return arr;
}

/* The value of the element of array ARR at the ARITY indices given in IND. 
   ARR may be either a simple array, GNAT array descriptor, or pointer 
   thereto.  */

value_ptr
ada_value_subscript (arr, arity, ind)
     value_ptr arr;
     int arity;
     value_ptr* ind;
{
  int k;
  value_ptr elt;

  elt = ada_coerce_to_simple_array (arr);
  for (k = 0; k < arity; k += 1)
    {
      if (TYPE_CODE (VALUE_TYPE (elt)) != TYPE_CODE_ARRAY)
	error("too many subscripts (%d expected)", k);
      elt = value_subscript (elt, ind[k]);
    }
  return elt;
}

/* If type is a record type in the form of a standard GNAT array
   descriptor, returns the number of dimensions for type.  If arr is a
   simple array, returns the number of "array of"s that prefix its
   type designation. Otherwise, returns 0. */

int
ada_array_arity (type)
     struct type* type;
{
  int arity;

  type = desc_base_type (type);

  arity = 0;
  if (TYPE_CODE (type) == TYPE_CODE_STRUCT) 
    return desc_arity (desc_bounds_type (type));
  else 
    while (TYPE_CODE (type) == TYPE_CODE_ARRAY) 
      {
	arity += 1;
	type = TYPE_TARGET_TYPE (type);
      }
	    
  return arity;
}

/* If type is a record type in the form of a standard GNAT array
   descriptor, returns the element type for type. If it is a simple
   array, returns the ultimate element type (after stripping all
   "array of" prefixes), otherwise returns NULL. */

struct type*
ada_array_element_type (type)
     struct type* type;
{
  type = desc_base_type (type);

  if (TYPE_CODE (type) == TYPE_CODE_STRUCT) 
    {
      int k;
      struct type* p_array_type;

      p_array_type = desc_data_type (type);

      k = ada_array_arity (type);
      if (k == 0)
	return NULL;
      
      /* Initially p_array_type = (*elt_type)[]...(k times)...[] */
      while (k >= 0 && p_array_type != NULL) 
	{
	  p_array_type = TYPE_TARGET_TYPE (p_array_type);
	  k -= 1;
	}
      return p_array_type;
    }
  else if (TYPE_CODE (type) == TYPE_CODE_ARRAY)
    {
      while (TYPE_CODE (type) == TYPE_CODE_ARRAY)
	type = TYPE_TARGET_TYPE (type);
      return type;
    }

  return NULL;
}

/* The type of nth index in arrays of given type (n numbering from 1).  Does 
   not examine memory. */

struct type*
ada_index_type (type, n)
     struct type* type;
     int n;
{
  type = desc_base_type (type);

  if (n > ada_array_arity (type))
    return NULL;

  if (ada_is_simple_array (type))
    {
      int i;

      for (i = 1; i < n; i += 1)
	type = TYPE_TARGET_TYPE (type);

      return TYPE_TARGET_TYPE (TYPE_FIELD_TYPE (type, 0));
    }
  else 
    return desc_index_type (desc_bounds_type (type), n);
}

/* Given that arr is an array value, returns the lower bound of the
   nth index (numbering from 1) if which is 0, and the upper bound if
   which is 1. */

value_ptr
ada_array_bound (arr, n, which)
     value_ptr arr;
     int n; 
     int which;
{
  if (ada_is_simple_array (VALUE_TYPE (arr))) 
    {
      struct type* type;
      struct type* range_type;
      struct type* index_type;

      if (TYPE_CODE (VALUE_TYPE (arr)) == TYPE_CODE_PTR)
	type = TYPE_TARGET_TYPE (VALUE_TYPE (arr));
      else
	type = VALUE_TYPE (arr);
      while (n > 1) 
	{
	  type = TYPE_TARGET_TYPE (type);
	  n -= 1;
	}

      range_type = TYPE_INDEX_TYPE (type);
      index_type = TYPE_TARGET_TYPE (range_type);
      if (TYPE_CODE (index_type) == TYPE_CODE_UNDEF)
	  index_type = builtin_type_long;
      return 
	value_from_longest (index_type,
			    (LONGEST) (which == 0 
				       ? TYPE_LOW_BOUND (range_type)
				       : TYPE_HIGH_BOUND (range_type)));
    }
  else
    return desc_one_bound (desc_bounds (arr), n, which);
}

/* Given that arr is an array value, returns the length of the
   nth index.  Does not work for arrays indexed by enumeration types with 
   representation clauses at the moment. */

value_ptr
ada_array_length (arr, n)
     value_ptr arr;
     int n; 
{
  if (ada_is_simple_array (VALUE_TYPE (arr))) 
    {
      struct type* type;
      struct type* range_type;
      struct type* index_type;

      if (TYPE_CODE (VALUE_TYPE (arr)) == TYPE_CODE_PTR)
	type = TYPE_TARGET_TYPE (VALUE_TYPE (arr));
      else
	type = VALUE_TYPE (arr);
      while (n > 1) 
	{
	  type = TYPE_TARGET_TYPE (type);
	  n -= 1;
	}

      range_type = TYPE_INDEX_TYPE (type);
      index_type = TYPE_TARGET_TYPE (range_type);
      if (TYPE_CODE (index_type) == TYPE_CODE_UNDEF)
	  index_type = builtin_type_long;
      return 
	value_from_longest (builtin_type_ada_int,
			    (LONGEST) TYPE_HIGH_BOUND (range_type)
			    - (LONGEST) TYPE_LOW_BOUND (range_type)
			    + 1);
    }
  else
    {
      return 
	value_from_longest (builtin_type_ada_int,
			    value_as_long (desc_one_bound (desc_bounds (arr),
							   n, 1))
			    - value_as_long (desc_one_bound (desc_bounds (arr),
							     n, 0))
			    + 1);
    }      
}


/* Name resolution */

/* The "demangled" name for the user-definable Ada operator corresponding
   to op. */

static const char*
ada_op_name (op)
     enum exp_opcode op;
{
  int i;

  for (i = 0; ada_opname_table[i].mangled != NULL; i += 1)
    {
      if (ada_opname_table[i].op == op)
	return ada_opname_table[i].demangled;
    }
  error ("Could not find operator name for opcode");
}


/* Same as evaluate_type (*EXP), but resolves ambiguous symbol 
   references (OP_UNRESOLVED_VALUES) and converts operators that are 
   user-defined into appropriate function calls.  The variable 
   unresolved_names contains a list of character strings referenced by 
   expout that should be freed.  May change (expand) *EXP.  */

void
ada_resolve (expp)
     struct expression** expp;
{
  int pc;
  pc = 0;
  ada_resolve_subexp (expp, &pc, 1);
}

/* Resolve the operator of the subexpression expression beginning at 
   position *POS of *EXP. "Resolving" consists of replacing
   OP_UNRESOLVED_VALUE with an appropriate OP_VAR_VALUE, replacing
   built-in operators with function calls to user-defined operators,
   where appropriate, and (when DEPROCEDURE_P is non-zero), converting
   function-valued variables into parameterless calls.  May expand EXP.   */

static value_ptr
ada_resolve_subexp (expp, pos, deprocedure_p) 
     struct expression** expp;
     int *pos;
     int deprocedure_p;
{
  int pc = *pos;
  int i;
  struct expression* exp;	/* Convenience: == *expp */
  enum exp_opcode op = (*expp)->elts[pc].opcode;
  value_ptr* argvec;		/* Vector of operand types (alloca'ed). */
  int nargs;			/* Number of operands */

  nargs = 0;
  exp = *expp;

  /* Pass one: resolve operands, saving their types and updating *pos. */
  switch (op)
    {
    case OP_VAR_VALUE:
    case OP_UNRESOLVED_VALUE:
      *pos += 4;
      break;

    case OP_FUNCALL:
      nargs = longest_to_int (exp->elts[pc + 1].longconst) + 1;
      if (exp->elts[pc+3].opcode == OP_UNRESOLVED_VALUE) 	
	{
	  *pos += 7;

	  argvec = (value_ptr *) alloca (sizeof (value_ptr) * (nargs + 1));
	  for (i = 0; i < nargs-1; i += 1)
	    argvec[i] = ada_resolve_subexp (expp, pos, 1);
	  argvec[i] = NULL;
	}
      else
	{
	  *pos += 3;
	  ada_resolve_subexp (expp, pos, 0);
	  for (i = 1; i < nargs; i += 1)
	    ada_resolve_subexp (expp, pos, 1);
	}
      exp = *expp;
      break;

    case OP_ATTRIBUTE:
      nargs = longest_to_int (exp->elts[pc + 1].longconst) + 1;
      *pos += 4;
      for (i = 0; i < nargs; i += 1)
	ada_resolve_subexp (expp, pos, 1);
      exp = *expp;
      break;

    case UNOP_ADDR:
      nargs = 1;
      *pos += 1;
      ada_resolve_subexp (expp, pos, 0);
      exp = *expp;
      break;

    default:
      switch (op) 
	{
	default:
	  error ("Unexpected operator during name resolution");
	case UNOP_CAST:
	case UNOP_ADDR:
	case UNOP_MBR:
	  nargs = 1;
	  *pos += 3;
	  break;
      
	case BINOP_ADD:
	case BINOP_SUB:
	case BINOP_MUL:
	case BINOP_DIV:
	case BINOP_REM:
	case BINOP_MOD:
	case BINOP_EXP:
	case BINOP_CONCAT:
	case BINOP_LOGICAL_AND:
	case BINOP_LOGICAL_OR:
	case BINOP_BITWISE_AND:
	case BINOP_BITWISE_IOR:
	case BINOP_BITWISE_XOR:

	case BINOP_EQUAL:
	case BINOP_NOTEQUAL:
	case BINOP_LESS:
	case BINOP_GTR:
	case BINOP_LEQ:
	case BINOP_GEQ:

	case BINOP_REPEAT:
	case BINOP_SUBSCRIPT:
	case BINOP_ASSIGN:
	case BINOP_COMMA:
	  nargs = 2;
	  *pos += 1;
	  break;

	case UNOP_NEG:
	case UNOP_PLUS:
	case UNOP_LOGICAL_NOT:
	case UNOP_ABS:
	case UNOP_IND:
	  nargs = 1;
	  *pos += 1;
	  break;

	case OP_LONG:
	case OP_DOUBLE:
	case OP_VAR_VALUE:
	  *pos += 4;
	  break;

	case OP_TYPE:
	case OP_BOOL:
	case OP_LAST:
	case OP_REGISTER:
	case OP_INTERNALVAR:
	  *pos += 3;
	  break;

	case UNOP_MEMVAL:
	  *pos += 3;
	  nargs = 1;
	  break;

	case STRUCTOP_STRUCT:
	case STRUCTOP_PTR:
	  nargs = 1;
	  *pos += 4 + BYTES_TO_EXP_ELEM (exp->elts[pc + 1].longconst + 1);
	  break;

	case OP_ARRAY:
	  *pos += 4;  
	  nargs = longest_to_int (exp->elts[pc + 2].longconst) + 1;
	  nargs -= longest_to_int (exp->elts[pc + 1].longconst);
	  /* A null array contains one dummy element to give the type. */
	  if (nargs == 0)
	    nargs = 1;
	  break;

	case TERNOP_SLICE:
	case TERNOP_MBR:
	  *pos += 1;
	  nargs = 3;
	  break;

	case BINOP_MBR:
	  *pos += 3;
	  nargs = 2;
	  break;
	}

      argvec = (value_ptr *) alloca (sizeof (value_ptr) * (nargs + 1));
      for (i = 0; i < nargs; i += 1)
	argvec[i] = ada_resolve_subexp (expp, pos, 1);
      argvec[i] = NULL;
      exp = *expp;
      break;
    }

  /* Pass two: perform any resolution on principal operator. */
  switch (op)
    {
    default:
      break;

    case OP_UNRESOLVED_VALUE:
      {
	struct symbol** candidate_syms;
	struct block** candidate_blocks;
	int n_candidates;

	n_candidates = ada_lookup_symbol_list (exp->elts[pc + 2].name,
					       exp->elts[pc + 1].block,
					       VAR_NAMESPACE,
					       &candidate_syms,
					       &candidate_blocks);
	
	if (n_candidates == 0)
	  error ("No definition found for %s", exp->elts[pc + 2].name);
	else if (n_candidates == 1)
	  i = 0;
	else if (deprocedure_p 
		 && ! is_nonfunction (candidate_syms, n_candidates))
	  {
	    i = ada_resolve_function (candidate_syms, candidate_blocks,
				      n_candidates, NULL, 0,
				      exp->elts[pc + 2].name);
	    if (i < 0) 
	      error ("Could not find a match for %s", exp->elts[pc + 2].name);
	  }
	else 
	  {
	    printf_filtered ("Multiple matches for %s\n", 
			     exp->elts[pc+2].name);
	    user_select_syms (candidate_syms, candidate_blocks, 
			      n_candidates, 1);
	    i = 0;
	  }

	exp->elts[pc].opcode = exp->elts[pc + 3].opcode = OP_VAR_VALUE;
	exp->elts[pc + 1].block = candidate_blocks[i];
	exp->elts[pc + 2].symbol = candidate_syms[i];
	if (innermost_block == NULL ||
	    contained_in (candidate_blocks[i], innermost_block))
	  innermost_block = candidate_blocks[i];
      }
      /* FALL THROUGH */

    case OP_VAR_VALUE:
      if (deprocedure_p && 
	  TYPE_CODE (SYMBOL_TYPE (exp->elts[pc+2].symbol)) == TYPE_CODE_FUNC)
	{
	  replace_operator_with_call (expp, pc, 0, 0, 
				      exp->elts[pc+2].symbol,
				      exp->elts[pc+1].block);
	  exp = *expp;
	}
      break;

    case OP_FUNCALL:
      {
	if (exp->elts[pc+3].opcode == OP_UNRESOLVED_VALUE) 	
	  {
	    struct symbol** candidate_syms;
	    struct block** candidate_blocks;
	    int n_candidates;

	    n_candidates = ada_lookup_symbol_list (exp->elts[pc + 5].name,
						   exp->elts[pc + 4].block,
						   VAR_NAMESPACE,
						   &candidate_syms,
						   &candidate_blocks);
	    if (n_candidates == 1)
	      i = 0;
	    else
	      {
		i = ada_resolve_function (candidate_syms, candidate_blocks,
					  n_candidates, argvec, nargs-1,
					  exp->elts[pc + 5].name);
		if (i < 0) 
		  error ("Could not find a match for %s", 
			 exp->elts[pc + 5].name);
	      }

	    exp->elts[pc + 3].opcode = exp->elts[pc + 6].opcode = OP_VAR_VALUE;
	    exp->elts[pc + 4].block = candidate_blocks[i];
	    exp->elts[pc + 5].symbol = candidate_syms[i];
	    if (innermost_block == NULL ||
		contained_in (candidate_blocks[i], innermost_block))
	      innermost_block = candidate_blocks[i];
	  }
      }
      break;
    case BINOP_ADD:
    case BINOP_SUB:
    case BINOP_MUL:
    case BINOP_DIV:
    case BINOP_REM:
    case BINOP_MOD:
    case BINOP_CONCAT:
    case BINOP_BITWISE_AND:
    case BINOP_BITWISE_IOR:
    case BINOP_BITWISE_XOR:
    case BINOP_EQUAL:
    case BINOP_NOTEQUAL:
    case BINOP_LESS:
    case BINOP_GTR:
    case BINOP_LEQ:
    case BINOP_GEQ:
    case BINOP_EXP:
    case UNOP_NEG:
    case UNOP_PLUS:
    case UNOP_LOGICAL_NOT:
    case UNOP_ABS:
      if (possible_user_operator_p (op, argvec))
	{
	  struct symbol** candidate_syms;
	  struct block** candidate_blocks;
	  int n_candidates;

	  n_candidates = ada_lookup_symbol_list (ada_op_name (op),
						 (struct block*) NULL,
						 VAR_NAMESPACE,
						 &candidate_syms,
						 &candidate_blocks);
	  i = ada_resolve_function (candidate_syms, candidate_blocks,
				    n_candidates, argvec, nargs,
				    ada_op_name (op));
	  if (i < 0)
	    break;

	  replace_operator_with_call (expp, pc, nargs, 1,
				      candidate_syms[i], candidate_blocks[i]);
	  exp = *expp;
	}
      break;
    }

  *pos = pc;
  return evaluate_subexp_type (exp, pos);
}

/* Return non-zero if formal type FTYPE matches actual type ATYPE.  If
   MAY_DEREF is non-zero, the formal may be a pointer and the  actual 
   a non-pointer. */ 
/* The term "match" here is rather loose.  The match is heuristic and
   liberal. */

static int
ada_type_match (ftype, atype, may_deref)
     struct type* ftype;
     struct type* atype;
     int may_deref;
{
  if (TYPE_CODE (ftype) == TYPE_CODE_VOID 
      || TYPE_CODE (atype) == TYPE_CODE_VOID)
    return 1;

  switch (TYPE_CODE (ftype)) 
    {
    default:
      return 1;
    case TYPE_CODE_PTR:
      if (TYPE_CODE (atype) == TYPE_CODE_PTR)
	return ada_type_match (TYPE_TARGET_TYPE (ftype),
			       TYPE_TARGET_TYPE (atype), 0);
      else return (may_deref && 
		   ada_type_match (TYPE_TARGET_TYPE (ftype), atype, 0));
    case TYPE_CODE_INT:
    case TYPE_CODE_ENUM:
    case TYPE_CODE_RANGE:
      switch (TYPE_CODE (atype))
	{
	case TYPE_CODE_INT:
	case TYPE_CODE_ENUM:
	case TYPE_CODE_RANGE:
	  return 1;
	default:
	  return 0;
	}

    case TYPE_CODE_ARRAY:
      return (TYPE_CODE (atype) == TYPE_CODE_ARRAY 
	      || ada_is_array_descriptor (atype));

    case TYPE_CODE_STRUCT:
      if (ada_is_array_descriptor (ftype))
	return (TYPE_CODE (atype) == TYPE_CODE_ARRAY 
		|| ada_is_array_descriptor (atype));
      else
	return (TYPE_CODE (atype) == TYPE_CODE_STRUCT
		&& ! ada_is_array_descriptor (atype));

    case TYPE_CODE_UNION:
    case TYPE_CODE_FLT:
      return (TYPE_CODE (atype) == TYPE_CODE (ftype));
    }
}

/* Return non-zero if the formals of FUNC "sufficiently match" the
   vector of actual argument types ACTUALS of size N_ACTUALS.  FUNC
   may also be an enumeral, in which case it is treated as a 0-
   argument function. */

static int
ada_args_match (func, actuals, n_actuals)
     struct symbol* func;
     value_ptr* actuals;
     int n_actuals;
{
  int i;
  struct type* func_type = SYMBOL_TYPE (func);

  if (SYMBOL_CLASS (func) == LOC_CONST && 
      TYPE_CODE (func_type) == TYPE_CODE_ENUM)
    return (n_actuals == 0);
  else if (func_type == NULL || TYPE_CODE (func_type) != TYPE_CODE_FUNC)
    return 0;

  if (TYPE_NFIELDS (func_type) != n_actuals)
    return 0;

  for (i = 0; i < n_actuals; i += 1)
    {
      struct type* ftype = TYPE_FIELD_TYPE (func_type, i);
      struct type* atype = VALUE_TYPE (actuals[i]);

      if (! ada_type_match (TYPE_FIELD_TYPE (func_type, i), 
			    VALUE_TYPE (actuals[i]), 1))
	return 0;
    }
  return 1;
}

/* Return the index in SYMS[0..NSYMS-1] of symbol for the 
   function (if any) that matches the types of the NARGS arguments in
   ARGS.  Asks the user if there is more than one.  Returns -1
   if there is no such symbol or none is selected.  NAME is used
   solely for messages.   May re-arrange and modify SYMS in
   the process; the index returned is for the modified vector.  BLOCKS
   is modified in parallel to SYMS. */

int
ada_resolve_function (syms, blocks, nsyms, args, nargs, name)
     struct symbol* syms[];
     struct block* blocks[];
     value_ptr* args;
     int nsyms, nargs;
     const char* name;
{
  int k;
  int m;			/* Number of hits */

  m = 0;
  for (k = 0; k < nsyms; k += 1)
    {
      struct type* type = SYMBOL_TYPE (syms[k]);

      if (ada_args_match (syms[k], args, nargs))
	{
	  syms[m] = syms[k];
	  if (blocks != NULL)
	    blocks[m] = blocks[k];
	  m += 1;
	}
    }

  if (m == 0)
    return -1;
  else if (m > 1)
    {
      printf_filtered ("Multiple matches for %s\n", name);
      user_select_syms (syms, blocks, m, 1);
      return 0;
    }
  return 0;
}

/* Given a list of NSYMS symbols in SYMS and corresponding blocks in */
/* BLOCKS, select up to MAX_RESULTS>0 by asking the user (if */
/* necessary), returning the number selected, and setting the first */
/* elements of SYMS and BLOCKS to the selected symbols and */
/* corresponding blocks.  Error if no symbols selected.   BLOCKS may */
/* be NULL, in which case it is ignored. */

/* NOTE: Adapted from decode_line_2 in symtab.c, with which it ought
   to be re-integrated one of these days. */

int
user_select_syms (syms, blocks, nsyms, max_results)
     struct symbol* syms[];
     struct block* blocks[];
     int nsyms;
     int max_results;
{
  int i;
  int num;
  int first_choice;
  char* args;
  const char* prompt;
  int* chosen;
  int n_chosen;

  if (max_results < 1)
    error ("Request to select 0 symbols!");
  if (nsyms <= 1)
    return nsyms;

  printf_unfiltered("[0] cancel\n");
  first_choice = (max_results == 1) ? 1 : 2;
  if (max_results > 1)
      printf_unfiltered("[1] all\n");

  for (i = 0; i < nsyms; i += 1)
    {
      if (syms[i] == NULL)
	continue;

      if (SYMBOL_CLASS (syms[i]) == LOC_BLOCK)
	{
	  struct symtab_and_line sal = find_function_start_sal (syms[i], 1);
	  printf_unfiltered ("[%d] %s at %s:%d\n",
			     i + first_choice, 
			     SYMBOL_SOURCE_NAME (syms[i]),
			     sal.symtab == NULL 
			       ? "<no source file available>"
			       : sal.symtab->filename, 
			     sal.line);
	  continue;
	}
      else 
	{
	  int is_enumeral = 
	    (SYMBOL_CLASS (syms[i]) == LOC_CONST
	     && SYMBOL_TYPE (syms[i]) != NULL
	     && TYPE_CODE (SYMBOL_TYPE (syms[i])) == TYPE_CODE_ENUM);
	  struct symtab* symtab = symtab_for_sym (syms[i]);

	  if (SYMBOL_LINE (syms[i]) != 0 && symtab != NULL)
	    printf_unfiltered ("[%d] %s at %s:%d\n",
			       i + first_choice,
			       SYMBOL_SOURCE_NAME (syms[i]),
			       symtab->filename, SYMBOL_LINE (syms[i]));
	  else if (symtab != NULL)
	    printf_unfiltered (is_enumeral 
			       ? "[%d] %s in %s (enumeral)\n"
			       : "[%d] %s at %s:?\n",
			       i + first_choice,
			       SYMBOL_SOURCE_NAME (syms[i]),
			       symtab->filename);
	  else
	    printf_unfiltered (is_enumeral
			       ? "[%d] %s (enumeral)\n"
			       : "[%d] %s at ?\n",
			       i + first_choice, SYMBOL_SOURCE_NAME (syms[i]));
	}
    }
  
  prompt = getenv ("PS2");
  if (prompt == NULL)
    prompt = ">";

  printf_unfiltered ("%s ", prompt);
  gdb_flush (gdb_stdout);

  args = command_line_input ((char *) NULL, 0, "overload-choice");
  
  if (args == NULL)
    error_no_arg ("one or more choice numbers");

  chosen = (int*) alloca (sizeof(int) * nsyms);
  n_chosen = 0;

  /* Set chosen[0 .. n_chosen-1] to the users' choices in ascending 
     order, as given in args.   Choices are validated. */
  while (1)
    {
      char* args2;
      int choice, j;

      while (isspace (*args))
	args += 1;
      if (*args == '\0' && n_chosen == 0)
	error_no_arg ("one or more choice numbers");
      else if (*args == '\0')
	break;

      choice = strtol (args, &args2, 10);
      if (args == args2 || choice < 0 || choice > nsyms + first_choice - 1)
	error ("Argument must be choice number");
      args = args2;

      if (choice == 0) 
	error ("cancelled");

      if (choice < first_choice)
	{
	  n_chosen = nsyms;
	  for (j = 0; j < nsyms; j += 1)
	    chosen[j] = j;
	  break;
	}
      choice -= first_choice;

      for (j = n_chosen-1; j >= 0 && choice < chosen[j]; j -= 1)
	{}

      if (j < 0 || choice != chosen[j])
	{
	  int k;
	  for (k = n_chosen-1; k > j; k -= 1)
	    chosen[k+1] = chosen[k];
	  chosen[j+1] = choice;
	  n_chosen += 1;
	}
    }

  if (n_chosen > max_results)
    error ("Select no more than %d of the above", max_results);
  
  for (i = 0; i < n_chosen; i += 1)
    {
      syms[i] = syms[chosen[i]];
      if (blocks != NULL) 
	blocks[i] = blocks[chosen[i]];
    }

  return n_chosen;
}

/* Replace the operator of length OPLEN at position PC in *EXPP with a call
/* on the function identified by SYM and BLOCK, and taking NARGS */
/* arguments.  Update *EXPP as needed to hold more space. */

static void
replace_operator_with_call (expp, pc, nargs, oplen, sym, block)
     struct expression** expp;
     int pc, nargs, oplen;
     struct symbol* sym;
     struct block* block; 
{
  /* A new expression, with 6 more elements (3 for funcall, 4 for function
     symbol, -oplen for operator being replaced). */
  struct expression* newexp = (struct expression*)
    xmalloc (sizeof (struct expression)
	     + EXP_ELEM_TO_BYTES ((*expp)->nelts + 7 - oplen));
  struct expression* exp = *expp;

  newexp->nelts = exp->nelts + 7 - oplen;
  newexp->language_defn = exp->language_defn;
  memcpy (newexp->elts, exp->elts, EXP_ELEM_TO_BYTES (pc));
  memcpy (newexp->elts + pc + 7, exp->elts + pc + oplen, 
	  EXP_ELEM_TO_BYTES (exp->nelts - pc - oplen));

  newexp->elts[pc].opcode = newexp->elts[pc + 2].opcode = OP_FUNCALL;
  newexp->elts[pc + 1].longconst = (LONGEST) nargs;

  newexp->elts[pc + 3].opcode = newexp->elts[pc + 6].opcode = OP_VAR_VALUE;
  newexp->elts[pc + 4].block = block;
  newexp->elts[pc + 5].symbol = sym;

  *expp = newexp;
  free (exp);
}  

/* Type-class predicates */

/* True iff TYPE is numeric (i.e., an INT, RANGE (of numeric type), or */
/* FLOAT.) */

static int
numeric_type_p (type)
     struct type* type;
{
  if (type == NULL)
    return 0;
  else {
    switch (TYPE_CODE (type))
      {
      case TYPE_CODE_INT:
      case TYPE_CODE_FLT:
	return 1;
      case TYPE_CODE_RANGE:
	return (type == TYPE_TARGET_TYPE (type)
		|| numeric_type_p (TYPE_TARGET_TYPE (type)));
      default:
	return 0;
      }
  }
}

/* True iff TYPE is integral (an INT or RANGE of INTs). */

static int
integer_type_p (type)
     struct type* type;
{
  if (type == NULL)
    return 0;
  else {
    switch (TYPE_CODE (type))
      {
      case TYPE_CODE_INT:
	return 1;
      case TYPE_CODE_RANGE:
	return (type == TYPE_TARGET_TYPE (type) 
		|| integer_type_p (TYPE_TARGET_TYPE (type)));
      default:
	return 0;
      }
  }
}

/* True iff TYPE is scalar (INT, RANGE, FLOAT, ENUM). */

static int
scalar_type_p (type)
     struct type* type;
{
  if (type == NULL)
    return 0;
  else {
    switch (TYPE_CODE (type))
      {
      case TYPE_CODE_INT:
      case TYPE_CODE_RANGE:
      case TYPE_CODE_ENUM:
      case TYPE_CODE_FLT:
	return 1;
      default:
	return 0;
      }
  }
}

/* True iff TYPE is discrete (INT, RANGE, ENUM). */

static int
discrete_type_p (type)
     struct type* type;
{
  if (type == NULL)
    return 0;
  else {
    switch (TYPE_CODE (type))
      {
      case TYPE_CODE_INT:
      case TYPE_CODE_RANGE:
      case TYPE_CODE_ENUM:
	return 1;
      default:
	return 0;
      }
  }
}

/* Returns non-zero if OP with operatands in the vector ARGS could be
   a user-defined function. Errs on the side of pre-defined operators
   (i.e., result 0). */

static int
possible_user_operator_p (op, args)
     enum exp_opcode op;
     value_ptr args[];
{
  struct type* type0 = VALUE_TYPE (args[0]);
  struct type* type1 = 
    (args[1] == NULL) ? NULL : VALUE_TYPE (args[1]);
  
  switch (op)
    {
    default:
      return 0;

    case BINOP_ADD:
    case BINOP_SUB:
    case BINOP_MUL:
    case BINOP_DIV:
      return (! (numeric_type_p (type0) && numeric_type_p (type1)));

    case BINOP_REM:
    case BINOP_MOD:
    case BINOP_BITWISE_AND:
    case BINOP_BITWISE_IOR:
    case BINOP_BITWISE_XOR:
      return (! (integer_type_p (type0) && integer_type_p (type1)));

    case BINOP_EQUAL:
    case BINOP_NOTEQUAL:
    case BINOP_LESS:
    case BINOP_GTR:
    case BINOP_LEQ:
    case BINOP_GEQ:
      return (! (scalar_type_p (type0) && scalar_type_p (type1)));

    case BINOP_CONCAT:
      return ((TYPE_CODE (type0) != TYPE_CODE_ARRAY && 
	       (TYPE_CODE (type0) != TYPE_CODE_PTR || 
		TYPE_CODE (TYPE_TARGET_TYPE (type0)) != TYPE_CODE_ARRAY))
	      || (TYPE_CODE (type1) != TYPE_CODE_ARRAY && 
		  (TYPE_CODE (type1) != TYPE_CODE_PTR || 
		   TYPE_CODE (TYPE_TARGET_TYPE (type1)) != TYPE_CODE_ARRAY)));

    case BINOP_EXP:
      return (! (numeric_type_p (type0) && integer_type_p (type1)));

    case UNOP_NEG:
    case UNOP_PLUS:
    case UNOP_LOGICAL_NOT:
    case UNOP_ABS:      
      return (! numeric_type_p (type0));

    }
}





/* Copy VAL onto the stack, using and updating *SP as the stack 
   pointer. Return VAL as an lvalue. */

static value_ptr
place_on_stack (val, sp)
     value_ptr val;
     CORE_ADDR* sp;
{
  CORE_ADDR old_sp = *sp;

#ifdef STACK_ALIGN
  *sp = push_bytes (*sp, VALUE_CONTENTS_RAW (val), 
		    STACK_ALIGN (TYPE_LENGTH (VALUE_TYPE (val))));
#else
  *sp = push_bytes (*sp, VALUE_CONTENTS_RAW (val), 
		    TYPE_LENGTH (VALUE_TYPE (val)));
#endif

  VALUE_LVAL (val) = lval_memory;
#if 1 INNER_THAN 2
  VALUE_ADDRESS (val) = *sp;
#else
  VALUE_ADDRESS (val) = old_sp;
#endif

  return val;
}

/* Return the value ACTUAL, converted to be an appropriate value for a
   formal of type FORMAL_TYPE.  Use *SP as a stack pointer for
   allocating any necessary descriptors (fat pointers), or copies of
   values not residing in memory, updating it as needed. */ 

static value_ptr
convert_actual (actual, formal_type, sp)
     value_ptr actual;
     struct type* formal_type;
     CORE_ADDR* sp;
{
  struct type* actual_type = VALUE_TYPE (actual);
  struct type* formal_target =
    TYPE_CODE (formal_type) == TYPE_CODE_PTR 
      ? TYPE_TARGET_TYPE (formal_type) : formal_type;
  struct type* actual_target = 
    TYPE_CODE (actual_type) == TYPE_CODE_PTR 
      ? TYPE_TARGET_TYPE (actual_type) : actual_type;

  if (ada_is_array_descriptor (formal_target)
      && TYPE_CODE (actual_target) == TYPE_CODE_ARRAY)
    return make_array_descriptor (formal_type, actual, sp);
  else if (TYPE_CODE (formal_type) == TYPE_CODE_PTR)
    {
      if (TYPE_CODE (formal_target) == TYPE_CODE_ARRAY
	  && ada_is_array_descriptor (actual_target)) 
	return desc_data (actual);
      else if (TYPE_CODE (actual_type) != TYPE_CODE_PTR)
	{
	  if (VALUE_LVAL (actual) != lval_memory)
	    {
	      value_ptr val = allocate_value (actual_type);
	      memcpy ((char*) VALUE_CONTENTS_RAW (val), 
		      (char*) VALUE_CONTENTS (actual),
		      TYPE_LENGTH (actual_type));
	      actual = place_on_stack (val, sp);
	    }
	  return value_addr (actual);
	}
    }
  else if (TYPE_CODE (actual_type) == TYPE_CODE_PTR)
    return value_ind (actual);

  return actual;
}


/* Push a descriptor of type TYPE for array value ARR on the stack at 
   *SP, updating *SP to reflect the new descriptor.  Return either 
   an lvalue representing the new descriptor, or (if TYPE is a pointer-
   to-descriptor type rather than a descriptor type), a value_ptr
   representing a pointer to this descriptor. */

static value_ptr
make_array_descriptor (type, arr, sp)
     struct type* type;
     value_ptr arr;
     CORE_ADDR* sp;
{
  struct type* bounds_type = desc_bounds_type (type);
  struct type* desc_type = desc_base_type (type);
  value_ptr descriptor = allocate_value (desc_type);
  value_ptr bounds = allocate_value (bounds_type);
  CORE_ADDR bounds_addr;
  int i;
  
  for (i = ada_array_arity (VALUE_TYPE (arr)); i > 0; i -= 1)
    {
      modify_general_field (VALUE_CONTENTS (bounds),
			    value_as_long (ada_array_bound (arr, i, 0)), 
			    desc_bound_bitpos (bounds_type, i, 0),
			    desc_bound_bitsize (bounds_type, i, 0));
      modify_general_field (VALUE_CONTENTS (bounds),
			    value_as_long (ada_array_bound (arr, i, 1)), 
			    desc_bound_bitpos (bounds_type, i, 1),
			    desc_bound_bitsize (bounds_type, i, 1));
    }
  
  bounds = place_on_stack (bounds, sp);
  
  modify_general_field (VALUE_CONTENTS (descriptor),
			value_as_pointer (arr),
			desc_data_bitpos (desc_type),
			desc_data_bitsize (desc_type));
  modify_general_field (VALUE_CONTENTS (descriptor),
			VALUE_ADDRESS (bounds),
			desc_bounds_bitpos (desc_type),
			desc_bounds_bitsize (desc_type));

  descriptor = place_on_stack (descriptor, sp);

  if (TYPE_CODE (type) == TYPE_CODE_PTR)
    return value_addr (descriptor);
  else
    return descriptor;
}


/* Assuming a dummy frame has been established on the target, perform any 
   conversions needed for calling function FUNC on the NARGS actual
   parameters in ARGS, other than standard C conversions.   Does
   nothing if FUNC does not have Ada-style prototype data, or if NARGS
   does not match the number of arguments expected.   Use *SP as a
   stack pointer for additional data that must be pushed, updating its
   value as needed. */

void
ada_convert_actuals (func, nargs, args, sp)
     value_ptr func;
     int nargs;
     value_ptr args[];
     CORE_ADDR* sp;
{
  int i;

  if (TYPE_NFIELDS (VALUE_TYPE (func)) == 0 
      || nargs != TYPE_NFIELDS (VALUE_TYPE (func)))
    return;

  for (i = 0; i < nargs; i += 1)
    args[i] = 
      convert_actual (args[i], TYPE_FIELD_TYPE (VALUE_TYPE (func), i), sp);
}



/* The vectors of symbols and blocks ultimately returned from */
/* ada_lookup_symbol_list. */

/* Current size of defn_symbols and defn_blocks */
static int defn_vector_size = 0; 

/* Current number of symbols found. */
static ndefns = 0;

static struct symbol** defn_symbols = NULL;
static struct block** defn_blocks = NULL;

/* Non-zero iff there is at least one non-function/non-enumeral symbol */
/* in SYMS[0..N-1].  We treat enumerals as functions, since they */
/* contend in overloading in the same way. */ 
static int
is_nonfunction (syms, n)
     struct symbol* syms[];
     int n;
{
  int i;

  for (i = 0; i < n; i += 1)
    if (TYPE_CODE (SYMBOL_TYPE (syms[i])) != TYPE_CODE_FUNC
	&& TYPE_CODE (SYMBOL_TYPE (syms[i])) != TYPE_CODE_ENUM)
      return 1;

  return 0;
}

/* Append SYM to the end of defn_symbols, and BLOCK to the end of */
/* defn_blocks, updating ndefns, and expanding defn_symbols and */
/* defn_blocks as needed. */

static void
add_defn_to_vec (sym, block)
     struct symbol* sym;
     struct block* block;
{
  int i;
  for (i = 0; i < ndefns; i += 1)
      if (sym == defn_symbols[i]) 
	return;

  if (defn_vector_size <= ndefns+1) 
    {
      if (defn_vector_size > 0)
	defn_vector_size *= 2;
      else
	defn_vector_size = 8;
      defn_symbols = (struct symbol**) 
	xrealloc (defn_symbols, defn_vector_size * sizeof (defn_symbols[0]));
      defn_blocks = (struct block**)
	xrealloc (defn_blocks, defn_vector_size * sizeof (defn_blocks[0]));
    }

  defn_symbols[ndefns] = sym;
  defn_blocks[ndefns] = block;
  ndefns += 1;
}

/* Look, in partial_symtab PST, for symbol NAME.  Check the global
   symbols if GLOBAL, the static symbols if not */

static struct partial_symbol *
ada_lookup_partial_symbol (pst, name, global, namespace)
     struct partial_symtab *pst;
     const char *name;
     int global;
     namespace_enum namespace;
{
  struct partial_symbol **start, **psym;
  int length = (global ? pst->n_global_syms : pst->n_static_syms);

  if (length == 0)
    {
      return (NULL);
    }
  
  start = (global ?
	   pst->objfile->global_psymbols.list + pst->globals_offset :
	   pst->objfile->static_psymbols.list + pst->statics_offset  );

  for (psym = start; psym < start + length; psym += 1)
    {
      if (namespace == SYMBOL_NAMESPACE (*psym))
	{
	  /* Beginning in GDB 4.14, partial symbol tables do not 
	     contain demangled names. */
	  if (SYMBOL_LANGUAGE (*psym) == language_ada 
	      && SYMBOL_DEMANGLED_NAME (*psym) == NULL)
	    SYMBOL_INIT_DEMANGLED_NAME (*psym, &pst->objfile->psymbol_obstack);
	  
	  if (SYMBOL_MATCHES_NAME (*psym, name))
	    {
	      return (*psym);
	    }
	}
    }

  return (NULL);
}

/* Find a symbol table (global or static) containing symbol SYM, or */
/* NULL if none. */ 

static struct symtab*
symtab_for_sym (sym)
     struct symbol* sym;
{
  struct symtab* s;
  struct objfile *objfile;
  struct block *b;
  int i;

  ALL_SYMTABS (objfile, s)
    {
      b = BLOCKVECTOR_BLOCK (BLOCKVECTOR (s), GLOBAL_BLOCK);
      for (i = 0; i < BLOCK_NSYMS (b); i += 1)
	if (sym == BLOCK_SYM (b, i))
	  return s;
      b = BLOCKVECTOR_BLOCK (BLOCKVECTOR (s), STATIC_BLOCK);
      for (i = 0; i < BLOCK_NSYMS (b); i += 1)
	if (sym == BLOCK_SYM (b, i))
	  return s;
    }

  return NULL;
}

/* Return non-zero if the SYMBOL_NAME of MSYMBOL, demangled according
   to GNAT conventions, is a match for NAME. (A minimal symbol's name
   can be incorrectly demangled due to aliasing between C++ and GNAT
   mangling conventions.) */

static int
ada_msymbol_matches_name (msymbol, name)
     struct minimal_symbol* msymbol;
     const char* name;
{
  if (SYMBOL_LANGUAGE (msymbol) == language_cplus) 
    {
      char* ada_demangling = ada_demangle (SYMBOL_NAME (msymbol));

      if (ada_demangling != NULL)
	return ada_match_name (ada_demangling, name);
    }

  return ada_match_name (SYMBOL_SOURCE_NAME (msymbol), name);
}

/* Return a minimal symbol matching NAME according to Ada demangling 
   rules. Returns NULL if there is no such minimal symbol. */

struct minimal_symbol*
ada_lookup_minimal_symbol (name)
     const char* name;
{
  struct objfile* objfile;
  struct minimal_symbol* msymbol;

  ALL_MSYMBOLS (objfile, msymbol)
    {
      if (ada_msymbol_matches_name (msymbol, name)
	  && MSYMBOL_TYPE (msymbol) != mst_solib_trampoline)
	return msymbol;
    }

  return NULL;
}

/* Find symbols in NAMESPACE matching NAME, in BLOCK and enclosing 
   scope and in global scopes, returning the number of matches.  Sets 
   *SYMS to point to a vector of matching symbols, with *BLOCKS
   pointing to the vector of corresponding blocks in which those
   symbols reside.  These two vectors are transient---good only to the
   next call of ada_lookup_symbol_list.  Any non-function/non-enumeral symbol
   match within the nest of blocks whose innermost member is BLOCK,
   is the outermost match returned (no other matches in that or
   enclosing blocks is returned).  If there are any matches in or
   surrounding BLOCK, then these alone are returned. */

/* It seems to me that we ought be able to integrate this with */
/* make_symbol_completion_list somehow by generalizing the latter. */
/* For now, though, we keep this (semi-redundantly) separate. */

int
ada_lookup_symbol_list (name, block, namespace, syms, blocks)
     const char *name;
     struct block *block;
     namespace_enum namespace;
     struct symbol*** syms;
     struct block*** blocks;
{
  struct symbol *sym;
  struct symtab *s;
  struct partial_symtab *ps;
  struct blockvector *bv;
  struct objfile *objfile;
  struct block *b;
  struct minimal_symbol *msymbol;

  int n_nonfuncs;

  ndefns = 0;

  /* Search specified block and its superiors.  */

  while (block != 0)
    {
      ada_add_block_symbols (block, name, namespace);

      /* If we found a non-function match, assume that's the one. */
      if (is_nonfunction (defn_symbols, ndefns))
	goto done;

      block = BLOCK_SUPERBLOCK (block);
    }

  /* If we found ANY matches in the specified BLOCK, we're done. */

  if (ndefns > 0)
    goto done;
  

  /* Now add symbols from all global blocks: symbol tables, minimal symbol
     tables, and psymtab's */
  
  ALL_SYMTABS (objfile, s)
    {
      bv = BLOCKVECTOR (s);
      block = BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK);
      ada_add_block_symbols (block, name, namespace);
    }

  if (namespace == VAR_NAMESPACE)
    {
      ALL_MSYMBOLS (objfile, msymbol)
	{
	  if (ada_msymbol_matches_name (msymbol, name))
	    {
	      switch (MSYMBOL_TYPE (msymbol))
		{
		case mst_solib_trampoline:
		  break;
		default:
		  s = find_pc_symtab (SYMBOL_VALUE_ADDRESS (msymbol));
		  if (s != NULL)
		    {
		      int old_ndefns = ndefns;
		      bv = BLOCKVECTOR (s);
		      block = BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK);
		      ada_add_block_symbols (block, 
					     SYMBOL_NAME (msymbol), 
					     namespace);
		      if (ndefns == old_ndefns) 
			{
			  block = BLOCKVECTOR_BLOCK (bv, STATIC_BLOCK);
			  ada_add_block_symbols (block, 
						 SYMBOL_NAME (msymbol), 
						 namespace);
			}
		    }
		}
	    }
	}
    }
      
  ALL_PSYMTABS (objfile, ps)
    {
      if (!ps->readin && ada_lookup_partial_symbol (ps, name, 1, namespace))
	{
	  s = PSYMTAB_TO_SYMTAB(ps);
	  bv = BLOCKVECTOR (s);
	  block = BLOCKVECTOR_BLOCK (bv, GLOBAL_BLOCK);
	  ada_add_block_symbols (block, name, namespace);
	}
    }
  
  /* Now add symbols from all per-file blocks if we've gotten no hits.  
     (Not strictly correct, but perhaps better than an error).
     Do the symtabs first, then check the psymtabs */
  
  if (ndefns == 0)
    {

      ALL_SYMTABS (objfile, s)
	{
	  bv = BLOCKVECTOR (s);
	  block = BLOCKVECTOR_BLOCK (bv, STATIC_BLOCK);
	  ada_add_block_symbols (block, name, namespace);
	}
      
      ALL_PSYMTABS (objfile, ps)
	{
	  if (!ps->readin 
	      && ada_lookup_partial_symbol (ps, name, 0, namespace))
	    {
	      s = PSYMTAB_TO_SYMTAB(ps);
	      bv = BLOCKVECTOR (s);
	      block = BLOCKVECTOR_BLOCK (bv, STATIC_BLOCK);
	      ada_add_block_symbols (block, name, namespace);
	    }
	}
    }  


 done:
  *syms = defn_symbols;
  *blocks = defn_blocks;
  return ndefns;
}

/* Add symbols from BLOCK matching identifier NAME in NAMESPACE to 
   vector *BLKSYMS, updating *BLKSYMS (if necessary), *SZ (the size of
   the vector *BLKSYMS), and *NBLKSYMS (the number of symbols
   currently stored in *BLKSYMS). */

static void 
ada_add_block_symbols (block, name, namespace)
     struct block* block;
     const char* name;
     namespace_enum namespace;
{
  int i;
  /* A matching argument symbol, if any. */
  struct symbol *arg_sym;
  /* Set true when we find a matching non-argument symbol */
  int found_sym;

  arg_sym = NULL; found_sym = 0;
  for (i = 0; i < BLOCK_NSYMS (block); i += 1)
    {
      struct symbol *sym = BLOCK_SYM (block, i);

      if (SYMBOL_NAMESPACE (sym) == namespace &&
	  SYMBOL_MATCHES_NAME (sym, name))
	{
	  switch (SYMBOL_CLASS (sym))
	    {
	    case LOC_ARG:
	    case LOC_LOCAL_ARG:
	    case LOC_REF_ARG:
	    case LOC_REGPARM:
	    case LOC_REGPARM_ADDR:
	    case LOC_BASEREG_ARG:
	      arg_sym = sym;
	      break;
	    default:
	      found_sym = 1;
	      fill_in_ada_prototype (sym);
	      add_defn_to_vec (sym, block);
	      break;
	    }
	}
    }

  if (! found_sym && arg_sym != NULL)
    {
      fill_in_ada_prototype (arg_sym);
      add_defn_to_vec (arg_sym, block);
    }
}



/* Assuming that SYM is the symbol for a function, fill in its type 
   with prototype information, if it is not already there.  
   
   Why is there provision in struct type for BOTH an array of argument
   types (TYPE_ARG_TYPES) and for an array of typed fields, whose
   comment suggests it may also represent argument types?  I presume
   this is some attempt to save space.  The problem is that argument
   names in Ada are significant.  Therefore, for Ada we use the
   (apparently older) TYPE_FIELD_* stuff to store argument types. */


static void
fill_in_ada_prototype (func)
     struct symbol* func;
{
  struct block* b;
  int nargs, nsyms;
  int i;
  struct type* ftype;
  struct type* rtype;
  int max_fields;

  if (func == NULL
      || TYPE_CODE (SYMBOL_TYPE (func)) != TYPE_CODE_FUNC
      || TYPE_FIELDS (SYMBOL_TYPE (func)) != NULL)
    return;

  /* We make each function type unique, so that each may have its own */
  /* parameter types.  This particular way of doing so wastes space: */
  /* it would be nicer to build the argument types while the original */
  /* function type is being built (FIXME). */
  rtype = TYPE_TARGET_TYPE (SYMBOL_TYPE (func));
  ftype = alloc_type (TYPE_OBJFILE (SYMBOL_TYPE (func)));
  make_function_type (rtype, &ftype);
  SYMBOL_TYPE (func) = ftype;

  b = SYMBOL_BLOCK_VALUE (func);
  nsyms = BLOCK_NSYMS (b);

  nargs = 0;
  max_fields = 8; 
  TYPE_FIELDS (ftype) = 
    (struct field*) xmalloc (sizeof (struct field) * max_fields);
  for (i = 0; i < nsyms; i += 1)
    {
      struct symbol *sym = BLOCK_SYM (b, i);

      if (nargs >= max_fields) 
	{
	  max_fields *= 2;
	  TYPE_FIELDS (ftype) = (struct field*)
	    xrealloc (TYPE_FIELDS (ftype), sizeof (struct field) * max_fields);
	}
	
      switch (SYMBOL_CLASS (sym)) 
	{
	case LOC_REF_ARG:
	case LOC_REGPARM_ADDR:
	  TYPE_FIELD_BITPOS (ftype, nargs) = nargs;
	  TYPE_FIELD_BITSIZE (ftype, nargs) = 0;
	  TYPE_FIELD_TYPE (ftype, nargs) = 
	    lookup_pointer_type (SYMBOL_TYPE (sym));
	  TYPE_FIELD_NAME (ftype, nargs) = SYMBOL_NAME (sym);
	  nargs += 1;
	
	  break;

	case LOC_ARG:
	case LOC_REGPARM:
	case LOC_LOCAL_ARG:
	case LOC_BASEREG_ARG:
	  TYPE_FIELD_BITPOS (ftype, nargs) = nargs;
	  TYPE_FIELD_BITSIZE (ftype, nargs) = 0;
	  TYPE_FIELD_TYPE (ftype, nargs) = SYMBOL_TYPE (sym);
	  TYPE_FIELD_NAME (ftype, nargs) = SYMBOL_NAME (sym);
	  nargs += 1;
	
	  break;

	default:
	  break;
	}
    }

  /* Re-allocate fields vector; if there are no fields, make the */
  /* fields pointer non-null anyway, to mark that this function type */
  /* has been filled in. */

  TYPE_NFIELDS (ftype) = nargs;
  if (nargs == 0)
    {
      static struct field dummy_field = {0, 0, 0, 0};
      free (TYPE_FIELDS (ftype));
      TYPE_FIELDS (ftype) = &dummy_field;
    }
  else
    {
      struct field* fields = 
	(struct field*) TYPE_ALLOC (ftype, nargs * sizeof (struct field));
      memcpy ((char*) fields, 
	      (char*) TYPE_FIELDS (ftype), 
	      nargs * sizeof (struct field));
      free (TYPE_FIELDS (ftype));
      TYPE_FIELDS (ftype) = fields;
    }
}


				/* Breakpoint-related */

/* Return all symbol table/line pairs of functions matching NAME'
   starting in BLOCK (plus all global blocks if BLOCK == NULL or NAME
   is not found in BLOCK), after selection by the user, if needed.
   NAME' is a "canonical function name" consisting of NAME if
   PREFERRED_LINE is -1, or NAME:PREFERRED_LINE otherwise. Returns
   with 0 elements if no matching non-minimal symbols to NAME found.
   FUNFIRSTLINE is non-zero if we desire the first line of real code
   in each function.  If CANONICAL is non-NULL, *CANONICAL is set to
   an array of pointers to canonical function names (see above)
   corresponding to the entries in the returned value. Error if user
   cancels the selection. */

struct symtabs_and_lines
ada_finish_decode_line_1 (name, preferred_line, funfirstline, block, canonical)
     const char* name;
     int preferred_line;
     int funfirstline;
     struct block* block;
     char*** canonical;
{
  struct symbol** symbols;
  struct block** blocks;
  int n_matches, i;
  struct symtabs_and_lines selected;
  struct cleanup* old_chain = make_cleanup (null_cleanup, NULL);
      
  n_matches = ada_lookup_symbol_list (name, block, VAR_NAMESPACE, 
				      &symbols, &blocks);
  if (n_matches == 0)
    {
      selected.nelts = 0;
      return selected;
    }

  if (preferred_line >= 0)
      selected.nelts = n_matches;
  else
    {
      selected.nelts = user_select_syms (symbols, blocks, n_matches, n_matches);
    }

  selected.sals = (struct symtab_and_line*) 
    xmalloc (sizeof (struct symtab_and_line) * selected.nelts);
  memset (selected.sals, 0, selected.nelts * sizeof (selected.sals[i]));
  make_cleanup (free, selected.sals);

  i = 0;
  while (i < selected.nelts)
    {
      if (SYMBOL_CLASS (symbols[i]) == LOC_BLOCK) 
	selected.sals[i] = find_function_start_sal (symbols[i], funfirstline);
      else if (SYMBOL_LINE (symbols[i]) != 0) 
	{
	  selected.sals[i].symtab = symtab_for_sym (symbols[i]);
	  selected.sals[i].line = SYMBOL_LINE (symbols[i]);
	}
      else if (preferred_line >= 0)
	{
	  /* Ignore this choice */
	  symbols[i] = symbols[selected.nelts-1];
	  blocks[i] = blocks[selected.nelts-1];
	  selected.nelts -= 1;
	  continue;
	}
      else 
	error ("Line number not known for symbol \"%s\"", name);
      i += 1;
    }

  if (preferred_line >= 0)
    {
      selected.nelts = 1;
      selected.sals[0] = 
	selected.sals[nearest_to_line (selected, preferred_line)];
    }

  if (canonical != NULL && (preferred_line >= 0 || n_matches > 1))
    {
      *canonical = (char**) xmalloc (sizeof(char*) * selected.nelts);
      for (i = 0; i < selected.nelts; i += 1)
	(*canonical)[i] = 
	  extended_canonical_line_spec (selected.sals[i], 
					SYMBOL_SOURCE_NAME (symbols[i]));
    }
   
  discard_cleanups (old_chain);
  return selected;
}  
      
/* The index of the symtab_and_line in SYMS_AND_LINES that is closest 
   to PREFERRED_LINE, with ties broken in favor of lower PC. */

static int
nearest_to_line (syms_and_lines, preferred_line)
     struct symtabs_and_lines syms_and_lines;
     int preferred_line;
{
  int i, r;
  r = 0;
  for (i = 1; i < syms_and_lines.nelts; i += 1)
    {
      if (abs (syms_and_lines.sals[r].line - preferred_line) > 
	  abs (syms_and_lines.sals[i].line - preferred_line)
	  || (abs (syms_and_lines.sals[r].line - preferred_line) ==
	      abs (syms_and_lines.sals[i].line - preferred_line)
	      && syms_and_lines.sals[r].pc > syms_and_lines.sals[i].pc))
	r = i;
    }
  return r;
}

/* A canonical line specification of the form FILE:NAME:LINENUM for
   symbol table and line data SAL.  NULL if insufficient
   information. The caller is responsible for releasing any space
   allocated. */

static char*
extended_canonical_line_spec (sal, name)
     struct symtab_and_line sal;
     const char* name;
{
  char* r;

  if (sal.symtab == NULL || sal.symtab->filename == NULL || 
      sal.line <= 0)
    return NULL;

  r = (char*) xmalloc (strlen (name) + strlen (sal.symtab->filename)  
		       + sizeof(sal.line)*3 + 3);
  sprintf (r, "%s:'%s':%d", sal.symtab->filename, name, sal.line);
  return r;
}



/* Field access. */

/* True if field number FIELD_NUM in struct or union type TYPE is supposed
   to be invisible to users. */

int
ada_is_ignored_field (type, field_num)
     struct type *type;
     int field_num;
{
  if (field_num < 0 || field_num > TYPE_NFIELDS (type))
    return 1;
  else 
    {
      const char* name = TYPE_FIELD_NAME (type, field_num);
      return (name == NULL
	      || name[0] == '_');
    }
}

/* True iff structure type TYPE has a tag field. */

int
ada_is_tagged_type (type)
     struct type *type;
{
  if (type == NULL || TYPE_CODE (type) != TYPE_CODE_STRUCT)
    return 0;

  return (ada_lookup_struct_elt_type (type, "_tag", 1, NULL) != NULL);
}

/* The type of the tag on VAL. */

struct type*
ada_tag_type (val)
     value_ptr val;
{
  return ada_lookup_struct_elt_type (VALUE_TYPE (val), "_tag", 0, NULL);
}

/* The value of the tag on VAL. */

value_ptr
ada_value_tag (val)
     value_ptr val;
{
  return ada_value_struct_elt (val, "_tag", "record");
}

/* The parent type of TYPE, or NULL if none. */

struct type*
ada_parent_type (type)
     struct type *type;
{
  int i;

  if (type == NULL || TYPE_CODE (type) != TYPE_CODE_STRUCT)
    return NULL;

  for (i = 0; i < TYPE_NFIELDS (type); i += 1)
    if (ada_is_parent_field (type, i))
      return TYPE_FIELD_TYPE (type, i);

  return NULL;
}

/* True iff field number FIELD_NUM of structure type TYPE contains the 
   parent-type (inherited) fields of a derived type.  Assumes TYPE is 
   a structure type with at least FIELD_NUM+1 fields. */

int
ada_is_parent_field (type, field_num)
     struct type *type;
     int field_num;
{
  const char* name = TYPE_FIELD_NAME (type, field_num);
  return (name != NULL && STREQ (name, "PARENT"));
}

/* True iff field number FIELD_NUM of structure type TYPE is a 
   transparent wrapper field (which should be silently traversed when doing
   field selection and flattened when printing).  Assumes TYPE is a 
   structure type with at least FIELD_NUM+1 fields.  Such fields are always
   structures. */

int
ada_is_wrapper_field (type, field_num)
     struct type *type;
     int field_num;
{
  const char* name = TYPE_FIELD_NAME (type, field_num);
  return (name != NULL 
	  && (STREQ (name, "PARENT") || STREQ (name, "REP")));
}

/* True iff field number FIELD_NUM of structure or union type TYPE 
   is a variant wrapper.  Assumes TYPE is a structure type with at least 
   FIELD_NUM+1 fields. */ 

int
ada_is_variant_part (type, field_num)
     struct type *type;
     int field_num;
{
  const char* name = TYPE_FIELD_NAME (type, field_num);
  return (name != NULL && STREQN (name, "VARIANTS", 8));
}

/* Assuming that field number FIELD_NUM of type TYPE is a variant wrapper 
   whose discriminants are contained in the record type OUTER_TYPE, 
   returns the type of the controlling discriminant for the variant.  */

struct type*
ada_variant_discrim_type (var_type, field_num, outer_type)
     struct type *var_type;
     int field_num;
     struct type *outer_type;
{
  char* name = ada_variant_discrim_name (var_type, field_num, outer_type);
  struct type *type = ada_lookup_struct_elt_type (outer_type, name, 1, NULL);
  if (type == NULL)
    return builtin_type_int;
  else
    return type;
}

/* Assuming that TYPE is the type of a variant wrapper, and FIELD_NUM is a 
   valid field number within it, returns 1 iff field FIELD_NUM of TYPE
   represents a 'when others' clause; otherwise 0. */

int
ada_is_others_clause (type, field_num)
     struct type *type;
     int field_num;
{
  const char* name = TYPE_FIELD_NAME (type, field_num);
  return (name != NULL && name[strlen (name) - 1] == 'O');
}

/* Assuming that field number FIELD_NUM of type TYPE is a variant wrapper 
   whose discriminant is contained in the record type OUTER_TYPE, 
   returns the name of the discriminant controlling the variant.  */

char * 
ada_variant_discrim_name (type, field_num, outer_type)
     struct type *type;
     int field_num;
     struct type *outer_type;
{
  char* name = TYPE_FIELD_NAME (type, field_num);

  /* Check for new (GNAT 3.10) convention */
  if (name[sizeof("VARIANTS")] == '_')
    return name + sizeof("VARIANTS_");
  else 
    {
      /* Old convention (only partially implemented) */
      int discrim_num;
      struct type* var_type = TYPE_FIELD_TYPE (type, field_num);

      if (TYPE_NFIELDS (var_type) == 0)
	return "";
      discrim_num = atoi (TYPE_FIELD_NAME (var_type, 0) + 1) - 1;      
      if (discrim_num < 0 || discrim_num > TYPE_NFIELDS (outer_type))
	return "";
      else
	return TYPE_FIELD_NAME (outer_type, discrim_num);
    }
}

/* Scan STR for a subtype-encoded number, beginning at position K. Put the 
   position of the character just past the number scanned in *NEW_K, 
   if NEW_K!=NULL. Put the scanned number in *R, if R!=NULL.  Return 1 
   if there was a valid number at the given position, and 0 otherwise.  A 
   "subtype-encoded" number consists of the absolute value in decimal, 
   followed by the letter 'm' to indicate a negative number.  Assumes 0m 
   does not occur. */

int
ada_scan_number (str, k, R, new_k)
     const char str[];
     int k;
     LONGEST *R;
     int *new_k;
{
  unsigned LONGEST RU;

  if (! isdigit (str[k]))
    return 0;

  /* Do it the hard way so as not to make any assumption about 
     the relationship of unsigned long (%lu scan format code) and
     LONGEST. */
  RU = 0;
  while (isdigit (str[k]))
    {
      RU = RU*10 + (str[k] - '0');
      k += 1;
    }

  if (str[k] == 'm') 
    {
      if (R != NULL)
	*R = (- (LONGEST) (RU-1)) - 1;
      k += 1;
    }
  else if (R != NULL)
    *R = (LONGEST) RU;

  /* NOTE on the above: Technically, C does not say what the results of 
     - (LONGEST) RU or (LONGEST) -RU are for RU == largest positive
     number representable as a LONGEST (although either would probably work
     in most implementations).  When RU>0, the locution in the then branch
     above is always equivalent to the negative of RU. */

  if (new_k != NULL)
    *new_k = k;
  return 1;
}

/* Assuming that TYPE is a variant part wrapper type (a VARIANTS field), 
   and FIELD_NUM is a valid field number within it, returns 1 iff VAL is 
   in the range encoded by field FIELD_NUM of TYPE; otherwise 0. */

int 
ada_in_variant (val, type, field_num)
     LONGEST val;
     struct type *type;
     int field_num;
{
  const char* name = TYPE_FIELD_NAME (type, field_num);
  int p;

  /* Skip over leading 'V': NOTE soon to be obsolete. */
  if (name[0] == 'V') 
    {
      if (! ada_scan_number (name, 1, NULL, &p))
	return 0;
    }
  else 
    p = 0;
  
  while (1)
    {
      switch (name[p]) 
	{
	case '\0':
	  return 0;
	case 'S':
	  {
	    LONGEST W;
	    if (! ada_scan_number (name, p + 1, &W, &p))
	      return 0;
	    if (val == W)
	      return 1;
	    break;
	  }
	case 'R':
	  {
	    LONGEST L, U;
	    if (! ada_scan_number (name, p + 1, &L, &p)
		|| name[p] != 'T'
		|| ! ada_scan_number (name, p + 1, &U, &p))
	      return 0;
	    if (val >= L && val <= U)
	      return 1;
	    break;
	  }
	case 'O':
	  return 1;
	default:
	  return 0;
	}
    }
}

/* Look for a field NAME in ARG. Adjust the address of ARG by OFFSET bytes,
   and search in it assuming it has (class) type TYPE.
   If found, return value, else return NULL.

   Searches recursively through wrapper fields (e.g., 'PARENT'). */

value_ptr
ada_search_struct_field (name, arg, offset, type)
     char *name;
     value_ptr arg;
     int offset;
     struct type *type;
{
  int i;
  CHECK_TYPEDEF (type);

  for (i = TYPE_NFIELDS (type) - 1; i >= 0; i -= 1)
    {
      char *t_field_name = TYPE_FIELD_NAME (type, i);

      if (t_field_name == NULL)
	continue;

      else if (STREQ (t_field_name, name))
	  return value_primitive_field (arg, offset, i, type);

      else if (ada_is_wrapper_field (type, i))
	{
	  value_ptr v = 
	    ada_search_struct_field (name, arg, 
				     offset + TYPE_FIELD_BITPOS (type, i) / 8, 
				     TYPE_FIELD_TYPE (type, i));
	  if (v != NULL)
	    return v;
	}

      else if (ada_is_variant_part (type, i))
	{
	  int j;
	  struct type *field_type = TYPE_FIELD_TYPE (type, i);
	  int var_offset = offset + TYPE_FIELD_BITPOS (type, i) / 8;

	  for (j = TYPE_NFIELDS (field_type) - 1; j >= 0; j -= 1)
	    {
	      value_ptr v = 
		ada_search_struct_field (name, arg, 
					 var_offset 
					 + TYPE_FIELD_BITPOS (field_type, j)/8,
					 TYPE_FIELD_TYPE (field_type, j));
	      if (v != NULL)
		return v;
	    }
	}
    }
  return NULL;
}
  
/* Given ARG, a value of type (pointer to a)* structure/union,
   extract the component named NAME from the ultimate target structure/union
   and return it as a value with its appropriate type.

   The routine searches for NAME among all members of the structure itself 
   and (recursively) among all members of any wrapper members (e.g., 'PARENT').

   ERR is a name (for use in error messages) that identifies the class 
   of entity that ARG is supposed to be. */

value_ptr
ada_value_struct_elt (arg, name, err)
     value_ptr arg;
     char *name;
     char *err;
{
  register struct type *t;
  value_ptr v;

  COERCE_ARRAY (arg);

  t = check_typedef (VALUE_TYPE (arg));

  /* Follow pointers until we get to a non-pointer.  */

  while (TYPE_CODE (t) == TYPE_CODE_PTR || TYPE_CODE (t) == TYPE_CODE_REF)
    {
      arg = value_ind (arg);
      /* Don't coerce fn pointer to fn and then back again!  */
      if (TYPE_CODE (VALUE_TYPE (arg)) != TYPE_CODE_FUNC)
	COERCE_ARRAY (arg);
      t = check_typedef (VALUE_TYPE (arg));
    }

  if (TYPE_CODE (t) == TYPE_CODE_MEMBER)
    error ("not implemented: member type in value_struct_elt");

  if (   TYPE_CODE (t) != TYPE_CODE_STRUCT
      && TYPE_CODE (t) != TYPE_CODE_UNION)
    error ("Attempt to extract a component of a value that is not a %s.", err);

  v = ada_search_struct_field (name, arg, 0, t);
  if (v == NULL)
    error ("There is no member named %s.", name);

  return v;
}

/* Given a type TYPE, look up the type of the component of type named NAME.
   If DISPP is non-null, add its byte displacement from the beginning of a 
   structure (pointed to by a value) of type TYPE to *DISPP (does not 
   work for packed fields).

   TYPE can be either a struct or union, or a pointer or reference to 
   a struct or union.  If it is a pointer or reference, its target 
   type is automatically used.

   Looks recursively into variant clauses and parent types.

   If NOERR is nonzero, return NULL if NAME is not suitably defined. */

struct type *
ada_lookup_struct_elt_type (type, name, noerr, dispp)
     struct type *type;
     char *name;
     int noerr;
     int *dispp;
{
  int i;

  if (name == NULL)
    goto BadName;

  while (1)
    {
      CHECK_TYPEDEF (type);
      if (TYPE_CODE (type) != TYPE_CODE_PTR
	  && TYPE_CODE (type) != TYPE_CODE_REF)
	break;
      type = TYPE_TARGET_TYPE (type);
    }

  if (TYPE_CODE (type) != TYPE_CODE_STRUCT &&
      TYPE_CODE (type) != TYPE_CODE_UNION)
    {
      target_terminal_ours ();
      gdb_flush (gdb_stdout);
      fprintf_unfiltered (gdb_stderr, "Type ");
      type_print (type, "", gdb_stderr, -1);
      error (" is not a structure or union type");
    }

  for (i = TYPE_NFIELDS (type) - 1; i >= 0; i -= 1)
    {
      char *t_field_name = TYPE_FIELD_NAME (type, i);
      struct type *t;
      int disp;
  
      if (t_field_name == NULL)
	continue;

      else if (STREQ (t_field_name, name))
	{
	  if (dispp != NULL) 
	    *dispp += TYPE_FIELD_BITPOS (type, i) / 8;
	  return TYPE_FIELD_TYPE (type, i);
	}

      else if (ada_is_wrapper_field (type, i))
	{
	  disp = 0;
	  t = ada_lookup_struct_elt_type (TYPE_FIELD_TYPE (type, i), name, 1,
					  &disp);
	  if (t != NULL)
	    {
	      if (dispp != NULL)
		*dispp += disp + TYPE_FIELD_BITPOS (type, i) / 8;
	      return t;
	    }
	}

      else if (ada_is_variant_part (type, i))
	{
	  int j;
	  struct type *field_type = TYPE_FIELD_TYPE (type, i);

	  for (j = TYPE_NFIELDS (field_type) - 1; j >= 0; j -= 1)
	    {
	      disp = 0;
	      t = ada_lookup_struct_elt_type (TYPE_FIELD_TYPE (field_type, j),
					      name, 1, &disp);
	      if (t != NULL)
		{
		  if (dispp != NULL) 
		    *dispp += disp + TYPE_FIELD_BITPOS (type, i) / 8;
		  return t;
		}
	    }
	}

    }

BadName:
  if (! noerr)
    {
      target_terminal_ours ();
      gdb_flush (gdb_stdout);
      fprintf_unfiltered (gdb_stderr, "Type ");
      type_print (type, "", gdb_stderr, -1);
      fprintf_unfiltered (gdb_stderr, " has no component named ");
      error ("%s", name == NULL ? "<null>" : name);
    }

  return NULL;
}

/* Attributes */

/* Table mapping attribute numbers to names */
/* NOTE: Keep up to date with enum ada_attribute definition in ada-lang.h */

static const char* attribute_names[] = {
  "<?>",

  "first", 
  "last",
  "length",
  "image",
  "img",
  "max",
  "min",
  "pos"
  "tag",
  "val",

  0
};

const char*
ada_attribute_name (n)
     int n;
{
  if (n > 0 && n < (int) ATR_END)
    return attribute_names[n];
  else
    return attribute_names[0];
}

/* Evaluate the 'POS attribute applied to ARG. */

static value_ptr
value_pos_atr (arg)
     value_ptr arg;
{
  struct type *type = VALUE_TYPE (arg);

  if (! discrete_type_p (type))
    error ("'POS only defined on discrete types");

  if (TYPE_CODE (type) == TYPE_CODE_ENUM)
    {
      int i;
      LONGEST v = value_as_long (arg);

      for (i = 0; i < TYPE_NFIELDS (type); i += 1) 
	{
	  if (v == TYPE_FIELD_BITPOS (type, i))
	    return value_from_longest (builtin_type_ada_int, i);
	}
      error ("enumeration value is invalid: can't find 'POS");
    }
  else
    return value_from_longest (builtin_type_ada_int, value_as_long (arg));
}

/* Evaluate the TYPE'VAL attribute applied to ARG. */

static value_ptr
value_val_atr (type, arg)
     struct type *type;
     value_ptr arg;
{
  if (! discrete_type_p (type))
    error ("'VAL only defined on discrete types");
  if (! integer_type_p (VALUE_TYPE (arg)))
    error ("'VAL requires integral argument");

  if (TYPE_CODE (type) == TYPE_CODE_ENUM)
    {
      long pos = value_as_long (arg);
      if (pos < 0 || pos >= TYPE_NFIELDS (type))
	error ("argument to 'VAL out of range");
      return 
	value_from_longest (type, TYPE_FIELD_BITPOS (type, pos));
    }
  else
    return value_from_longest (type, value_as_long (arg));
}


/* Evaluation */

/* True if TYPE appears to be an Ada string type. */

int
ada_is_string_type (type)
     struct type *type;
{
  if (type != NULL 
      && TYPE_CODE (type) != TYPE_CODE_PTR
      && (ada_is_simple_array (type) || ada_is_array_descriptor (type))
      && ada_array_arity (type) == 1)
    {
      struct type *elttype = ada_array_element_type (type);

      /* NOTE: This is a heuristic test that could stand improvement. */
      return 
	(TYPE_CODE (elttype) == TYPE_CODE_CHAR
	 || TYPE_CODE (elttype) == TYPE_CODE_INT
	 || TYPE_CODE (elttype) == TYPE_CODE_RANGE)
	&& TYPE_NAME (elttype) != NULL
	&& STREQ (TYPE_NAME (elttype), "character");
    }
  else 
    return 0;
}


/* True if TYPE is a struct type introduced by the compiler to force the
   alignment of a value.  Such types have a single field with a
   distinctive name. */

int
ada_is_aligner_type (type)
     struct type *type;
{
  return (TYPE_CODE (type) == TYPE_CODE_STRUCT
	  && TYPE_NFIELDS (type) == 1
	  && STREQ (TYPE_FIELD_NAME (type, 0), "F"));
}

/* The type of value designated by TYPE, with all aligners removed. */

struct type*
ada_aligned_type (type)
     struct type* type;
{
  if (ada_is_aligner_type (type))
    return ada_aligned_type (TYPE_FIELD_TYPE (type, 0));
  else
    return type;
}


/* The address of the aligned value in an object at address VALADDR
   having type TYPE.  Assumes ada_is_aligner_type (TYPE). */

char*
ada_aligned_value_addr (type, valaddr)
     struct type *type;
     char *valaddr;
{
  if (ada_is_aligner_type (type)) 
    return ada_aligned_value_addr (TYPE_FIELD_TYPE (type, 0),
				   valaddr + TYPE_FIELD_BITPOS (type, 0) / 8);
  else
    return valaddr;
}


static value_ptr
evaluate_subexp (expect_type, exp, pos, noside)
     struct type *expect_type;
     register struct expression *exp;
     register int *pos;
     enum noside noside;
{
  return (*exp->language_defn->evaluate_exp) (expect_type, exp, pos, noside);
}

/* Evaluate the subexpression of EXP starting at *POS as for
   evaluate_type, updating *POS to point just past the evaluated
   expression. */

static value_ptr
evaluate_subexp_type (exp, pos)
     struct expression* exp;
     int* pos;
{
  return (*exp->language_defn->evaluate_exp) 
    (NULL_TYPE, exp, pos, EVAL_AVOID_SIDE_EFFECTS);
}

/* If VAL has an aligner type, return the value it wraps. */

static value_ptr
unwrap_value (val)
     value_ptr val;
{
  struct type* type = VALUE_TYPE (val);
  if (ada_is_aligner_type (type))
    return unwrap_value (value_struct_elt (&val, NULL, "F", NULL,
					   "internal structure"));
  else
    return val;
}
    
value_ptr
ada_evaluate_subexp (expect_type, exp, pos, noside)
     struct type *expect_type;
     struct expression *exp;
     int *pos;
     enum noside noside;
{
  enum exp_opcode op;
  enum ada_attribute atr;
  int tem, tem2, tem3;
  int pc;
  value_ptr arg1 = NULL, arg2 = NULL, arg3;
  struct type *type;
  int nargs;
  value_ptr *argvec;

  /* Is this right? */
  expect_type = NULL_TYPE;

  pc = *pos; *pos += 1;
  op = exp->elts[pc].opcode;

  switch (op) 
    {
    default:
      *pos -= 1;
      return unwrap_value (evaluate_subexp_standard (expect_type, exp, pos, noside));

    case OP_UNRESOLVED_VALUE:
      /* Only encountered when an unresolved symbol occurs in a
         context other than a function call, in which case, it is
	 illegal. */
      (*pos) += 3;
      if (noside == EVAL_SKIP)
	goto nosideret;
      else 
	error ("Unexpected unresolved symbol, %s, during evaluation",
	       exp->elts[pc + 2].name);

    case OP_ARRAY:
      (*pos) += 3;
      tem2 = longest_to_int (exp->elts[pc + 1].longconst);
      tem3 = longest_to_int (exp->elts[pc + 2].longconst);
      nargs = tem3 - tem2 + 1;
      type = expect_type ? check_typedef (expect_type) : NULL_TYPE;

      argvec = (value_ptr *) alloca (sizeof (value_ptr) * nargs + 1);
      for (tem = 0; tem == 0 || tem < nargs; tem += 1)
	/* At least one element gets inserted for the type */
	{
	  /* Ensure that array expressions are coerced into pointer objects. */
	  argvec[tem] = evaluate_subexp_with_coercion (exp, pos, noside);
	}
      if (noside == EVAL_SKIP)
	goto nosideret;
      return value_array (tem2, tem3, argvec);

    case OP_FUNCALL:
      (*pos) += 2;

      /* Allocate arg vector, including space for the function to be
	 called in argvec[0] and a terminating NULL */
      nargs = longest_to_int (exp->elts[pc + 1].longconst);
      argvec = (value_ptr *) alloca (sizeof (value_ptr) * (nargs + 2));

      if (exp->elts[*pos].opcode == OP_UNRESOLVED_VALUE) 
	error ("Unexpected unresolved symbol, %s, during evaluation",
	       exp->elts[pc + 5].name);
      else
	{
	  for (tem = 0; tem <= nargs; tem += 1)
	    argvec[tem] = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  argvec[tem] = 0;

	  if (noside == EVAL_SKIP)
	    goto nosideret;
	}

      type = VALUE_TYPE (argvec[0]);
      if (TYPE_CODE (type) == TYPE_CODE_PTR)
	{	
	  switch (TYPE_CODE (TYPE_TARGET_TYPE (type)))
	    {
	    case TYPE_CODE_FUNC:
	      type = TYPE_TARGET_TYPE (type);
	      break;
	    case TYPE_CODE_ARRAY:
	    case TYPE_CODE_STRUCT: /*FIX ME*/
	      if (noside != EVAL_AVOID_SIDE_EFFECTS)
		argvec[0] = value_ind (argvec[0]);
	      type = TYPE_TARGET_TYPE (type);
	      break;
	    default:
	      error ("cannot subscript or call something of type `%s'",
		     TYPE_NAME (VALUE_TYPE (argvec[0])));
	      break;
	  }
	}
	  
      switch (TYPE_CODE (type))
	{
	case TYPE_CODE_FUNC:
	  if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    return allocate_value (TYPE_TARGET_TYPE (type));
	  return call_function_by_hand (argvec[0], nargs, argvec + 1);
	case TYPE_CODE_STRUCT: 
	  {
	    int arity = ada_array_arity (type);
	    type = ada_array_element_type (type);
	    if (type == NULL) 
	      error ("cannot subscript or call a record");
	    if (arity != nargs) 
	      error ("wrong number of subscripts; expecting %d", arity);
	    if (noside == EVAL_AVOID_SIDE_EFFECTS) 
	      return allocate_value (ada_aligned_type (type));
	    return unwrap_value (ada_value_subscript (argvec[0], nargs, argvec+1));
	  }
	case TYPE_CODE_ARRAY:
	  if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    {	
	      type = ada_array_element_type (type);
	      if (type == NULL)
		error ("element type of array unknown");
	      else
		return allocate_value (ada_aligned_type (type));
	    }
	  return unwrap_value (ada_value_subscript (argvec[0], nargs, argvec+1));
	default:
	  error ("Internal error in evaluate_subexp");
	}

    case TERNOP_SLICE:
      {
	value_ptr array = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	int lowbound
	  = value_as_long (evaluate_subexp (NULL_TYPE, exp, pos, noside));
	int upper
	  = value_as_long (evaluate_subexp (NULL_TYPE, exp, pos, noside));
	if (noside == EVAL_SKIP)
	  goto nosideret;
	if (ada_is_array_descriptor (VALUE_TYPE (array)))
	  array = ada_coerce_to_simple_array (array);
	if (noside == EVAL_AVOID_SIDE_EFFECTS)
	  /* The following will get the bounds wrong, but only in contexts
	     where the value is not being requested (FIXME?). */
	  return array;
	else
	  return value_slice (array, lowbound, upper - lowbound + 1);
      }

    case UNOP_MBR:
      (*pos) += 2;
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      type = exp->elts[pc + 1].type;

      if (noside == EVAL_SKIP)
	goto nosideret;

      switch (TYPE_CODE (type)) 
	{
	default:
	  warning ("Membership test incompletely implemented; always returns true");
	  return value_from_longest (builtin_type_int, (LONGEST) 1);
	  
	case TYPE_CODE_RANGE:
	  arg2 = value_from_longest (builtin_type_int, 
				     (LONGEST) TYPE_LOW_BOUND (type));
	  arg3 = value_from_longest (builtin_type_int, 
				     (LONGEST) TYPE_HIGH_BOUND (type));
	  return 
	    value_from_longest (builtin_type_int,
				(value_less (arg1,arg3) 
				 || value_equal (arg1,arg3))
				&& (value_less (arg2,arg1)
				    || value_equal (arg2,arg1)));
	}

    case BINOP_MBR:
      (*pos) += 2;
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);

      if (noside == EVAL_SKIP)
	goto nosideret;

      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return value_zero (builtin_type_int, not_lval);

      tem = longest_to_int (exp->elts[pc + 1].longconst);

      if (tem < 1 || tem > ada_array_arity (VALUE_TYPE (arg2)))
	error ("invalid dimension number to '%s", "range");

      arg3 = ada_array_bound (arg2, tem, 1);
      arg2 = ada_array_bound (arg2, tem, 0);

      return 
	value_from_longest (builtin_type_int,
			    (value_less (arg1,arg3) 
			     || value_equal (arg1,arg3))
			    && (value_less (arg2,arg1)
				|| value_equal (arg2,arg1)));

    case TERNOP_MBR:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      arg3 = evaluate_subexp (NULL_TYPE, exp, pos, noside);

      if (noside == EVAL_SKIP)
	goto nosideret;

      return 
	value_from_longest (builtin_type_int,
			    (value_less (arg1,arg3) 
			     || value_equal (arg1,arg3))
			    && (value_less (arg2,arg1)
				|| value_equal (arg2,arg1)));

    case OP_ATTRIBUTE:
      *pos += 3;
      atr = (enum ada_attribute) longest_to_int (exp->elts[pc + 2].longconst);
      switch (atr) 
	{
	default:
	  error ("unexpected attribute encountered");

	case ATR_FIRST:
	case ATR_LAST:
	case ATR_LENGTH:
	  arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  if (exp->elts[*pos].opcode != OP_LONG) 
	      error ("illegal operand to '%s", ada_attribute_name (atr));
	  tem = longest_to_int (exp->elts[*pos+2].longconst);
	  *pos += 4;

	  if (noside == EVAL_SKIP)
	    goto nosideret;

	  if (tem < 1 || tem > ada_array_arity (VALUE_TYPE (arg1)))
	    error ("invalid dimension number to '%s", ada_attribute_name (atr));

	  if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    {
	      type = ada_index_type (VALUE_TYPE (arg1), tem);
	      if (type == NULL) 
		error ("attempt to take bound of something that is not an array");
	      return allocate_value (type);
	    }

	  switch (atr) 
	    {
	    default: 
	      error ("unexpected attribute encountered");
	    case ATR_FIRST:
	      return ada_array_bound (arg1, tem, 0);
	    case ATR_LAST:
	      return ada_array_bound (arg1, tem, 1);
	    case ATR_LENGTH:
	      return ada_array_length (arg1, tem);
	    }

	case ATR_TAG:
	  arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  if (noside == EVAL_SKIP)
	    goto nosideret;

	  if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    return 	
	      value_zero (ada_tag_type (arg1), not_lval);
	  
	  return ada_value_tag (arg1);
	  
	case ATR_MIN:
	case ATR_MAX:
	  evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
	  arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  if (noside == EVAL_SKIP)
	    goto nosideret;
	  else if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    return value_zero (VALUE_TYPE (arg1), not_lval);
	  else
	    return value_binop (arg1, arg2, 
				atr == ATR_MIN ? BINOP_MIN : BINOP_MAX);

	case ATR_POS:
	  evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
	  arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  if (noside == EVAL_SKIP)
	    goto nosideret;
	  else if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    return value_zero (builtin_type_ada_int, not_lval);
	  else 
	    return value_pos_atr (arg1);

	case ATR_VAL:
	  evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
	  arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  type = exp->elts[pc + 5].type;
	  if (noside == EVAL_SKIP)
	    goto nosideret;
	  else if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    return value_zero (type, not_lval);
	  else 
	    return value_val_atr (type, arg1);
	}

    case BINOP_EXP:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (binop_user_defined_p (op, arg1, arg2))
	return unwrap_value (value_x_binop (arg1, arg2, op, OP_NULL,EVAL_NORMAL));
      else
	if (noside == EVAL_AVOID_SIDE_EFFECTS)
	  return value_zero (VALUE_TYPE (arg1), not_lval);
      else
	return value_binop (arg1, arg2, op);

    case UNOP_PLUS:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (unop_user_defined_p (op, arg1))
	return unwrap_value (value_x_unop (arg1, op,EVAL_NORMAL));
      else
	return arg1;

    case UNOP_ABS:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (value_less (arg1, value_zero (VALUE_TYPE (arg1), not_lval)))
	return value_neg (arg1);
      else
	return arg1;

    case UNOP_IND:
      if (expect_type && TYPE_CODE (expect_type) == TYPE_CODE_PTR)
        expect_type = TYPE_TARGET_TYPE (check_typedef (expect_type));
      arg1 = evaluate_subexp (expect_type, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	{
	  type = check_typedef (VALUE_TYPE (arg1));
	  if (TYPE_CODE (type) == TYPE_CODE_PTR
	      || TYPE_CODE (type) == TYPE_CODE_REF
	      /* In C you can dereference an array to get the 1st elt.  */
	      || TYPE_CODE (type) == TYPE_CODE_ARRAY
	      )
	    return value_zero (ada_aligned_type (TYPE_TARGET_TYPE (type)),
			       lval_memory);
	  else if (TYPE_CODE (type) == TYPE_CODE_INT)
	    /* GDB allows dereferencing an int.  */
	    return value_zero (builtin_type_int, lval_memory);
	  else if (ada_is_array_descriptor (VALUE_TYPE (arg1)))
	      /* GDB allows dereferencing GNAT array descriptors. */
	      return value_at_lazy (ada_type_of_array (arg1, 0), 0,NULL);
	  else
	    error ("Attempt to take contents of a non-pointer value.");
	}
      else if (ada_is_array_descriptor (VALUE_TYPE (arg1)))
	/* GDB allows dereferencing GNAT array descriptors. */
	return ada_coerce_to_simple_array (arg1);
      else
	return unwrap_value (value_ind (arg1));

    case STRUCTOP_STRUCT:
      tem = longest_to_int (exp->elts[pc + 1].longconst);
      (*pos) += 3 + BYTES_TO_EXP_ELEM (tem + 1);
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return value_zero (ada_aligned_type 
			   (ada_lookup_struct_elt_type (VALUE_TYPE (arg1),
							&exp->elts[pc + 2].string,
							0, NULL)),
			   lval_memory);
      else
	return unwrap_value (ada_value_struct_elt (arg1,
						   &exp->elts[pc + 2].string,
						   "record"));
    case OP_TYPE:
      /* The value is not supposed to be used. This is here to make it
         easier to accommodate expressions that contain types. */
      (*pos) += 2;
      if (noside == EVAL_SKIP)
	goto nosideret;
      else if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return allocate_value (builtin_type_void);
      else 
	error ("Attempt to use a type name as an expression");
      
    case STRUCTOP_PTR:
      tem = longest_to_int (exp->elts[pc + 1].longconst);
      (*pos) += 3 + BYTES_TO_EXP_ELEM (tem + 1);
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return value_zero (ada_aligned_type 
			   (ada_lookup_struct_elt_type (VALUE_TYPE (arg1),
							&exp->elts[pc + 2].string,
							0, NULL)),
			   lval_memory);
      else
	return unwrap_value (ada_value_struct_elt (arg1,
						   &exp->elts[pc + 2].string,
						   "record access"));
    }

 nosideret:
  return value_from_longest (builtin_type_long, (LONGEST) 1);
}


/* Table mapping opcodes into strings for printing operators
   and precedences of the operators.  */

static const struct op_print ada_op_print_tab[] =
  {
    {":=",  BINOP_ASSIGN, PREC_ASSIGN, 1},
    {"or else", BINOP_LOGICAL_OR, PREC_LOGICAL_OR, 0},
    {"and then", BINOP_LOGICAL_AND, PREC_LOGICAL_AND, 0},
    {"or",  BINOP_BITWISE_IOR, PREC_BITWISE_IOR, 0},
    {"xor",  BINOP_BITWISE_XOR, PREC_BITWISE_XOR, 0},
    {"and",  BINOP_BITWISE_AND, PREC_BITWISE_AND, 0},
    {"=", BINOP_EQUAL, PREC_EQUAL, 0},
    {"/=", BINOP_NOTEQUAL, PREC_EQUAL, 0},
    {"<=", BINOP_LEQ, PREC_ORDER, 0},
    {">=", BINOP_GEQ, PREC_ORDER, 0},
    {">",  BINOP_GTR, PREC_ORDER, 0},
    {"<",  BINOP_LESS, PREC_ORDER, 0},
    {">>", BINOP_RSH, PREC_SHIFT, 0},
    {"<<", BINOP_LSH, PREC_SHIFT, 0},
    {"+",  BINOP_ADD, PREC_ADD, 0},
    {"-",  BINOP_SUB, PREC_ADD, 0},
    {"&",  BINOP_CONCAT, PREC_ADD, 0},
    {"*",  BINOP_MUL, PREC_MUL, 0},
    {"/",  BINOP_DIV, PREC_MUL, 0},
    {"rem",  BINOP_REM, PREC_MUL, 0},
    {"mod",  BINOP_MOD, PREC_MUL, 0},
    {"**", BINOP_EXP, PREC_REPEAT, 0 },
    {"@",  BINOP_REPEAT, PREC_REPEAT, 0},
    {"-",  UNOP_NEG, PREC_PREFIX, 0},
    {"+",  UNOP_PLUS, PREC_PREFIX, 0},
    {"not",  UNOP_LOGICAL_NOT, PREC_PREFIX, 0},
    {"not",  UNOP_COMPLEMENT, PREC_PREFIX, 0},
    {"*",  UNOP_IND, PREC_PREFIX, 0},  /* FIXME: postfix .ALL */
    {"&",  UNOP_ADDR, PREC_PREFIX, 0}, /* FIXME: postfix 'ACCESS */
    {NULL, 0, 0, 0}
};


struct type* builtin_type_ada_int;
struct type* builtin_type_ada_short;
struct type* builtin_type_ada_long;
struct type* builtin_type_ada_long_long;
struct type* builtin_type_ada_char;
struct type* builtin_type_ada_float;
struct type* builtin_type_ada_double;
struct type* builtin_type_ada_long_double;
struct type* builtin_type_ada_natural;
struct type* builtin_type_ada_positive;

struct type ** const (ada_builtin_types[]) = 
{
  
  &builtin_type_ada_int,
  &builtin_type_ada_long,
  &builtin_type_ada_short,
  &builtin_type_ada_char,
  &builtin_type_ada_float,
  &builtin_type_ada_double,
  &builtin_type_ada_long_long,
  &builtin_type_ada_long_double,
  &builtin_type_ada_natural,
  &builtin_type_ada_positive,

  /* The following types are carried over from C for convenience. */
  &builtin_type_int,
  &builtin_type_long,
  &builtin_type_short,
  &builtin_type_char,
  &builtin_type_float,
  &builtin_type_double,
  &builtin_type_long_long,
  &builtin_type_void,
  &builtin_type_signed_char,
  &builtin_type_unsigned_char,
  &builtin_type_unsigned_short,
  &builtin_type_unsigned_int,
  &builtin_type_unsigned_long,
  &builtin_type_unsigned_long_long,
  &builtin_type_long_double,
  &builtin_type_complex,
  &builtin_type_double_complex,
  0
};

const struct language_defn ada_language_defn = {
  "ada",			/* Language name */
  language_ada,
  ada_builtin_types,
  range_check_off,
  type_check_off,
  ada_parse,
  ada_error,
  ada_evaluate_subexp,
  ada_printchar,		/* Print a character constant */
  ada_printstr,			/* Function to print string constant */
  ada_create_fundamental_type,	/* Create fundamental type in this language */
  ada_print_type,		/* Print a type using appropriate syntax */
  ada_val_print,		/* Print a value using appropriate syntax */
  ada_value_print,		/* Print a top-level value */
  {"",     "",    "",  ""},	/* Binary format info */
#if 0
  {"8#%lo#",  "8#",   "o", "#"},	/* Octal format info */
  {"%ld",   "",    "d", ""},	/* Decimal format info */
  {"16#%lx#", "16#",  "x", "#"},	/* Hex format info */
#else
  /* Copied from c-lang.c. */
  {"0%lo",  "0",   "o", ""},	/* Octal format info */
  {"%ld",   "",    "d", ""},	/* Decimal format info */
  {"0x%lx", "0x",  "x", ""},	/* Hex format info */
#endif
  ada_op_print_tab,		/* expression operators for printing */
  1,				/* c-style arrays (FIXME?) */
  0,				/* String lower bound (FIXME?) */
  &builtin_type_ada_char,
  LANG_MAGIC
};

void
_initialize_ada_language ()
{
  builtin_type_ada_int =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / TARGET_CHAR_BIT,
	       0,
	       "integer", (struct objfile *) NULL);
  builtin_type_ada_long =
    init_type (TYPE_CODE_INT, TARGET_LONG_BIT / TARGET_CHAR_BIT,
	       0,
	       "long_integer", (struct objfile *) NULL);
  builtin_type_ada_short =
    init_type (TYPE_CODE_INT, TARGET_SHORT_BIT / TARGET_CHAR_BIT,
	       0,
	       "short_integer", (struct objfile *) NULL);
  builtin_type_ada_char =
    init_type (TYPE_CODE_INT, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       0,
	       "character", (struct objfile *) NULL);
  builtin_type_ada_float =
    init_type (TYPE_CODE_FLT, TARGET_FLOAT_BIT / TARGET_CHAR_BIT,
	       0,
	       "float", (struct objfile *) NULL);
  builtin_type_ada_double =
    init_type (TYPE_CODE_FLT, TARGET_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "long_float", (struct objfile *) NULL);
  builtin_type_ada_long_long =
    init_type (TYPE_CODE_INT, TARGET_LONG_LONG_BIT / TARGET_CHAR_BIT,
	       0,
	       "long_long_integer", (struct objfile *) NULL);
  builtin_type_ada_long_double =
    init_type (TYPE_CODE_FLT, TARGET_LONG_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "long_long_float", (struct objfile *) NULL);
  builtin_type_ada_natural =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / TARGET_CHAR_BIT,
	       0,
	       "natural", (struct objfile *) NULL);
  builtin_type_ada_positive =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / TARGET_CHAR_BIT,
	       0,
	       "positive", (struct objfile *) NULL);

  add_language (&ada_language_defn);
}
