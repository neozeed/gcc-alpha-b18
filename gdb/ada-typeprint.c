/* Support for printing Ada types for GDB, the GNU debugger.
   Copyright 1986, 1988, 1989, 1991, 1997 Free Software Foundation, Inc.

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
#include "obstack.h"
#include "bfd.h"		/* Binary File Description */
#include "symtab.h"
#include "gdbtypes.h"
#include "expression.h"
#include "value.h"
#include "gdbcore.h"
#include "target.h"
#include "command.h"
#include "gdbcmd.h"
#include "language.h"
#include "demangle.h"
#include "c-lang.h"
#include "typeprint.h"
#include "ada-lang.h"

#include <ctype.h>
#include <string.h>
#include <errno.h>

static int
print_record_field_types PARAMS ((struct type *, struct type *, 
				  GDB_FILE *, int, int));


static char* name_buffer;
static int name_buffer_len;

/* The (demangled) Ada name of TYPE. This value persists until the
   next call. */

static char*
ada_type_name (type)
     struct type *type;
{
  if (type == NULL || TYPE_NAME (type) == NULL)
    return NULL;
  else 
    {
      char* raw_name = TYPE_NAME (type);
      char *s, *q; 

      if (name_buffer == NULL || name_buffer_len <= strlen (raw_name))
	{
	  name_buffer_len = 16 + 2 * strlen (raw_name);
	  name_buffer = xrealloc (name_buffer, name_buffer_len);
	}
      strcpy (name_buffer, raw_name);

      s = (char*) strstr (name_buffer, "___");
      if (s != NULL)
	*s = '\0';

      s = name_buffer + strlen (name_buffer) - 1;
      while (s > name_buffer && (s[0] != '_' || s[-1] != '_'))
	s -= 1;

      if (s == name_buffer)
	return name_buffer;

      if (! islower (s[1]))
	return NULL;

      for (s = q = name_buffer; *s != '\0'; q += 1)
	{
	  if (s[0] == '_' && s[1] == '_')
	    {
	      *q = '.'; s += 2;
	    }
	  else
	    {
	      *q = *s; s += 1;
	    }
	}
      *q = '\0';
      return name_buffer;
    }
}


/* Print a description of a type in the format of a 
   typedef for the current language.
   NEW is the new name for a type TYPE. */

void
ada_typedef_print (type, new, stream)
   struct type *type;
   struct symbol *new;
   GDB_FILE *stream;
{
  fprintf_filtered (stream, "type %s is ", SYMBOL_SOURCE_NAME(new));
  type_print (type, "", stream, 1);
}

/* Print range type TYPE on STREAM. */

static void
print_range (type, stream)
     struct type *type;
     GDB_FILE *stream;
{
  print_type_scalar (type, (LONGEST) TYPE_LOW_BOUND (type), stream);
  fprintf_filtered (stream, " .. ");
  print_type_scalar (type, (LONGEST) TYPE_HIGH_BOUND (type), stream);
}

/* Print enumerated type TYPE on STREAM. */

static void
print_enum_type (type, stream)
     struct type *type;
     GDB_FILE *stream;
{
  int len = TYPE_NFIELDS (type);
  int i, lastval;

  fprintf_filtered (stream, "(");
  wrap_here (" ");

  lastval = 0;
  for (i = 0; i < len; i++)
    {
      QUIT;
      if (i) fprintf_filtered (stream, ", ");
      wrap_here ("    ");
      fputs_filtered (TYPE_FIELD_NAME (type, i), stream);
      if (lastval != TYPE_FIELD_BITPOS (type, i))
	{
	  fprintf_filtered (stream, " => %d", TYPE_FIELD_BITPOS (type, i));
	  lastval = TYPE_FIELD_BITPOS (type, i);
	}
      lastval += 1;
    }
  fprintf_filtered (stream, ")");
}

/* Print simple (constrained) array type TYPE on STREAM.  LEVEL is the 
   recursion (indentation) level, in case the element type itself has 
   nested structure, and SHOW is the number of levels of record level
   to show (see ada_print_type). */

