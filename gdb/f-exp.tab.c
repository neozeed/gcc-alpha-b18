#if defined(__STDC__) || defined(__cplusplus)
#define YYCONST const
#define YYPARAMS(x) x
#define YYDEFUN(name, arglist, args) name(args)
#define YYAND ,
#define YYPTR void *
#else
#define YYCONST
#define YYPARAMS(x) ()
#define YYDEFUN(name, arglist, args) name arglist args;
#define YYAND ;
#define YYPTR char *
#endif
#ifndef lint
YYCONST static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley +Cygnus.28) 01/20/91";
#endif
#define YYBYACC 1
#ifndef YYDONT_INCLUDE_STDIO
#include <stdio.h>
#endif
#ifdef __cplusplus
#include <stdlib.h> /* for xmalloc/xrealloc/free */
#endif
#line 44 "./f-exp.y"

#include "defs.h"
#include "gdb_string.h"
#include "expression.h"
#include "value.h"
#include "parser-defs.h"
#include "language.h"
#include "f-lang.h"
#include "bfd.h" /* Required by objfiles.h.  */
#include "symfile.h" /* Required by objfiles.h.  */
#include "objfiles.h" /* For have_full_symbols and have_partial_symbols */

/* Remap normal yacc parser interface names (yyparse, yylex, yyerror, etc),
   as well as gratuitiously global symbol names, so we can have multiple
   yacc generated parsers in gdb.  Note that these are only the variables
   produced by yacc.  If other parser generators (bison, byacc, etc) produce
   additional global names that conflict at link time, then those parser
   generators need to be fixed instead of adding those names to this list. */

#define	yymaxdepth f_maxdepth
#define	yyparse	f_parse
#define	yylex	f_lex
#define	yyerror	f_error
#define	yylval	f_lval
#define	yychar	f_char
#define	yydebug	f_debug
#define	yypact	f_pact	
#define	yyr1	f_r1			
#define	yyr2	f_r2			
#define	yydef	f_def		
#define	yychk	f_chk		
#define	yypgo	f_pgo		
#define	yyact	f_act		
#define	yyexca	f_exca
#define yyerrflag f_errflag
#define yynerrs	f_nerrs
#define	yyps	f_ps
#define	yypv	f_pv
#define	yys	f_s
#define	yy_yys	f_yys
#define	yystate	f_state
#define	yytmp	f_tmp
#define	yyv	f_v
#define	yy_yyv	f_yyv
#define	yyval	f_val
#define	yylloc	f_lloc
#define yyreds	f_reds		/* With YYDEBUG defined */
#define yytoks	f_toks		/* With YYDEBUG defined */
#define yylhs	f_yylhs
#define yylen	f_yylen
#define yydefred f_yydefred
#define yydgoto	f_yydgoto
#define yysindex f_yysindex
#define yyrindex f_yyrindex
#define yygindex f_yygindex
#define yytable	 f_yytable
#define yycheck	 f_yycheck

#ifndef YYDEBUG
#define	YYDEBUG	1		/* Default to no yydebug support */
#endif

int yyparse PARAMS ((void));

static int yylex PARAMS ((void));

void yyerror PARAMS ((char *));

static void growbuf_by_size PARAMS ((int));

static int match_string_literal PARAMS ((void));

#line 122 "./f-exp.y"
typedef union
  {
    LONGEST lval;
    struct {
      LONGEST val;
      struct type *type;
    } typed_val;
    DOUBLEST dval;
    struct symbol *sym;
    struct type *tval;
    struct stoken sval;
    struct ttype tsym;
    struct symtoken ssym;
    int voidval;
    struct block *bval;
    enum exp_opcode opcode;
    struct internalvar *ivar;

    struct type **tvec;
    int *ivec;
  } YYSTYPE;
