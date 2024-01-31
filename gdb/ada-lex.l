/* FLEX lexer for Ada expressions, for GDB.
   Copyright (C) 1994, 1997
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

/*----------------------------------------------------------------------*/

/* The converted version of this file is to be included in ada-exp.y, */
/* the Ada parser for gdb.  The function yylex obtains characters from */
/* the global pointer lexptr.  It returns a syntactic category for */
/* each successive token and places a semantic value into yylval */
/* (ada-lval), defined by the parser.   */

/* Run flex with (at least) the -i option (case-insensitive), and the -I */
/* option (interactive---no unnecessary lookahead).  */

DIG	[0-9]
NUM10	({DIG}({DIG}|_)*)
HEXDIG	[0-9a-f]
NUM16	({HEXDIG}({HEXDIG}|_)*)
OCTDIG	[0-7]
LETTER	[a-z_]
ID	({LETTER}({LETTER}|{DIG})*)
WHITE	[ \t\n]
TICK	("'"{WHITE}*)
GRAPHIC [a-z0-9 #&'()*+,-./:;<>=_|!$%?@\[\]\\^`{}~]

EXP	(e[+-]{NUM10})
POSEXP  (e"+"?{NUM10})

%{
#define NUMERAL_WIDTH 256

/* Temporary staging for numeric literals. */
static char numbuf[NUMERAL_WIDTH]; 

static void canonicalizeNumeral PARAMS ((char* s1, const char*));
static int processInt PARAMS ((const char*, const char*, const char*));
static int processReal PARAMS ((const char*));
static int processId PARAMS ((const char*, int));
static int digitval PARAMS ((char));

#undef YY_DECL
#define YY_DECL static int yylex PARAMS (( void )) 

#undef YY_INPUT
#define YY_INPUT(BUF, RESULT, MAX_SIZE) \
    if ( *lexptr == '\000' ) \
      (RESULT) = YY_NULL; \
    else \
      { \
        *(BUF) = *lexptr; \
        (RESULT) = 1; \
	lexptr += 1; \
      }

static char *tempbuf = NULL;
static int tempbufsize = 0;

static void
resize_tempbuf PARAMS ((unsigned int));

%}

%%

{WHITE}		 { }

"--".*		 { yyterminate(); }

{NUM10}{POSEXP}  { 
		   canonicalizeNumeral (numbuf, yytext); 
		   return processInt (NULL, numbuf, strrchr(numbuf, 'e')+1);
		 }

{NUM10}          { 
		   canonicalizeNumeral (numbuf, yytext); 
		   return processInt (NULL, numbuf, NULL);
		 }

{NUM10}"#"{HEXDIG}({HEXDIG}|_)*"#"{POSEXP} {
		   canonicalizeNumeral (numbuf, yytext);
    		   return processInt (numbuf,
				      strchr (numbuf, '#') + 1, 
				      strrchr(numbuf, '#') + 1);
		 }

{NUM10}"#"{HEXDIG}({HEXDIG}|_)*"#" {
		   canonicalizeNumeral (numbuf, yytext);
    		   return processInt (numbuf, strchr (numbuf, '#') + 1, NULL);
		 }

"0x"{HEXDIG}+	{
		  canonicalizeNumeral (numbuf, yytext+2);
		  return processInt ("16#", numbuf, NULL);
		}


{NUM10}"."{NUM10}{EXP} {
		   canonicalizeNumeral (numbuf, yytext); 
		   return processReal (numbuf);
		}

{NUM10}"."{NUM10} {
		   canonicalizeNumeral (numbuf, yytext); 
		   return processReal (numbuf);
		}

{NUM10}"#"{NUM16}"."{NUM16}"#"{EXP} {
                   error ("Based real literals not implemented yet.");
		}

{NUM10}"#"{NUM16}"."{NUM16}"#" {
                   error ("Based real literals not implemented yet.");
		}

"."{WHITE}*"'"[^']+"'" { 
		  char* name = strchr(yytext, '\'') + 1;
                  processId(name, yyleng-(name-yytext)-1);
		  yylval.sval = yylval.ssym.stoken;
		  return DOT_LITERAL_NAME;
		}


"'"({GRAPHIC}|\")"'" {
		   yylval.typed_val.type = builtin_type_ada_char;
		   yylval.typed_val.val = yytext[1];
		   return INT;
		}

\"{GRAPHIC}*\"  {
		   resize_tempbuf (yyleng-1);
		   strncpy(tempbuf, yytext+1, yyleng-2);
		   tempbuf[yyleng-2] = '\000';
		   yylval.sval.ptr = tempbuf;
		   yylval.sval.length = yyleng-2;
		   return STRING;
		}

