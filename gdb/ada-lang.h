/* Ada language support definitions for GDB, the GNU debugger.
   Copyright 1992, 1997 Free Software Foundation, Inc.

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

#ifdef __STDC__		/* Forward decls for prototypes */
struct value;
#endif

#if !defined (ADA_LANG_H)
#define ADA_LANG_H 1

#include "value.h"
#include "gdbtypes.h"

/* Chain of cleanups for arguments of OP_UNRESOLVED_VALUE names.  Created in
   yyparse and freed in ada_resolve. */
extern struct cleanup* unresolved_names;

/* Corresponding mangled/demangled names and opcodes for Ada user-definable 
   operators. */
struct ada_opname_map {
  const char* mangled;
  const char* demangled;
  enum exp_opcode op;
};

/* Table of Ada operators in mangled and demangled forms. */
/* Defined in ada-lang.c */
extern const struct ada_opname_map ada_opname_table[];

/* Discriminated types */

/* A dynamic type (type code TYPE_CODE_DYNAMIC) is a structure or array type 
   whose instances have structures that depend on run-time quantities, 
   including local or static variables and other fields of the instance.
   For example, a record might contain a field that supplies the upper bound 
   of another field of the record that has an array type. As another
   example, the upper bound of an array might depend on a local
   variable.  

   For such a type, the macro TYPE_DYNAMIC_TEMPLATE yields a struct or
   array type indicating the fields of actual instances.  Typically,
   some of the array types in this type have bounds that will
   eventually be overridden.  The size of the TYPE_DYNAMIC_TYPE is
   therefore meaningless.  

   The macro TYPE_DYNAMIC_NFIELDS gives the number of quantities in the
   dynamic type that are to be overridden with dynamic information.
   For each k, 0 <= k < TYPE_DYNAMIC_NFIELDS(T), the macros
   TYPE_DYNAMIC_FIELD(T,k) gives the identifier (see below) of the kth quantity
   in type TYPE_DYNAMIC_TEMPLATE(T) that is supplied by run-time data,
   and TYPE_DYNAMIC_SOURCE(T, k) identifies the source of this data.

   TYPE_DYNAMIC_SOURCE(T, k) is a C string.  It may have the form
   "*.NAME", in which case NAME must be the name of a field in
   TYPE_DYNAMIC_TEMPLATE(T) that that is at a fixed location in all
   objects of type T.  Other values of TYPE_DYNAMIC_SOURCE(T, k)
   denote variables resolved in the context of the object possessing
   type T. 

   TYPE_DYNAMIC_FIELD(T, k) is a C string.  It has the form
   F1.F2...Fn, denoting a "field" of TYPE_DYNAMIC_TEMPLATE(T) that is
   overridden in each instance of the type.  Here, the term "field"
   refers both to ordinary fields (members) of a struct, but also to a
   set of notional fields of array objects and union objects.
   Specifically, array objects are treated as if they have fields LB0,
   UB0, LB1, UB1, etc., corresponding to bounds: LB0..UB0 for the
   first bound, LB1..UB1 for the second, etc.  Union types are treated
   as if they had a field TAG indicating which branch of the union
   currently applied (see further below).  If any of the Fi in
   TYPE_DYNAMIC_FIELD(T, k) denote a field with a pointer type, it is
   the pointed-to object that is referred to.

   Fields of TYPE_DYNAMIC_TEMPLATE(T) that have union types may
   be "tagged" by dynamic quantities, as described above.  Such union
   objects should have member names that encode ranges of integers
   (FIXME: Fill this in).  If U is the (union) type of such a field,
   then union_field_selected_by(U, m) gives the ordinal number of the
   field of U indicated by the integer tag value m.

   No value_ptr should ever have a TYPE_CODE_DYNAMIC code.  Instead,
   whenever a value is formed by fetching a variable of a dynamic
   type, T, or dereferencing a T*, a new type is constructed on the
   fly from the value being fetched that is a modified instance of
   TYPE_DYNAMIC_TEMPLATE(T). */


#define TYPE_DYNAMIC_TEMPLATE(thistype) TYPE_TARGET_TYPE(thistype)
#define TYPE_DYNAMIC_FIELD(thistype,k) TYPE_FIELD(thistype, 2*(k)).name
#define TYPE_DYNAMIC_SOURCE(thistype,k) TYPE_FIELD(thistype, 2*(k)+1).name

/* Identifiers for Ada attributes that need special processing.  Be sure 
   to update the table attribute_names in ada-lang.c whenever you change this.
   */

enum ada_attribute {
  /* Invalid attribute for error checking. */
  ATR_INVALID,

