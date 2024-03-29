/* RunTime Type Identification
   Copyright (C) 1995, 1996 Free Software Foundation, Inc.
   Mostly written by Jason Merrill (jason@cygnus.com).

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


#include "config.h"
#include "tree.h"
#include "cp-tree.h"
#include "flags.h"
#include "output.h"
#include "assert.h"

#ifndef INT_TYPE_SIZE
#define INT_TYPE_SIZE BITS_PER_WORD
#endif

extern tree define_function ();
extern tree build_t_desc_overload ();
extern struct obstack *permanent_obstack;

tree type_info_type_node;
tree tinfo_fn_id;
tree tinfo_fn_type;

void
init_rtti_processing ()
{
  type_info_type_node = xref_tag
    (class_type_node, get_identifier ("type_info"), NULL_TREE, 1);
  tinfo_fn_id = get_identifier ("__tf");
  tinfo_fn_type = build_function_type
    (build_reference_type (build_type_variant (type_info_type_node, 1, 0)),
     void_list_node);
}

/* Given a pointer to an object with at least one virtual table
   pointer somewhere, return a pointer to a possible sub-object that
   has a virtual table pointer in it that is the vtable parent for
   that sub-object.  */

static tree
build_headof_sub (exp)
     tree exp;
{
  tree type = TREE_TYPE (TREE_TYPE (exp));
  tree basetype = CLASSTYPE_RTTI (type);
  tree binfo = get_binfo (basetype, type, 0);

  exp = convert_pointer_to_real (binfo, exp);
  return exp;
}

/* Given the expression EXP of type `class *', return the head of the
   object pointed to by EXP with type cv void*, if the class has any
   virtual functions (TYPE_VIRTUAL_P), else just return the
   expression.  */

static tree
build_headof (exp)
     tree exp;
{
  tree type = TREE_TYPE (exp);
  tree aref;
  tree offset;

  if (TREE_CODE (type) != POINTER_TYPE)
    {
      error ("`headof' applied to non-pointer type");
      return error_mark_node;
    }
  type = TREE_TYPE (type);

  if (!TYPE_VIRTUAL_P (type))
    return exp;

  /* If we don't have rtti stuff, get to a sub-object that does.  */
  if (!CLASSTYPE_VFIELDS (TREE_TYPE (TREE_TYPE (exp))))
    exp = build_headof_sub (exp);

  /* We use this a couple of times below, protect it.  */
  exp = save_expr (exp);

  aref = build_vtbl_ref (build_indirect_ref (exp, NULL_PTR), integer_zero_node);

  if (flag_vtable_thunks)
    offset = aref;
  else
    offset = build_component_ref (aref, delta_identifier, NULL_TREE, 0);

  type = build_type_variant (ptr_type_node, TREE_READONLY (exp),
			     TREE_THIS_VOLATILE (exp));
  return build (PLUS_EXPR, type, exp,
		convert (ptrdiff_type_node, offset));
}

/* Build a call to a generic entry point taking and returning void.  */

static tree
call_void_fn (name)
     char *name;
{
  tree d = get_identifier (name);
  tree type;
  
  if (IDENTIFIER_GLOBAL_VALUE (d))
    d = IDENTIFIER_GLOBAL_VALUE (d);
  else
    {
      push_obstacks (&permanent_obstack, &permanent_obstack);

      type = build_function_type (void_type_node, void_list_node);
      d = build_lang_decl (FUNCTION_DECL, d, type);
      DECL_EXTERNAL (d) = 1;
      TREE_PUBLIC (d) = 1;
      DECL_ARTIFICIAL (d) = 1;
      pushdecl_top_level (d);
      make_function_rtl (d);
      assemble_external (d);

      pop_obstacks ();
    }

  return build_call (d, void_type_node, NULL_TREE);
}

/* Get a bad_cast node for the program to throw...

   See libstdc++/exception.cc for __throw_bad_cast */

static tree
throw_bad_cast ()
{
  return call_void_fn ("__throw_bad_cast");
}

static tree
throw_bad_typeid ()
{
  return call_void_fn ("__throw_bad_typeid");
}

/* Return the type_info function associated with the expression EXP.  If
   EXP is a reference to a polymorphic class, return the dynamic type;
   otherwise return the static type of the expression.  */

tree
get_tinfo_fn_dynamic (exp)
     tree exp;
{
  tree type;

  if (exp == error_mark_node)
    return error_mark_node;

  if (type_unknown_p (exp))
    {
      error ("typeid of overloaded function");
      return error_mark_node;
    }

  type = TREE_TYPE (exp);

  /* peel back references, so they match.  */
  if (TREE_CODE (type) == REFERENCE_TYPE)
    type = TREE_TYPE (type);

  /* Peel off cv qualifiers.  */
  type = TYPE_MAIN_VARIANT (type);

  /* If exp is a reference to polymorphic type, get the real type_info.  */
  if (TYPE_VIRTUAL_P (type) && ! resolves_to_fixed_type_p (exp, 0))
    {
      /* build reference to type_info from vtable.  */
      tree t;

      if (! flag_rtti)
	warning ("taking dynamic typeid of object without -frtti");

      /* If we don't have rtti stuff, get to a sub-object that does.  */
      if (! CLASSTYPE_VFIELDS (type))
	{
	  exp = build_unary_op (ADDR_EXPR, exp, 0);
	  exp = build_headof_sub (exp);
	  exp = build_indirect_ref (exp, NULL_PTR);
	}

      if (flag_vtable_thunks)
	t = build_vfn_ref ((tree *) 0, exp, integer_one_node);
      else
	t = build_vfn_ref ((tree *) 0, exp, integer_zero_node);
      TREE_TYPE (t) = build_pointer_type (tinfo_fn_type);
      return t;
    }

  /* otherwise return the type_info for the static type of the expr.  */
  return get_tinfo_fn (TYPE_MAIN_VARIANT (type));
}

tree
build_typeid (exp)
     tree exp;
{
  exp = get_tinfo_fn_dynamic (exp);
  exp = build_call (exp, TREE_TYPE (tinfo_fn_type), NULL_TREE);
  return convert_from_reference (exp);
}  

