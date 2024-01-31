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
typedef union {
  char *id;
  int number;
} YYSTYPE;
extern YYSTYPE yylval;
