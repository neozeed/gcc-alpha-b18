/* Support for printing Ada values for GDB, the GNU debugger.  
   Copyright 1986, 1988, 1989, 1991, 1992, 1993, 1994, 1997
             Free Software Foundation, Inc.

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

#include "defs.h"
#include "symtab.h"
#include "gdbtypes.h"
#include "expression.h"
#include "value.h"
#include "demangle.h"
#include "valprint.h"
#include "language.h"
#include "ada-lang.h"
#include "c-lang.h"

extern int inspect_it;

static int
print_field_values PARAMS ((struct type*, char*, GDB_FILE*, 
			    int, int, enum val_prettyprint,
			    int, struct type*, char*));

static int
print_variant_part PARAMS ((struct type*, int, char*, 
			    GDB_FILE*, int, int, enum val_prettyprint,
			    int, struct type*, char*));



/* Assuming TYPE is a simple array type, prints its lower bound on STREAM,
   if non-standard (i.e., other than 1 for numbers, other than lower bound
   of index type for enumerated type). Returns 1 if something printed, 
   otherwise 0. */

static int 
print_optional_low_bound (stream, type)
     GDB_FILE *stream;
     struct type *type;
{
  struct type *range_type = TYPE_INDEX_TYPE (type);
  struct type *index_type = TYPE_TARGET_TYPE (range_type);
  long low_bound = TYPE_LOW_BOUND (range_type);

  switch (TYPE_CODE (index_type)) {
  case TYPE_CODE_ENUM:
    if (low_bound == TYPE_FIELD_BITPOS (index_type, 0))
      return 0;
    break;
  case TYPE_CODE_UNDEF:
    index_type = builtin_type_long;
    /* FALL THROUGH */
  default:
    if (low_bound == 1)
      return 0;
    break;
  }

  print_type_scalar (index_type, (LONGEST) low_bound, stream);
  fprintf_filtered (stream, " => ");
  return 1;
}

/* Print data of type TYPE located at VALADDR (within GDB), which came from
   the inferior at address ADDRESS, onto stdio stream STREAM according to
   FORMAT (a letter as for the printf % codes or 0 for natural format).  
   The data at VALADDR is in target byte order.

   If the data is printed as a string, returns the number of string characters
   printed.

   If DEREF_REF is nonzero, then dereference references, otherwise just print
   them like pointers.

   RECURSE indicates the amount of indentation to supply before
   continuation lines; this amount is roughly twice the value of RECURSE.

   When PRETTY is non-zero, prints record fields on separate lines.
   (For some reason, the current version of gdb instead uses a global
   variable---prettyprint_arrays--- to causes a similar effect on
   arrays.)  */

int
ada_val_print (type, valaddr, address, stream, format, deref_ref, recurse,
	       pretty)
     struct type *type;
     char *valaddr;
     CORE_ADDR address;
     GDB_FILE *stream;
     int format;
     int deref_ref;
     int recurse;
     enum val_prettyprint pretty;
{
  unsigned int len;
  struct type *elttype;
  unsigned int eltlen;
  LONGEST val;
  CORE_ADDR addr;

  CHECK_TYPEDEF (type);

  valaddr = ada_aligned_value_addr (type, valaddr);
  type = ada_aligned_type (type);

  switch (TYPE_CODE (type))
    {
    default:
      return c_val_print (type, valaddr, address, stream, format, 
			  deref_ref, recurse, pretty);

    case TYPE_CODE_STRUCT:
	if (ada_is_array_descriptor (type))
	  {
	    value_ptr val = 
		ada_coerce_to_simple_array_ptr (value_at_lazy (type, address,NULL));
	    return ada_val_print (VALUE_TYPE (val), VALUE_CONTENTS (val),
				  VALUE_ADDRESS (val), stream, format, 
				  deref_ref, recurse, pretty);
	  }
	else if (ada_is_bogus_array_descriptor (type))
	  {
	    fprintf_filtered (stream, "(...?)");
	    return 0;
	  }			      
	else
	  {
	    ada_print_record  (type, valaddr, address, stream, format,
			       recurse, pretty);
	    return 0;
	  }

    case TYPE_CODE_ARRAY:
      if (TYPE_LENGTH (type) > 0 && TYPE_LENGTH (TYPE_TARGET_TYPE (type)) > 0)
	{
	  elttype = TYPE_TARGET_TYPE (type);
	  eltlen = TYPE_LENGTH (elttype);
	  len = TYPE_LENGTH (type) / eltlen;
	  /* For an array of chars, print with string syntax.  */
	  if (ada_is_string_type (type) 
	      && (format == 0 || format == 's'))
	    {
	      if (prettyprint_arrays)
		{
		  print_spaces_filtered (2 + 2 * recurse, stream);
		}
	      /* If requested, look for the first null char and only print
		 elements up to it.  */
	      if (stop_print_at_null)
		{
		  int temp_len;
		  
		  /* Look for a NULL char. */
		  for (temp_len = 0;
		       valaddr[temp_len]
		       && temp_len < len && temp_len < print_max;
		       temp_len++);
		  len = temp_len;
		}
	      
	      LA_PRINT_STRING (stream, valaddr, len, 0);
	    }
	  else
	    {
	      len = 0;
	      fprintf_filtered (stream, "(");
	      print_optional_low_bound (stream, type);
	      val_print_array_elements (type, valaddr, address, stream,
					format, deref_ref, recurse, pretty, 0);
	      fprintf_filtered (stream, ")");
	    }
	  gdb_flush (stream);
	  return len;
	}
    }
}