tree
build_x_typeid (exp)
     tree exp;
{
  tree cond = NULL_TREE;
  tree type = TREE_TYPE (tinfo_fn_type);
  int nonnull;

  if (processing_template_decl)
    return build_min_nt (TYPEID_EXPR, exp);

  if (TREE_CODE (exp) == INDIRECT_REF
      && TREE_CODE (TREE_TYPE (TREE_OPERAND (exp, 0))) == POINTER_TYPE
      && TYPE_VIRTUAL_P (TREE_TYPE (exp))
      && ! resolves_to_fixed_type_p (exp, &nonnull)
      && ! nonnull)
    {
      exp = stabilize_reference (exp);
      cond = convert (boolean_type_node, TREE_OPERAND (exp, 0));
    }

  exp = get_tinfo_fn_dynamic (exp);

  if (exp == error_mark_node)
    return error_mark_node;

  exp = build_call (exp, type, NULL_TREE);

  if (cond)
    {
      tree bad = throw_bad_typeid ();

      bad = build_compound_expr
	(tree_cons (NULL_TREE, bad, build_tree_list
		    (NULL_TREE, convert (type, integer_zero_node))));
      exp = build (COND_EXPR, type, cond, exp, bad);
    }

  return convert_from_reference (exp);
}

static tree
get_tinfo_var (type)
     tree type;
{
  tree tname = build_overload_with_type (get_identifier ("__ti"), type);
  tree tdecl, arrtype;
  int size;

  if (IDENTIFIER_GLOBAL_VALUE (tname))
    return IDENTIFIER_GLOBAL_VALUE (tname);
    
  /* Figure out how much space we need to allocate for the type_info object.
     If our struct layout or the type_info classes are changed, this will
     need to be modified.  */
  if (TYPE_VOLATILE (type) || TYPE_READONLY (type))
    size = 3 * POINTER_SIZE + INT_TYPE_SIZE;
  else if (TREE_CODE (type) == POINTER_TYPE
	   && ! (TREE_CODE (TREE_TYPE (type)) == OFFSET_TYPE
		 || TREE_CODE (TREE_TYPE (type)) == METHOD_TYPE))
    size = 3 * POINTER_SIZE;
  else if (IS_AGGR_TYPE (type))
    {
      if (CLASSTYPE_N_BASECLASSES (type) == 0)
	size = 2 * POINTER_SIZE;
      else if (! TYPE_USES_COMPLEX_INHERITANCE (type)
	       && (TREE_VIA_PUBLIC
		   (TREE_VEC_ELT (TYPE_BINFO_BASETYPES (type), 0))))
	size = 3 * POINTER_SIZE;
      else
	size = 3 * POINTER_SIZE + INT_TYPE_SIZE;
    }
  else
    size = 2 * POINTER_SIZE;

  push_obstacks (&permanent_obstack, &permanent_obstack);

  /* The type for a character array of the appropriate size.  */
  arrtype = build_cplus_array_type
    (unsigned_char_type_node,
     build_index_type (size_int (size / BITS_PER_UNIT - 1)));

  tdecl = build_decl (VAR_DECL, tname, arrtype);
  TREE_PUBLIC (tdecl) = 1;
  DECL_EXTERNAL (tdecl) = 1;
  DECL_ARTIFICIAL (tdecl) = 1;
  pushdecl_top_level (tdecl);
  cp_finish_decl (tdecl, NULL_TREE, NULL_TREE, 0, 0);

  pop_obstacks ();

  return tdecl;
}

tree
get_tinfo_fn (type)
     tree type;
{
  tree name;
  tree d;

  if (TREE_CODE (type) == OFFSET_TYPE)
    type = TREE_TYPE (type);
  if (TREE_CODE (type) == METHOD_TYPE)
    type = build_function_type (TREE_TYPE (type),
				TREE_CHAIN (TYPE_ARG_TYPES (type)));

  name = build_overload_with_type (tinfo_fn_id, type);

  if (IDENTIFIER_GLOBAL_VALUE (name))
    return IDENTIFIER_GLOBAL_VALUE (name);

  push_obstacks (&permanent_obstack, &permanent_obstack);

  d = build_lang_decl (FUNCTION_DECL, name, tinfo_fn_type);
  DECL_EXTERNAL (d) = 1;
  TREE_PUBLIC (d) = 1;
  DECL_ARTIFICIAL (d) = 1;
  DECL_NOT_REALLY_EXTERN (d) = 1;
  DECL_MUTABLE_P (d) = 1;
  TREE_TYPE (name) = copy_to_permanent (type);
  pushdecl_top_level (d);
  make_function_rtl (d);
  assemble_external (d);
  mark_inline_for_output (d);
  if (at_eof)
    import_export_decl (d);

  pop_obstacks ();

  return d;
}

static tree
get_typeid_1 (type)
     tree type;
{
  tree t = build_call
    (get_tinfo_fn (type), TREE_TYPE (tinfo_fn_type), NULL_TREE);
  return convert_from_reference (t);
}
  
/* Return the type_info object for TYPE, creating it if necessary.  */

tree
get_typeid (type)
     tree type;
{
  if (type == error_mark_node)
    return error_mark_node;
  
  if (processing_template_decl)
    return build_min_nt (TYPEID_EXPR, type);

  /* If the type of the type-id is a reference type, the result of the
     typeid expression refers to a type_info object representing the
     referenced type.  */
  if (TREE_CODE (type) == REFERENCE_TYPE)
    type = TREE_TYPE (type);

  /* The top-level cv-qualifiers of the lvalue expression or the type-id
     that is the operand of typeid are always ignored.  */
  type = TYPE_MAIN_VARIANT (type);

  return get_typeid_1 (type);
}

/* Check whether TEST is null before returning RESULT.  If TEST is used in
   RESULT, it must have previously had a save_expr applied to it.  */

static tree
ifnonnull (test, result)
     tree test, result;
{
  return build (COND_EXPR, TREE_TYPE (result),
		build (EQ_EXPR, boolean_type_node, test, integer_zero_node),
		convert (TREE_TYPE (result), integer_zero_node),
		result);
}

/* Execute a dynamic cast, as described in section 5.2.6 of the 9/93 working
   paper.  */

