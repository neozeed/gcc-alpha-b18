
/*  A Bison parser, made from ./ada-exp.y
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	INT	258
#define	NULL_PTR	259
#define	FLOAT	260
#define	STRING	261
#define	NAME	262
#define	BLOCKNAME	263
#define	TYPENAME	264
#define	DOT_LITERAL_NAME	265
#define	COLONCOLON	266
#define	ERROR	267
#define	ALL	268
#define	LAST	269
#define	REGNAME	270
#define	INTERNAL_VARIABLE	271
#define	ASSIGN	272
#define	_AND_	273
#define	OR	274
#define	XOR	275
#define	THEN	276
#define	ELSE	277
#define	NOTEQUAL	278
#define	LEQ	279
#define	GEQ	280
#define	IN	281
#define	DOTDOT	282
#define	UNARY	283
#define	MOD	284
#define	REM	285
#define	STARSTAR	286
#define	ABS	287
#define	NOT	288
#define	TICK_ACCESS	289
#define	TICK_FIRST	290
#define	TICK_LAST	291
#define	TICK_LENGTH	292
#define	TICK_MAX	293
#define	TICK_MIN	294
#define	TICK_POS	295
#define	TICK_RANGE	296
#define	TICK_TAG	297
#define	TICK_VAL	298
#define	ARROW	299
#define	NEW	300

#line 38 "./ada-exp.y"


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

#line 130 "./ada-exp.y"


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


#line 155 "./ada-exp.y"
typedef union
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
  } YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		191
#define	YYFLAG		-32768
#define	YYNTBASE	64

#define YYTRANSLATE(x) ((unsigned)(x) <= 300 ? yytranslate[x] : 79)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    34,     2,    54,
    59,    36,    32,    60,    33,    53,    37,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    58,    25,
    23,    26,     2,    31,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    55,     2,    63,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    61,     2,    62,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    24,    27,    28,
    29,    30,    35,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    56,    57
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,     8,    12,    16,    20,    23,    26,
    29,    32,    36,    39,    44,    45,    51,    58,    59,    61,
    65,    69,    75,    80,    84,    88,    92,    96,   100,   104,
   108,   112,   116,   120,   124,   128,   132,   138,   144,   148,
   155,   162,   167,   171,   175,   179,   183,   188,   192,   197,
   201,   204,   208,   212,   216,   219,   227,   235,   241,   247,
   248,   252,   254,   256,   257,   259,   261,   263,   265,   267,
   269,   271,   274,   276,   280,   283,   288,   293,   296,   300,
   302,   306,   309,   313,   317,   320,   324,   326,   329,   331,
   333,   335,   337,   339,   341,   344,   347
};

static const short yyrhs[] = {    66,
     0,    65,     0,    75,     0,    67,     0,    66,    58,    67,
     0,    67,    17,    67,     0,    67,    53,    13,     0,    33,
    67,     0,    32,    67,     0,    42,    67,     0,    41,    67,
     0,    67,    53,    77,     0,    67,    10,     0,    67,    54,
    69,    59,     0,     0,     6,    54,    68,    69,    59,     0,
    67,    54,    67,    30,    67,    59,     0,     0,    67,     0,
    77,    56,    67,     0,    69,    60,    67,     0,    69,    60,
    77,    56,    67,     0,    61,    75,    62,    67,     0,    54,
    66,    59,     0,    67,    40,    67,     0,    67,    36,    67,
     0,    67,    37,    67,     0,    67,    39,    67,     0,    67,
    38,    67,     0,    67,    31,    67,     0,    67,    32,    67,
     0,    67,    34,    67,     0,    67,    33,    67,     0,    67,
    23,    67,     0,    67,    24,    67,     0,    67,    27,    67,
     0,    67,    29,    67,    30,    67,     0,    67,    29,    67,
    50,    70,     0,    67,    29,    75,     0,    67,    42,    29,
    67,    30,    67,     0,    67,    42,    29,    67,    50,    70,
     0,    67,    42,    29,    75,     0,    67,    28,    67,     0,
    67,    25,    67,     0,    67,    26,    67,     0,    67,    18,
    67,     0,    67,    18,    21,    67,     0,    67,    19,    67,
     0,    67,    19,    22,    67,     0,    67,    20,    67,     0,
    67,    43,     0,    67,    44,    70,     0,    67,    45,    70,
     0,    67,    46,    70,     0,    67,    51,     0,    72,    48,
    54,    67,    60,    67,    59,     0,    72,    47,    54,    67,
    60,    67,    59,     0,    72,    49,    54,    67,    59,     0,
    71,    52,    54,    67,    59,     0,     0,    54,     3,    59,
     0,    76,     0,    71,     0,     0,     3,     0,     5,     0,
     4,     0,    14,     0,    15,     0,    16,     0,     6,     0,
    57,    75,     0,    74,     0,    74,    53,    13,     0,    73,
    74,     0,    73,    74,    53,    13,     0,    75,    54,    67,
    59,     0,     8,    11,     0,    73,    77,    11,     0,    78,
     0,    74,    53,    77,     0,    74,    10,     0,    74,    53,
     6,     0,     9,    53,    77,     0,     9,    10,     0,     9,
    53,     6,     0,    76,     0,    75,    43,     0,     9,     0,
     7,     0,     8,     0,     9,     0,     7,     0,     8,     0,
    36,    67,     0,    34,    67,     0,    67,    55,    67,    63,
     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   234,   235,   238,   245,   246,   251,   255,   259,   263,   267,
   271,   275,   279,   285,   290,   295,   303,   308,   311,   313,
   315,   317,   321,   328,   334,   338,   342,   346,   350,   354,
   358,   362,   366,   370,   374,   378,   382,   384,   388,   392,
   395,   400,   407,   411,   415,   419,   423,   427,   431,   435,
   439,   441,   443,   445,   447,   449,   451,   453,   455,   459,
   461,   465,   472,   474,   481,   488,   495,   501,   507,   513,
   519,   545,   550,   554,   561,   565,   571,   577,   596,   614,
   618,   620,   622,   624,   627,   630,   636,   637,   641,   644,
   645,   646,   649,   651,   657,   659,   661
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","INT","NULL_PTR",
"FLOAT","STRING","NAME","BLOCKNAME","TYPENAME","DOT_LITERAL_NAME","COLONCOLON",
"ERROR","ALL","LAST","REGNAME","INTERNAL_VARIABLE","ASSIGN","_AND_","OR","XOR",
"THEN","ELSE","'='","NOTEQUAL","'<'","'>'","LEQ","GEQ","IN","DOTDOT","'@'","'+'",
"'-'","'&'","UNARY","'*'","'/'","MOD","REM","STARSTAR","ABS","NOT","TICK_ACCESS",
"TICK_FIRST","TICK_LAST","TICK_LENGTH","TICK_MAX","TICK_MIN","TICK_POS","TICK_RANGE",
"TICK_TAG","TICK_VAL","'.'","'('","'['","ARROW","NEW","';'","')'","','","'{'",
"'}'","']'","start","type_exp","exp1","exp","@1","arglist","tick_arglist","type_prefix",
"opt_type_prefix","block","variable","type","typename","name","name_not_typename", NULL
};
#endif

static const short yyr1[] = {     0,
    64,    64,    65,    66,    66,    67,    67,    67,    67,    67,
    67,    67,    67,    67,    68,    67,    67,    69,    69,    69,
    69,    69,    67,    67,    67,    67,    67,    67,    67,    67,
    67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
    67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
    67,    67,    67,    67,    67,    67,    67,    67,    67,    70,
    70,    71,    72,    72,    67,    67,    67,    67,    67,    67,
    67,    67,    67,    67,    67,    67,    67,    73,    73,    74,
    74,    74,    74,    74,    74,    74,    75,    75,    76,    77,
    77,    77,    78,    78,    67,    67,    67
};

static const short yyr2[] = {     0,
     1,     1,     1,     1,     3,     3,     3,     2,     2,     2,
     2,     3,     2,     4,     0,     5,     6,     0,     1,     3,
     3,     5,     4,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     5,     5,     3,     6,
     6,     4,     3,     3,     3,     3,     4,     3,     4,     3,
     2,     3,     3,     3,     2,     7,     7,     5,     5,     0,
     3,     1,     1,     0,     1,     1,     1,     1,     1,     1,
     1,     2,     1,     3,     2,     4,     4,     2,     3,     1,
     3,     2,     3,     3,     2,     3,     1,     2,     1,     1,
     1,     1,     1,     1,     2,     2,     4
};

static const short yydefact[] = {    64,
    65,    67,    66,    71,    93,    94,    89,    68,    69,    70,
    64,    64,    64,    64,    64,    64,    64,     0,     0,     2,
     1,     4,    63,     0,     0,    73,     3,    87,    80,    15,
    78,    85,     0,     9,     0,     8,    96,    95,    11,    10,
     0,    89,    72,    87,     0,    64,    13,    64,    64,    64,
    64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
    64,    64,    64,    64,    64,    64,    64,     0,    51,    60,
    60,    60,    55,     0,    64,    64,     0,     0,     0,     0,
    93,    94,    92,    75,     0,    82,     0,    88,    64,    64,
    86,    90,    91,    92,    84,    24,    64,     5,     6,    64,
    46,    64,    48,    50,    34,    35,    44,    45,    36,    43,
     0,    39,    30,    31,    33,    32,    26,    27,    29,    28,
    25,    64,     0,    52,    53,    54,     7,    12,    94,    89,
    19,     0,     0,     0,    64,    64,    64,    64,     0,    79,
    83,    74,    81,     0,    19,     0,    23,    47,    49,    64,
    60,     0,    42,     0,    64,    14,    64,    64,    97,     0,
     0,     0,     0,    76,    77,    16,    37,    38,    64,    60,
    61,     0,    21,     0,    20,    59,    64,    64,    58,    40,
    41,    17,    64,     0,     0,    22,    57,    56,     0,     0,
     0
};

static const short yydefgoto[] = {   189,
    20,    21,    22,    90,   132,   124,    23,    24,    25,    26,
    35,    28,   133,    29
};

static const short yypact[] = {   292,
-32768,-32768,-32768,   -48,-32768,     1,    10,-32768,-32768,-32768,
   292,   292,   292,   292,   292,   292,   292,    51,    51,-32768,
    11,   894,    36,    28,   121,    13,   -30,    71,-32768,-32768,
-32768,-32768,   156,   276,   -30,   276,    19,    19,   276,   276,
   -40,-32768,    53,-32768,   -36,   292,-32768,   292,   204,   248,
   292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
   292,   292,   292,   292,   292,   292,   292,    73,-32768,    54,
    54,    54,-32768,    23,   145,   292,    56,    59,    63,    67,
     3,   122,    10,    15,   127,-32768,    74,-32768,   292,   145,
-32768,-32768,-32768,-32768,-32768,-32768,   292,   894,   933,   292,
   970,   292,   970,   970,    61,    61,    61,    61,    61,    61,
   777,   -30,   995,   276,   276,   276,   188,   188,   188,   188,
   188,   292,   129,-32768,-32768,-32768,-32768,-32768,     6,     5,
   855,   -38,    86,   381,   292,   292,   292,   292,   128,-32768,
-32768,-32768,-32768,   501,   894,   -26,    19,   970,   970,   292,
    54,   816,   -30,    84,   292,-32768,   336,   292,-32768,   547,
   423,   462,   593,-32768,-32768,-32768,    61,-32768,   292,    54,
-32768,   639,   894,    89,   894,-32768,   292,   292,-32768,    61,
-32768,-32768,   292,   685,   731,   894,-32768,-32768,   155,   157,
-32768
};

static const short yypgoto[] = {-32768,
-32768,   139,   -11,-32768,    78,   -61,-32768,-32768,-32768,   144,
     9,    66,   -17,-32768
};


#define	YYLAST		1050


static const short yytable[] = {    34,
    36,    37,    38,    39,    40,    30,    88,    85,    27,   125,
   126,    31,    88,   -90,    32,    95,    31,    46,    96,    32,
   156,   157,    86,    89,    86,    97,    43,    45,    47,    92,
    93,    94,   166,   157,    98,   127,    99,   101,   103,   104,
   105,   106,   107,   108,   109,   110,   111,   113,   114,   115,
   116,   117,   118,   119,   120,   121,   128,    33,   -90,    42,
   -92,   -91,    33,   131,   134,    87,   112,   139,    46,   143,
    47,    74,    75,    76,    78,    79,    80,   144,   145,   141,
    92,    93,    94,    44,    44,   147,   142,    77,   148,   168,
   149,    59,    60,    61,    62,    88,    63,    64,    65,    66,
    67,   122,    68,    69,    70,    71,    72,   123,   181,   135,
   152,    73,   136,    74,    75,    76,   137,   -62,   -62,   -62,
   138,   143,   -62,   160,   161,   162,   163,    81,    82,    83,
   153,   154,   -91,   141,    92,    93,    94,   140,   167,   174,
   164,   158,   171,   172,   183,   173,   175,     1,     2,     3,
     4,    81,   129,   130,   190,    41,   191,   180,     8,     9,
    10,    91,    92,    93,    94,   184,   185,   146,    84,     0,
     0,   186,     0,     0,     0,     0,    11,    12,    13,     0,
    14,     0,     0,     0,     0,    15,    16,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    47,    17,     0,
     0,    18,     0,   -18,   -18,    19,     1,     2,     3,     4,
     5,     6,     7,     0,     0,     0,     0,     8,     9,    10,
     0,     0,     0,     0,   100,     0,     0,    67,     0,    68,
    69,    70,    71,    72,     0,    11,    12,    13,    73,    14,
    74,    75,    76,     0,    15,    16,     0,     0,     0,     0,
     1,     2,     3,     4,     5,     6,     7,    17,     0,     0,
    18,     8,     9,    10,    19,     0,     0,     0,     0,   102,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
    12,    13,     0,    14,     0,    47,     0,     0,    15,    16,
     0,     0,     0,     0,     1,     2,     3,     4,     5,     6,
     7,    17,     0,     0,    18,     8,     9,    10,    19,     0,
     0,    63,    64,    65,    66,    67,     0,    68,    69,    70,
    71,    72,     0,    11,    12,    13,    73,    14,    74,    75,
    76,     0,    15,    16,     0,     0,     0,     0,     1,     2,
     3,     4,    81,   129,   130,    17,     0,     0,    18,     8,
     9,    10,    19,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    11,    12,    13,
     0,    14,     0,     0,     0,     0,    15,    16,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    17,
    47,     0,    18,     0,     0,     0,    19,    48,    49,    50,
    51,     0,     0,    52,    53,    54,    55,    56,    57,    58,
     0,    59,    60,    61,    62,     0,    63,    64,    65,    66,
    67,     0,    68,    69,    70,    71,    72,     0,     0,     0,
     0,    73,    47,    74,    75,    76,     0,     0,     0,    48,
    49,    50,    51,   159,     0,    52,    53,    54,    55,    56,
    57,    58,     0,    59,    60,    61,    62,     0,    63,    64,
    65,    66,    67,     0,    68,    69,    70,    71,    72,     0,
     0,    47,     0,    73,     0,    74,    75,    76,    48,    49,
    50,    51,   177,     0,    52,    53,    54,    55,    56,    57,
    58,     0,    59,    60,    61,    62,     0,    63,    64,    65,
    66,    67,     0,    68,    69,    70,    71,    72,     0,     0,
    47,     0,    73,     0,    74,    75,    76,    48,    49,    50,
    51,   178,     0,    52,    53,    54,    55,    56,    57,    58,
     0,    59,    60,    61,    62,     0,    63,    64,    65,    66,
    67,     0,    68,    69,    70,    71,    72,     0,     0,     0,
     0,    73,     0,    74,    75,    76,    47,     0,     0,   165,
     0,     0,     0,    48,    49,    50,    51,     0,     0,    52,
    53,    54,    55,    56,    57,    58,     0,    59,    60,    61,
    62,     0,    63,    64,    65,    66,    67,     0,    68,    69,
    70,    71,    72,     0,     0,     0,     0,    73,     0,    74,
    75,    76,    47,     0,     0,   176,     0,     0,     0,    48,
    49,    50,    51,     0,     0,    52,    53,    54,    55,    56,
    57,    58,     0,    59,    60,    61,    62,     0,    63,    64,
    65,    66,    67,     0,    68,    69,    70,    71,    72,     0,
     0,     0,     0,    73,     0,    74,    75,    76,    47,     0,
     0,   179,     0,     0,     0,    48,    49,    50,    51,     0,
     0,    52,    53,    54,    55,    56,    57,    58,     0,    59,
    60,    61,    62,     0,    63,    64,    65,    66,    67,     0,
    68,    69,    70,    71,    72,     0,     0,     0,     0,    73,
     0,    74,    75,    76,    47,     0,     0,   182,     0,     0,
     0,    48,    49,    50,    51,     0,     0,    52,    53,    54,
    55,    56,    57,    58,     0,    59,    60,    61,    62,     0,
    63,    64,    65,    66,    67,     0,    68,    69,    70,    71,
    72,     0,     0,     0,     0,    73,     0,    74,    75,    76,
    47,     0,     0,   187,     0,     0,     0,    48,    49,    50,
    51,     0,     0,    52,    53,    54,    55,    56,    57,    58,
     0,    59,    60,    61,    62,     0,    63,    64,    65,    66,
    67,     0,    68,    69,    70,    71,    72,     0,     0,     0,
     0,    73,     0,    74,    75,    76,    47,     0,     0,   188,
     0,     0,     0,    48,    49,    50,    51,     0,     0,    52,
    53,    54,    55,    56,    57,    58,   150,    59,    60,    61,
    62,     0,    63,    64,    65,    66,    67,     0,    68,    69,
    70,    71,    72,     0,     0,    47,   151,    73,     0,    74,
    75,    76,    48,    49,    50,    51,     0,     0,    52,    53,
    54,    55,    56,    57,    58,   169,    59,    60,    61,    62,
     0,    63,    64,    65,    66,    67,     0,    68,    69,    70,
    71,    72,     0,     0,    47,   170,    73,     0,    74,    75,
    76,    48,    49,    50,    51,     0,     0,    52,    53,    54,
    55,    56,    57,    58,   155,    59,    60,    61,    62,     0,
    63,    64,    65,    66,    67,     0,    68,    69,    70,    71,
    72,     0,     0,    47,     0,    73,     0,    74,    75,    76,
    48,    49,    50,    51,     0,     0,    52,    53,    54,    55,
    56,    57,    58,     0,    59,    60,    61,    62,     0,    63,
    64,    65,    66,    67,     0,    68,    69,    70,    71,    72,
     0,     0,    47,     0,    73,     0,    74,    75,    76,-32768,
    49,    50,    51,     0,     0,    52,    53,    54,    55,    56,
    57,    58,     0,    59,    60,    61,    62,     0,    63,    64,
    65,    66,    67,     0,    68,    69,    70,    71,    72,    47,
     0,     0,     0,    73,     0,    74,    75,    76,     0,     0,
     0,     0,    52,    53,    54,    55,    56,    57,    58,     0,
    59,    60,    61,    62,    47,    63,    64,    65,    66,    67,
     0,    68,    69,    70,    71,    72,     0,     0,     0,     0,
    73,     0,    74,    75,    76,     0,    60,    61,    62,     0,
    63,    64,    65,    66,    67,     0,    68,    69,    70,    71,
    72,     0,     0,     0,     0,    73,     0,    74,    75,    76
};

static const short yycheck[] = {    11,
    12,    13,    14,    15,    16,    54,    43,    25,     0,    71,
    72,    11,    43,    11,    10,    33,    11,    58,    59,    10,
    59,    60,    10,    54,    10,    62,    18,    19,    10,     7,
     8,     9,    59,    60,    46,    13,    48,    49,    50,    51,
    52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
    62,    63,    64,    65,    66,    67,    74,    53,    56,     9,
    56,    56,    53,    75,    76,    53,    58,    53,    58,    87,
    10,    53,    54,    55,    47,    48,    49,    89,    90,     6,
     7,     8,     9,    18,    19,    97,    13,    52,   100,   151,
   102,    31,    32,    33,    34,    43,    36,    37,    38,    39,
    40,    29,    42,    43,    44,    45,    46,    54,   170,    54,
   122,    51,    54,    53,    54,    55,    54,    47,    48,    49,
    54,   139,    52,   135,   136,   137,   138,     7,     8,     9,
   122,     3,    11,     6,     7,     8,     9,    11,   150,   157,
    13,    56,    59,   155,    56,   157,   158,     3,     4,     5,
     6,     7,     8,     9,     0,    17,     0,   169,    14,    15,
    16,     6,     7,     8,     9,   177,   178,    90,    25,    -1,
    -1,   183,    -1,    -1,    -1,    -1,    32,    33,    34,    -1,
    36,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    10,    54,    -1,
    -1,    57,    -1,    59,    60,    61,     3,     4,     5,     6,
     7,     8,     9,    -1,    -1,    -1,    -1,    14,    15,    16,
    -1,    -1,    -1,    -1,    21,    -1,    -1,    40,    -1,    42,
    43,    44,    45,    46,    -1,    32,    33,    34,    51,    36,
    53,    54,    55,    -1,    41,    42,    -1,    -1,    -1,    -1,
     3,     4,     5,     6,     7,     8,     9,    54,    -1,    -1,
    57,    14,    15,    16,    61,    -1,    -1,    -1,    -1,    22,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
    33,    34,    -1,    36,    -1,    10,    -1,    -1,    41,    42,
    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
     9,    54,    -1,    -1,    57,    14,    15,    16,    61,    -1,
    -1,    36,    37,    38,    39,    40,    -1,    42,    43,    44,
    45,    46,    -1,    32,    33,    34,    51,    36,    53,    54,
    55,    -1,    41,    42,    -1,    -1,    -1,    -1,     3,     4,
     5,     6,     7,     8,     9,    54,    -1,    -1,    57,    14,
    15,    16,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
    -1,    36,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
    10,    -1,    57,    -1,    -1,    -1,    61,    17,    18,    19,
    20,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
    -1,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
    40,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
    -1,    51,    10,    53,    54,    55,    -1,    -1,    -1,    17,
    18,    19,    20,    63,    -1,    23,    24,    25,    26,    27,
    28,    29,    -1,    31,    32,    33,    34,    -1,    36,    37,
    38,    39,    40,    -1,    42,    43,    44,    45,    46,    -1,
    -1,    10,    -1,    51,    -1,    53,    54,    55,    17,    18,
    19,    20,    60,    -1,    23,    24,    25,    26,    27,    28,
    29,    -1,    31,    32,    33,    34,    -1,    36,    37,    38,
    39,    40,    -1,    42,    43,    44,    45,    46,    -1,    -1,
    10,    -1,    51,    -1,    53,    54,    55,    17,    18,    19,
    20,    60,    -1,    23,    24,    25,    26,    27,    28,    29,
    -1,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
    40,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
    -1,    51,    -1,    53,    54,    55,    10,    -1,    -1,    59,
    -1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    23,
    24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
    34,    -1,    36,    37,    38,    39,    40,    -1,    42,    43,
    44,    45,    46,    -1,    -1,    -1,    -1,    51,    -1,    53,
    54,    55,    10,    -1,    -1,    59,    -1,    -1,    -1,    17,
    18,    19,    20,    -1,    -1,    23,    24,    25,    26,    27,
    28,    29,    -1,    31,    32,    33,    34,    -1,    36,    37,
    38,    39,    40,    -1,    42,    43,    44,    45,    46,    -1,
    -1,    -1,    -1,    51,    -1,    53,    54,    55,    10,    -1,
    -1,    59,    -1,    -1,    -1,    17,    18,    19,    20,    -1,
    -1,    23,    24,    25,    26,    27,    28,    29,    -1,    31,
    32,    33,    34,    -1,    36,    37,    38,    39,    40,    -1,
    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    51,
    -1,    53,    54,    55,    10,    -1,    -1,    59,    -1,    -1,
    -1,    17,    18,    19,    20,    -1,    -1,    23,    24,    25,
    26,    27,    28,    29,    -1,    31,    32,    33,    34,    -1,
    36,    37,    38,    39,    40,    -1,    42,    43,    44,    45,
    46,    -1,    -1,    -1,    -1,    51,    -1,    53,    54,    55,
    10,    -1,    -1,    59,    -1,    -1,    -1,    17,    18,    19,
    20,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
    -1,    31,    32,    33,    34,    -1,    36,    37,    38,    39,
    40,    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,
    -1,    51,    -1,    53,    54,    55,    10,    -1,    -1,    59,
    -1,    -1,    -1,    17,    18,    19,    20,    -1,    -1,    23,
    24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
    34,    -1,    36,    37,    38,    39,    40,    -1,    42,    43,
    44,    45,    46,    -1,    -1,    10,    50,    51,    -1,    53,
    54,    55,    17,    18,    19,    20,    -1,    -1,    23,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
    -1,    36,    37,    38,    39,    40,    -1,    42,    43,    44,
    45,    46,    -1,    -1,    10,    50,    51,    -1,    53,    54,
    55,    17,    18,    19,    20,    -1,    -1,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
    36,    37,    38,    39,    40,    -1,    42,    43,    44,    45,
    46,    -1,    -1,    10,    -1,    51,    -1,    53,    54,    55,
    17,    18,    19,    20,    -1,    -1,    23,    24,    25,    26,
    27,    28,    29,    -1,    31,    32,    33,    34,    -1,    36,
    37,    38,    39,    40,    -1,    42,    43,    44,    45,    46,
    -1,    -1,    10,    -1,    51,    -1,    53,    54,    55,    17,
    18,    19,    20,    -1,    -1,    23,    24,    25,    26,    27,
    28,    29,    -1,    31,    32,    33,    34,    -1,    36,    37,
    38,    39,    40,    -1,    42,    43,    44,    45,    46,    10,
    -1,    -1,    -1,    51,    -1,    53,    54,    55,    -1,    -1,
    -1,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
    31,    32,    33,    34,    10,    36,    37,    38,    39,    40,
    -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,    -1,
    51,    -1,    53,    54,    55,    -1,    32,    33,    34,    -1,
    36,    37,    38,    39,    40,    -1,    42,    43,    44,    45,
    46,    -1,    -1,    -1,    -1,    51,    -1,    53,    54,    55
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/sww/share/lib/bison-1.25/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/usr/sww/share/lib/bison-1.25/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to xreallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to xreallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 239 "./ada-exp.y"
{ write_exp_elt_opcode (OP_TYPE);
			  write_exp_elt_type (yyvsp[0].tval);
			  write_exp_elt_opcode (OP_TYPE);;
    break;}
case 5:
#line 247 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_COMMA); ;
    break;}
case 6:
#line 252 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_ASSIGN); ;
    break;}
case 7:
#line 256 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_IND); ;
    break;}
case 8:
#line 260 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_NEG); ;
    break;}
case 9:
#line 264 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_PLUS); ;
    break;}
case 10:
#line 268 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_LOGICAL_NOT); ;
    break;}
case 11:
#line 272 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_ABS); ;
    break;}
case 12:
#line 276 "./ada-exp.y"
{ write_exp_elt_opcode (STRUCTOP_STRUCT);
			  write_exp_string (downcase_token (yyvsp[0].sval));
			  write_exp_elt_opcode (STRUCTOP_STRUCT); ;
    break;}
case 13:
#line 280 "./ada-exp.y"
{ write_exp_elt_opcode (STRUCTOP_STRUCT);
			  write_exp_string (yyvsp[0].sval);
			  write_exp_elt_opcode (STRUCTOP_STRUCT); ;
    break;}
case 14:
#line 286 "./ada-exp.y"
{ write_exp_elt_opcode (OP_FUNCALL);
			  write_exp_elt_longcst (yyvsp[-1].lval);
			  write_exp_elt_opcode (OP_FUNCALL);
		        ;
    break;}
case 15:
#line 291 "./ada-exp.y"
{ write_var (expression_context_block,
				     name_cons (NULL_NAME,
						string_to_operator (yyvsp[-1].sval), 1));
			;
    break;}
case 16:
#line 296 "./ada-exp.y"
{ 
			  write_exp_elt_opcode (OP_FUNCALL);
			  write_exp_elt_longcst (yyvsp[-1].lval);
			  write_exp_elt_opcode (OP_FUNCALL);
		        ;
    break;}
case 17:
#line 304 "./ada-exp.y"
{ write_exp_elt_opcode (TERNOP_SLICE); ;
    break;}
case 18:
#line 308 "./ada-exp.y"
{ yyval.lval = 0; ;
    break;}
case 19:
#line 312 "./ada-exp.y"
{ yyval.lval = 1; ;
    break;}
case 20:
#line 314 "./ada-exp.y"
{ yyval.lval = 1; ;
    break;}
case 21:
#line 316 "./ada-exp.y"
{ yyval.lval = yyvsp[-2].lval + 1; ;
    break;}
case 22:
#line 318 "./ada-exp.y"
{ yyval.lval = yyvsp[-4].lval + 1; ;
    break;}
case 23:
#line 323 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_MEMVAL);
			  write_exp_elt_type (yyvsp[-2].tval);
			  write_exp_elt_opcode (UNOP_MEMVAL); ;
    break;}
case 24:
#line 329 "./ada-exp.y"
{ ;
    break;}
case 25:
#line 335 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_EXP); ;
    break;}
case 26:
#line 339 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_MUL); ;
    break;}
case 27:
#line 343 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_DIV); ;
    break;}
case 28:
#line 347 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_REM); ;
    break;}
case 29:
#line 351 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_MOD); ;
    break;}
case 30:
#line 355 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_REPEAT); ;
    break;}
case 31:
#line 359 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_ADD); ;
    break;}
case 32:
#line 363 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_CONCAT); ;
    break;}
case 33:
#line 367 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_SUB); ;
    break;}
case 34:
#line 371 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_EQUAL); ;
    break;}
case 35:
#line 375 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_NOTEQUAL); ;
    break;}
case 36:
#line 379 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_LEQ); ;
    break;}
case 37:
#line 383 "./ada-exp.y"
{ write_exp_elt_opcode (TERNOP_MBR); ;
    break;}
case 38:
#line 385 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_MBR); 
			  write_exp_elt_longcst ((LONGEST) yyvsp[0].lval);
			  write_exp_elt_opcode (BINOP_MBR); ;
    break;}
case 39:
#line 389 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_MBR); 
		          write_exp_elt_type (yyvsp[0].tval);
		          write_exp_elt_opcode (UNOP_MBR); ;
    break;}
case 40:
#line 393 "./ada-exp.y"
{ write_exp_elt_opcode (TERNOP_MBR); 
		          write_exp_elt_opcode (UNOP_LOGICAL_NOT); ;
    break;}
case 41:
#line 396 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_MBR); 
			  write_exp_elt_longcst ((LONGEST) yyvsp[0].lval);
			  write_exp_elt_opcode (BINOP_MBR);
		          write_exp_elt_opcode (UNOP_LOGICAL_NOT); ;
    break;}
case 42:
#line 401 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_MBR); 
		          write_exp_elt_type (yyvsp[0].tval);
		          write_exp_elt_opcode (UNOP_MBR);
		          write_exp_elt_opcode (UNOP_LOGICAL_NOT); ;
    break;}
case 43:
#line 408 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_GEQ); ;
    break;}
case 44:
#line 412 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_LESS); ;
    break;}
case 45:
#line 416 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_GTR); ;
    break;}
case 46:
#line 420 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_BITWISE_AND); ;
    break;}
case 47:
#line 424 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_LOGICAL_AND); ;
    break;}
case 48:
#line 428 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_BITWISE_IOR); ;
    break;}
case 49:
#line 432 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_LOGICAL_OR); ;
    break;}
case 50:
#line 436 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_BITWISE_XOR); ;
    break;}
case 51:
#line 440 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_ADDR); ;
    break;}
case 52:
#line 442 "./ada-exp.y"
{ write_attribute_call1 (ATR_FIRST, yyvsp[0].lval); ;
    break;}
case 53:
#line 444 "./ada-exp.y"
{ write_attribute_call1 (ATR_LAST, yyvsp[0].lval); ;
    break;}
case 54:
#line 446 "./ada-exp.y"
{ write_attribute_call1 (ATR_LENGTH, yyvsp[0].lval); ;
    break;}
case 55:
#line 448 "./ada-exp.y"
{ write_attribute_call0 (ATR_TAG); ;
    break;}
case 56:
#line 450 "./ada-exp.y"
{ write_attribute_calln (ATR_MIN, 2); ;
    break;}
case 57:
#line 452 "./ada-exp.y"
{ write_attribute_calln (ATR_MAX, 2); ;
    break;}
case 58:
#line 454 "./ada-exp.y"
{ write_attribute_calln (ATR_POS, 1); ;
    break;}
case 59:
#line 456 "./ada-exp.y"
{ write_attribute_calln (ATR_VAL, 1); ;
    break;}
case 60:
#line 460 "./ada-exp.y"
{ yyval.lval = 1; ;
    break;}
case 61:
#line 462 "./ada-exp.y"
{ yyval.lval = yyvsp[-1].typed_val.val; ;
    break;}
case 62:
#line 467 "./ada-exp.y"
{ write_exp_elt_opcode (OP_TYPE);
			  write_exp_elt_type (yyvsp[0].tsym.type);
			  write_exp_elt_opcode (OP_TYPE); ;
    break;}
case 64:
#line 475 "./ada-exp.y"
{ write_exp_elt_opcode (OP_TYPE);
			  write_exp_elt_type (builtin_type_void);
			  write_exp_elt_opcode (OP_TYPE); ;
    break;}
case 65:
#line 482 "./ada-exp.y"
{ write_exp_elt_opcode (OP_LONG);
			  write_exp_elt_type (yyvsp[0].typed_val.type);
			  write_exp_elt_longcst ((LONGEST)(yyvsp[0].typed_val.val));
			  write_exp_elt_opcode (OP_LONG); ;
    break;}
case 66:
#line 489 "./ada-exp.y"
{ write_exp_elt_opcode (OP_DOUBLE);
			  write_exp_elt_type (yyvsp[0].typed_val_float.type);
			  write_exp_elt_dblcst (yyvsp[0].typed_val_float.dval);
			  write_exp_elt_opcode (OP_DOUBLE); ;
    break;}
case 67:
#line 496 "./ada-exp.y"
{ write_exp_elt_opcode (OP_LONG);
			  write_exp_elt_type (builtin_type_int);
			  write_exp_elt_longcst ((LONGEST)(0));
			  write_exp_elt_opcode (OP_LONG); ;
    break;}
case 68:
#line 502 "./ada-exp.y"
{ write_exp_elt_opcode (OP_LAST);
			  write_exp_elt_longcst ((LONGEST) yyvsp[0].lval);
			  write_exp_elt_opcode (OP_LAST); ;
    break;}
case 69:
#line 508 "./ada-exp.y"
{ write_exp_elt_opcode (OP_REGISTER);
			  write_exp_elt_longcst ((LONGEST) yyvsp[0].lval);
			  write_exp_elt_opcode (OP_REGISTER); ;
    break;}
case 70:
#line 514 "./ada-exp.y"
{ write_exp_elt_opcode (OP_INTERNALVAR);
			  write_exp_elt_intern (yyvsp[0].ivar);
			  write_exp_elt_opcode (OP_INTERNALVAR); ;
    break;}
case 71:
#line 520 "./ada-exp.y"
{ /* Ada strings are converted into array constants 
			     a lower bound of 1.  Thus, the array upper bound 
			     is the string length. */
			  char *sp = yyvsp[0].sval.ptr; int count;
			  if (yyvsp[0].sval.length == 0) 
			    { /* One dummy character for the type */
			      write_exp_elt_opcode (OP_LONG);
			      write_exp_elt_type (builtin_type_ada_char);
			      write_exp_elt_longcst ((LONGEST)(0));
			      write_exp_elt_opcode (OP_LONG);
			    }
			  for (count = yyvsp[0].sval.length; count > 0; count -= 1)
			    {
			      write_exp_elt_opcode (OP_LONG);
			      write_exp_elt_type (builtin_type_ada_char);
			      write_exp_elt_longcst ((LONGEST)(*sp));
			      sp += 1;
			      write_exp_elt_opcode (OP_LONG);
			    }
			  write_exp_elt_opcode (OP_ARRAY);
			  write_exp_elt_longcst ((LONGEST) 1);
			  write_exp_elt_longcst ((LONGEST) (yyvsp[0].sval.length));
			  write_exp_elt_opcode (OP_ARRAY); ;
    break;}
