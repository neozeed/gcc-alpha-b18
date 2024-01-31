/* YACC parser for Ada expressions, for GDB.
   Copyright (C) 1986, 1989, 1990, 1991, 1993, 1994, 1997
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

/* Parse an Ada expression from text in a string,
   and return the result as a  struct expression  pointer.
   That structure contains arithmetic operations in reverse polish,
   with constants represented by operations that are followed by special data.
   See expression.h for the details of the format.
   What is important here is that it can be built up sequentially
   during the process of parsing; the lower levels of the tree always
   come first in the result.

   malloc's and realloc's in this file are transformed to
   xmalloc and xrealloc respectively by the same sed command in the
   makefile that remaps any other malloc/realloc inserted by the parser
   generator.  Doing this with #defines and trying to control the interaction
   with include files (<malloc.h> and <stdlib.h> for example) just became
   too messy, particularly when such includes can be inserted at random
   times by the parser generator.  */
   
%{

#include "defs.h"
#include <string.h>
#include <ctype.h>
#include "expression.h"
#include "value.h"
#include "parser-defs.h"
#include "language.h"
#include "ada-lang.h"
#include "bfd.h" /* Required by objfiles.h.  */
#include "symfile.h" /* Required by objfiles.h.  */
#include "objfiles.h" /* For have_full_symbols and have_partial_symbols */

/* Remap normal yacc parser interface names (yyparse, yylex, yyerror, etc),
   as well as gratuitiously global symbol names, so we can have multiple
   yacc generated parsers in gdb.  These are only the variables
   produced by yacc.  If other parser generators (bison, byacc, etc) produce
   additional global names that conflict at link time, then those parser
   generators need to be fixed instead of adding those names to this list. */

/* NOTE: This is clumsy, especially since BISON and FLEX provide --prefix  
   options.  I presume we are maintaining it to accommodate systems
   without BISON?  (PNH) */

#define	yymaxdepth ada_maxdepth
#define	yyparse	_ada_parse	/* ada_parse calls this after  initialization */
#define	yylex	ada_lex
#define	yyerror	ada_error
#define	yylval	ada_lval
#define	yychar	ada_char
#define	yydebug	ada_debug
#define	yypact	ada_pact	
#define	yyr1	ada_r1			
#define	yyr2	ada_r2			
#define	yydef	ada_def		
#define	yychk	ada_chk		
#define	yypgo	ada_pgo		
#define	yyact	ada_act		
#define	yyexca	ada_exca
#define yyerrflag ada_errflag
#define yynerrs	ada_nerrs
#define	yyps	ada_ps
#define	yypv	ada_pv
#define	yys	ada_s
#define	yy_yys	ada_yys
#define	yystate	ada_state
#define	yytmp	ada_tmp
#define	yyv	ada_v
#define	yy_yyv	ada_yyv
#define	yyval	ada_val
#define	yylloc	ada_lloc
#define yyreds	ada_reds		/* With YYDEBUG defined */
#define yytoks	ada_toks		/* With YYDEBUG defined */

#ifndef YYDEBUG
#define	YYDEBUG	0		/* Default to no yydebug support */
#endif

int
yyparse PARAMS ((void));

static int
yylex PARAMS ((void));

void
yyerror PARAMS ((char *));

static struct stoken
downcase_token PARAMS ((struct stoken));

static char*
save_downcase_string PARAMS ((const char*, int)); 

static struct stoken
string_to_operator PARAMS ((struct stoken));

static void
write_attribute_call0 PARAMS ((enum ada_attribute));

static void
write_attribute_call1 PARAMS ((enum ada_attribute, LONGEST));

static void
write_attribute_calln PARAMS ((enum ada_attribute, int));

%}

/* Although the yacc "value" of an expression is not used,
   since the result is stored in the structure being created,
   other node types do have values.  */