tree
build_dynamic_cast (type, expr)
     tree type, expr;
{
  enum tree_code tc = TREE_CODE (type);
  tree exprtype = TREE_TYPE (expr);
  enum tree_code ec;
  tree dcast_fn;

  if (type == error_mark_node || expr == error_mark_node)
    return error_mark_node;
  
  if (processing_template_decl)
    {
      tree t = build_min (DYNAMIC_CAST_EXPR, type, expr);
      return t;
    }

  assert (exprtype != NULL_TREE);
  ec = TREE_CODE (exprtype);

  switch (tc)
    {
    case POINTER_TYPE:
      if (ec == REFERENCE_TYPE)
	{
	  expr = convert_from_reference (expr);
	  exprtype = TREE_TYPE (expr);
	  ec = TREE_CODE (exprtype);
	}
      if (ec != POINTER_TYPE)
	goto fail;
      if (TREE_CODE (TREE_TYPE (exprtype)) != RECORD_TYPE)
	goto fail;
      if (TYPE_SIZE (TREE_TYPE (exprtype)) == NULL_TREE)
	goto fail;
      if (TREE_READONLY (TREE_TYPE (exprtype)) &&
	  ! TYPE_READONLY (TREE_TYPE (type)))
	goto fail;
      if (TYPE_MAIN_VARIANT (TREE_TYPE (type)) == void_type_node)
	break;
      /* else fall through */
    case REFERENCE_TYPE:
      if (TREE_CODE (TREE_TYPE (type)) != RECORD_TYPE)
	goto fail;
      if (TYPE_SIZE (TREE_TYPE (type)) == NULL_TREE)
	goto fail;
      break;
      /* else fall through */
    default:
      goto fail;
    }

  /* Apply trivial conversion T -> T& for dereferenced ptrs.  */
  if (ec == RECORD_TYPE)
    {
      exprtype = build_type_variant (exprtype, TREE_READONLY (expr),
				     TREE_THIS_VOLATILE (expr));
      exprtype = build_reference_type (exprtype);
      expr = convert_to_reference (exprtype, expr, CONV_IMPLICIT,
				   LOOKUP_NORMAL, NULL_TREE);
      ec = REFERENCE_TYPE;
    }

  if (tc == REFERENCE_TYPE)
    {
      if (ec != REFERENCE_TYPE)
	goto fail;
      if (TREE_CODE (TREE_TYPE (exprtype)) != RECORD_TYPE)
	goto fail;
      if (TYPE_SIZE (TREE_TYPE (exprtype)) == NULL_TREE)
	goto fail;
      if (TREE_READONLY (TREE_TYPE (exprtype)) &&
	  ! TYPE_READONLY (TREE_TYPE (type)))
	goto fail;
    }

  /* If *type is an unambiguous accessible base class of *exprtype,
     convert statically.  */
  {
    int distance;
    tree path;

    distance = get_base_distance (TREE_TYPE (type), TREE_TYPE (exprtype), 1,
				  &path);
    if (distance >= 0)
      return build_vbase_path (PLUS_EXPR, type, expr, path, 0);
  }

  /* Otherwise *exprtype must be a polymorphic class (have a vtbl).  */
  if (TYPE_VIRTUAL_P (TREE_TYPE (exprtype)))
    {
      tree expr1;
      /* if TYPE is `void *', return pointer to complete object.  */
      if (tc == POINTER_TYPE
	  && TYPE_MAIN_VARIANT (TREE_TYPE (type)) == void_type_node)
	{
	  /* if b is an object, dynamic_cast<void *>(&b) == (void *)&b.  */
	  if (TREE_CODE (expr) == ADDR_EXPR
	      && TREE_CODE (TREE_OPERAND (expr, 0)) == VAR_DECL
	      && TREE_CODE (TREE_TYPE (TREE_OPERAND (expr, 0))) == RECORD_TYPE)
	    return build1 (NOP_EXPR, type, expr);

	  /* Since expr is used twice below, save it.  */
	  expr = save_expr (expr);

	  expr1 = build_headof (expr);
	  if (TREE_TYPE (expr1) != type)
	    expr1 = build1 (NOP_EXPR, type, expr1);
	  return ifnonnull (expr, expr1);
	}
      else
	{
	  tree retval;
          tree result, td1, td2, td3, elems, expr2;

 	  /* If we got here, we can't convert statically.  Therefore,
	     dynamic_cast<D&>(b) (b an object) cannot succeed.  */
	  if (ec == REFERENCE_TYPE)
	    {
	      if (TREE_CODE (expr) == VAR_DECL
		  && TREE_CODE (TREE_TYPE (expr)) == RECORD_TYPE)
		{
		  cp_warning ("dynamic_cast of `%#D' to `%#T' can never succeed",
			      expr, type);
		  return throw_bad_cast ();
		}
	    }
	  /* Ditto for dynamic_cast<D*>(&b).  */
	  else if (TREE_CODE (expr) == ADDR_EXPR)
	    {
	      tree op = TREE_OPERAND (expr, 0);
	      if (TREE_CODE (op) == VAR_DECL
		  && TREE_CODE (TREE_TYPE (op)) == RECORD_TYPE)
		{
		  cp_warning ("dynamic_cast of `%#D' to `%#T' can never succeed",
			      expr, type);
		  retval = build_int_2 (0, 0); 
		  TREE_TYPE (retval) = type; 
		  return retval;
		}
	    }

	  /* Since expr is used twice below, save it.  */
	  expr = save_expr (expr);

	  expr1 = expr;
	  if (tc == REFERENCE_TYPE)
	    expr1 = build_unary_op (ADDR_EXPR, expr1, 0);

	  /* Build run-time conversion.  */
	  expr2 = build_headof (expr1);

	  if (ec == POINTER_TYPE)
	    td1 = get_tinfo_fn_dynamic (build_indirect_ref (expr, NULL_PTR));
	  else
	    td1 = get_tinfo_fn_dynamic (expr);
	  td1 = decay_conversion (td1);
	  
	  td2 = decay_conversion
	    (get_tinfo_fn (TYPE_MAIN_VARIANT (TREE_TYPE (type))));
	  td3 = decay_conversion
	    (get_tinfo_fn (TYPE_MAIN_VARIANT (TREE_TYPE (exprtype))));

          elems = tree_cons
	    (NULL_TREE, td1, tree_cons
	     (NULL_TREE, td2, tree_cons
	      (NULL_TREE, build_int_2 (1, 0), tree_cons
	       (NULL_TREE, expr2, tree_cons
		(NULL_TREE, td3, tree_cons
		 (NULL_TREE, expr1, NULL_TREE))))));

	  dcast_fn = get_identifier ("__dynamic_cast");
	  if (IDENTIFIER_GLOBAL_VALUE (dcast_fn))
	    dcast_fn = IDENTIFIER_GLOBAL_VALUE (dcast_fn);
	  else
	    {
	      tree tmp;

	      push_obstacks (&permanent_obstack, &permanent_obstack);
	      tmp = tree_cons
		(NULL_TREE, TREE_TYPE (td1), tree_cons
		 (NULL_TREE, TREE_TYPE (td1), tree_cons
		  (NULL_TREE, integer_type_node, tree_cons
		   (NULL_TREE, ptr_type_node, tree_cons
		    (NULL_TREE, TREE_TYPE (td1), tree_cons
		     (NULL_TREE, ptr_type_node, void_list_node))))));
	      tmp = build_function_type (ptr_type_node, tmp);
	      dcast_fn = build_lang_decl (FUNCTION_DECL, dcast_fn, tmp);
	      DECL_EXTERNAL (dcast_fn) = 1;
	      TREE_PUBLIC (dcast_fn) = 1;
	      DECL_ARTIFICIAL (dcast_fn) = 1;
	      pushdecl_top_level (dcast_fn);
	      make_function_rtl (dcast_fn);
	      assemble_external (dcast_fn);
	      pop_obstacks ();
	    }
	  
          result = build_call
	    (dcast_fn, TREE_TYPE (TREE_TYPE (dcast_fn)), elems);

	  if (tc == REFERENCE_TYPE)
	    {
	      expr1 = throw_bad_cast ();
	      expr1 = build_compound_expr
		(tree_cons (NULL_TREE, expr1,
			    build_tree_list (NULL_TREE, convert
					     (type, integer_zero_node))));
	      TREE_TYPE (expr1) = type;
	      result = save_expr (result);
	      return build (COND_EXPR, type, result, result, expr1);
	    }

	  /* Now back to the type we want from a void*.  */
	  result = convert (type, result);
          return ifnonnull (expr, result);
	}
    }

 fail:
  cp_error ("cannot dynamic_cast `%E' (of type `%#T') to type `%#T'",
	    expr, exprtype, type);
  return error_mark_node;
}