/* Assuming that field FIELD_NUM of TYPE is a variant part wrapper 
   (VARIANTS clause) in a value of type OUTER_TYPE that is stored in GDB 
   at OUTER_VALADDR, determine which variant clause (field number in TYPE, 
   numbering from 0) is applicable.  Returns -1 if none are. */

static int 
which_variant_applies (type, field_num, outer_type, outer_valaddr)
     struct type *type;
     int field_num;
     struct type *outer_type;
     char* outer_valaddr;
{
  int others_clause;
  int i;
  int disp;
  struct type* discrim_type;
  char* discrim_name = ada_variant_discrim_name (type, field_num, outer_type);
  LONGEST discrim_val;
  struct type* var_type = TYPE_FIELD_TYPE (type, field_num);

  disp = 0;
  discrim_type = 
    ada_lookup_struct_elt_type (outer_type, discrim_name, 1, &disp);
  if (discrim_type == NULL)
    return -1;
  discrim_val = unpack_long (discrim_type, outer_valaddr + disp);

  others_clause = -1;
  for (i = 0; i < TYPE_NFIELDS (var_type); i += 1)
    {
      if (ada_is_others_clause (var_type, i))
	others_clause = i;
      else if (ada_in_variant (discrim_val, var_type, i))
	return i;
    }

  return others_clause;
}

static int
print_variant_part (type, field_num, valaddr, 
		    stream, format, recurse, pretty, comma_needed,
		    outer_type, outer_valaddr)
     struct type *type;
     int field_num;
     char *valaddr;
     GDB_FILE *stream;
     int format;
     int recurse;
     enum val_prettyprint pretty;
     int comma_needed;
     struct type *outer_type;
     char *outer_valaddr;
{
  int which = 
    which_variant_applies (type, field_num, outer_type, outer_valaddr);
  struct type *var_type = TYPE_FIELD_TYPE (type, field_num);

  if (which < 0)
    return 0;
  else
    return print_field_values (TYPE_FIELD_TYPE (var_type, which),
			       valaddr
			       + TYPE_FIELD_BITPOS (type, field_num)/8
			       + TYPE_FIELD_BITPOS (var_type, which)/8,
			       stream, format, recurse, pretty,
			       comma_needed, outer_type, outer_valaddr);
}

int
ada_value_print (val, stream, format, pretty)
     value_ptr val;
     GDB_FILE *stream;
     int format;
     enum val_prettyprint pretty;
{
  struct type *type = VALUE_TYPE (val);

  /* If it is a pointer, indicate what it points to. */
  if (TYPE_CODE (type) == TYPE_CODE_PTR ||
      TYPE_CODE (type) == TYPE_CODE_REF)
    {
      /* Hack:  remove (char *) for char strings.  Their
	 type is indicated by the quoted string anyway. */
      if (TYPE_CODE (type) == TYPE_CODE_PTR &&
	  TYPE_LENGTH (TYPE_TARGET_TYPE (type)) == sizeof(char) &&
	  TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_INT &&
	  !TYPE_UNSIGNED (TYPE_TARGET_TYPE (type)))
	{
	  /* Print nothing */
	}
      else
	{
	  fprintf_filtered (stream, "(");
	  type_print (type, "", stream, -1);
	  fprintf_filtered (stream, ") ");
	}
    }
  else if (ada_is_array_descriptor (type)) 
    {
      fprintf_filtered (stream, "(");
      type_print (type, "", stream, -1);
      fprintf_filtered (stream, ") ");
    }
  else if (ada_is_bogus_array_descriptor (type))
    {
      fprintf_filtered (stream, "(");
      type_print (type, "", stream, -1);
      fprintf_filtered (stream, ") (...?)");
      return 0;
    }
  return (val_print (type, VALUE_CONTENTS (val),
		     VALUE_ADDRESS (val), stream, format, 1, 0, pretty));
}