#line 145 "./f-exp.y"
/* YYSTYPE gets defined by %union */
static int parse_number PARAMS ((char *, int, int, YYSTYPE *));
#line 123 "y.tab.c"
#define INT 257
#define FLOAT 258
#define STRING_LITERAL 259
#define BOOLEAN_LITERAL 260
#define NAME 261
#define TYPENAME 262
#define NAME_OR_INT 263
#define SIZEOF 264
#define ERROR 265
#define INT_KEYWORD 266
#define INT_S2_KEYWORD 267
#define LOGICAL_S1_KEYWORD 268
#define LOGICAL_S2_KEYWORD 269
#define LOGICAL_KEYWORD 270
#define REAL_KEYWORD 271
#define REAL_S8_KEYWORD 272
#define REAL_S16_KEYWORD 273
#define COMPLEX_S8_KEYWORD 274
#define COMPLEX_S16_KEYWORD 275
#define COMPLEX_S32_KEYWORD 276
#define BOOL_AND 277
#define BOOL_OR 278
#define BOOL_NOT 279
#define CHARACTER 280
#define VARIABLE 281
#define ASSIGN_MODIFY 282
#define ABOVE_COMMA 283
#define EQUAL 284
#define NOTEQUAL 285
#define LESSTHAN 286
#define GREATERTHAN 287
#define LEQ 288
#define GEQ 289
#define LSH 290
#define RSH 291
#define UNARY 292
#define YYERRCODE 256
static YYCONST short yylhs[] = {                                        -1,
    0,    0,    2,    1,    1,    1,    1,    1,    1,    1,
   15,    1,   14,   14,   14,   14,   16,   17,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    3,
    4,   10,   10,    9,    9,    9,    9,    9,    8,    8,
    8,    7,    7,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,   13,    6,    6,   11,
   11,   11,   12,
};
static YYCONST short yylen[] = {                                         2,
    1,    1,    1,    3,    2,    2,    2,    2,    2,    2,
    0,    5,    0,    1,    1,    3,    3,    3,    3,    4,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    1,    1,    1,    1,    1,    4,    1,    1,    1,
    1,    1,    2,    1,    2,    1,    2,    1,    3,    2,
    1,    2,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    3,    1,
    1,    1,    1,
};
static YYCONST short yydefred[] = {                                      0,
   42,   44,   49,   48,   83,   64,   43,    0,   65,   66,
   70,   69,   68,   71,   72,   73,   74,   75,   76,    0,
   67,   46,    0,    0,    0,    0,    0,    0,    0,    2,
   45,    3,    0,   51,   50,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   11,    0,    0,    0,
   61,    0,   53,    0,    0,    4,    0,   19,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   57,   55,   62,   78,    0,    0,    0,   60,    0,    0,
    0,    0,    0,   15,    0,   63,   59,    0,    0,   12,
   79,    0,    0,
};
static YYCONST short yydgoto[] = {                                      28,
   42,   30,   31,  104,   33,  105,   71,   72,   73,   34,
    0,   35,    0,  113,  100,  114,   44,
};
static YYCONST short yysindex[] = {                                   1080,
    0,    0,    0,    0,    0,    0,    0, 1044,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1105,
    0,    0, 1105, 1105, 1105, 1080, 1105,    0,  991,    0,
    0,    0,  -29,    0,    0, 1080,  -36,  -36,  -36,  -36,
  -36,  938,  -22,   -8,  -36, 1105, 1105, 1105, 1105, 1105,
 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105,
 1105, 1105, 1105, 1105, 1105, 1105,    0,  -29,  -29, 1123,
    0,  -34,    0,   -4, 1105,    0, 1105,    0,  898, 1006,
  991,  991,  951, 1029,   64,  681,  681,  -35,  -35,  -35,
  -35,  -15,  -15,  227,  145,  145,  -36,  -36,  -36, 1105,
    0,    0,    0,    0,  -41,   11, 1177,    0, 1159,  991,
  -36,  966,  -26,    0,  -47,    0,    0, 1105, 1105,    0,
    0,  991,  991,
};
static YYCONST short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   41,    0,
    0,    0,   35,    0,    0,    0,    1,   26,   55,   94,
  122,    0,    0,    0,  153,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   36,  133,    0,
    0,  134,    0,    0,    0,    0,    0,    0,   17,   47,
   16,   86,  535,   82,  199,  110,  562,  825,  871,  890,
  916,  617,  636,  590,  544,  571,  207,  414,  462,  -21,
    0,    0,    0,    0,    0,    0,    0,    0,  487,   12,
  516,  -20,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -10,   10,
};
static YYCONST short yygindex[] = {                                      0,
 1454,    0,    0,   14,    0,    0,  -16,    0,   77,    0,
    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 1573
static YYCONST short yytable[] = {                                     116,
   10,   66,  115,   67,   67,  107,   64,   62,   68,   63,
   70,   65,   69,   32,  120,   41,   38,  119,   77,   13,
   14,   66,   13,   14,   67,    8,   64,   62,   61,   63,
   17,   65,   78,   17,   52,   56,  109,   10,   10,   43,
    1,   10,   10,   10,   10,   10,   39,   10,   61,   74,
   16,  117,   18,   16,    6,  108,   41,   38,   10,   41,
   38,   10,    8,    8,   10,    0,    8,    8,    8,    8,
    8,    0,    8,   41,   38,   52,   56,   38,   52,   56,
    0,   36,    0,    8,    0,   40,    8,   39,    0,    8,
   39,    6,    6,    7,   10,    6,    6,    6,    6,    6,
   66,    6,    0,   67,   39,   64,   62,   39,   63,   29,
   65,    0,    6,    0,    0,    6,    0,    0,    6,    8,
    0,    5,   36,    0,   10,   36,   40,   61,  121,   40,
    7,    7,   54,   58,    7,    7,    7,    7,    7,   36,
    7,    0,   36,   40,  101,  102,  106,   29,    6,    8,
   29,    7,    9,   29,    7,    0,    0,    7,    5,    5,
    0,    0,    5,    5,    5,    5,    5,   29,    5,    0,
   29,    0,    0,   54,   58,   36,   54,   58,    6,    5,
    0,   66,    5,    0,   67,    5,   64,    7,    0,    9,
    9,   65,    0,    9,    9,    9,    9,    9,   35,    9,
    0,    0,    0,   29,    0,   36,   22,    0,    0,    0,
    9,    0,    0,    9,    6,    5,    9,    7,    9,   10,
   11,   12,   13,   14,   15,   16,   17,   18,   19,    0,
    0,    0,   21,   29,    0,    0,   35,    0,    0,   35,
    0,    0,   35,   22,   22,    5,    9,   22,   22,   22,
   22,   22,    0,   22,   59,   60,   35,    0,    0,   35,
    0,    0,    0,   66,   22,    0,   67,   22,   64,   62,
   22,   63,    0,   65,    0,    0,    9,   10,   10,    0,
    0,    0,   10,    0,   10,   10,   10,   10,   10,   10,
   10,   10,   35,   38,   38,    0,    0,    0,   38,    0,
   22,    0,    8,    8,    0,    0,    0,    8,    0,    8,
    8,    8,    8,    8,    8,    8,    8,    0,    0,    0,
    0,    0,   35,    0,   39,    0,    0,    0,   39,    0,
   22,    6,    6,    0,    0,    0,    6,    0,    6,    6,
    6,    6,    6,    6,    6,    6,    0,   53,   54,   55,
   56,   57,   58,   59,   60,    0,    0,    0,   36,   36,
    0,    0,    0,   36,    0,    0,    0,    0,    0,    0,
    7,    7,    0,    0,    0,    7,    0,    7,    7,    7,
    7,    7,    7,    7,    7,    0,   29,   29,    0,    0,
    0,   29,    0,   29,   29,    0,    0,    0,    5,    5,
    0,    0,    0,    5,    0,    5,    5,    5,    5,    5,
    5,    5,    5,   23,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    9,
    9,    0,    0,    0,    9,    0,    9,    9,    9,    9,
    9,    9,    9,    9,    0,    0,    0,    0,    0,    0,
   23,   23,    0,    0,   23,   23,   23,   23,   23,    0,
   23,   24,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   23,    0,    0,   23,   35,   35,   23,    0,    0,
   35,    0,    0,   22,   22,    0,   47,    0,   22,    0,
   22,   22,   22,   22,   22,   22,   22,   22,   24,   24,
    0,    0,   24,   24,   24,   24,   24,   23,   24,    0,
    0,    0,    0,    0,    0,   20,    0,    0,    0,   24,
    0,    0,   24,   47,   47,   24,    0,   47,   47,   47,
   47,   47,    0,   47,   37,    0,    0,   23,    0,    0,
    0,    0,    0,   25,   47,    0,    0,   47,    0,    0,
   47,    0,   20,   20,    0,   24,   20,   20,   20,   20,
   20,   30,   20,    0,    0,    0,    0,    0,    0,    0,
   26,    0,    0,   20,    0,   37,   20,    0,   37,   20,
   47,   25,    0,    0,   25,   24,   25,   25,   25,   21,
    0,    0,   37,    0,    0,   37,    0,    0,    0,   30,
    0,   25,   30,    0,   25,   30,    0,   25,   26,   20,
   47,   26,    0,   26,   26,   26,   27,    0,    0,   30,
    0,    0,   30,    0,    0,    0,    0,   21,   26,    0,
   21,   26,    0,   21,   26,   28,    0,   25,    0,   20,
    0,    0,    0,    0,    0,    0,    0,   21,    0,    0,
   21,    0,    0,   21,   27,   30,    0,   27,   37,    0,
   27,    0,    0,    0,   26,    0,    0,   25,    0,    0,
    0,    0,    0,   28,   27,    0,   28,   27,    0,   28,
    0,    0,    0,   21,    0,   30,    0,    0,    0,    0,
   23,   23,    0,   28,   26,   23,   28,   23,   23,   23,
   23,   23,   23,   23,   23,    0,    0,    0,    0,    0,
   27,    0,    0,   21,    0,    0,    0,   66,    0,    0,
   67,    0,   64,   62,    0,   63,    0,   65,    0,   28,
    0,    0,    0,    0,    0,    0,    0,    0,   24,   24,
   27,    0,    0,   24,   61,   24,   24,   24,   24,   24,
   24,   24,   24,    0,    0,    0,    0,    0,    0,   28,
    0,    0,    0,   47,   47,    0,    0,    0,   47,    0,
   47,   47,   47,   47,   47,   47,   47,   47,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   20,   20,    0,    0,    0,   20,    0,   20,
   20,   20,   20,   20,   20,   20,   20,    0,    0,    0,
    0,   37,   37,    0,    0,    0,   37,    0,    0,    0,
   25,   25,    0,    0,   33,   25,    0,   25,   25,   25,
   25,   25,   25,   25,   25,    0,    0,    0,   30,   30,
    0,    0,    0,   30,    0,   30,   30,   26,   26,    0,
    0,    0,   26,    0,   26,   26,   26,   26,   26,   26,
   26,   26,   33,    0,    0,   33,   21,   21,   33,    0,
   34,   21,    0,   21,   21,   21,   21,   21,   21,   21,
   21,    0,   33,    0,    0,   33,    0,    0,    0,   31,
    0,    0,    0,   27,   27,    0,    0,    0,   27,    0,
   27,   27,   27,   27,   27,   27,   27,   27,   34,    0,
    0,   34,   28,   28,   34,   32,    0,   28,   33,   28,
   28,   28,   28,   28,   28,   28,   28,   31,   34,    0,
   31,   34,    0,   31,   66,   52,    0,   67,    0,   64,
   62,    0,   63,    0,   65,    0,    0,   31,   33,    0,
   31,    0,    0,   32,    0,    0,   32,    0,    0,   32,
    0,   61,    0,    0,   34,    0,   55,   56,   57,   58,
   59,   60,    0,   32,   66,   52,   32,   67,   76,   64,
   62,   75,   63,   31,   65,    0,    0,   66,   52,    0,
   67,   51,   64,   62,   34,   63,    0,   65,   49,    0,
    0,   61,   66,   52,    0,   67,    0,   64,   62,   32,
   63,    0,   65,   31,   61,    0,    0,    0,    0,    0,
    0,   50,    0,  118,    0,    0,   49,   66,   52,   61,
   67,   51,   64,   62,    0,   63,    0,   65,    0,   32,
    0,    0,   66,   52,   51,   67,    0,   64,   62,    0,
   63,   49,   65,    0,   61,    0,    0,    0,    0,   51,
    0,   50,    0,    0,    0,   66,   52,    0,   67,   61,
   64,   62,    0,   63,    0,   65,    0,    0,    0,    0,
    0,   23,    0,   36,   51,   25,    0,    0,   24,   50,
    0,    0,   61,    0,    0,    0,    0,    0,    0,   51,
    0,   33,   33,    0,    0,    0,   33,    0,   33,   33,
   33,   33,   33,   33,   50,    0,    0,   23,    0,   26,
    0,   25,    0,    0,   24,    0,    0,    0,    0,   50,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   23,    0,   26,    0,   25,   34,   34,   24,
    0,    0,   34,    0,   34,   34,   34,   34,   34,   34,
   68,    0,   70,  103,   69,    0,   31,   31,    0,   27,
    0,   31,    0,   31,   31,   31,   31,   31,   31,    0,
    0,   53,   54,   55,   56,   57,   58,   59,   60,    0,
    0,    0,   32,   32,    0,    0,    0,   32,   26,   32,
   32,   32,   32,   32,   32,   27,    0,    0,    0,    0,
    0,    0,    0,    0,   46,   47,    0,  103,    0,   48,
    0,   53,   54,   55,   56,   57,   58,   59,   60,    0,
   27,    0,    0,    0,   53,   54,   55,   56,   57,   58,
   59,   60,   46,   47,    0,    0,    0,   48,    0,   53,
   54,   55,   56,   57,   58,   59,   60,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   46,   47,    0,
    0,    0,   48,    0,   53,   54,   55,   56,   57,   58,
   59,   60,   46,    0,   27,    0,    0,    0,    0,   53,
   54,   55,   56,   57,   58,   59,   60,    0,    0,    0,
    1,    2,    3,    4,    5,    0,    7,    8,    0,    0,
    0,    0,   53,   54,   55,   56,   57,   58,   59,   60,
    0,    0,   20,    0,   22,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,    2,    3,    4,
    5,    6,    7,    8,    0,    9,   10,   11,   12,   13,
   14,   15,   16,   17,   18,   19,    0,    0,   20,   21,
   22,    1,    2,    3,    4,    5,    0,    7,    8,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   20,    6,   22,    0,    0,    9,   10,
   11,   12,   13,   14,   15,   16,   17,   18,   19,    0,
    0,    0,   21,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    1,    2,    3,    4,    5,
    0,    7,    8,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   20,    6,   22,
    0,    0,    9,   10,   11,   12,   13,   14,   15,   16,
   17,   18,   19,   29,    0,    0,   21,    0,    0,    0,
    0,   37,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   38,    0,    0,   39,   40,   41,    0,
   45,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   79,
   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,
   90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
    0,    0,    0,    0,    0,    0,    0,    0,  110,    0,
  111,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  112,    0,    0,    0,    0,    0,    0,
    0,    0,  111,    0,    0,    0,    0,    0,    0,    0,
    0,  122,  123,
};
static YYCONST short yycheck[] = {                                      41,
    0,   37,   44,   40,   40,   40,   42,   43,   38,   45,
   40,   47,   42,    0,   41,    0,    0,   44,   41,   41,
   41,   37,   44,   44,   40,    0,   42,   43,   64,   45,
   41,   47,   41,   44,    0,    0,   41,   37,   38,   26,
    0,   41,   42,   43,   44,   45,    0,   47,   64,   36,
   41,   41,   41,   44,    0,   72,   41,   41,   58,   44,
   44,   61,   37,   38,   64,   -1,   41,   42,   43,   44,
   45,   -1,   47,   58,   58,   41,   41,   61,   44,   44,
   -1,    0,   -1,   58,   -1,    0,   61,   41,   -1,   64,
   44,   37,   38,    0,   94,   41,   42,   43,   44,   45,
   37,   47,   -1,   40,   58,   42,   43,   61,   45,    0,
   47,   -1,   58,   -1,   -1,   61,   -1,   -1,   64,   94,
   -1,    0,   41,   -1,  124,   44,   41,   64,  115,   44,
   37,   38,    0,    0,   41,   42,   43,   44,   45,   58,
   47,   -1,   61,   58,   68,   69,   70,   38,   94,  124,
   41,   58,    0,   44,   61,   -1,   -1,   64,   37,   38,
   -1,   -1,   41,   42,   43,   44,   45,   58,   47,   -1,
   61,   -1,   -1,   41,   41,   94,   44,   44,  124,   58,
   -1,   37,   61,   -1,   40,   64,   42,   94,   -1,   37,
   38,   47,   -1,   41,   42,   43,   44,   45,    0,   47,
   -1,   -1,   -1,   94,   -1,  124,    0,   -1,   -1,   -1,
   58,   -1,   -1,   61,  262,   94,   64,  124,  266,  267,
  268,  269,  270,  271,  272,  273,  274,  275,  276,   -1,
   -1,   -1,  280,  124,   -1,   -1,   38,   -1,   -1,   41,
   -1,   -1,   44,   37,   38,  124,   94,   41,   42,   43,
   44,   45,   -1,   47,  290,  291,   58,   -1,   -1,   61,
   -1,   -1,   -1,   37,   58,   -1,   40,   61,   42,   43,
   64,   45,   -1,   47,   -1,   -1,  124,  277,  278,   -1,
   -1,   -1,  282,   -1,  284,  285,  286,  287,  288,  289,
  290,  291,   94,  277,  278,   -1,   -1,   -1,  282,   -1,
   94,   -1,  277,  278,   -1,   -1,   -1,  282,   -1,  284,
  285,  286,  287,  288,  289,  290,  291,   -1,   -1,   -1,
   -1,   -1,  124,   -1,  278,   -1,   -1,   -1,  282,   -1,
  124,  277,  278,   -1,   -1,   -1,  282,   -1,  284,  285,
  286,  287,  288,  289,  290,  291,   -1,  284,  285,  286,
  287,  288,  289,  290,  291,   -1,   -1,   -1,  277,  278,
   -1,   -1,   -1,  282,   -1,   -1,   -1,   -1,   -1,   -1,
  277,  278,   -1,   -1,   -1,  282,   -1,  284,  285,  286,
  287,  288,  289,  290,  291,   -1,  277,  278,   -1,   -1,
   -1,  282,   -1,  284,  285,   -1,   -1,   -1,  277,  278,
   -1,   -1,   -1,  282,   -1,  284,  285,  286,  287,  288,
  289,  290,  291,    0,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  277,
  278,   -1,   -1,   -1,  282,   -1,  284,  285,  286,  287,
  288,  289,  290,  291,   -1,   -1,   -1,   -1,   -1,   -1,
   37,   38,   -1,   -1,   41,   42,   43,   44,   45,   -1,
   47,    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   58,   -1,   -1,   61,  277,  278,   64,   -1,   -1,
  282,   -1,   -1,  277,  278,   -1,    0,   -1,  282,   -1,
  284,  285,  286,  287,  288,  289,  290,  291,   37,   38,
   -1,   -1,   41,   42,   43,   44,   45,   94,   47,   -1,
   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   58,
   -1,   -1,   61,   37,   38,   64,   -1,   41,   42,   43,
   44,   45,   -1,   47,    0,   -1,   -1,  124,   -1,   -1,
   -1,   -1,   -1,    0,   58,   -1,   -1,   61,   -1,   -1,
   64,   -1,   37,   38,   -1,   94,   41,   42,   43,   44,
   45,    0,   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
    0,   -1,   -1,   58,   -1,   41,   61,   -1,   44,   64,
   94,   38,   -1,   -1,   41,  124,   43,   44,   45,    0,
   -1,   -1,   58,   -1,   -1,   61,   -1,   -1,   -1,   38,
   -1,   58,   41,   -1,   61,   44,   -1,   64,   38,   94,
  124,   41,   -1,   43,   44,   45,    0,   -1,   -1,   58,
   -1,   -1,   61,   -1,   -1,   -1,   -1,   38,   58,   -1,
   41,   61,   -1,   44,   64,    0,   -1,   94,   -1,  124,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   -1,   -1,
   61,   -1,   -1,   64,   38,   94,   -1,   41,  124,   -1,
   44,   -1,   -1,   -1,   94,   -1,   -1,  124,   -1,   -1,
   -1,   -1,   -1,   38,   58,   -1,   41,   61,   -1,   44,
   -1,   -1,   -1,   94,   -1,  124,   -1,   -1,   -1,   -1,
  277,  278,   -1,   58,  124,  282,   61,  284,  285,  286,
  287,  288,  289,  290,  291,   -1,   -1,   -1,   -1,   -1,
   94,   -1,   -1,  124,   -1,   -1,   -1,   37,   -1,   -1,
   40,   -1,   42,   43,   -1,   45,   -1,   47,   -1,   94,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  277,  278,
  124,   -1,   -1,  282,   64,  284,  285,  286,  287,  288,
  289,  290,  291,   -1,   -1,   -1,   -1,   -1,   -1,  124,
   -1,   -1,   -1,  277,  278,   -1,   -1,   -1,  282,   -1,
  284,  285,  286,  287,  288,  289,  290,  291,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  277,  278,   -1,   -1,   -1,  282,   -1,  284,
  285,  286,  287,  288,  289,  290,  291,   -1,   -1,   -1,
   -1,  277,  278,   -1,   -1,   -1,  282,   -1,   -1,   -1,
  277,  278,   -1,   -1,    0,  282,   -1,  284,  285,  286,
  287,  288,  289,  290,  291,   -1,   -1,   -1,  277,  278,
   -1,   -1,   -1,  282,   -1,  284,  285,  277,  278,   -1,
   -1,   -1,  282,   -1,  284,  285,  286,  287,  288,  289,
  290,  291,   38,   -1,   -1,   41,  277,  278,   44,   -1,
    0,  282,   -1,  284,  285,  286,  287,  288,  289,  290,
  291,   -1,   58,   -1,   -1,   61,   -1,   -1,   -1,    0,
   -1,   -1,   -1,  277,  278,   -1,   -1,   -1,  282,   -1,
  284,  285,  286,  287,  288,  289,  290,  291,   38,   -1,
   -1,   41,  277,  278,   44,    0,   -1,  282,   94,  284,
  285,  286,  287,  288,  289,  290,  291,   38,   58,   -1,
   41,   61,   -1,   44,   37,   38,   -1,   40,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   58,  124,   -1,
   61,   -1,   -1,   38,   -1,   -1,   41,   -1,   -1,   44,
   -1,   64,   -1,   -1,   94,   -1,  286,  287,  288,  289,
  290,  291,   -1,   58,   37,   38,   61,   40,   41,   42,
   43,   44,   45,   94,   47,   -1,   -1,   37,   38,   -1,
   40,   94,   42,   43,  124,   45,   -1,   47,   61,   -1,
   -1,   64,   37,   38,   -1,   40,   -1,   42,   43,   94,
   45,   -1,   47,  124,   64,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   58,   -1,   -1,   61,   37,   38,   64,
   40,   94,   42,   43,   -1,   45,   -1,   47,   -1,  124,
   -1,   -1,   37,   38,   94,   40,   -1,   42,   43,   -1,
   45,   61,   47,   -1,   64,   -1,   -1,   -1,   -1,   94,
   -1,  124,   -1,   -1,   -1,   37,   38,   -1,   40,   64,
   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,
   -1,   38,   -1,   40,   94,   42,   -1,   -1,   45,  124,
   -1,   -1,   64,   -1,   -1,   -1,   -1,   -1,   -1,   94,
   -1,  277,  278,   -1,   -1,   -1,  282,   -1,  284,  285,
  286,  287,  288,  289,  124,   -1,   -1,   38,   -1,   40,
   -1,   42,   -1,   -1,   45,   -1,   -1,   -1,   -1,  124,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   38,   -1,   40,   -1,   42,  277,  278,   45,
   -1,   -1,  282,   -1,  284,  285,  286,  287,  288,  289,
   38,   -1,   40,   41,   42,   -1,  277,  278,   -1,  126,
   -1,  282,   -1,  284,  285,  286,  287,  288,  289,   -1,
   -1,  284,  285,  286,  287,  288,  289,  290,  291,   -1,
   -1,   -1,  277,  278,   -1,   -1,   -1,  282,   40,  284,
  285,  286,  287,  288,  289,  126,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  277,  278,   -1,   41,   -1,  282,
   -1,  284,  285,  286,  287,  288,  289,  290,  291,   -1,
  126,   -1,   -1,   -1,  284,  285,  286,  287,  288,  289,
  290,  291,  277,  278,   -1,   -1,   -1,  282,   -1,  284,
  285,  286,  287,  288,  289,  290,  291,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  277,  278,   -1,
   -1,   -1,  282,   -1,  284,  285,  286,  287,  288,  289,
  290,  291,  277,   -1,  126,   -1,   -1,   -1,   -1,  284,
  285,  286,  287,  288,  289,  290,  291,   -1,   -1,   -1,
  257,  258,  259,  260,  261,   -1,  263,  264,   -1,   -1,
   -1,   -1,  284,  285,  286,  287,  288,  289,  290,  291,
   -1,   -1,  279,   -1,  281,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,  263,  264,   -1,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,   -1,   -1,  279,  280,
  281,  257,  258,  259,  260,  261,   -1,  263,  264,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  279,  262,  281,   -1,   -1,  266,  267,
  268,  269,  270,  271,  272,  273,  274,  275,  276,   -1,
   -1,   -1,  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,  261,
   -1,  263,  264,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  279,  262,  281,
   -1,   -1,  266,  267,  268,  269,  270,  271,  272,  273,
  274,  275,  276,    0,   -1,   -1,  280,   -1,   -1,   -1,
   -1,    8,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   20,   -1,   -1,   23,   24,   25,   -1,
   27,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   46,
   47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
   57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   75,   -1,
   77,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  100,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  109,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  118,  119,
};
#define YYFINAL 28
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 292
#if YYDEBUG
static YYCONST char *YYCONST yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,
0,0,"':'",0,0,"'='",0,"'?'","'@'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'|'",0,"'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"INT","FLOAT","STRING_LITERAL",
"BOOLEAN_LITERAL","NAME","TYPENAME","NAME_OR_INT","SIZEOF","ERROR",
"INT_KEYWORD","INT_S2_KEYWORD","LOGICAL_S1_KEYWORD","LOGICAL_S2_KEYWORD",
"LOGICAL_KEYWORD","REAL_KEYWORD","REAL_S8_KEYWORD","REAL_S16_KEYWORD",
"COMPLEX_S8_KEYWORD","COMPLEX_S16_KEYWORD","COMPLEX_S32_KEYWORD","BOOL_AND",
"BOOL_OR","BOOL_NOT","CHARACTER","VARIABLE","ASSIGN_MODIFY","ABOVE_COMMA",
"EQUAL","NOTEQUAL","LESSTHAN","GREATERTHAN","LEQ","GEQ","LSH","RSH","UNARY",
};
static YYCONST char *YYCONST yyrule[] = {
"$accept : start",
"start : exp",
"start : type_exp",
"type_exp : type",
"exp : '(' exp ')'",
"exp : '*' exp",
"exp : '&' exp",
"exp : '-' exp",
"exp : BOOL_NOT exp",
"exp : '~' exp",
"exp : SIZEOF exp",
"$$1 :",
"exp : exp '(' $$1 arglist ')'",
"arglist :",
"arglist : exp",
"arglist : substring",
"arglist : arglist ',' exp",
"substring : exp ':' exp",
"complexnum : exp ',' exp",
"exp : '(' complexnum ')'",
"exp : '(' type ')' exp",
"exp : exp '@' exp",
"exp : exp '*' exp",
"exp : exp '/' exp",
"exp : exp '%' exp",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : exp LSH exp",
"exp : exp RSH exp",
"exp : exp EQUAL exp",
"exp : exp NOTEQUAL exp",
"exp : exp LEQ exp",
"exp : exp GEQ exp",
"exp : exp LESSTHAN exp",
"exp : exp GREATERTHAN exp",
"exp : exp '&' exp",
"exp : exp '^' exp",
"exp : exp '|' exp",
"exp : exp BOOL_AND exp",
"exp : exp BOOL_OR exp",
"exp : exp '=' exp",
"exp : exp ASSIGN_MODIFY exp",
"exp : INT",
"exp : NAME_OR_INT",
"exp : FLOAT",
"exp : variable",
"exp : VARIABLE",
"exp : SIZEOF '(' type ')'",
"exp : BOOLEAN_LITERAL",
"exp : STRING_LITERAL",
"variable : name_not_typename",
"type : ptype",
"ptype : typebase",
"ptype : typebase abs_decl",
"abs_decl : '*'",
"abs_decl : '*' abs_decl",
"abs_decl : '&'",
"abs_decl : '&' abs_decl",
"abs_decl : direct_abs_decl",
"direct_abs_decl : '(' abs_decl ')'",
"direct_abs_decl : direct_abs_decl func_mod",
"direct_abs_decl : func_mod",
"func_mod : '(' ')'",
"func_mod : '(' nonempty_typelist ')'",
"typebase : TYPENAME",
"typebase : INT_KEYWORD",
"typebase : INT_S2_KEYWORD",
"typebase : CHARACTER",
"typebase : LOGICAL_KEYWORD",
"typebase : LOGICAL_S2_KEYWORD",
"typebase : LOGICAL_S1_KEYWORD",
"typebase : REAL_KEYWORD",
"typebase : REAL_S8_KEYWORD",
"typebase : REAL_S16_KEYWORD",
"typebase : COMPLEX_S8_KEYWORD",
"typebase : COMPLEX_S16_KEYWORD",
"typebase : COMPLEX_S32_KEYWORD",
"typename : TYPENAME",
"nonempty_typelist : type",
"nonempty_typelist : nonempty_typelist ',' type",
"name : NAME",
"name : TYPENAME",
"name : NAME_OR_INT",
"name_not_typename : NAME",
};
#endif
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif
#ifdef YYSTACKSIZE
#ifndef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#endif
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
#ifndef YYMAXSTACKSIZE
#define YYMAXSTACKSIZE 10000
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
YYSTYPE yyval;
YYSTYPE yylval;
static short *yyss;
static YYSTYPE *yyvs;
static int yystacksize;
#define yyfree(x) free(x)
extern int yylex();