/* Build and initialize various sorts of descriptors.  Every descriptor
   node has a name associated with it (the name created by mangling).
   For this reason, we use the identifier as our access to the __*_desc
   nodes, instead of sticking them directly in the types.  Otherwise we
   would burden all built-in types (and pointer types) with slots that
   we don't necessarily want to use.

   For each descriptor we build, we build a variable that contains
   the descriptor's information.  When we need this info at runtime,
   all we need is access to these variables.

   Note: these constructors always return the address of the descriptor
   info, since that is simplest for their mutual interaction.  */

extern tree const_string_type_node;

/* Build an initializer for a __si_type_info node.  */

static void
expand_si_desc (tdecl, type)
     tree tdecl;
     tree type;
{
  tree t, elems, fn;
  char *name = build_overload_name (type, 1, 1);
  tree name_string = combine_strings (build_string (strlen (name)+1, name));

  type = BINFO_TYPE (TREE_VEC_ELT (TYPE_BINFO_BASETYPES (type), 0));
  expand_expr_stmt (get_typeid_1 (type));
  t = decay_conversion (get_tinfo_var (type));
  elems = tree_cons
    (NULL_TREE, decay_conversion (tdecl), tree_cons
     (NULL_TREE, decay_conversion (name_string), tree_cons
      (NULL_TREE, t, NULL_TREE)));

  fn = get_identifier ("__rtti_si");
  if (IDENTIFIER_GLOBAL_VALUE (fn))
    fn = IDENTIFIER_GLOBAL_VALUE (fn);
  else
    {
      tree tmp;
      push_obstacks (&permanent_obstack, &permanent_obstack);
      tmp = tree_cons
	(NULL_TREE, ptr_type_node, tree_cons
	 (NULL_TREE, const_string_type_node, tree_cons
	  (NULL_TREE, build_pointer_type (type_info_type_node),
	   void_list_node)));
      tmp = build_function_type	(void_type_node, tmp);
  
      fn = build_lang_decl (FUNCTION_DECL, fn, tmp);
      DECL_EXTERNAL (fn) = 1;
      TREE_PUBLIC (fn) = 1;
      DECL_ARTIFICIAL (fn) = 1;
      pushdecl_top_level (fn);
      make_function_rtl (fn);
      assemble_external (fn);
      pop_obstacks ();
    }

  fn = build_call (fn, TREE_TYPE (TREE_TYPE (fn)), elems);
  expand_expr_stmt (fn);
}

/* Build an initializer for a __class_type_info node.  */