%{

/* A struct ada_name is a pair of strings, one a concatenation of identifiers 
   separated by '.'s with the capitalization originally specified by
   the user, and the other the same string mapped to lower case,
   except for those identifiers specified as `literal', as in x.'abC'. */

struct ada_name {
  struct stoken original;	
  struct stoken lookup_form;
}; 

static struct ada_name NULL_NAME = { {"", 0}, {"", 0} };

static struct ada_name
name_cons PARAMS ((struct ada_name, struct stoken, int));

static void 
write_var PARAMS ((struct block*, struct ada_name));

static void
write_var_from_name PARAMS ((struct block*, struct stoken, struct stoken));

%} 

%union
  {
    LONGEST lval;
    struct {
      LONGEST val;
      struct type *type;
    } typed_val;
    struct {
      DOUBLEST dval;
      struct type *type;
    } typed_val_float;
    struct symbol *sym;
    struct type *tval;
    struct stoken sval;
    struct ttype tsym;
    struct symtoken ssym;
    int voidval;
    struct block *bval;
    enum exp_opcode opcode;
    struct internalvar *ivar;

    struct ada_name name;
  }

%type <voidval> exp exp1 type_exp start 
%type <tval> type 
%type <name> variable 

%token <typed_val> INT NULL_PTR 
%token <typed_val_float> FLOAT

/* Both NAME and TYPENAME tokens represent symbols in the input,
   and both convey their data as strings.
   But a TYPENAME is a string that happens to be defined as a typedef
   or builtin type name (such as int or char)
   and a NAME is any other symbol.
   Contexts where this distinction is not important can use the
   nonterminal "name", which matches either NAME or TYPENAME.  */

%token <sval> STRING
%token <ssym> NAME BLOCKNAME 
%token <tsym> TYPENAME
%token <sval> DOT_LITERAL_NAME
%type <sval> name name_not_typename
%type <tsym> typename
%type <bval> block 
%type <lval> arglist tick_arglist

%token COLONCOLON
%token ERROR
%token ALL

/* Special type cases, put in to allow the parser to distinguish different
   legal basetypes.  */
%token <lval> LAST REGNAME

%token <ivar> INTERNAL_VARIABLE

%nonassoc ASSIGN
%left _AND_ OR XOR THEN ELSE
%left '=' NOTEQUAL '<' '>' LEQ GEQ IN DOTDOT
%left '@'
%left '+' '-' '&'
%left UNARY
%left '*' '/' MOD REM
%right STARSTAR ABS NOT
 /* The following are right-associative only so that reductions at this 
    precedence have lower precedence than '.' and '('. The syntax still 
    forces a.b.c, e.g., to be LEFT-associated. */
%right TICK_ACCESS TICK_FIRST TICK_LAST TICK_LENGTH 
%right TICK_MAX TICK_MIN TICK_POS TICK_RANGE TICK_TAG TICK_VAL
%right '.' '(' '[' DOT_LITERAL_NAME
%left COLONCOLON

%token ARROW NEW


%%

start   :	exp1
	|	type_exp
	;

type_exp:	type
			{ write_exp_elt_opcode (OP_TYPE);
			  write_exp_elt_type ($1);
			  write_exp_elt_opcode (OP_TYPE);}
	;

/* Expressions, including the sequencing operator.  */
exp1	:	exp
	|	exp1 ';' exp
			{ write_exp_elt_opcode (BINOP_COMMA); }		
	;

/* Expressions, not including the sequencing operator.  */
exp	: 	exp ASSIGN exp   /* Extension for convenience */
			{ write_exp_elt_opcode (BINOP_ASSIGN); }
	;

exp	:	exp '.' ALL
			{ write_exp_elt_opcode (UNOP_IND); }
	;

exp	:	'-' exp    %prec UNARY
			{ write_exp_elt_opcode (UNOP_NEG); }
	;

exp	:	'+' exp    %prec UNARY
			{ write_exp_elt_opcode (UNOP_PLUS); }
	;

exp     :	NOT exp    %prec UNARY
			{ write_exp_elt_opcode (UNOP_LOGICAL_NOT); }
	;