static YYPTR
YYDEFUN (yyxmalloc, (bytes), unsigned bytes)
{
    YYPTR ptr = (YYPTR) xmalloc (bytes);
    if (ptr != 0) return (ptr);
    yyerror ("yyparse: memory exhausted");
    return (0);
}

static YYPTR
YYDEFUN (yyxrealloc, (old, bytes), YYPTR old YYAND unsigned bytes)
{
    YYPTR ptr = (YYPTR) xrealloc (old, bytes);
    if (ptr != 0) return (ptr);
    yyerror ("yyparse: memory exhausted");
    return (0);
}

static int
#ifdef __GNUC__
inline
#endif
yygrow ()
{
    int old_stacksize = yystacksize;
    short *new_yyss;
    YYSTYPE *new_yyvs;

    if (yystacksize == YYMAXSTACKSIZE)
        return (1);
    yystacksize += (yystacksize + 1 ) / 2;
    if (yystacksize > YYMAXSTACKSIZE)
        yystacksize = YYMAXSTACKSIZE;
#if YYDEBUG
    if (yydebug)
        printf("yydebug: growing stack size from %d to %d\n",
               old_stacksize, yystacksize);
#endif
    new_yyss = (short *) yyxrealloc ((char *)yyss, yystacksize * sizeof (short));
    if (new_yyss == 0)
        return (1);
    new_yyvs = (YYSTYPE *) yyxrealloc ((char *)yyvs, yystacksize * sizeof (YYSTYPE));
    if (new_yyvs == 0)
    {
        yyfree (new_yyss);
        return (1);
    }
    yyss = new_yyss;
    yyvs = new_yyvs;
    return (0);
}
#line 625 "./f-exp.y"