static void
expand_class_desc (tdecl, type)
     tree tdecl;
     tree type;
{
  tree name_string;
  tree fn, tmp;
  char *name;

  int i = CLASSTYPE_N_BASECLASSES (type);
  int base_cnt = 0;
  tree binfos = TYPE_BINFO_BASETYPES (type);
#if 0
  /* See code below that used these.  */
  tree vb = CLASSTYPE_VBASECLASSES (type);
  int n_base = i;
#endif
  tree base, elems, access, offset, isvir;
  tree elt, elts = NULL_TREE;
  static tree base_info_type_node;

  if (base_info_type_node == NULL_TREE)
    {
      tree fields [4];

      /* A reasonably close approximation of __class_type_info::base_info */

      push_obstacks (&permanent_obstack, &permanent_obstack);
      base_info_type_node = make_lang_type (RECORD_TYPE);

      /* Actually const __user_type_info * */
      fields [0] = build_lang_field_decl
	(FIELD_DECL, NULL_TREE,
	 build_pointer_type (build_type_variant (type_info_type_node, 1, 0)));
      fields [1] = build_lang_field_decl
	(FIELD_DECL, NULL_TREE, unsigned_intSI_type_node);
      DECL_BIT_FIELD (fields[1]) = 1;
      DECL_FIELD_SIZE (fields[1]) = 29;

      fields [2] = build_lang_field_decl
	(FIELD_DECL, NULL_TREE, boolean_type_node);
      DECL_BIT_FIELD (fields[2]) = 1;
      DECL_FIELD_SIZE (fields[2]) = 1;

      /* Actually enum access */
      fields [3] = build_lang_field_decl
	(FIELD_DECL, NULL_TREE, integer_type_node);
      DECL_BIT_FIELD (fields[3]) = 1;
      DECL_FIELD_SIZE (fields[3]) = 2;

      finish_builtin_type (base_info_type_node, "__base_info", fields,
			   3, ptr_type_node);
      pop_obstacks ();
    }

  while (--i >= 0)
    {
      tree binfo = TREE_VEC_ELT (binfos, i);

      expand_expr_stmt (get_typeid_1 (BINFO_TYPE (binfo)));
      base = decay_conversion (get_tinfo_var (BINFO_TYPE (binfo)));

      if (TREE_VIA_VIRTUAL (binfo))
	{
	  tree t = BINFO_TYPE (binfo);
	  char *name;
	  tree field;

	  name = (char *) alloca (TYPE_NAME_LENGTH (t)+sizeof (VBASE_NAME)+1);
	  sprintf (name, VBASE_NAME_FORMAT, TYPE_NAME_STRING (t));
	  field = lookup_field (type, get_identifier (name), 0, 0);
	  offset = size_binop (FLOOR_DIV_EXPR, 
		DECL_FIELD_BITPOS (field), size_int (BITS_PER_UNIT));
	}
      else
	offset = BINFO_OFFSET (binfo);

      if (TREE_VIA_PUBLIC (binfo))
        access = access_public_node;
      else if (TREE_VIA_PROTECTED (binfo))
	access = access_protected_node;
      else
	access = access_private_node;
      if (TREE_VIA_VIRTUAL (binfo))
	isvir = boolean_true_node;
      else
	isvir = boolean_false_node;

      elt = build
	(CONSTRUCTOR, base_info_type_node, NULL_TREE, tree_cons
	 (NULL_TREE, base, tree_cons
	  (NULL_TREE, offset, tree_cons
	   (NULL_TREE, isvir, tree_cons
	    (NULL_TREE, access, NULL_TREE)))));
      TREE_HAS_CONSTRUCTOR (elt) = TREE_CONSTANT (elt) = TREE_STATIC (elt) = 1;
      elts = tree_cons (NULL_TREE, elt, elts);
      base_cnt++;
    }
#if 0
  i = n_base;
  while (vb)
    {
      tree b;
      access = access_public_node;
      while (--i >= 0)
	{
	  b = TREE_VEC_ELT (binfos, i);
	  if (BINFO_TYPE (vb) == BINFO_TYPE (b) && TREE_VIA_VIRTUAL (b))
	    {
	      if (TREE_VIA_PUBLIC (b))
		access = access_public_node;
	      else if (TREE_VIA_PROTECTED (b))
		access = access_protected_node;
	      else
		access = access_private_node;
	      break;
	    }
	}
      base = build_t_desc (BINFO_TYPE (vb), 1);
      offset = BINFO_OFFSET (vb);
      isvir = build_int_2 (1, 0);

      base_list = tree_cons (NULL_TREE, base, base_list);
      isvir_list = tree_cons (NULL_TREE, isvir, isvir_list);
      acc_list = tree_cons (NULL_TREE, access, acc_list);
      off_list = tree_cons (NULL_TREE, offset, off_list);

      base_cnt++;
      vb = TREE_CHAIN (vb);
    }
#endif

  name = build_overload_name (type, 1, 1);
  name_string = combine_strings (build_string (strlen (name)+1, name));

  {
    tree arrtype = build_array_type (base_info_type_node, NULL_TREE);
    elts = build (CONSTRUCTOR, arrtype, NULL_TREE, elts);
    TREE_HAS_CONSTRUCTOR (elts) = TREE_CONSTANT (elts) =
      TREE_STATIC (elts) = 1;
    complete_array_type (arrtype, elts, 1);
  }

  elems = tree_cons
    (NULL_TREE, decay_conversion (tdecl), tree_cons
     (NULL_TREE, decay_conversion (name_string), tree_cons
      (NULL_TREE, decay_conversion (elts), tree_cons
       (NULL_TREE, build_int_2 (base_cnt, 0), NULL_TREE))));

  fn = get_identifier ("__rtti_class");
  if (IDENTIFIER_GLOBAL_VALUE (fn))
    fn = IDENTIFIER_GLOBAL_VALUE (fn);
  else
    {
      push_obstacks (&permanent_obstack, &permanent_obstack);
      tmp = tree_cons
	(NULL_TREE, ptr_type_node, tree_cons
	 (NULL_TREE, const_string_type_node, tree_cons
	  (NULL_TREE, build_pointer_type (base_info_type_node), tree_cons
	   (NULL_TREE, sizetype, void_list_node))));
      tmp = build_function_type	(void_type_node, tmp);
  
      fn = build_lang_decl (FUNCTION_DECL, fn, tmp);
      DECL_EXTERNAL (fn) = 1;
      TREE_PUBLIC (fn) = 1;
      DECL_ARTIFICIAL (fn) = 1;
      pushdecl_top_level (fn);
      make_function_rtl (fn);
      assemble_external (fn);
      pop_obstacks ();
    }

  fn = build_call (fn, TREE_TYPE (TREE_TYPE (fn)), elems);
  expand_expr_stmt (fn);
}

/* Build an initializer for a __pointer_type_info node.  */

static void
expand_ptr_desc (tdecl, type)
     tree tdecl;
     tree type;
{
  tree t, elems, fn;
  char *name = build_overload_name (type, 1, 1);
  tree name_string = combine_strings (build_string (strlen (name)+1, name));

  type = TREE_TYPE (type);
  expand_expr_stmt (get_typeid_1 (type));
  t = decay_conversion (get_tinfo_var (type));
  elems = tree_cons
    (NULL_TREE, decay_conversion (tdecl), tree_cons
     (NULL_TREE, decay_conversion (name_string), tree_cons
      (NULL_TREE, t, NULL_TREE)));

  fn = get_identifier ("__rtti_ptr");
  if (IDENTIFIER_GLOBAL_VALUE (fn))
    fn = IDENTIFIER_GLOBAL_VALUE (fn);
  else
    {
      tree tmp;
      push_obstacks (&permanent_obstack, &permanent_obstack);
      tmp = tree_cons
	(NULL_TREE, ptr_type_node, tree_cons
	 (NULL_TREE, const_string_type_node, tree_cons
	  (NULL_TREE, build_pointer_type (type_info_type_node),
	   void_list_node)));
      tmp = build_function_type	(void_type_node, tmp);
  
      fn = build_lang_decl (FUNCTION_DECL, fn, tmp);
      DECL_EXTERNAL (fn) = 1;
      TREE_PUBLIC (fn) = 1;
      DECL_ARTIFICIAL (fn) = 1;
      pushdecl_top_level (fn);
      make_function_rtl (fn);
      assemble_external (fn);
      pop_obstacks ();
    }

  fn = build_call (fn, TREE_TYPE (TREE_TYPE (fn)), elems);
  expand_expr_stmt (fn);
}

/* Build an initializer for a __attr_type_info node.  */