case 72:
#line 546 "./ada-exp.y"
{ error ("NEW not implemented."); ;
    break;}
case 73:
#line 551 "./ada-exp.y"
{ write_var (expression_context_block, yyvsp[0].name); ;
    break;}
case 74:
#line 555 "./ada-exp.y"
{ write_var (expression_context_block, yyvsp[-2].name);
			  write_exp_elt_opcode (UNOP_IND);
			;
    break;}
case 75:
#line 562 "./ada-exp.y"
{ write_var (yyvsp[-1].bval, yyvsp[0].name); ;
    break;}
case 76:
#line 566 "./ada-exp.y"
{ write_var (yyvsp[-3].bval, yyvsp[-2].name);
			  write_exp_elt_opcode (UNOP_IND);
			;
    break;}
case 77:
#line 572 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_CAST);
			  write_exp_elt_type (yyvsp[-3].tval);
			  write_exp_elt_opcode (UNOP_CAST); ;
    break;}
case 78:
#line 578 "./ada-exp.y"
{
			  if (yyvsp[-1].ssym.sym != 0)
			      yyval.bval = SYMBOL_BLOCK_VALUE (yyvsp[-1].ssym.sym);
			  else
			    {
			      struct symtab *tem =
				lookup_symtab (save_downcase_string
					       (yyvsp[-1].ssym.stoken.ptr,
						yyvsp[-1].ssym.stoken.length));
			      if (tem)
				yyval.bval = BLOCKVECTOR_BLOCK
					 (BLOCKVECTOR (tem), STATIC_BLOCK);
			      else
				error ("No file or function \"%s\".",
				       copy_name (yyvsp[-1].ssym.stoken));
			    }
			;
    break;}