exp	:       ABS exp	   %prec UNARY
			{ write_exp_elt_opcode (UNOP_ABS); }
	;

exp	:	exp '.' name
			{ write_exp_elt_opcode (STRUCTOP_STRUCT);
			  write_exp_string (downcase_token ($3));
			  write_exp_elt_opcode (STRUCTOP_STRUCT); }
	|	exp DOT_LITERAL_NAME
			{ write_exp_elt_opcode (STRUCTOP_STRUCT);
			  write_exp_string ($2);
			  write_exp_elt_opcode (STRUCTOP_STRUCT); }
	;

exp	:	exp '(' arglist ')'	%prec ARROW  
			{ write_exp_elt_opcode (OP_FUNCALL);
			  write_exp_elt_longcst ($3);
			  write_exp_elt_opcode (OP_FUNCALL);
		        }
        |	STRING '(' 
			{ write_var (expression_context_block,
				     name_cons (NULL_NAME,
						string_to_operator ($1), 1));
			}
		arglist ')'
			{ 
			  write_exp_elt_opcode (OP_FUNCALL);
			  write_exp_elt_longcst ($4);
			  write_exp_elt_opcode (OP_FUNCALL);
		        }
	;

exp     :	exp '(' exp DOTDOT exp ')'
			{ write_exp_elt_opcode (TERNOP_SLICE); }
	;
			  

arglist	:		{ $$ = 0; }
	;

arglist	:	exp
			{ $$ = 1; }
	|	name ARROW exp
			{ $$ = 1; }
	|	arglist ',' exp
			{ $$ = $1 + 1; }
	|	arglist ',' name ARROW exp
			{ $$ = $1 + 1; }
	;

exp	:	'{' type '}' exp  %prec '.'
		/* GDB extension */
			{ write_exp_elt_opcode (UNOP_MEMVAL);
			  write_exp_elt_type ($2);
			  write_exp_elt_opcode (UNOP_MEMVAL); }
	;

exp	:	'(' exp1 ')'
			{ }
	;

/* Binary operators in order of decreasing precedence.  */

exp 	: 	exp STARSTAR exp
			{ write_exp_elt_opcode (BINOP_EXP); }
	;

exp	:	exp '*' exp
			{ write_exp_elt_opcode (BINOP_MUL); }
	;

exp	:	exp '/' exp
			{ write_exp_elt_opcode (BINOP_DIV); }
	;

exp	:	exp REM exp /* May need to be fixed to give correct Ada REM */
			{ write_exp_elt_opcode (BINOP_REM); }
	;

exp	:	exp MOD exp
			{ write_exp_elt_opcode (BINOP_MOD); }
	;

exp	:	exp '@' exp	/* GDB extension */
			{ write_exp_elt_opcode (BINOP_REPEAT); }
	;

exp	:	exp '+' exp
			{ write_exp_elt_opcode (BINOP_ADD); }
	;

exp	:	exp '&' exp
			{ write_exp_elt_opcode (BINOP_CONCAT); }
	;

exp	:	exp '-' exp
			{ write_exp_elt_opcode (BINOP_SUB); }
	;

exp	:	exp '=' exp
			{ write_exp_elt_opcode (BINOP_EQUAL); }
	;

exp	:	exp NOTEQUAL exp
			{ write_exp_elt_opcode (BINOP_NOTEQUAL); }
	;

exp	:	exp LEQ exp
			{ write_exp_elt_opcode (BINOP_LEQ); }
	;