static void
expand_attr_desc (tdecl, type)
     tree tdecl;
     tree type;
{
  tree elems, t, fn;
  char *name = build_overload_name (type, 1, 1);
  tree name_string = combine_strings (build_string (strlen (name)+1, name));
  tree attrval = build_int_2
    (TYPE_READONLY (type) | TYPE_VOLATILE (type) * 2, 0);

  expand_expr_stmt (get_typeid_1 (TYPE_MAIN_VARIANT (type)));
  t = decay_conversion (get_tinfo_var (TYPE_MAIN_VARIANT (type)));
  elems = tree_cons
    (NULL_TREE, decay_conversion (tdecl), tree_cons
     (NULL_TREE, decay_conversion (name_string), tree_cons
      (NULL_TREE, attrval, tree_cons (NULL_TREE, t, NULL_TREE))));

  fn = get_identifier ("__rtti_attr");
  if (IDENTIFIER_GLOBAL_VALUE (fn))
    fn = IDENTIFIER_GLOBAL_VALUE (fn);
  else
    {
      tree tmp;
      push_obstacks (&permanent_obstack, &permanent_obstack);
      tmp = tree_cons
	(NULL_TREE, ptr_type_node, tree_cons
	 (NULL_TREE, const_string_type_node, tree_cons
	  (NULL_TREE, integer_type_node, tree_cons
	   (NULL_TREE, build_pointer_type (type_info_type_node),
	    void_list_node))));
      tmp = build_function_type	(void_type_node, tmp);
  
      fn = build_lang_decl (FUNCTION_DECL, fn, tmp);
      DECL_EXTERNAL (fn) = 1;
      TREE_PUBLIC (fn) = 1;
      DECL_ARTIFICIAL (fn) = 1;
      pushdecl_top_level (fn);
      make_function_rtl (fn);
      assemble_external (fn);
      pop_obstacks ();
    }

  fn = build_call (fn, TREE_TYPE (TREE_TYPE (fn)), elems);
  expand_expr_stmt (fn);
}

/* Build an initializer for a type_info node that just has a name.  */

static void
expand_generic_desc (tdecl, type, fnname)
     tree tdecl;
     tree type;
     char *fnname;
{
  char *name = build_overload_name (type, 1, 1);
  tree name_string = combine_strings (build_string (strlen (name)+1, name));
  tree elems = tree_cons
    (NULL_TREE, decay_conversion (tdecl), tree_cons
     (NULL_TREE, decay_conversion (name_string), NULL_TREE));

  tree fn = get_identifier (fnname);
  if (IDENTIFIER_GLOBAL_VALUE (fn))
    fn = IDENTIFIER_GLOBAL_VALUE (fn);
  else
    {
      tree tmp;
      push_obstacks (&permanent_obstack, &permanent_obstack);
      tmp = tree_cons
	(NULL_TREE, ptr_type_node, tree_cons
	 (NULL_TREE, const_string_type_node, void_list_node));
      tmp = build_function_type (void_type_node, tmp);
  
      fn = build_lang_decl (FUNCTION_DECL, fn, tmp);
      DECL_EXTERNAL (fn) = 1;
      TREE_PUBLIC (fn) = 1;
      DECL_ARTIFICIAL (fn) = 1;
      pushdecl_top_level (fn);
      make_function_rtl (fn);
      assemble_external (fn);
      pop_obstacks ();
    }

  fn = build_call (fn, TREE_TYPE (TREE_TYPE (fn)), elems);
  expand_expr_stmt (fn);
}

/* Generate the code for a type_info initialization function.
   Note that we take advantage of the passage

   5.2.7  Type identification                               [expr.typeid]
   
   Whether or not the destructor is called for the type_info object at the
   end of the program is unspecified.

   and don't bother to arrange for these objects to be destroyed.  It
   doesn't matter, anyway, since the destructors don't do anything.
       
   This must only be called from toplevel (i.e. from finish_file)!  */

void
synthesize_tinfo_fn (fndecl)
     tree fndecl;
{
  tree type = TREE_TYPE (DECL_NAME (fndecl));
  tree tmp, addr;

  tree tdecl = get_tinfo_var (type);
  DECL_EXTERNAL (tdecl) = 0;
  TREE_STATIC (tdecl) = 1;
  DECL_COMMON (tdecl) = 1;
  TREE_USED (tdecl) = 1;
  DECL_ALIGN (tdecl) = TYPE_ALIGN (ptr_type_node);
  cp_finish_decl (tdecl, NULL_TREE, NULL_TREE, 0, 0);

  start_function (NULL_TREE, fndecl, NULL_TREE, 1);
  store_parm_decls ();
  clear_last_expr ();
  push_momentary ();

  /* If the first word of the array (the vtable) is non-zero, we've already
     initialized the object, so don't do it again.  */
  addr = decay_conversion (tdecl);
  tmp = convert (build_pointer_type (ptr_type_node), addr);
  tmp = build_indirect_ref (tmp, 0);
  tmp = build_binary_op (EQ_EXPR, tmp, integer_zero_node, 1);
  expand_start_cond (tmp, 0);

  if (TREE_CODE (type) == FUNCTION_TYPE)
    expand_generic_desc (tdecl, type, "__rtti_func");
  else if (TREE_CODE (type) == ARRAY_TYPE)
    expand_generic_desc (tdecl, type, "__rtti_array");
  else if (TYPE_VOLATILE (type) || TYPE_READONLY (type))
    expand_attr_desc (tdecl, type);
  else if (TREE_CODE (type) == POINTER_TYPE)
    {
      if (TREE_CODE (TREE_TYPE (type)) == OFFSET_TYPE)
	expand_generic_desc (tdecl, type, "__rtti_ptmd");
      else if (TREE_CODE (TREE_TYPE (type)) == METHOD_TYPE)
	expand_generic_desc (tdecl, type, "__rtti_ptmf");
      else
	expand_ptr_desc (tdecl, type);
    }
  else if (TYPE_PTRMEMFUNC_P (type))
    expand_generic_desc (tdecl, type, "__rtti_ptmf");
  else if (IS_AGGR_TYPE (type))
    {
      if (CLASSTYPE_N_BASECLASSES (type) == 0)
	expand_generic_desc (tdecl, type, "__rtti_user");
      else if (! TYPE_USES_COMPLEX_INHERITANCE (type)
	       && (TREE_VIA_PUBLIC
		   (TREE_VEC_ELT (TYPE_BINFO_BASETYPES (type), 0))))
	expand_si_desc (tdecl, type);
      else
	expand_class_desc (tdecl, type);
    }
  else if (TREE_CODE (type) == ENUMERAL_TYPE)
    expand_generic_desc (tdecl, type, "__rtti_user");
  else
    my_friendly_abort (252);

  expand_end_cond ();

  /* OK, now return the type_info object.  */
  tmp = convert (build_pointer_type (type_info_type_node), addr);
  tmp = build_indirect_ref (tmp, 0);
  c_expand_return (tmp);
  finish_function (lineno, 0, 0);
}