/* Take care of parsing a number (anything that starts with a digit).
   Set yylval and return the token type; update lexptr.
   LEN is the number of characters in it.  */

/*** Needs some error checking for the float case ***/

static int
parse_number (p, len, parsed_float, putithere)
     register char *p;
     register int len;
     int parsed_float;
     YYSTYPE *putithere;
{
  register LONGEST n = 0;
  register LONGEST prevn = 0;
  register int i;
  register int c;
  register int base = input_radix;
  int unsigned_p = 0;
  int long_p = 0;
  ULONGEST high_bit;
  struct type *signed_type;
  struct type *unsigned_type;

  if (parsed_float)
    {
      /* It's a float since it contains a point or an exponent.  */
      /* [dD] is not understood as an exponent by atof, change it to 'e'.  */
      char *tmp, *tmp2;

      tmp = strsave (p);
      for (tmp2 = tmp; *tmp2; ++tmp2)
	if (*tmp2 == 'd' || *tmp2 == 'D')
	  *tmp2 = 'e';
      putithere->dval = atof (tmp);
      free (tmp);
      return FLOAT;
    }

  /* Handle base-switching prefixes 0x, 0t, 0d, 0 */
  if (p[0] == '0')
    switch (p[1])
      {
      case 'x':
      case 'X':
	if (len >= 3)
	  {
	    p += 2;
	    base = 16;
	    len -= 2;
	  }
	break;
	
      case 't':
      case 'T':
      case 'd':
      case 'D':
	if (len >= 3)
	  {
	    p += 2;
	    base = 10;
	    len -= 2;
	  }
	break;
	
      default:
	base = 8;
	break;
      }
  
  while (len-- > 0)
    {
      c = *p++;
      if (c >= 'A' && c <= 'Z')
	c += 'a' - 'A';
      if (c != 'l' && c != 'u')
	n *= base;
      if (c >= '0' && c <= '9')
	n += i = c - '0';
      else
	{
	  if (base > 10 && c >= 'a' && c <= 'f')
	    n += i = c - 'a' + 10;
	  else if (len == 0 && c == 'l') 
            long_p = 1;
	  else if (len == 0 && c == 'u')
	    unsigned_p = 1;
	  else
	    return ERROR;	/* Char not a digit */
	}
      if (i >= base)
	return ERROR;		/* Invalid digit in this base */
      
      /* Portably test for overflow (only works for nonzero values, so make
	 a second check for zero).  */
      if ((prevn >= n) && n != 0)
	unsigned_p=1;		/* Try something unsigned */
      /* If range checking enabled, portably test for unsigned overflow.  */
      if (RANGE_CHECK && n != 0)
	{
	  if ((unsigned_p && (unsigned)prevn >= (unsigned)n))
	    range_error("Overflow on numeric constant.");	 
	}
      prevn = n;
    }
  
  /* If the number is too big to be an int, or it's got an l suffix
     then it's a long.  Work out if this has to be a long by
     shifting right and and seeing if anything remains, and the
     target int size is different to the target long size.
     
     In the expression below, we could have tested
     (n >> TARGET_INT_BIT)
     to see if it was zero,
     but too many compilers warn about that, when ints and longs
     are the same size.  So we shift it twice, with fewer bits
     each time, for the same result.  */
  
  if ((TARGET_INT_BIT != TARGET_LONG_BIT 
       && ((n >> 2) >> (TARGET_INT_BIT-2)))   /* Avoid shift warning */
      || long_p)
    {
      high_bit = ((ULONGEST)1) << (TARGET_LONG_BIT-1);
      unsigned_type = builtin_type_unsigned_long;
      signed_type = builtin_type_long;
    }
  else 
    {
      high_bit = ((ULONGEST)1) << (TARGET_INT_BIT-1);
      unsigned_type = builtin_type_unsigned_int;
      signed_type = builtin_type_int;
    }    
  
  putithere->typed_val.val = n;
  
  /* If the high bit of the worked out type is set then this number
     has to be unsigned. */
  
  if (unsigned_p || (n & high_bit)) 
    putithere->typed_val.type = unsigned_type;
  else 
    putithere->typed_val.type = signed_type;
  
  return INT;
}