exp	:	exp IN exp DOTDOT exp
			{ write_exp_elt_opcode (TERNOP_MBR); }
        |       exp IN exp TICK_RANGE tick_arglist
			{ write_exp_elt_opcode (BINOP_MBR); 
			  write_exp_elt_longcst ((LONGEST) $5);
			  write_exp_elt_opcode (BINOP_MBR); }
 	|	exp IN type
			{ write_exp_elt_opcode (UNOP_MBR); 
		          write_exp_elt_type ($3);
		          write_exp_elt_opcode (UNOP_MBR); }
	|	exp NOT IN exp DOTDOT exp
			{ write_exp_elt_opcode (TERNOP_MBR); 
		          write_exp_elt_opcode (UNOP_LOGICAL_NOT); }
        |       exp NOT IN exp TICK_RANGE tick_arglist
			{ write_exp_elt_opcode (BINOP_MBR); 
			  write_exp_elt_longcst ((LONGEST) $6);
			  write_exp_elt_opcode (BINOP_MBR);
		          write_exp_elt_opcode (UNOP_LOGICAL_NOT); }
 	|	exp NOT IN type
			{ write_exp_elt_opcode (UNOP_MBR); 
		          write_exp_elt_type ($4);
		          write_exp_elt_opcode (UNOP_MBR);
		          write_exp_elt_opcode (UNOP_LOGICAL_NOT); }
	;

exp	:	exp GEQ exp
			{ write_exp_elt_opcode (BINOP_GEQ); }
	;

exp	:	exp '<' exp
			{ write_exp_elt_opcode (BINOP_LESS); }
	;

exp	:	exp '>' exp
			{ write_exp_elt_opcode (BINOP_GTR); }
	;

exp     :	exp _AND_ exp  /* Fix for Ada elementwise AND. */
			{ write_exp_elt_opcode (BINOP_BITWISE_AND); }
        ;

exp     :       exp _AND_ THEN exp	%prec _AND_
			{ write_exp_elt_opcode (BINOP_LOGICAL_AND); }
        ;

exp     :	exp OR exp     /* Fix for Ada elementwise OR */
			{ write_exp_elt_opcode (BINOP_BITWISE_IOR); }
        ;

exp     :       exp OR ELSE exp        
			{ write_exp_elt_opcode (BINOP_LOGICAL_OR); }
        ;

exp     :       exp XOR exp    /* Fix for Ada elementwise XOR */
			{ write_exp_elt_opcode (BINOP_BITWISE_XOR); }
        ;

exp	:	exp TICK_ACCESS
			{ write_exp_elt_opcode (UNOP_ADDR); }
	|	exp TICK_FIRST tick_arglist
			{ write_attribute_call1 (ATR_FIRST, $3); }
	|	exp TICK_LAST tick_arglist
			{ write_attribute_call1 (ATR_LAST, $3); }
	| 	exp TICK_LENGTH tick_arglist
			{ write_attribute_call1 (ATR_LENGTH, $3); }
	|	exp TICK_TAG
			{ write_attribute_call0 (ATR_TAG); }
        |       opt_type_prefix TICK_MIN '(' exp ',' exp ')'
			{ write_attribute_calln (ATR_MIN, 2); }
        |       opt_type_prefix TICK_MAX '(' exp ',' exp ')'
			{ write_attribute_calln (ATR_MAX, 2); }
	| 	opt_type_prefix TICK_POS '(' exp ')'
			{ write_attribute_calln (ATR_POS, 1); }
	|	type_prefix TICK_VAL '(' exp ')'
			{ write_attribute_calln (ATR_VAL, 1); }
	;

tick_arglist :			%prec '('
			{ $$ = 1; }
	| 	'(' INT ')'
			{ $$ = $2.val; }
	;

type_prefix :
		typename
			{ write_exp_elt_opcode (OP_TYPE);
			  write_exp_elt_type ($1.type);
			  write_exp_elt_opcode (OP_TYPE); }
	;

opt_type_prefix :
		type_prefix
	| 	/* EMPTY */     
			{ write_exp_elt_opcode (OP_TYPE);
			  write_exp_elt_type (builtin_type_void);
			  write_exp_elt_opcode (OP_TYPE); }
	;
		

exp	:	INT
			{ write_exp_elt_opcode (OP_LONG);
			  write_exp_elt_type ($1.type);
			  write_exp_elt_longcst ((LONGEST)($1.val));
			  write_exp_elt_opcode (OP_LONG); }
	;