static void
print_array_type (type, stream, show, level)
     struct type *type;
     GDB_FILE *stream;
     int show;
     int level;
{
  fprintf_filtered (stream, "array (");

  if (show < 0) 
    fprintf_filtered (stream, "...");
  else
    {
      if (ada_is_simple_array (type)) 
	{
	  struct type* arr_type;

	  for (arr_type = type; TYPE_CODE (arr_type) == TYPE_CODE_ARRAY;
	       arr_type = TYPE_TARGET_TYPE (arr_type))
	    {
	      if (arr_type != type)
		fprintf_filtered (stream, ", ");
	      print_range (TYPE_INDEX_TYPE (arr_type), stream);
	    }
	}
      else 
	{
	  int i, i0;
	  for (i = i0 = ada_array_arity (type); i > 0; i -= 1)
	    fprintf_filtered (stream, "%s<>", i == i0 ? "" : ", ");
	}
    }

  fprintf_filtered (stream, ") of ");
  wrap_here ("");
  ada_print_type (ada_array_element_type (type), "", stream, show, level+1);
}

/* Print the choices encoded by field FIELD_NUM of variant-part TYPE on
   STREAM, assuming the VAL_TYPE is the type of the values. */

static void
print_choices (type, field_num, stream, val_type)
     struct type *type;
     int field_num;
     GDB_FILE *stream;
     struct type *val_type;
{
  int have_output;
  int p;
  const char* name = TYPE_FIELD_NAME (type, field_num);

  have_output = 0;

  /* Skip over leading 'V': NOTE soon to be obsolete. */
  if (name[0] == 'V')
    {
      if (! ada_scan_number (name, 1, NULL, &p))
	goto Huh;
    }
  else
    p = 0;

  while (1)
    {
      switch (name[p]) 
	{
	default:
	  return;
	case 'S':
	case 'R':
	case 'O':
	  if (have_output) 
	    fprintf_filtered (stream, " | ");
	  have_output = 1;
	  break;
	}

      switch (name[p]) 
	{
	case 'S':
	  {
	    LONGEST W;
	    if (! ada_scan_number (name, p + 1, &W, &p))
	      goto Huh;
	    print_type_scalar (val_type, W, stream);
	    break;
	  }
	case 'R':
	  {
	    LONGEST L, U;
	    if (! ada_scan_number (name, p + 1, &L, &p)
		|| name[p] != 'T'
		|| ! ada_scan_number (name, p + 1, &U, &p))
	      goto Huh;
	    print_type_scalar (val_type, L, stream);
	    fprintf_filtered (stream, " .. ");
	    print_type_scalar (val_type, U, stream);
	    break;
	  }
	case 'O':
	  fprintf_filtered (stream, "others");
	  p += 1;
	  break;
	}
    }

Huh:
  fprintf_filtered (stream, "??");

}

/* Assuming that field FIELD_NUM of TYPE is a VARIANTS field whose 
   discriminant is contained in OUTER_TYPE, print its variants on STREAM.  
   LEVEL is the recursion
   (indentation) level, in case any of the fields themselves have
   nested structure, and SHOW is the number of levels of record level
   to show (see ada_print_type). For this purpose, fields nested in a
   variant part are taken to be at the same level as the fields
   immediately outside the variant part. */

static void
print_variant_clauses (type, field_num, outer_type, stream, show, level)
     struct type *type;
     int field_num;
     struct type *outer_type;
     GDB_FILE *stream;
     int show;
     int level;
{
  int i;
  struct type *discr_type = 
    ada_variant_discrim_type (type, field_num, outer_type);
  struct type *var_type = TYPE_FIELD_TYPE (type, field_num);

  for (i = 0; i < TYPE_NFIELDS (var_type); i += 1) 
    {
      fprintf_filtered (stream, "\n%*swhen ", level + 4, "");
      print_choices (var_type, i, stream, discr_type);
      fprintf_filtered (stream, " =>");
      if (print_record_field_types (TYPE_FIELD_TYPE (var_type, i), 
				    outer_type, stream, show, level+4) <= 0)
	fprintf_filtered (stream, " null;");
    }
}