case 79:
#line 597 "./ada-exp.y"
{ struct symbol** syms;
			  struct block** blocks;
			  int nsyms;
			  nsyms = ada_lookup_symbol_list (copy_name (yyvsp[-1].sval), yyvsp[-2].bval,
							  VAR_NAMESPACE, 
							  &syms,
							  &blocks);
			  if (nsyms == 0 || SYMBOL_CLASS (syms[0]) != LOC_BLOCK)
			    error ("No function \"%s\" in specified context.",
				   copy_name (yyvsp[-1].sval));
			  else if (nsyms > 1)
			    warning ("Function name \"%s\" ambiguous here",
				     copy_name (yyvsp[-1].sval));
			  yyval.bval = SYMBOL_BLOCK_VALUE (syms[0]); ;
    break;}
case 80:
#line 615 "./ada-exp.y"
{ yyval.name = name_cons (NULL_NAME, yyvsp[0].sval, 0); ;
    break;}
case 81:
#line 619 "./ada-exp.y"
{ yyval.name = name_cons (yyvsp[-2].name, yyvsp[0].sval, 0); ;
    break;}
case 82:
#line 621 "./ada-exp.y"
{ yyval.name = name_cons (yyvsp[-1].name, yyvsp[0].sval, 1); ;
    break;}