exp	:	FLOAT
			{ write_exp_elt_opcode (OP_DOUBLE);
			  write_exp_elt_type ($1.type);
			  write_exp_elt_dblcst ($1.dval);
			  write_exp_elt_opcode (OP_DOUBLE); }
	;

exp	:	NULL_PTR
			{ write_exp_elt_opcode (OP_LONG);
			  write_exp_elt_type (builtin_type_int);
			  write_exp_elt_longcst ((LONGEST)(0));
			  write_exp_elt_opcode (OP_LONG); }

exp	:	LAST
			{ write_exp_elt_opcode (OP_LAST);
			  write_exp_elt_longcst ((LONGEST) $1);
			  write_exp_elt_opcode (OP_LAST); }
	;

exp	:	REGNAME /* GDB extension */
			{ write_exp_elt_opcode (OP_REGISTER);
			  write_exp_elt_longcst ((LONGEST) $1);
			  write_exp_elt_opcode (OP_REGISTER); }
	;

exp	:	INTERNAL_VARIABLE /* GDB extension */
			{ write_exp_elt_opcode (OP_INTERNALVAR);
			  write_exp_elt_intern ($1);
			  write_exp_elt_opcode (OP_INTERNALVAR); }
	;

exp	:	STRING		%prec '('
			{ /* Ada strings are converted into array constants 
			     a lower bound of 1.  Thus, the array upper bound 
			     is the string length. */
			  char *sp = $1.ptr; int count;
			  if ($1.length == 0) 
			    { /* One dummy character for the type */
			      write_exp_elt_opcode (OP_LONG);
			      write_exp_elt_type (builtin_type_ada_char);
			      write_exp_elt_longcst ((LONGEST)(0));
			      write_exp_elt_opcode (OP_LONG);
			    }
			  for (count = $1.length; count > 0; count -= 1)
			    {
			      write_exp_elt_opcode (OP_LONG);
			      write_exp_elt_type (builtin_type_ada_char);
			      write_exp_elt_longcst ((LONGEST)(*sp));
			      sp += 1;
			      write_exp_elt_opcode (OP_LONG);
			    }
			  write_exp_elt_opcode (OP_ARRAY);
			  write_exp_elt_longcst ((LONGEST) 1);
			  write_exp_elt_longcst ((LONGEST) ($1.length));
			  write_exp_elt_opcode (OP_ARRAY); }
	;

exp	: 	NEW type	%prec TICK_ACCESS
			{ error ("NEW not implemented."); }
	;


exp	:	variable	%prec '.'
			{ write_var (expression_context_block, $1); }
	;

exp	: 	variable '.' ALL
			{ write_var (expression_context_block, $1);
			  write_exp_elt_opcode (UNOP_IND);
			}
	;


exp	:	block variable  %prec '.'  /* GDB extension */
			{ write_var ($1, $2); }
	;

exp	: 	block variable '.' ALL     /* GDB extension */
			{ write_var ($1, $2);
			  write_exp_elt_opcode (UNOP_IND);
			}
	;

exp	: 	type '(' exp ')'
			{ write_exp_elt_opcode (UNOP_CAST);
			  write_exp_elt_type ($1);
			  write_exp_elt_opcode (UNOP_CAST); }
        ;

block	:	BLOCKNAME COLONCOLON  /* GDB extension */
			{
			  if ($1.sym != 0)
			      $$ = SYMBOL_BLOCK_VALUE ($1.sym);
			  else
			    {
			      struct symtab *tem =
				lookup_symtab (save_downcase_string
					       ($1.stoken.ptr,
						$1.stoken.length));
			      if (tem)
				$$ = BLOCKVECTOR_BLOCK
					 (BLOCKVECTOR (tem), STATIC_BLOCK);
			      else
				error ("No file or function \"%s\".",
				       copy_name ($1.stoken));
			    }
			}

	|	block name COLONCOLON /* GDB extension */
			{ struct symbol** syms;
			  struct block** blocks;
			  int nsyms;
			  nsyms = ada_lookup_symbol_list (copy_name ($2), $1,
							  VAR_NAMESPACE, 
							  &syms,
							  &blocks);
			  if (nsyms == 0 || SYMBOL_CLASS (syms[0]) != LOC_BLOCK)
			    error ("No function \"%s\" in specified context.",
				   copy_name ($2));
			  else if (nsyms > 1)
			    warning ("Function name \"%s\" ambiguous here",
				     copy_name ($2));
			  $$ = SYMBOL_BLOCK_VALUE (syms[0]); }
	;