/* Assuming that field FIELD_NUM of TYPE is a variant part whose 
   discriminants are contained in OUTER_TYPE, print a description of it
   on STREAM.  LEVEL is the recursion (indentation) level, in case any of 
   the fields themselves have nested structure, and SHOW is the number of 
   levels of record level to show (see ada_print_type). For this purpose, 
   fields nested in a variant part are taken to be at the same level as the 
   fields immediately outside the variant part. */

static void
print_variant_part (type, field_num, outer_type, stream, show, level)
     struct type *type;
     int field_num;
     struct type *outer_type;
     GDB_FILE *stream;
     int show;
     int level;
{
  fprintf_filtered (stream, "\n%*scase %s is", level + 4, "",
		    ada_variant_discrim_name (type, field_num, outer_type));
  print_variant_clauses (type, field_num, outer_type, stream, show, level + 4);
  fprintf_filtered (stream, "\n%*send case;", level + 4, "");
}

/* Print a description on STREAM of the fields in record type TYPE, whose 
   discriminants are in OUTER_TYPE.  LEVEL is the recursion (indentation) 
   level, in case any of the fields themselves have nested structure, 
   and SHOW is the number of levels of record level to show 
   (see ada_print_type).  Does not print parent type information of TYPE. 
   Returns 0 if no fields printed, -1 for an incomplete type, else > 0. 
   Prints each field beginning on a new line, but does not put a new line at
   end. */

static int
print_record_field_types (type, outer_type, stream, show, level)
     struct type *type;
     struct type *outer_type;
     GDB_FILE *stream;
     int show;
     int level;
{
  int len, i, flds;

  flds = 0;
  len = TYPE_NFIELDS (type);

  if (len == 0 && (TYPE_FLAGS (type) & TYPE_FLAG_STUB) != 0)
    return -1;

  for (i = 0; i < len; i += 1)
    {
      QUIT;

      if (ada_is_parent_field (type, i) 
	  || ada_is_ignored_field (type, i))
	;
      else if (ada_is_wrapper_field (type, i))
	flds += print_record_field_types (TYPE_FIELD_TYPE (type, i), type,
					  stream, show, level);
      else if (ada_is_variant_part (type, i)) 
	{
	  print_variant_part (type, i, type, stream, show, level);
	  flds = 1;
	}
      else
	{
	  flds += 1;
	  fprintf_filtered (stream, "\n%*s", level + 4, "");
	  ada_print_type (TYPE_FIELD_TYPE (type, i),
			  TYPE_FIELD_NAME (type, i),
			  stream, show - 1, level + 4);
	  fprintf_filtered (stream, ";");
	}
    }

  return flds;
}

/* Print record type TYPE on STREAM.  LEVEL is the recursion (indentation) 
   level, in case the element type itself has nested structure, and SHOW is 
   the number of levels of record level to show (see ada_print_type). */

static void
print_record_type (type, stream, show, level)
     struct type *type;
     GDB_FILE *stream;
     int show;
     int level;
{
  struct type *parent_type = ada_parent_type (type);

  if (parent_type != NULL && TYPE_NAME (parent_type) != NULL) 
    fprintf (stream, "new %s with ", ada_type_name (parent_type));
  else if (parent_type == NULL && ada_is_tagged_type (type))
    fprintf (stream, "tagged ");

  fprintf_filtered (stream, "record");

  if (show < 0)
    fprintf_filtered (stream, " ... end record");
  else
    {
      int flds;

      flds = 0;
      if (parent_type != NULL && TYPE_NAME (parent_type) == NULL)
	flds += print_record_field_types (parent_type, parent_type, 
					  stream, show, level);
      flds += print_record_field_types (type, type, stream, show, level);
      
      if (flds > 0)
	fprintf_filtered (stream, "\n%*send record", level, "");
      else if (flds < 0) 
	fprintf_filtered (stream, " <incomplete type> end record");
      else 
	fprintf_filtered (stream, " null; end record");
    }
}

/* Print function or procedure type TYPE on STREAM.  Make it a header
   for function or procedure NAME if NAME is not null. */