case 83:
#line 623 "./ada-exp.y"
{ yyval.name = name_cons (yyvsp[-2].name, string_to_operator (yyvsp[0].sval), 1); ;
    break;}
case 84:
#line 625 "./ada-exp.y"
{ yyval.name = name_cons (name_cons (NULL_NAME, yyvsp[-2].tsym.stoken, 0), 
					  yyvsp[0].sval, 0); ;
    break;}
case 85:
#line 628 "./ada-exp.y"
{ yyval.name = name_cons (name_cons (NULL_NAME, yyvsp[-1].tsym.stoken, 0),
					  yyvsp[0].sval, 1); ;
    break;}
case 86:
#line 631 "./ada-exp.y"
{ yyval.name = name_cons (name_cons (NULL_NAME, yyvsp[-2].tsym.stoken, 0), 
					  string_to_operator (yyvsp[0].sval), 
					  1); ;
    break;}
case 87:
#line 636 "./ada-exp.y"
{ yyval.tval = yyvsp[0].tsym.type; ;
    break;}
case 88:
#line 638 "./ada-exp.y"
{ yyval.tval = lookup_pointer_type (yyvsp[-1].tval); ;
    break;}
case 90:
#line 644 "./ada-exp.y"
{ yyval.sval = yyvsp[0].ssym.stoken; ;
    break;}
case 91:
#line 645 "./ada-exp.y"
{ yyval.sval = yyvsp[0].ssym.stoken; ;
    break;}
case 92:
#line 646 "./ada-exp.y"
{ yyval.sval = yyvsp[0].tsym.stoken; ;
    break;}
case 93:
#line 650 "./ada-exp.y"
{ yyval.sval = yyvsp[0].ssym.stoken; ;
    break;}
case 94:
#line 651 "./ada-exp.y"
{ yyval.sval = yyvsp[0].ssym.stoken; ;
    break;}
case 95:
#line 658 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_IND); ;
    break;}
case 96:
#line 660 "./ada-exp.y"
{ write_exp_elt_opcode (UNOP_ADDR); ;
    break;}
case 97:
#line 662 "./ada-exp.y"
{ write_exp_elt_opcode (BINOP_SUBSCRIPT); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/usr/sww/share/lib/bison-1.25/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) xmalloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 665 "./ada-exp.y"


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

  result.original.ptr = (char*) xmalloc (lenr + 1);
  result.lookup_form.ptr = (char*) xmalloc (lenr + 1);
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