if		{ 
		  while (*lexptr != 'i' && *lexptr != 'I') 
		    lexptr -= 1; 
		  yyrestart(NULL); 
		  return 0;
		}

	/* ADA KEYWORDS */

abs		{ return ABS; }
all		{ return ALL; }
and		{ return _AND_; }
else		{ return ELSE; }
in		{ return IN; }
mod		{ return MOD; }
new		{ return NEW; }
not		{ return NOT; }
null		{ return NULL_PTR; }
or		{ return OR; }
rem		{ return REM; }
then		{ return THEN; }
xor		{ return XOR; }

        /* ATTRIBUTES */

{TICK}unchecked_access		|
{TICK}unrestricted_access 	|
{TICK}access     { return TICK_ACCESS; }
{TICK}first      { return TICK_FIRST; }
{TICK}last       { return TICK_LAST; }
{TICK}length	 { return TICK_LENGTH; }
{TICK}max	 { return TICK_MAX; }
{TICK}min	 { return TICK_MIN; }
{TICK}pos	 { return TICK_POS; }
{TICK}range	 { return TICK_RANGE; }
{TICK}tag	 { return TICK_TAG; }
{TICK}val	 { return TICK_VAL; }
{TICK}{ID}       { error ("unrecognized attribute: `%s'", yytext+1); } 

	/* PUNCTUATION */

"=>"		{ return ARROW; }
".."		{ return DOTDOT; }
"**"		{ return STARSTAR; }
":="		{ return ASSIGN; }
"/="		{ return NOTEQUAL; }
"<="		{ return LEQ; }
">="		{ return GEQ; }

