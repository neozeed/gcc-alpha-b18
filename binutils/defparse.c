#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 22 "./defparse.y"
typedef union {
  char *id;
  int number;
} YYSTYPE;
#line 17 "y.tab.c"
#define NAME 257
#define LIBRARY 258
#define DESCRIPTION 259
#define STACKSIZE 260
#define HEAPSIZE 261
#define CODE 262
#define DATA 263
#define SECTIONS 264
#define EXPORTS 265
#define IMPORTS 266
#define VERSION 267
#define BASE 268
#define CONSTANT 269
#define READ 270
#define WRITE 271
#define EXECUTE 272
#define SHARED 273
#define NONAME 274
#define ID 275
#define NUMBER 276
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,   10,   10,   10,   10,   10,   10,   10,   10,
   10,   10,   10,   10,   11,   11,   14,   13,   13,   15,
   15,   12,   12,   16,    6,    6,   17,   17,    7,    7,
    5,    5,    5,    5,    4,    4,    3,    3,    8,    8,
    2,    2,    9,    9,    1,    1,
};
short yylen[] = {                                         2,
    2,    1,    3,    3,    2,    2,    3,    3,    2,    2,
    2,    2,    2,    4,    2,    1,    5,    2,    1,    5,
    3,    2,    1,    2,    3,    1,    1,    0,    2,    0,
    1,    1,    1,    1,    1,    0,    1,    0,    1,    0,
    2,    0,    2,    0,    3,    0,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    2,   39,    0,    0,    6,    0,    0,   31,
   32,   33,   34,   26,    0,    0,    0,    0,   23,    0,
    0,   16,    0,    0,   19,    0,    1,    0,    3,    4,
    0,    7,    8,   27,    0,    0,   22,    0,    0,   15,
    0,    0,   18,    0,    0,   29,   25,   43,    0,    0,
   21,    0,   14,   45,   41,   37,    0,    0,   35,   17,
   20,
};
short yydgoto[] = {                                      12,
   39,   60,   67,   70,   24,   25,   42,   15,   49,   13,
   31,   28,   34,   32,   35,   29,   45,
};
short yysindex[] = {                                   -254,
 -261, -261, -259, -258, -257, -247, -247, -248, -246, -245,
 -255, -254,    0,    0, -251, -251,    0,  -16,  -16,    0,
    0,    0,    0,    0,  -13,  -13, -247, -248,    0,  -29,
 -246,    0,  -46, -245,    0,  -12,    0,  -28,    0,    0,
 -241,    0,    0,    0, -247,  -13,    0, -239,  -27,    0,
 -237, -235,    0, -234, -233,    0,    0,    0, -232, -229,
    0,    2,    0,    0,    0,    0, -228, -226,    0,    0,
    0,
};
short yyrindex[] = {                                      0,
  130,  130,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  142,  142,    0,  153,  153,    0,
    0,    0,    0,    0,   96,  113,    0,  164,    0,   20,
  175,    0,    0,  186,    0,  197,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    1,    0,    0,   39,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   58,
    0,    0,    0,    0,    0,    0,   77,    0,    0,    0,
    0,
};
short yygindex[] = {                                      0,
   30,    0,    0,    0,    5,   -5,   28,   49,    0,   40,
    0,    0,    0,   22,   21,   26,    0,
};
#define YYTABLESIZE 464
short yytable[] = {                                      51,
   24,   26,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   10,   11,   14,   52,   17,   38,   18,   19,   44,
   36,   46,   20,   21,   22,   23,   27,   41,   30,   33,
   44,   48,   55,   54,   56,   58,   59,   61,   42,   62,
   69,   63,   64,   65,   66,   40,   43,   68,   71,   57,
   16,   37,   50,   47,   53,    0,    0,   38,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   36,    0,    0,    0,
    0,    0,    0,   44,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    9,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   10,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   40,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   46,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   30,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   11,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    5,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   12,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   13,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   24,   24,   24,
   24,   24,   24,   24,   24,   24,   24,   24,    0,    0,
   28,   28,   28,   28,    0,   24,   44,   44,   44,   44,
   44,   44,   44,   44,   44,   44,   44,    0,   44,    0,
    0,    0,    0,   44,   44,   42,   42,   42,   42,   42,
   42,   42,   42,   42,   42,   42,    0,   42,    0,    0,
    0,    0,   42,   42,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   38,   38,    0,   38,    0,    0,    0,
    0,    0,   38,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,    0,    0,    0,    0,    0,    0,
    0,   36,    9,    9,    9,    9,    9,    9,    9,    9,
    9,    9,    9,    0,    0,   28,   28,   28,   28,   10,
   10,   10,   10,   10,   10,   10,   10,   10,   10,   10,
    0,    0,   28,   28,   28,   28,   40,   40,   40,   40,
   40,   40,   40,   40,   40,   40,   40,   40,   46,   46,
   46,   46,   46,   46,   46,   46,   46,   46,   46,   30,
   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
   11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
   11,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,
};
short yycheck[] = {                                      46,
    0,    7,  257,  258,  259,  260,  261,  262,  263,  264,
  265,  266,  267,  275,   61,  275,  268,  276,  276,    0,
  276,   27,  270,  271,  272,  273,  275,   44,  275,  275,
   44,   61,   61,   46,  276,  275,   64,  275,    0,  275,
  269,  276,  276,  276,  274,   16,   19,   46,  275,   45,
    2,   12,   31,   28,   34,   -1,   -1,    0,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,
   -1,   -1,   -1,   64,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,    0,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,   -1,   -1,
  270,  271,  272,  273,   -1,  275,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,   -1,  269,   -1,
   -1,   -1,   -1,  274,  275,  257,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,   -1,  269,   -1,   -1,
   -1,   -1,  274,  275,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,   -1,  269,   -1,   -1,   -1,
   -1,   -1,  275,  257,  258,  259,  260,  261,  262,  263,
  264,  265,  266,  267,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  275,  257,  258,  259,  260,  261,  262,  263,  264,
  265,  266,  267,   -1,   -1,  270,  271,  272,  273,  257,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
   -1,   -1,  270,  271,  272,  273,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  257,  258,
  259,  260,  261,  262,  263,  264,  265,  266,  267,  257,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,
  267,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  257,  258,  259,  260,  261,  262,  263,  264,
  265,  266,  267,  257,  258,  259,  260,  261,  262,  263,
  264,  265,  266,  267,
};
#define YYFINAL 12
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 276
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"','",0,"'.'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'='",0,0,"'@'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"NAME","LIBRARY",
"DESCRIPTION","STACKSIZE","HEAPSIZE","CODE","DATA","SECTIONS","EXPORTS",
"IMPORTS","VERSION","BASE","CONSTANT","READ","WRITE","EXECUTE","SHARED",
"NONAME","ID","NUMBER",
};
char *yyrule[] = {
"$accept : start",
"start : start command",
"start : command",
"command : NAME opt_name opt_base",
"command : LIBRARY opt_name opt_base",
"command : EXPORTS explist",
"command : DESCRIPTION ID",
"command : STACKSIZE NUMBER opt_number",
"command : HEAPSIZE NUMBER opt_number",
"command : CODE attr_list",
"command : DATA attr_list",
"command : SECTIONS seclist",
"command : IMPORTS implist",
"command : VERSION NUMBER",
"command : VERSION NUMBER '.' NUMBER",
"explist : explist expline",
"explist : expline",
"expline : ID opt_equal_name opt_ordinal opt_NONAME opt_CONSTANT",
"implist : implist impline",
"implist : impline",
"impline : ID '=' ID '.' ID",
"impline : ID '.' ID",
"seclist : seclist secline",
"seclist : secline",
"secline : ID attr_list",
"attr_list : attr_list opt_comma attr",
"attr_list : attr",
"opt_comma : ','",
"opt_comma :",
"opt_number : ',' NUMBER",
"opt_number :",
"attr : READ",
"attr : WRITE",
"attr : EXECUTE",
"attr : SHARED",
"opt_CONSTANT : CONSTANT",
"opt_CONSTANT :",
"opt_NONAME : NONAME",
"opt_NONAME :",
"opt_name : ID",
"opt_name :",
"opt_ordinal : '@' NUMBER",
"opt_ordinal :",
"opt_equal_name : '=' ID",
"opt_equal_name :",
"opt_base : BASE '=' NUMBER",
"opt_base :",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

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

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
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
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
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
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 3:
#line 42 "./defparse.y"
{ def_name (yyvsp[-1].id, yyvsp[0].number); }
break;
case 4:
#line 43 "./defparse.y"
{ def_library (yyvsp[-1].id, yyvsp[0].number); }
break;
case 6:
#line 45 "./defparse.y"
{ def_description (yyvsp[0].id);}
break;
case 7:
#line 46 "./defparse.y"
{ def_stacksize (yyvsp[-1].number, yyvsp[0].number);}
break;
case 8:
#line 47 "./defparse.y"
{ def_heapsize (yyvsp[-1].number, yyvsp[0].number);}
break;
case 9:
#line 48 "./defparse.y"
{ def_code (yyvsp[0].number);}
break;
case 10:
#line 49 "./defparse.y"
{ def_data (yyvsp[0].number);}
break;
case 13:
#line 52 "./defparse.y"
{ def_version (yyvsp[0].number,0);}
break;
case 14:
#line 53 "./defparse.y"
{ def_version (yyvsp[-2].number,yyvsp[0].number);}
break;
case 17:
#line 64 "./defparse.y"
{ def_exports (yyvsp[-4].id, yyvsp[-3].id, yyvsp[-2].number, yyvsp[-1].number, yyvsp[0].number);}
break;
case 20:
#line 72 "./defparse.y"
{ def_import (yyvsp[-4].id,yyvsp[-2].id,yyvsp[0].id);}
break;
case 21:
#line 73 "./defparse.y"
{ def_import (0, yyvsp[-2].id,yyvsp[0].id);}
break;
case 24:
#line 81 "./defparse.y"
{ def_section (yyvsp[-1].id,yyvsp[0].number);}
break;
case 29:
#line 93 "./defparse.y"
{ yyval.number=yyvsp[0].number;}
break;
case 30:
#line 94 "./defparse.y"
{ yyval.number=-1;}
break;
case 31:
#line 98 "./defparse.y"
{ yyval.number = 1;}
break;
case 32:
#line 99 "./defparse.y"
{ yyval.number = 2;}
break;
case 33:
#line 100 "./defparse.y"
{ yyval.number=4;}
break;
case 34:
#line 101 "./defparse.y"
{ yyval.number=8;}
break;
case 35:
#line 105 "./defparse.y"
{yyval.number=1;}
break;
case 36:
#line 106 "./defparse.y"
{yyval.number=0;}
break;
case 37:
#line 109 "./defparse.y"
{yyval.number=1;}
break;
case 38:
#line 110 "./defparse.y"
{yyval.number=0;}
break;
case 39:
#line 113 "./defparse.y"
{ yyval.id =yyvsp[0].id; }
break;
case 40:
#line 114 "./defparse.y"
{ yyval.id=""; }
break;
case 41:
#line 118 "./defparse.y"
{ yyval.number=yyvsp[0].number;}
break;
case 42:
#line 119 "./defparse.y"
{ yyval.number=-1;}
break;
case 43:
#line 123 "./defparse.y"
{ yyval.id = yyvsp[0].id; }
break;
case 44:
#line 124 "./defparse.y"
{ yyval.id =  0; }
break;
case 45:
#line 127 "./defparse.y"
{ yyval.number= yyvsp[0].number;}
break;
case 46:
#line 128 "./defparse.y"
{ yyval.number=-1;}
break;
#line 544 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
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
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