variable:	name_not_typename
			{ $$ = name_cons (NULL_NAME, $1, 0); }
	;

variable:	variable '.' name
			{ $$ = name_cons ($1, $3, 0); }
	|	variable DOT_LITERAL_NAME
			{ $$ = name_cons ($1, $2, 1); }
	|	variable '.' STRING
			{ $$ = name_cons ($1, string_to_operator ($3), 1); }
	|	TYPENAME '.' name
			{ $$ = name_cons (name_cons (NULL_NAME, $1.stoken, 0), 
					  $3, 0); }
	|	TYPENAME DOT_LITERAL_NAME
			{ $$ = name_cons (name_cons (NULL_NAME, $1.stoken, 0),
					  $2, 1); }
	|	TYPENAME '.' STRING
			{ $$ = name_cons (name_cons (NULL_NAME, $1.stoken, 0), 
					  string_to_operator ($3), 
					  1); }
	;

type	:	typename	{ $$ = $1.type; }
	| 	type TICK_ACCESS 
				{ $$ = lookup_pointer_type ($1); }
        ;

typename:	TYPENAME	%prec '.'
	;

name	:	NAME { $$ = $1.stoken; }
	|	BLOCKNAME { $$ = $1.stoken; }
	|	TYPENAME { $$ = $1.stoken; }
	;

name_not_typename :
		NAME { $$ = $1.stoken; }
	|	BLOCKNAME { $$ = $1.stoken; }
	;

/* Some extensions borrowed from C, for the benefit of those who find they
   can't get used to Ada notation in GDB. */

exp	:	'*' exp		%prec '.'
			{ write_exp_elt_opcode (UNOP_IND); }
	|	'&' exp		%prec '.'
			{ write_exp_elt_opcode (UNOP_ADDR); }
	|	exp '[' exp ']'
			{ write_exp_elt_opcode (BINOP_SUBSCRIPT); }
	;

%%

/* yylex defined in ada-lex.c: Reads one token, getting characters */
/* through lexptr.  */

/* Remap normal flex interface names (yylex) as well as gratuitiously */
/* global symbol names, so we can have multiple flex-generated parsers */
/* in gdb.  */

/* (See note above on previous definitions for YACC.) */

#define yy_create_buffer ada_yy_create_buffer
#define yy_delete_buffer ada_yy_delete_buffer
#define yy_init_buffer ada_yy_init_buffer
#define yy_load_buffer_state ada_yy_load_buffer_state
#define yy_switch_to_buffer ada_yy_switch_to_buffer
#define yyrestart ada_yyrestart
#define yytext ada_yytext
#define yywrap ada_yywrap

/* The following kludge was found necessary to prevent conflicts between */
/* defs.h and non-standard stdlib.h files.  */
#define qsort __qsort__dummy
#include "ada-lex.c"

int
ada_parse ()
{
  yyrestart (yyin);		/* (Re-)initialize lexer. */
  return _ada_parse ();
}

void
yyerror (msg)
     char *msg;
{
  error ("A %s in expression, near `%s'.", (msg ? msg : "error"), lexptr);
}

/* Append NAME to PREFIX.  Unless IS_LITERAL is non-zero, the 
   lookup_form of the result is folded to lower-case.  All resulting
   strings are cleaned up after parsing and name resolution. */