struct token
{
  char *operator;
  int token;
  enum exp_opcode opcode;
};

static const struct token dot_ops[] =
{
  { ".and.", BOOL_AND, BINOP_END },
  { ".AND.", BOOL_AND, BINOP_END },
  { ".or.", BOOL_OR, BINOP_END },
  { ".OR.", BOOL_OR, BINOP_END },
  { ".not.", BOOL_NOT, BINOP_END },
  { ".NOT.", BOOL_NOT, BINOP_END },
  { ".eq.", EQUAL, BINOP_END },
  { ".EQ.", EQUAL, BINOP_END },
  { ".eqv.", EQUAL, BINOP_END },
  { ".NEQV.", NOTEQUAL, BINOP_END },
  { ".neqv.", NOTEQUAL, BINOP_END },
  { ".EQV.", EQUAL, BINOP_END },
  { ".ne.", NOTEQUAL, BINOP_END },
  { ".NE.", NOTEQUAL, BINOP_END },
  { ".le.", LEQ, BINOP_END },
  { ".LE.", LEQ, BINOP_END },
  { ".ge.", GEQ, BINOP_END },
  { ".GE.", GEQ, BINOP_END },
  { ".gt.", GREATERTHAN, BINOP_END },
  { ".GT.", GREATERTHAN, BINOP_END },
  { ".lt.", LESSTHAN, BINOP_END },
  { ".LT.", LESSTHAN, BINOP_END },
  { NULL, 0, 0 }
};