ada_print_record (type, valaddr, address, stream, format, recurse, pretty)
     struct type *type;
     char *valaddr;
     CORE_ADDR address;
     GDB_FILE *stream;
     int format;
     int recurse;
     enum val_prettyprint pretty;
{
  CHECK_TYPEDEF (type);

  fprintf_filtered (stream, "(");

  if (print_field_values (type, valaddr, stream, format, recurse, pretty,
			  0, type, valaddr) != 0
      && pretty)
    {
      fprintf_filtered (stream, "\n");
      print_spaces_filtered (2 * recurse, stream);
    }

  fprintf_filtered (stream, ")");
}

/* Print out fields of value at VALADDR having structure type TYPE.
  
   TYPE, VALADDR, STREAM, FORMAT, RECURSE, and PRETTY have the
   same meanings as in ada_print_value and ada_val_print.   

   OUTER_TYPE and OUTER_VALADDR give type and address of enclosing record
   (used to get discriminant values when printing variant parts).

   COMMA_NEEDED is 1 if fields have been printed at the current recursion 
   level, so that a comma is needed before any field printed by this
   call. 

   Returns 1 if COMMA_NEEDED or any fields were printed. */

static int
print_field_values (type, valaddr, stream, format, recurse, pretty, 
		    comma_needed, outer_type, outer_valaddr)
     struct type *type;
     char *valaddr;
     GDB_FILE *stream;
     int format;
     int recurse;
     enum val_prettyprint pretty;
     int comma_needed;
     struct type *outer_type;
     char *outer_valaddr;
{
  int i, len;

  len = TYPE_NFIELDS (type);

  for (i = 0; i < len; i += 1)
    {
      if (ada_is_ignored_field (type, i))
	  continue;

      if (ada_is_wrapper_field (type, i))
	{
	  comma_needed = 
	    print_field_values (TYPE_FIELD_TYPE (type, i),
				valaddr 
				+ TYPE_FIELD_BITPOS (type, i) / 8,
				stream, format, recurse, pretty,
				comma_needed, type, valaddr);
	  continue;
	}
      else if (ada_is_variant_part (type, i))
	{
	  comma_needed =
	    print_variant_part (type, i, valaddr,
				stream, format, recurse, pretty, comma_needed,
				outer_type, outer_valaddr);
	  continue;
	}

      if (comma_needed)
	fprintf_filtered (stream, ", ");
      comma_needed = 1;

      if (pretty)
	{
	  fprintf_filtered (stream, "\n");
	  print_spaces_filtered (2 + 2 * recurse, stream);
	}
      else 
	{
	  wrap_here (n_spaces (2 + 2 * recurse));
	}
      if (inspect_it)
	{
	  if (TYPE_CODE (TYPE_FIELD_TYPE (type, i)) == TYPE_CODE_PTR)
	    fputs_filtered ("\"( ptr \"", stream);
	  else
	    fputs_filtered ("\"( nodef \"", stream);
	  fprintf_symbol_filtered (stream, TYPE_FIELD_NAME (type, i),
				   language_cplus, DMGL_NO_OPTS);
	  fputs_filtered ("\" \"", stream);
	  fprintf_symbol_filtered (stream, TYPE_FIELD_NAME (type, i),
				   language_cplus, DMGL_NO_OPTS);
	  fputs_filtered ("\") \"", stream);
	}
      else
	{
	  annotate_field_begin (TYPE_FIELD_TYPE (type, i));
	  fprintf_symbol_filtered (stream, TYPE_FIELD_NAME (type, i),
				   language_cplus, DMGL_NO_OPTS);
	  annotate_field_name_end ();
	  fputs_filtered (" => ", stream);
	  annotate_field_value ();
	}

      if (TYPE_FIELD_PACKED (type, i))
	{
	  value_ptr v;

	  /* Bitfields require special handling, especially due to byte
	     order problems.  */
	  if (TYPE_FIELD_IGNORE (type, i))
	    {
	      fputs_filtered ("<optimized out or zero length>", stream);
	    }
	  else
	    {
	      v = value_from_longest (TYPE_FIELD_TYPE (type, i),
				      unpack_field_as_long (type, valaddr, i));

	      val_print (TYPE_FIELD_TYPE(type, i), VALUE_CONTENTS (v), 0,
			 stream, format, 0, recurse + 1, pretty);
	    }
	}
      else
	  val_print (TYPE_FIELD_TYPE (type, i), 
		     valaddr + TYPE_FIELD_BITPOS (type, i) / 8,
		     0, stream, format, 0, recurse + 1, pretty);
      annotate_field_end ();
    }

  return comma_needed;
}