static struct ada_name
name_cons (prefix, name, is_literal)
     struct ada_name prefix;
     struct stoken name;
     int is_literal;
{
  int len0 = prefix.original.length;
  int lenr = len0 + name.length + (len0 > 0);
  struct ada_name result;

  result.original.ptr = (char*) malloc (lenr + 1);
  result.lookup_form.ptr = (char*) malloc (lenr + 1);
  result.original.length = result.lookup_form.length = lenr;
  add_name_string_cleanup (result.original.ptr);
  add_name_string_cleanup (result.lookup_form.ptr);

  strcpy (result.original.ptr, prefix.original.ptr);
  if (len0 > 0)
    {
      strcpy (result.original.ptr+len0, ".");
      strncpy (result.original.ptr+len0+1, name.ptr, name.length);
    }
  else
    strncpy (result.original.ptr, name.ptr, name.length);
  result.original.ptr[lenr] = '\000';

  strcpy (result.lookup_form.ptr, result.original.ptr);
  if (! is_literal)
    {	
      int k;
      for (k = lenr - name.length; result.lookup_form.ptr[k] != '\000'; k += 1)
	result.lookup_form.ptr[k] = tolower (result.lookup_form.ptr[k]);
    }

  return result;
}

/* The operator name corresponding to operator symbol STRING (adds 
   quotes and maps to lower-case).  Destroys the previous contents of
   the array pointed to by STRING.ptr.  Error if STRING does not match
   a valid Ada operator.  Assumes that STRING.ptr points to a
   null-terminated string and that, if STRING is a valid operator
   symbol, the array pointed to by STRING.ptr contains at least
   STRING.length+3 characters. */ 

static struct stoken
string_to_operator (string)
     struct stoken string;
{
  int i;

  for (i = 0; ada_opname_table[i].mangled != NULL; i += 1)
    {
      if (string.length == strlen (ada_opname_table[i].demangled)-2
	  && strncasecmp (string.ptr, ada_opname_table[i].demangled+1,
			  string.length) == 0)
	{
	  strncpy (string.ptr, ada_opname_table[i].demangled,
		   string.length+2);
	  string.length += 2;
	  return string;
	}
    }
  error ("Invalid operator symbol `%s'", string.ptr);
}

/* Emit expression to access an instance of NAME[0..LEN-1]. If BLK is 
   non-null, starts search in context BLK. Use ERROR_NAME for error
   messages. */

static void
write_var_from_name (blk, name, error_name)
     struct block* blk; 
     struct stoken name, error_name;
{
  struct symbol** syms;  
  struct block** blocks;
  struct stoken prefix;

  if (ada_lookup_symbol_list (copy_name (name), blk, VAR_NAMESPACE, 
			      &syms, &blocks) == 0)
    {
      /* Before giving up on NAME, try for a minimal symbol that has no 
	 matching full symbol. */
      struct minimal_symbol* msymbol = 
	ada_lookup_minimal_symbol (copy_name (name));
      if (msymbol != NULL)
	{
	  write_exp_msymbol (msymbol,
			     lookup_function_type (builtin_type_int),
			     builtin_type_int);
	  return;
	}
    }
  else
    {
      /* One or more matches: record name and starting block for later 
         resolution by ada_resolve (even when unambiguous, since that
	 is harmless and simplifies the procedure). */
      write_exp_elt_opcode (OP_UNRESOLVED_VALUE);
      write_exp_elt_block (blk);
      write_exp_elt_name (copy_name (name));
      write_exp_elt_opcode (OP_UNRESOLVED_VALUE);
      return;
    }

  prefix = name;
  for (prefix.length -= 1;
       prefix.length > 0 && prefix.ptr[prefix.length] != '.';
       prefix.length -= 1)
    { }