struct f77_boolean_val 
{
  char *name;
  int value;
}; 

static const struct f77_boolean_val boolean_values[]  = 
{
  { ".true.", 1 },
  { ".TRUE.", 1 },
  { ".false.", 0 },
  { ".FALSE.", 0 },
  { NULL, 0 }
};

static const struct token f77_keywords[] = 
{
  { "complex_16", COMPLEX_S16_KEYWORD, BINOP_END },
  { "complex_32", COMPLEX_S32_KEYWORD, BINOP_END },
  { "character", CHARACTER, BINOP_END },
  { "integer_2", INT_S2_KEYWORD, BINOP_END },
  { "logical_1", LOGICAL_S1_KEYWORD, BINOP_END },
  { "logical_2", LOGICAL_S2_KEYWORD, BINOP_END },
  { "complex_8", COMPLEX_S8_KEYWORD, BINOP_END },
  { "integer", INT_KEYWORD, BINOP_END },
  { "logical", LOGICAL_KEYWORD, BINOP_END },
  { "real_16", REAL_S16_KEYWORD, BINOP_END },
  { "complex", COMPLEX_S8_KEYWORD, BINOP_END },
  { "sizeof", SIZEOF, BINOP_END },
  { "real_8", REAL_S8_KEYWORD, BINOP_END },
  { "real", REAL_KEYWORD, BINOP_END },
  { NULL, 0, 0 }
}; 

/* Implementation of a dynamically expandable buffer for processing input
   characters acquired through lexptr and building a value to return in
   yylval. Ripped off from ch-exp.y */ 

static char *tempbuf;		/* Current buffer contents */
static int tempbufsize;		/* Size of allocated buffer */
static int tempbufindex;	/* Current index into buffer */

#define GROWBY_MIN_SIZE 64	/* Minimum amount to grow buffer by */

#define CHECKBUF(size) \
  do { \
    if (tempbufindex + (size) >= tempbufsize) \
      { \
	growbuf_by_size (size); \
      } \
  } while (0);


/* Grow the static temp buffer if necessary, including allocating the first one
   on demand. */

static void
growbuf_by_size (count)
     int count;
{
  int growby;

  growby = max (count, GROWBY_MIN_SIZE);
  tempbufsize += growby;
  if (tempbuf == NULL)
    tempbuf = (char *) xmalloc (tempbufsize);
  else
    tempbuf = (char *) xrealloc (tempbuf, tempbufsize);
}

/* Blatantly ripped off from ch-exp.y. This routine recognizes F77 
   string-literals. 
   
   Recognize a string literal.  A string literal is a nonzero sequence
   of characters enclosed in matching single quotes, except that
   a single character inside single quotes is a character literal, which
   we reject as a string literal.  To embed the terminator character inside
   a string, it is simply doubled (I.E. 'this''is''one''string') */

static int
match_string_literal ()
{
  char *tokptr = lexptr;

  for (tempbufindex = 0, tokptr++; *tokptr != '\0'; tokptr++)
    {
      CHECKBUF (1);
      if (*tokptr == *lexptr)
	{
	  if (*(tokptr + 1) == *lexptr)
	    tokptr++;
	  else
	    break;
	}
      tempbuf[tempbufindex++] = *tokptr;
    }
  if (*tokptr == '\0'					/* no terminator */
      || tempbufindex == 0)				/* no string */
    return 0;
  else
    {
      tempbuf[tempbufindex] = '\0';
      yylval.sval.ptr = tempbuf;
      yylval.sval.length = tempbufindex;
      lexptr = ++tokptr;
      return STRING_LITERAL;
    }
}

/* Read one token, getting characters through lexptr.  */