  ATR_FIRST,
  ATR_LAST,
  ATR_LENGTH,
  ATR_IMAGE,
  ATR_IMG,
  ATR_MAX,
  ATR_MIN,
  ATR_POS,
  ATR_TAG,
  ATR_VAL,

  /* Dummy last attribute. */
  ATR_END
};

extern struct type* builtin_type_ada_int;
extern struct type* builtin_type_ada_short;
extern struct type* builtin_type_ada_long;
extern struct type* builtin_type_ada_long_long;
extern struct type* builtin_type_ada_char;
extern struct type* builtin_type_ada_float;
extern struct type* builtin_type_ada_double;
extern struct type* builtin_type_ada_long_double;
extern struct type* builtin_type_ada_natural;
extern struct type* builtin_type_ada_positive;

extern int
ada_parse PARAMS ((void));	/* Defined in ada-exp.y */

extern void
ada_error PARAMS ((char *));	/* Defined in ada-exp.y */

extern void			/* Defined in ada-typeprint.c */
ada_print_type PARAMS ((struct type*, char*, GDB_FILE*, int, int));

extern int
ada_val_print PARAMS ((struct type*, char*, CORE_ADDR, GDB_FILE*, int, int,
		       int, enum val_prettyprint));

extern int
ada_value_print PARAMS ((struct value*, GDB_FILE*, int, enum val_prettyprint));


				/* Defined in ada-lang.c */


extern void
ada_convert_actuals PARAMS ((value_ptr, int, value_ptr*, CORE_ADDR*));

extern value_ptr
ada_value_subscript PARAMS ((value_ptr, int, value_ptr*));

extern struct type*
ada_array_element_type PARAMS ((struct type*));

extern int
ada_array_arity PARAMS ((struct type*));

struct type*
ada_type_of_array PARAMS ((value_ptr, int));

extern value_ptr
ada_coerce_to_simple_array PARAMS ((value_ptr));

extern value_ptr
ada_coerce_to_simple_array_ptr PARAMS ((value_ptr));

extern int
ada_is_simple_array PARAMS ((struct type*));

extern int
ada_is_array_descriptor PARAMS ((struct type*));

extern int
ada_is_bogus_array_descriptor PARAMS ((struct type*));

extern struct type*
ada_index_type PARAMS ((struct type*, int));

extern value_ptr
ada_array_bound PARAMS ((value_ptr, int, int));

extern int
ada_lookup_symbol_list PARAMS ((const char*, struct block*, namespace_enum,
				struct symbol***, struct block***));

extern struct minimal_symbol*
ada_lookup_minimal_symbol PARAMS ((const char*));

extern void
ada_resolve PARAMS ((struct expression**));

extern int
ada_resolve_function PARAMS ((struct symbol**, struct block**, int, 
			      value_ptr*, int, const char*));

extern void
ada_fill_in_ada_prototype PARAMS ((struct symbol*));

extern int
user_select_syms PARAMS ((struct symbol**, struct block**, int, int));

extern struct symtabs_and_lines
ada_finish_decode_line_1 PARAMS ((const char*, int, int, 
				  struct block*, char***));

extern int
ada_scan_number PARAMS ((const char*, int, LONGEST*, int*));

extern struct type*
ada_parent_type PARAMS ((struct type*));

extern int
ada_is_ignored_field PARAMS ((struct type*, int));

extern int
ada_is_string_type PARAMS ((struct type*));

extern int 
ada_is_tagged_type PARAMS ((struct type*));

extern struct type*
ada_tag_type PARAMS ((value_ptr));

extern value_ptr
ada_value_tag PARAMS ((value_ptr));

extern int
ada_is_parent_field PARAMS ((struct type*, int));

extern int
ada_is_wrapper_field PARAMS ((struct type*, int));

extern int
ada_is_variant_part PARAMS ((struct type*, int));

extern struct type*
ada_variant_discrim_type PARAMS ((struct type*, int, struct type*));

extern int
ada_is_others_clause PARAMS ((struct type*, int));

extern int
ada_in_variant PARAMS ((LONGEST, struct type*, int));

extern char*
ada_variant_discrim_name PARAMS ((struct type*, int, struct type*));

extern struct type*
ada_lookup_struct_elt_type PARAMS ((struct type*, char*, int, int*));

extern value_ptr
ada_value_struct_elt PARAMS ((value_ptr, char*, char*));

extern value_ptr
ada_search_struct_field PARAMS ((char*, value_ptr, int, struct type*));

extern int
ada_is_aligner_type PARAMS ((struct type*));

extern struct type*
ada_aligned_type PARAMS ((struct type*));

extern char*
ada_aligned_value_addr PARAMS ((struct type*, char*));

extern const char*
ada_attribute_name PARAMS ((int));

#endif