  if (prefix.length == 0)
    {
      if (!have_full_symbols () && !have_partial_symbols ())
	error ("No symbol table is loaded.  Use the \"file\" command.");
      else if (blk != NULL) 
	error ("No definition of \"%s\" in specified context.", 
	       copy_name (error_name));
      else
	error ("No definition of \"%s\" in current context.", 
	       copy_name (error_name));
    }
  else 
    { 
      struct stoken suffix;	/* The last component of NAME. */
      suffix.length = name.length - prefix.length - 1;
      suffix.ptr = name.ptr + prefix.length + 1;

      /* Check the prefix. If it is unambiguous and names a function
	 (actually, a "block"), we check to see if name without the prefix is 
	 a local in that function. If it is undefined, we
	 try to treat this as a structure access.  It doesn't catch
	 all cases of selecting local variables of functions---so sue me. */

      if  (ada_lookup_symbol_list (copy_name (prefix), blk, VAR_NAMESPACE, 
				   &syms, &blocks) == 1
	   && SYMBOL_CLASS (syms[0]) == LOC_BLOCK)
	{
	  struct block* prefix_block = blocks[0];
	  int nsyms = 
	    ada_lookup_symbol_list (copy_name (suffix), blk,
				    VAR_NAMESPACE, &syms, &blocks);
	  int k;

	  for (k = 0; k < nsyms; k += 1)
	    if (contained_in (blocks[k], prefix_block)) 
	      {
		write_exp_elt_opcode (OP_UNRESOLVED_VALUE);
		write_exp_elt_block (blocks[k]);
		write_exp_elt_name (copy_name (suffix));
		write_exp_elt_opcode (OP_UNRESOLVED_VALUE);
		return;
	      }
	}


      /* Treat as structure access. */

      write_var_from_name (blk, prefix, error_name);
      write_exp_elt_opcode (STRUCTOP_STRUCT);
      write_exp_string (suffix);
      write_exp_elt_opcode (STRUCTOP_STRUCT);
    }
}
  
/* Generate expression for BLK :: NAME or NAME (when BLK == NULL). */

static void 
write_var (blk, name)
     struct block* blk;
     struct ada_name name;
{
  write_var_from_name (blk, name.lookup_form, name.original);
}


/* Write a call on parameterless attribute ATR.  */

static void
write_attribute_call0 (atr)
     enum ada_attribute atr;
{
  write_exp_elt_opcode (OP_ATTRIBUTE);
  write_exp_elt_longcst ((LONGEST) 0);
  write_exp_elt_longcst ((LONGEST) atr);
  write_exp_elt_opcode (OP_ATTRIBUTE);
}

/* Write a call on an attribute ATR with one constant integer
   parameter. */

static void
write_attribute_call1 (atr, arg)
     enum ada_attribute atr;
     LONGEST arg;
{
  write_exp_elt_opcode (OP_LONG);
  write_exp_elt_type (builtin_type_int);
  write_exp_elt_longcst (arg);
  write_exp_elt_opcode (OP_LONG);
  write_exp_elt_opcode (OP_ATTRIBUTE);
  write_exp_elt_longcst ((LONGEST) 1);
  write_exp_elt_longcst ((LONGEST) atr);
  write_exp_elt_opcode (OP_ATTRIBUTE);
}  

/* Write a call on an attribute ATR with N parameters, whose code must have
   been generated previously. */

static void
write_attribute_calln (atr, n)
     enum ada_attribute atr;
     int n;
{
  write_exp_elt_opcode (OP_ATTRIBUTE);
  write_exp_elt_longcst ((LONGEST) n);
  write_exp_elt_longcst ((LONGEST) atr);
  write_exp_elt_opcode (OP_ATTRIBUTE);
}  

/* Return a token that is the same as TOK, but with its name in lower 
   case. */

static struct stoken
downcase_token (tok)
     struct stoken tok;
{
  tok.ptr = save_downcase_string (tok.ptr, tok.length);
  return tok;
}

/* Return S[0..LEN-1], terminated by a null byte, with upper-case 
   letters mapped to lower case.  The string is added to the name
   cleanup list, released at the end of parsing. */

static char*
save_downcase_string (s, len)
     const char s[];
     int len;
{
  int i;
  char* new_name = savestring (s, len);
  add_name_string_cleanup (new_name);
  
  for (i = 0; i < len; i += 1)
    new_name[i] = tolower (s[i]);
  return new_name;
}