static int
yylex ()
{
  int c;
  int namelen;
  unsigned int i,token;
  char *tokstart;
  
 retry:
  
  tokstart = lexptr;
  
  /* First of all, let us make sure we are not dealing with the 
     special tokens .true. and .false. which evaluate to 1 and 0.  */
  
  if (*lexptr == '.')
    { 
      for (i = 0; boolean_values[i].name != NULL; i++)
	{
	  if STREQN (tokstart, boolean_values[i].name,
		    strlen (boolean_values[i].name))
	    {
	      lexptr += strlen (boolean_values[i].name); 
	      yylval.lval = boolean_values[i].value; 
	      return BOOLEAN_LITERAL;
	    }
	}
    }
  
  /* See if it is a special .foo. operator */
  
  for (i = 0; dot_ops[i].operator != NULL; i++)
    if (STREQN (tokstart, dot_ops[i].operator, strlen (dot_ops[i].operator)))
      {
	lexptr += strlen (dot_ops[i].operator);
	yylval.opcode = dot_ops[i].opcode;
	return dot_ops[i].token;
      }
  
  switch (c = *tokstart)
    {
    case 0:
      return 0;
      
    case ' ':
    case '\t':
    case '\n':
      lexptr++;
      goto retry;
      
    case '\'':
      token = match_string_literal ();
      if (token != 0)
	return (token);
      break;
      
    case '(':
      paren_depth++;
      lexptr++;
      return c;
      
    case ')':
      if (paren_depth == 0)
	return 0;
      paren_depth--;
      lexptr++;
      return c;
      
    case ',':
      if (comma_terminates && paren_depth == 0)
	return 0;
      lexptr++;
      return c;
      
    case '.':
      /* Might be a floating point number.  */
      if (lexptr[1] < '0' || lexptr[1] > '9')
	goto symbol;		/* Nope, must be a symbol. */
      /* FALL THRU into number case.  */
      
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      {
        /* It's a number.  */
	int got_dot = 0, got_e = 0, got_d = 0, toktype;
	register char *p = tokstart;
	int hex = input_radix > 10;
	
	if (c == '0' && (p[1] == 'x' || p[1] == 'X'))
	  {
	    p += 2;
	    hex = 1;
	  }
	else if (c == '0' && (p[1]=='t' || p[1]=='T' || p[1]=='d' || p[1]=='D'))
	  {
	    p += 2;
	    hex = 0;
	  }
	
	for (;; ++p)
	  {
	    if (!hex && !got_e && (*p == 'e' || *p == 'E'))
	      got_dot = got_e = 1;
	    else if (!hex && !got_d && (*p == 'd' || *p == 'D'))
	      got_dot = got_d = 1;
	    else if (!hex && !got_dot && *p == '.')
	      got_dot = 1;
	    else if (((got_e && (p[-1] == 'e' || p[-1] == 'E'))
		     || (got_d && (p[-1] == 'd' || p[-1] == 'D')))
		     && (*p == '-' || *p == '+'))
	      /* This is the sign of the exponent, not the end of the
		 number.  */
	      continue;
	    /* We will take any letters or digits.  parse_number will
	       complain if past the radix, or if L or U are not final.  */
	    else if ((*p < '0' || *p > '9')
		     && ((*p < 'a' || *p > 'z')
			 && (*p < 'A' || *p > 'Z')))
	      break;
	  }
	toktype = parse_number (tokstart, p - tokstart, got_dot|got_e|got_d,
				&yylval);
        if (toktype == ERROR)
          {
	    char *err_copy = (char *) alloca (p - tokstart + 1);
	    
	    memcpy (err_copy, tokstart, p - tokstart);
	    err_copy[p - tokstart] = 0;
	    error ("Invalid number \"%s\".", err_copy);
	  }
	lexptr = p;
	return toktype;
      }
      
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '|':
    case '&':
    case '^':
    case '~':
    case '!':
    case '@':
    case '<':
    case '>':
    case '[':
    case ']':
    case '?':
    case ':':
    case '=':
    case '{':
    case '}':
    symbol:
      lexptr++;
      return c;
    }
  
  if (!(c == '_' || c == '$'
	|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
    /* We must have come across a bad character (e.g. ';').  */
    error ("Invalid character '%c' in expression.", c);
  
  namelen = 0;
  for (c = tokstart[namelen];
       (c == '_' || c == '$' || (c >= '0' && c <= '9') 
	|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); 
       c = tokstart[++namelen]);
  
  /* The token "if" terminates the expression and is NOT 
     removed from the input stream.  */
  
  if (namelen == 2 && tokstart[0] == 'i' && tokstart[1] == 'f')
    return 0;
  
  lexptr += namelen;
  
  /* Catch specific keywords.  */
  
  for (i = 0; f77_keywords[i].operator != NULL; i++)
    if (STREQN(tokstart, f77_keywords[i].operator,
               strlen(f77_keywords[i].operator)))
      {
	/* 	lexptr += strlen(f77_keywords[i].operator); */ 
	yylval.opcode = f77_keywords[i].opcode;
	return f77_keywords[i].token;
      }
  
  yylval.sval.ptr = tokstart;
  yylval.sval.length = namelen;
  
  if (*tokstart == '$')
    {
      write_dollar_variable (yylval.sval);
      return VARIABLE;
    }
  
  /* Use token-type TYPENAME for symbols that happen to be defined
     currently as names of types; NAME for other symbols.
     The caller is not constrained to care about the distinction.  */
  {
    char *tmp = copy_name (yylval.sval);
    struct symbol *sym;
    int is_a_field_of_this = 0;
    int hextype;
    
    sym = lookup_symbol (tmp, expression_context_block,
			 VAR_NAMESPACE,
			 current_language->la_language == language_cplus
			 ? &is_a_field_of_this : NULL,
			 NULL);
    if (sym && SYMBOL_CLASS (sym) == LOC_TYPEDEF)
      {
	yylval.tsym.type = SYMBOL_TYPE (sym);
	return TYPENAME;
      }
    if ((yylval.tsym.type = lookup_primitive_typename (tmp)) != 0)
      return TYPENAME;
    
    /* Input names that aren't symbols but ARE valid hex numbers,
       when the input radix permits them, can be names or numbers
       depending on the parse.  Note we support radixes > 16 here.  */
    if (!sym
	&& ((tokstart[0] >= 'a' && tokstart[0] < 'a' + input_radix - 10)
	    || (tokstart[0] >= 'A' && tokstart[0] < 'A' + input_radix - 10)))
      {
 	YYSTYPE newlval;	/* Its value is ignored.  */
	hextype = parse_number (tokstart, namelen, 0, &newlval);
	if (hextype == INT)
	  {
	    yylval.ssym.sym = sym;
	    yylval.ssym.is_a_field_of_this = is_a_field_of_this;
	    return NAME_OR_INT;
	  }
      }
    
    /* Any other kind of symbol */
    yylval.ssym.sym = sym;
    yylval.ssym.is_a_field_of_this = is_a_field_of_this;
    return NAME;
  }
}

void
yyerror (msg)
     char *msg;
{
  error ("A %s in expression, near `%s'.", (msg ? msg : "error"), lexptr);
}
#line 1302 "y.tab.c"
#define YYABORT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#if YYDEBUG
#ifdef __cplusplus
extern "C" char *getenv();
#else
extern char *getenv();
#endif
#endif

int
yyparse()
{
    register int yym, yyn, yystate;
    register YYSTYPE *yyvsp;
    register short *yyssp;
    short *yysse;
#if YYDEBUG
    register YYCONST char *yys;

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == 0)
    {
        yyss = (short *) yyxmalloc (YYSTACKSIZE * sizeof (short));
        if (yyss == 0)
          goto yyabort;
        yyvs = (YYSTYPE *) yyxmalloc (YYSTACKSIZE * sizeof (YYSTYPE));
        if (yyvs == 0)
        {
            yyfree (yyss);
            goto yyabort;
        }
        yystacksize = YYSTACKSIZE;
    }
    yysse = yyss + yystacksize - 1;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;
    goto yyloop;

yypush_lex:
    yyval = yylval;
    yystate = yytable[yyn];
yypush:
    if (yyssp >= yysse)
    {
        int depth = yyssp - yyss;
        if (yygrow() != 0)
             goto yyoverflow;
        yysse = yyss + yystacksize -1;
        yyssp = depth + yyss;
        yyvsp = depth + yyvs;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    yyn = yysindex[yystate];
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, reading %d (%s)\n", yystate,
                    yychar, yys);
        }
#endif
    }
    if (yyn != 0
        && ((yyn += yychar), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
        && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: state %d, shifting to state %d\n",
                    yystate, yytable[yyn]);
#endif
        if (yyerrflag > 0)  --yyerrflag;
        yychar = (-1);
        goto yypush_lex;
    }
    yyn = yyrindex[yystate];
    if (yyn != 0
        && ((yyn += yychar), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
        && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            yyn = yysindex[*yyssp];
            if (yyn != 0
                && ((yyn += YYERRCODE), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
                && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
#endif
                goto yypush_lex;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("yydebug: state %d, reducing by rule %d (%s)\n",
                yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 3:
#line 226 "./f-exp.y"
{ write_exp_elt_opcode(OP_TYPE);
			  write_exp_elt_type(yyvsp[0].tval);
			  write_exp_elt_opcode(OP_TYPE); }
break;
case 4:
#line 232 "./f-exp.y"
{ }
break;
case 5:
#line 237 "./f-exp.y"
{ write_exp_elt_opcode (UNOP_IND); }
break;
case 6:
#line 240 "./f-exp.y"
{ write_exp_elt_opcode (UNOP_ADDR); }
break;
case 7:
#line 243 "./f-exp.y"
{ write_exp_elt_opcode (UNOP_NEG); }
break;
case 8:
#line 247 "./f-exp.y"
{ write_exp_elt_opcode (UNOP_LOGICAL_NOT); }
break;
case 9:
#line 251 "./f-exp.y"
{ write_exp_elt_opcode (UNOP_COMPLEMENT); }
break;
case 10:
#line 255 "./f-exp.y"
{ write_exp_elt_opcode (UNOP_SIZEOF); }
break;
case 11:
#line 264 "./f-exp.y"
{ start_arglist (); }
break;
case 12:
#line 266 "./f-exp.y"
{ write_exp_elt_opcode (OP_F77_UNDETERMINED_ARGLIST);
			  write_exp_elt_longcst ((LONGEST) end_arglist ());
			  write_exp_elt_opcode (OP_F77_UNDETERMINED_ARGLIST); }
break;
case 14:
#line 275 "./f-exp.y"
{ arglist_len = 1; }
break;
case 15:
#line 279 "./f-exp.y"
{ arglist_len = 2;}
break;
case 16:
#line 282 "./f-exp.y"
{ arglist_len++; }
break;
case 17:
#line 286 "./f-exp.y"
{ }
break;
case 18:
#line 291 "./f-exp.y"
{ }
break;
case 19:
#line 295 "./f-exp.y"
{ write_exp_elt_opcode(OP_COMPLEX); }
break;
case 20:
#line 299 "./f-exp.y"
{ write_exp_elt_opcode (UNOP_CAST);
			  write_exp_elt_type (yyvsp[-2].tval);
			  write_exp_elt_opcode (UNOP_CAST); }
break;
case 21:
#line 307 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_REPEAT); }
break;
case 22:
#line 311 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_MUL); }
break;
case 23:
#line 315 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_DIV); }
break;
case 24:
#line 319 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_REM); }
break;
case 25:
#line 323 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_ADD); }
break;
case 26:
#line 327 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_SUB); }
break;
case 27:
#line 331 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_LSH); }
break;
case 28:
#line 335 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_RSH); }
break;
case 29:
#line 339 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_EQUAL); }
break;
case 30:
#line 343 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_NOTEQUAL); }
break;
case 31:
#line 347 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_LEQ); }
break;
case 32:
#line 351 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_GEQ); }
break;
case 33:
#line 355 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_LESS); }
break;
case 34:
#line 359 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_GTR); }
break;
case 35:
#line 363 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_BITWISE_AND); }
break;
case 36:
#line 367 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_BITWISE_XOR); }
break;
case 37:
#line 371 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_BITWISE_IOR); }
break;
case 38:
#line 375 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_LOGICAL_AND); }
break;
case 39:
#line 380 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_LOGICAL_OR); }
break;
case 40:
#line 384 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_ASSIGN); }
break;
case 41:
#line 388 "./f-exp.y"
{ write_exp_elt_opcode (BINOP_ASSIGN_MODIFY);
			  write_exp_elt_opcode (yyvsp[-1].opcode);
			  write_exp_elt_opcode (BINOP_ASSIGN_MODIFY); }
break;
case 42:
#line 394 "./f-exp.y"
{ write_exp_elt_opcode (OP_LONG);
			  write_exp_elt_type (yyvsp[0].typed_val.type);
			  write_exp_elt_longcst ((LONGEST)(yyvsp[0].typed_val.val));
			  write_exp_elt_opcode (OP_LONG); }
break;
case 43:
#line 401 "./f-exp.y"
{ YYSTYPE val;
			  parse_number (yyvsp[0].ssym.stoken.ptr, yyvsp[0].ssym.stoken.length, 0, &val);
			  write_exp_elt_opcode (OP_LONG);
			  write_exp_elt_type (val.typed_val.type);
			  write_exp_elt_longcst ((LONGEST)val.typed_val.val);
			  write_exp_elt_opcode (OP_LONG); }
break;
case 44:
#line 410 "./f-exp.y"
{ write_exp_elt_opcode (OP_DOUBLE);
			  write_exp_elt_type (builtin_type_f_real_s8);
			  write_exp_elt_dblcst (yyvsp[0].dval);
			  write_exp_elt_opcode (OP_DOUBLE); }
break;
case 47:
#line 423 "./f-exp.y"
{ write_exp_elt_opcode (OP_LONG);
			  write_exp_elt_type (builtin_type_f_integer);
			  CHECK_TYPEDEF (yyvsp[-1].tval);
			  write_exp_elt_longcst ((LONGEST) TYPE_LENGTH (yyvsp[-1].tval));
			  write_exp_elt_opcode (OP_LONG); }
break;
case 48:
#line 431 "./f-exp.y"
{ write_exp_elt_opcode (OP_BOOL);
			  write_exp_elt_longcst ((LONGEST) yyvsp[0].lval);
			  write_exp_elt_opcode (OP_BOOL);
			}
break;
case 49:
#line 438 "./f-exp.y"
{
			  write_exp_elt_opcode (OP_STRING);
			  write_exp_string (yyvsp[0].sval);
			  write_exp_elt_opcode (OP_STRING);
			}
break;
case 50:
#line 446 "./f-exp.y"
{ struct symbol *sym = yyvsp[0].ssym.sym;

			  if (sym)
			    {
			      if (symbol_read_needs_frame (sym))
				{
				  if (innermost_block == 0 ||
				      contained_in (block_found, 
						    innermost_block))
				    innermost_block = block_found;
				}
			      write_exp_elt_opcode (OP_VAR_VALUE);
			      /* We want to use the selected frame, not
				 another more inner frame which happens to
				 be in the same block.  */
			      write_exp_elt_block (NULL);
			      write_exp_elt_sym (sym);
			      write_exp_elt_opcode (OP_VAR_VALUE);
			      break;
			    }
			  else
			    {
			      struct minimal_symbol *msymbol;
			      register char *arg = copy_name (yyvsp[0].ssym.stoken);

			      msymbol =
				lookup_minimal_symbol (arg, NULL, NULL);
			      if (msymbol != NULL)
				{
				  write_exp_msymbol (msymbol,
						     lookup_function_type (builtin_type_int),
						     builtin_type_int);
				}
			      else if (!have_full_symbols () && !have_partial_symbols ())
				error ("No symbol table is loaded.  Use the \"file\" command.");
			      else
				error ("No symbol \"%s\" in current context.",
				       copy_name (yyvsp[0].ssym.stoken));
			    }
			}
break;
case 53:
#line 494 "./f-exp.y"
{
		  /* This is where the interesting stuff happens.  */
		  int done = 0;
		  int array_size;
		  struct type *follow_type = yyvsp[-1].tval;
		  struct type *range_type;
		  
		  while (!done)
		    switch (pop_type ())
		      {
		      case tp_end:
			done = 1;
			break;
		      case tp_pointer:
			follow_type = lookup_pointer_type (follow_type);
			break;
		      case tp_reference:
			follow_type = lookup_reference_type (follow_type);
			break;
		      case tp_array:
			array_size = pop_type_int ();
			if (array_size != -1)
			  {
			    range_type =
			      create_range_type ((struct type *) NULL,
						 builtin_type_f_integer, 0,
						 array_size - 1);
			    follow_type =
			      create_array_type ((struct type *) NULL,
						 follow_type, range_type);
			  }
			else
			  follow_type = lookup_pointer_type (follow_type);
			break;
		      case tp_function:
			follow_type = lookup_function_type (follow_type);
			break;
		      }
		  yyval.tval = follow_type;
		}
break;
case 54:
#line 537 "./f-exp.y"
{ push_type (tp_pointer); yyval.voidval = 0; }
break;
case 55:
#line 539 "./f-exp.y"
{ push_type (tp_pointer); yyval.voidval = yyvsp[0].voidval; }
break;
case 56:
#line 541 "./f-exp.y"
{ push_type (tp_reference); yyval.voidval = 0; }
break;
case 57:
#line 543 "./f-exp.y"
{ push_type (tp_reference); yyval.voidval = yyvsp[0].voidval; }
break;
case 59:
#line 548 "./f-exp.y"
{ yyval.voidval = yyvsp[-1].voidval; }
break;
case 60:
#line 550 "./f-exp.y"
{ push_type (tp_function); }
break;
case 61:
#line 552 "./f-exp.y"
{ push_type (tp_function); }
break;
case 62:
#line 556 "./f-exp.y"
{ yyval.voidval = 0; }
break;
case 63:
#line 558 "./f-exp.y"
{ free ((PTR)yyvsp[-1].tvec); yyval.voidval = 0; }
break;
case 64:
#line 563 "./f-exp.y"
{ yyval.tval = yyvsp[0].tsym.type; }
break;
case 65:
#line 565 "./f-exp.y"
{ yyval.tval = builtin_type_f_integer; }
break;
case 66:
#line 567 "./f-exp.y"
{ yyval.tval = builtin_type_f_integer_s2; }
break;
case 67:
#line 569 "./f-exp.y"
{ yyval.tval = builtin_type_f_character; }
break;
case 68:
#line 571 "./f-exp.y"
{ yyval.tval = builtin_type_f_logical;}
break;
case 69:
#line 573 "./f-exp.y"
{ yyval.tval = builtin_type_f_logical_s2;}
break;
case 70:
#line 575 "./f-exp.y"
{ yyval.tval = builtin_type_f_logical_s1;}
break;
case 71:
#line 577 "./f-exp.y"
{ yyval.tval = builtin_type_f_real;}
break;
case 72:
#line 579 "./f-exp.y"
{ yyval.tval = builtin_type_f_real_s8;}
break;
case 73:
#line 581 "./f-exp.y"
{ yyval.tval = builtin_type_f_real_s16;}
break;
case 74:
#line 583 "./f-exp.y"
{ yyval.tval = builtin_type_f_complex_s8;}
break;
case 75:
#line 585 "./f-exp.y"
{ yyval.tval = builtin_type_f_complex_s16;}
break;
case 76:
#line 587 "./f-exp.y"
{ yyval.tval = builtin_type_f_complex_s32;}
break;
case 78:
#line 595 "./f-exp.y"
{ yyval.tvec = (struct type **) xmalloc (sizeof (struct type *) * 2);
		  yyval.ivec[0] = 1;	/* Number of types in vector */
		  yyval.tvec[1] = yyvsp[0].tval;
		}
break;
case 79:
#line 600 "./f-exp.y"
{ int len = sizeof (struct type *) * (++(yyvsp[-2].ivec[0]) + 1);
		  yyval.tvec = (struct type **) xrealloc ((char *) yyvsp[-2].tvec, len);
		  yyval.tvec[yyval.ivec[0]] = yyvsp[0].tval;
		}
break;
case 80:
#line 607 "./f-exp.y"
{ yyval.sval = yyvsp[0].ssym.stoken; }
break;
case 81:
#line 609 "./f-exp.y"
{ yyval.sval = yyvsp[0].tsym.stoken; }
break;
case 82:
#line 611 "./f-exp.y"
{ yyval.sval = yyvsp[0].ssym.stoken; }
break;
#line 1884 "y.tab.c"
    }
    yyssp -= yym;
    yyvsp -= yym;
    yym = yylhs[yyn];
    yystate = *yyssp;
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    yyn = yygindex[yym];
	 if (yyn != 0
        && ((yyn += yystate), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
        && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
#endif
    goto yypush;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