#if 0
/* This is the old dossier type descriptor generation code, it's much
   more extended than rtti. It's reserved for later use.  */
/* Build an initializer for a __t_desc node.  So that we can take advantage
   of recursion, we accept NULL for TYPE.
   DEFINITION is greater than zero iff we must define the type descriptor
   (as opposed to merely referencing it).  1 means treat according to
   #pragma interface/#pragma implementation rules.  2 means define as
   global and public, no matter what.  */

tree
build_t_desc (type, definition)
     tree type;
     int definition;
{
  tree tdecl;
  tree tname, name_string;
  tree elems, fields;
  tree parents, vbases, offsets, ivars, methods, target_type;
  int method_count = 0, field_count = 0;

  if (type == NULL_TREE)
    return NULL_TREE;

  tname = build_t_desc_overload (type);
  if (IDENTIFIER_AS_DESC (tname)
      && (!definition || TREE_ASM_WRITTEN (IDENTIFIER_AS_DESC (tname))))
    return IDENTIFIER_AS_DESC (tname);

  tdecl = lookup_name (tname, 0);
  if (tdecl == NULL_TREE)
    {
      tdecl = build_decl (VAR_DECL, tname, __t_desc_type_node);
      DECL_EXTERNAL (tdecl) = 1;
      TREE_PUBLIC (tdecl) = 1;
      tdecl = pushdecl_top_level (tdecl);
    }
  /* If we previously defined it, return the defined result.  */
  else if (definition && DECL_INITIAL (tdecl))
    return IDENTIFIER_AS_DESC (tname);

  if (definition)
    {
      tree taggr = type;
      /* Let T* and T& be written only when T is written (if T is an aggr).
         We do this for const, but not for volatile, since volatile
	 is rare and const is not.  */
      if (!TYPE_VOLATILE (taggr)
	  && (TREE_CODE (taggr) == POINTER_TYPE
	      || TREE_CODE (taggr) == REFERENCE_TYPE)
	  && IS_AGGR_TYPE (TREE_TYPE (taggr)))
	taggr = TREE_TYPE (taggr);

      /* If we know that we don't need to write out this type's
	 vtable, then don't write out it's dossier.  Somebody
	 else will take care of that.  */
      if (IS_AGGR_TYPE (taggr) && CLASSTYPE_VFIELD (taggr))
	{
	  if (CLASSTYPE_VTABLE_NEEDS_WRITING (taggr))
	    {
	      TREE_PUBLIC (tdecl) = ! CLASSTYPE_INTERFACE_ONLY (taggr)
		&& CLASSTYPE_INTERFACE_KNOWN (taggr);
	      DECL_EXTERNAL (tdecl) = 0;
	    }
	  else
	    {
	      if (write_virtuals != 0)
		TREE_PUBLIC (tdecl) = 1;
	    }
	}
      else
	{
	  DECL_EXTERNAL (tdecl) = 0;
	  TREE_PUBLIC (tdecl) = (definition > 1);
	}
    }
  SET_IDENTIFIER_AS_DESC (tname, build_unary_op (ADDR_EXPR, tdecl, 0));

  if (!definition || DECL_EXTERNAL (tdecl))
    {
      /* That's it!  */
      cp_finish_decl (tdecl, NULL_TREE, NULL_TREE, 0, 0);
      return IDENTIFIER_AS_DESC (tname);
    }

  /* Show that we are defining the t_desc for this type.  */
  DECL_INITIAL (tdecl) = error_mark_node;

  parents = build_tree_list (NULL_TREE, integer_zero_node);
  vbases = build_tree_list (NULL_TREE, integer_zero_node);
  offsets = build_tree_list (NULL_TREE, integer_zero_node);
  methods = NULL_TREE;
  ivars = NULL_TREE;

  if (TYPE_LANG_SPECIFIC (type))
    {
      int i = CLASSTYPE_N_BASECLASSES (type);
      tree method_vec = CLASSTYPE_METHOD_VEC (type);
      tree *meth, *end;
      tree binfos = TYPE_BINFO_BASETYPES (type);
      tree vb = CLASSTYPE_VBASECLASSES (type);

      while (--i >= 0)
	parents = tree_cons (NULL_TREE, build_t_desc (BINFO_TYPE (TREE_VEC_ELT (binfos, i)), 0), parents);

      while (vb)
	{
	  vbases = tree_cons (NULL_TREE, build_t_desc (BINFO_TYPE (vb), 0), vbases);
	  offsets = tree_cons (NULL_TREE, BINFO_OFFSET (vb), offsets);
	  vb = TREE_CHAIN (vb);
	}

      if (method_vec)
	for (meth = TREE_VEC_END (method_vec),
	     end = &TREE_VEC_ELT (method_vec, 0); meth-- != end; )
	  if (*meth)
	    {
	      methods = tree_cons (NULL_TREE, build_m_desc (*meth), methods);
	      method_count++;
	    }
    }

  if (IS_AGGR_TYPE (type))
    {
      for (fields = TYPE_FIELDS (type); fields; fields = TREE_CHAIN (fields))
	if (TREE_CODE (fields) == FIELD_DECL
	    || TREE_CODE (fields) == VAR_DECL)
	  {
	    ivars = tree_cons (NULL_TREE, build_i_desc (fields), ivars);
	    field_count++;
	  }
      ivars = nreverse (ivars);
    }

  parents = finish_table (NULL_TREE, build_pointer_type (__t_desc_type_node), parents, 0);
  vbases = finish_table (NULL_TREE, build_pointer_type (__t_desc_type_node), vbases, 0);
  offsets = finish_table (NULL_TREE, integer_type_node, offsets, 0);
  if (methods == NULL_TREE)
    methods = null_pointer_node;
  else
    methods = build_unary_op (ADDR_EXPR,
			      finish_table (NULL_TREE, __m_desc_type_node, methods, 0),
			      0);
  if (ivars == NULL_TREE)
    ivars = null_pointer_node;
  else
    ivars = build_unary_op (ADDR_EXPR,
			    finish_table (NULL_TREE, __i_desc_type_node, ivars, 0),
			    0);
  if (TREE_TYPE (type))
    target_type = build_t_desc (TREE_TYPE (type), definition);
  else
    target_type = integer_zero_node;

  name_string = combine_strings (build_string (IDENTIFIER_LENGTH (tname)+1, IDENTIFIER_POINTER (tname)));

  elems = tree_cons (NULL_TREE, build_unary_op (ADDR_EXPR, name_string, 0),
	   tree_cons (NULL_TREE,
		      TYPE_SIZE(type)? size_in_bytes(type) : integer_zero_node,
	     /* really should use bitfield initialization here.  */
	     tree_cons (NULL_TREE, integer_zero_node,
	      tree_cons (NULL_TREE, target_type,
	       tree_cons (NULL_TREE, build_int_2 (field_count, 2),
		tree_cons (NULL_TREE, build_int_2 (method_count, 2),
		 tree_cons (NULL_TREE, ivars,
		  tree_cons (NULL_TREE, methods,
		   tree_cons (NULL_TREE, build_unary_op (ADDR_EXPR, parents, 0),
		    tree_cons (NULL_TREE, build_unary_op (ADDR_EXPR, vbases, 0),
		     build_tree_list (NULL_TREE, build_unary_op (ADDR_EXPR, offsets, 0))))))))))));
  return build_generic_desc (tdecl, elems);
}