static void
print_func_type (type, stream, name)
     struct type *type;
     GDB_FILE *stream;
     char* name;
{
  int i, len = TYPE_NFIELDS (type);

  if (TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_VOID)
    fprintf_filtered (stream, "procedure");
  else
    fprintf_filtered (stream, "function");

  if (name != NULL && name[0] != '\0') 
    fprintf_filtered (stream, " %s", name);

  if (len > 0) 
    {
      fprintf_filtered (stream, " (");
      for (i = 0; i < len; i += 1)
	{
	  if (i > 0)
	    {
	      fputs_filtered ("; ", stream);
	      wrap_here ("    ");
	    }
	  fprintf_filtered (stream, "a%d: ", i+1);
	  ada_print_type (TYPE_FIELD_TYPE (type, i), "", stream, -1, 0);
	}
      fprintf_filtered (stream, ")");
    }      

  if (TYPE_CODE (TYPE_TARGET_TYPE (type)) != TYPE_CODE_VOID)
    {
      fprintf_filtered (stream, " return ");
      ada_print_type (TYPE_TARGET_TYPE (type), "", stream, 0, 0);
    }
}


/* Print a description of a type TYPE.
   Output goes to STREAM (via stdio).
   If VARSTRING is a non-empty string, print as an Ada variable/field
       declaration.
   SHOW+1 is the maximum number of levels of internal type structure 
      to show (this applies to record types, enumerated types, and
      array types).
   SHOW is the number of levels of internal type structure to show
      when there is a type name for the SHOWth deepest level (0th is 
      outer level).
   When SHOW<0, no inner structure is shown.
   LEVEL indicates level of recursion (for nested definitions). */

void
ada_print_type (type, varstring, stream, show, level)
     struct type *type;
     char *varstring;
     GDB_FILE *stream;
     int show;
     int level;
{
  enum type_code code;
  int demangled_args;
  char* type_name = ada_type_name (type);
  int is_var_decl = (varstring != NULL && varstring[0] != '\0');

  if (type == NULL)
    {
      if (is_var_decl)
	fprintf_filtered (stream, "%s: ", varstring);
      fprintf_filtered (stream, "<null type?>");
      return;
    }

  if (show > 0)
      CHECK_TYPEDEF (type);

  if (is_var_decl && TYPE_CODE (type) != TYPE_CODE_FUNC)
      fprintf_filtered (stream, "%s: ", varstring);

  if (type_name != NULL && show <= 0)
    {
      fprintf_filtered (stream, "%s", type_name);
      return;
    }

  if (ada_is_aligner_type (type))
    ada_print_type (ada_aligned_type (type), "", stream, show, level);
  else
  switch (TYPE_CODE (type))
    {
    default:
      fprintf_filtered (stream, "<");
      c_print_type (type, "", stream, show, level);
      fprintf_filtered (stream, ">");
      break;
    case TYPE_CODE_PTR:
      fprintf_filtered (stream, "access ");
      ada_print_type (TYPE_TARGET_TYPE (type), "", stream, show,
		      level);
      break;
    case TYPE_CODE_REF:
      /* ??? Needs revisiting */
      fprintf_filtered (stream, "<ref> ");
      ada_print_type (TYPE_TARGET_TYPE (type), "", stream, show,
		      level);
      break;
    case TYPE_CODE_ARRAY:
      print_array_type (type, stream, show, level);
      break;
    case TYPE_CODE_INT:
      fprintf_filtered (stream, "<%d-byte integer>", TYPE_LENGTH (type));
      break;
    case TYPE_CODE_RANGE:
      fprintf_filtered (stream, "range ");
      print_range (type, stream);
      break;
    case TYPE_CODE_ENUM:
      if (show < 0)
	fprintf_filtered (stream, "(...)");
      else
	print_enum_type (type, stream);
      break;
    case TYPE_CODE_STRUCT:
      if (ada_is_array_descriptor (type)) 
	print_array_type (type, stream, show, level);
      else if (ada_is_bogus_array_descriptor (type))
	fprintf_filtered (stream, "array (?) of ? (<mal-formed descriptor>)");
      else
	print_record_type (type, stream, show, level);
      break;
    case TYPE_CODE_FUNC:
      print_func_type (type, stream, varstring);
      break;
    }
}