[-&'*+./:<>=|;\[\]] { return yytext[0]; }

","		{ if (paren_depth == 0 && comma_terminates)
		    {
		      lexptr -= 2;
		      yyrestart(NULL);
		      return 0;
		    }
		  else 
		    return ',';
		}

"("		{ paren_depth += 1; return '('; }
")"		{ if (paren_depth == 0) 
		    {
		      lexptr -= 2;
		      yyrestart(NULL);
		      return 0;
		    }
		  else 
 		    {
		      paren_depth -= 1; 
		      return ')';
		    }
		}

{ID}		{ return processId(yytext, yyleng); }

	/* GDB EXPRESSION CONSTRUCTS  */

"'"[^']+"'"/{WHITE}*::  { 
                  return processId(yytext+1, yyleng-2);
		}

"::"		{ return COLONCOLON; }
[{}@]		{ return yytext[0]; }

"$$"		{ yylval.lval = -1; return LAST; }
"$$"{DIG}+	{ yylval.lval = -atoi(yytext+2); return LAST; }
"$"		{ yylval.lval = 0; return LAST; }
"$"{DIG}+	{ yylval.lval = atoi(yytext+1); return LAST; }


	/* REGISTERS AND GDB CONVENIENCE VARIABLES */

"$"({LETTER}|{DIG}|"$")+  {
    		  int c;
		  for (c = 0; c < NUM_REGS; c++)
		    if (strcmp (yytext + 1, reg_names[c]) == 0)
		      {
			yylval.lval = c;
			return REGNAME;
		      }
		  for (c = 0; c < num_std_regs; c++)
		    if (strcmp (yytext+1, std_regs[c].name) == 0)
		      {	
			yylval.lval = std_regs[c].regnum;
			return REGNAME;
		      }
		  yylval.sval.ptr = yytext;
		  yylval.sval.length = yyleng;
		  yylval.ivar = 
		    lookup_internalvar (copy_name (yylval.sval) + 1);
		  return INTERNAL_VARIABLE;
		}

	/* CATCH-ALL ERROR CASE */

.		{ error ("Invalid character '%s' in expression.", yytext); }
%%

/* Make sure that tempbuf points at an array at least N characters long. */

static void
resize_tempbuf (n)
     unsigned int n;
{
  if (tempbufsize < n)
    {
      tempbufsize = (n+63) & ~63;
      tempbuf = (char*) xrealloc (tempbuf, tempbufsize);
    }
}
 

/* Convert hex digit c into the corresponding int 0-15. */

static int
digitval(c)
     char c;
{
  if (isdigit(c))
    return c - '0';
  else
    return tolower(c) - 'a' + 10;
}


/* Copy S2 to S1, removing all underscores, and downcasing all letters. */

static void
canonicalizeNumeral (s1,s2)
     char* s1;
     const char* s2;
{
  for (; *s2 != '\000'; s2 += 1) 
    {
      if (*s2 != '_')
	{
	  *s1 = tolower(*s2);
	  s1 += 1;
	}
    }
  s1[0] = '\000';
}

#define HIGH_BYTE_POSN ((sizeof (unsigned LONGEST) - 1) * 8)

/* True (non-zero) iff DIGIT is a valid digit in radix BASE, 
   where 2 <= BASE <= 16.  */

static int
is_digit_in_base (digit, base)
     unsigned char digit;
     int base;
{
  if (!isxdigit (digit))
    return 0;
  if (base <= 10)
    return (isdigit (digit) && digit < base + '0');
  else 
    return (isdigit (digit) || tolower (digit) < base - 10 + 'a');
}

static int
digit_to_int (c)
     unsigned char c;
{
  if (isdigit (c))
    return c - '0';
  else
    return tolower (c) - 'a' + 10;
}

/* As for strtoul, but for unsigned LONGEST results. */
unsigned LONGEST
strtoulst (num, trailer, base)
     const char *num;
     const char **trailer;
     int base;
{
  unsigned long high_part;
  unsigned LONGEST result;
  int i;
  unsigned char lim;

  if (base < 2 || base > 16)
    {
      errno = EINVAL;
      return 0;
    }
  lim = base - 1 + '0';

  result = high_part = 0;
  for (i = 0; is_digit_in_base (num[i], base); i += 1)
    {
      result = result*base + digit_to_int (num[i]);
      high_part = high_part*base + result >> HIGH_BYTE_POSN;
      result &= (1 << HIGH_BYTE_POSN) - 1;
      if (high_part > 0xff) 
	{
	  errno = ERANGE;
	  result = high_part = 0;
	  break;
	}
    }

  if (trailer != NULL)
    *trailer = &num[i];

  return result + (high_part << HIGH_BYTE_POSN);
}



/* Interprets the prefix of NUM that consists of digits of the given BASE
   as an integer of that BASE, with the string EXP as an exponent.
   Puts value in *semval, and returns INT, if the string is valid.  Causes
   an error if the number.   BASE, if NULL, defaults to "10", and EXP to "1".
   The EXP does not contain a leading 'e' or 'E'. */

static int
processInt (base0, num0, exp0)
     const char* num0;
     const char* base0;
     const char* exp0;
{
  LONGEST result;
  long exp;
  int base;

  char* trailer;

  if (base0 == NULL)
    base = 10;
  else
    {	
      base = strtol (base0, (char**) NULL, 10);
      if (base < 2 || base > 16)
	error ("Invalid base: %d.", base);
    }

  if (exp0 == NULL)
    exp = 0;
  else
    exp = strtol(exp0, (char**) NULL, 10);

  errno = 0;
  result = strtoulst (num0, &trailer, base);
  if (errno == ERANGE)
	error ("Integer literal out of range");
  if (isxdigit(*trailer))
    error ("Invalid digit `%c' in based literal", *trailer);

  while (exp > 0) 
    {
      if (result > (ULONG_MAX / base))
	error ("Integer literal out of range");
      result *= base;
      exp -= 1;
    }
  
  yylval.typed_val.val = result;
  yylval.typed_val.type = builtin_type_ada_int;

  return INT;
}

static int
processReal (num0)
     const char* num0;
{
  if (sizeof (DOUBLEST) <= sizeof (float))
    {
      sscanf (num0, "%g", &yylval.typed_val_float.dval);
      yylval.typed_val_float.type = builtin_type_ada_float;
    }
  else if (sizeof (DOUBLEST) <= sizeof (double))
    {
      sscanf (num0, "%lg", &yylval.typed_val_float.dval);
      yylval.typed_val_float.type = builtin_type_ada_double;
    }
  else
    {
#ifdef PRINTF_HAS_LONG_DOUBLE
      sscanf (num0, "%Lg", &yylval.typed_val_float.dval);
#else
      /* Scan it into a double, then convert and assign it to the 
	 long double.  This at least wins with values representable 
	 in the range of doubles. */
      double temp;
      sscanf (num0, "%lg", &temp);
      yylval.typed_val_float.dval = temp;
#endif
      yylval.typed_val_float.type = builtin_type_ada_long_double;
    }
  return FLOAT;
}

static int
processId (name0, len)
     const char *name0;
     int len;
{
  struct symbol** syms;
  struct block** blocks;
  int nsyms;
  char* name = savestring (name0, len);
  char* lc_name = save_downcase_string (name0, len);
  int i, k;

  add_name_string_cleanup (name);

  nsyms = ada_lookup_symbol_list (name, expression_context_block,
				  VAR_NAMESPACE, &syms, &blocks);


  /* Call lookup_symtab, not lookup_partial_symtab, in case there are
     no psymtabs (coff, xcoff, or some future change to blow away the
     psymtabs once symbols are read).  */
  if ((nsyms == 1 && SYMBOL_CLASS (syms[0]) == LOC_BLOCK)
      || lookup_symtab (name) != NULL
      || lookup_symtab (lc_name) != NULL)
    {
      if (nsyms == 1)
	yylval.ssym.sym = syms[0];
      else
	yylval.ssym.sym = NULL;
      yylval.ssym.is_a_field_of_this = 0;
      yylval.ssym.stoken.ptr = name;
      yylval.ssym.stoken.length = len;
      return BLOCKNAME;
    }

  /* Check for a type definition. */

  /* Look for a symbol that doesn't denote void.  This is (I think) a */
  /* temporary kludge to get around problems in GNAT output. */
  k = -1;
  for (i = 0; i < nsyms; i += 1)
    {
      if (SYMBOL_CLASS (syms[i]) == LOC_TYPEDEF && 
	  TYPE_CODE (SYMBOL_TYPE (syms[i])) != TYPE_CODE_VOID)
	{
	  yylval.tsym.type = SYMBOL_TYPE (syms[i]);
	  yylval.tsym.stoken.ptr = name;
	  yylval.tsym.stoken.length = len;
	  return TYPENAME;
	}
      else if (SYMBOL_CLASS (syms[i]) == LOC_TYPEDEF)
	k = i;
    }
  if (k != -1)
    error ("`%s' matches only void type name(s)", name);

  yylval.tsym.type = lookup_primitive_typename (lc_name);
  if (yylval.tsym.type != NULL)
    {
      yylval.tsym.stoken.ptr = name;
      yylval.tsym.stoken.length = len;
      return TYPENAME;
    }
  
  /* Any other kind of symbol */
  yylval.ssym.sym = NULL;
  yylval.tsym.stoken.ptr = name;
  yylval.tsym.stoken.length = len;
  yylval.ssym.is_a_field_of_this = 0;
  return NAME;
}

int
yywrap()
{
  return 1;
}