/* Build an initializer for a __i_desc node.  */

tree
build_i_desc (decl)
     tree decl;
{
  tree elems, name_string;
  tree taggr;

  name_string = DECL_NAME (decl);
  name_string = combine_strings (build_string (IDENTIFIER_LENGTH (name_string)+1, IDENTIFIER_POINTER (name_string)));

  /* Now decide whether this ivar should cause it's type to get
     def'd or ref'd in this file.  If the type we are looking at
     has a proxy definition, we look at the proxy (i.e., a
     `foo *' is equivalent to a `foo').  */
  taggr = TREE_TYPE (decl);

  if ((TREE_CODE (taggr) == POINTER_TYPE
       || TREE_CODE (taggr) == REFERENCE_TYPE)
      && TYPE_VOLATILE (taggr) == 0)
    taggr = TREE_TYPE (taggr);

  elems = tree_cons (NULL_TREE, build_unary_op (ADDR_EXPR, name_string, 0),
	     tree_cons (NULL_TREE, DECL_FIELD_BITPOS (decl),
		build_tree_list (NULL_TREE, build_t_desc (TREE_TYPE (decl),
							  ! IS_AGGR_TYPE (taggr)))));
  taggr = build (CONSTRUCTOR, __i_desc_type_node, NULL_TREE, elems);
  TREE_CONSTANT (taggr) = 1;
  TREE_STATIC (taggr) = 1;
  TREE_READONLY (taggr) = 1;
  return taggr;
}

/* Build an initializer for a __m_desc node.  */

tree
build_m_desc (decl)
     tree decl;
{
  tree taggr, elems, name_string;
  tree parm_count, req_count, vindex, vcontext;
  tree parms;
  int p_count, r_count;
  tree parm_types = NULL_TREE;

  for (parms = TYPE_ARG_TYPES (TREE_TYPE (decl)), p_count = 0, r_count = 0;
       parms != NULL_TREE; parms = TREE_CHAIN (parms), p_count++)
    {
      taggr = TREE_VALUE (parms);
      if ((TREE_CODE (taggr) == POINTER_TYPE
	   || TREE_CODE (taggr) == REFERENCE_TYPE)
	  && TYPE_VOLATILE (taggr) == 0)
	taggr = TREE_TYPE (taggr);

      parm_types = tree_cons (NULL_TREE, build_t_desc (TREE_VALUE (parms),
						       ! IS_AGGR_TYPE (taggr)),
			      parm_types);
      if (TREE_PURPOSE (parms) == NULL_TREE)
	r_count++;
    }

  parm_types = finish_table (NULL_TREE, build_pointer_type (__t_desc_type_node),
			     nreverse (parm_types), 0);
  parm_count = build_int_2 (p_count, 0);
  req_count = build_int_2 (r_count, 0);

  if (DECL_VINDEX (decl))
    vindex = DECL_VINDEX (decl);
  else
    vindex = integer_zero_node;
  if (DECL_CONTEXT (decl)
      && TREE_CODE_CLASS (TREE_CODE (DECL_CONTEXT (decl))) == 't')
    vcontext = build_t_desc (DECL_CONTEXT (decl), 0);
  else
    vcontext = integer_zero_node;
  name_string = DECL_NAME (decl);
  if (name_string == NULL)
      name_string = DECL_ASSEMBLER_NAME (decl);
  name_string = combine_strings (build_string (IDENTIFIER_LENGTH (name_string)+1, IDENTIFIER_POINTER (name_string)));

  /* Now decide whether the return type of this mvar
     should cause it's type to get def'd or ref'd in this file.
     If the type we are looking at has a proxy definition,
     we look at the proxy (i.e., a `foo *' is equivalent to a `foo').  */
  taggr = TREE_TYPE (TREE_TYPE (decl));

  if ((TREE_CODE (taggr) == POINTER_TYPE
       || TREE_CODE (taggr) == REFERENCE_TYPE)
      && TYPE_VOLATILE (taggr) == 0)
    taggr = TREE_TYPE (taggr);

  elems = tree_cons (NULL_TREE, build_unary_op (ADDR_EXPR, name_string, 0),
	     tree_cons (NULL_TREE, vindex,
		tree_cons (NULL_TREE, vcontext,
		   tree_cons (NULL_TREE, build_t_desc (TREE_TYPE (TREE_TYPE (decl)),
						       ! IS_AGGR_TYPE (taggr)),
		      tree_cons (NULL_TREE, build_c_cast (build_pointer_type (default_function_type), build_unary_op (ADDR_EXPR, decl, 0)),
			 tree_cons (NULL_TREE, parm_count,
			    tree_cons (NULL_TREE, req_count,
			       build_tree_list (NULL_TREE, build_unary_op (ADDR_EXPR, parm_types, 0)))))))));

  taggr = build (CONSTRUCTOR, __m_desc_type_node, NULL_TREE, elems);
  TREE_CONSTANT (taggr) = 1;
  TREE_STATIC (taggr) = 1;
  TREE_READONLY (taggr) = 1;
  return taggr;
}
#endif /* dossier */
