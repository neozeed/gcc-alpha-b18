/* C code produced by gperf version 2.5 (GNU C++ version) */
/* Command-line: gperf -p -j1 -i 1 -g -o -t -G -N is_reserved_word -k1,3,$ ../g77-new/c-parse.gperf  */
/* Command-line: gperf -p -j1 -i 1 -g -o -t -N is_reserved_word -k1,3,$ c-parse.gperf  */ 
struct resword { char *name; short token; enum rid rid; };

#define TOTAL_KEYWORDS 81
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 20
#define MIN_HASH_VALUE 11
#define MAX_HASH_VALUE 157
/* maximum key range = 147, duplicates = 0 */

#ifdef __GNUC__
inline
#endif
static unsigned int
hash (str, len)
     register char *str;
     register int unsigned len;
{
  static unsigned char asso_values[] =
    {
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158,   2, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
     158, 158, 158, 158, 158,   1, 158,  18,   1,  58,
      56,   6,  44,  64,  13,  45, 158,   4,  26,  68,
       2,  74,   1, 158,   2,  13,   1,  33,  48,   5,
       5,   3,  12, 158, 158, 158, 158, 158,
    };
  register int hval = len;

  switch (hval)
    {
      default:
      case 3:
        hval += asso_values[str[2]];
      case 2:
      case 1:
        hval += asso_values[str[0]];
        break;
    }
  return hval + asso_values[str[len - 1]];
}

static struct resword wordlist[] =
  {
       {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, 
       {"",}, {"",}, 
       {"return",  RETURN, NORID},
       {"__real__",  REALPART, NORID},
       {"__typeof__",  TYPEOF, NORID},
       {"__restrict",  TYPE_QUAL, RID_RESTRICT},
       {"extern",  SCSPEC, RID_EXTERN},
       {"break",  BREAK, NORID},
       {"@encode",  ENCODE, NORID},
       {"@private",  PRIVATE, NORID},
       {"@selector",  SELECTOR, NORID},
       {"@interface",  INTERFACE, NORID},
       {"__extension__",  EXTENSION, NORID},
       {"struct",  STRUCT, NORID},
       {"",}, 
       {"restrict",  TYPE_QUAL, RID_RESTRICT},
       {"__signed__",  TYPESPEC, RID_SIGNED},
       {"@defs",  DEFS, NORID},
       {"__asm__",  ASM_KEYWORD, NORID},
       {"",}, 
       {"else",  ELSE, NORID},
       {"",}, 
       {"__alignof__",  ALIGNOF, NORID},
       {"",}, 
       {"__attribute__",  ATTRIBUTE, NORID},
       {"",}, 
       {"__real",  REALPART, NORID},
       {"__attribute",  ATTRIBUTE, NORID},
       {"__label__",  LABEL, NORID},
       {"",}, 
       {"@protocol",  PROTOCOL, NORID},
       {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, 
       {"@class",  CLASS, NORID},
       {"",}, 
       {"in",  TYPE_QUAL, RID_IN},
       {"int",  TYPESPEC, RID_INT},
       {"for",  FOR, NORID},
       {"typeof",  TYPEOF, NORID},
       {"typedef",  SCSPEC, RID_TYPEDEF},
       {"__typeof",  TYPEOF, NORID},
       {"__imag__",  IMAGPART, NORID},
       {"",}, 
       {"__inline__",  SCSPEC, RID_INLINE},
       {"__iterator",  SCSPEC, RID_ITERATOR},
       {"__iterator__",  SCSPEC, RID_ITERATOR},
       {"__inline",  SCSPEC, RID_INLINE},
       {"while",  WHILE, NORID},
       {"__volatile__",  TYPE_QUAL, RID_VOLATILE},
       {"",}, 
       {"@end",  END, NORID},
       {"__volatile",  TYPE_QUAL, RID_VOLATILE},
       {"const",  TYPE_QUAL, RID_CONST},
       {"__const",  TYPE_QUAL, RID_CONST},
       {"bycopy",  TYPE_QUAL, RID_BYCOPY},
       {"__const__",  TYPE_QUAL, RID_CONST},
       {"@protected",  PROTECTED, NORID},
       {"__complex__",  TYPESPEC, RID_COMPLEX},
       {"__alignof",  ALIGNOF, NORID},
       {"__complex",  TYPESPEC, RID_COMPLEX},
       {"continue",  CONTINUE, NORID},
       {"sizeof",  SIZEOF, NORID},
       {"register",  SCSPEC, RID_REGISTER},
       {"switch",  SWITCH, NORID},
       {"__signed",  TYPESPEC, RID_SIGNED},
       {"out",  TYPE_QUAL, RID_OUT},
       {"",}, 
       {"case",  CASE, NORID},
       {"char",  TYPESPEC, RID_CHAR},
       {"inline",  SCSPEC, RID_INLINE},
       {"",}, 
       {"union",  UNION, NORID},
       {"",}, 
       {"@implementation",  IMPLEMENTATION, NORID},
       {"volatile",  TYPE_QUAL, RID_VOLATILE},
       {"oneway",  TYPE_QUAL, RID_ONEWAY},
       {"",}, 
       {"if",  IF, NORID},
       {"__asm",  ASM_KEYWORD, NORID},
       {"short",  TYPESPEC, RID_SHORT},
       {"",}, 
       {"static",  SCSPEC, RID_STATIC},
       {"long",  TYPESPEC, RID_LONG},
       {"auto",  SCSPEC, RID_AUTO},
       {"",}, {"",}, 
       {"@public",  PUBLIC, NORID},
       {"double",  TYPESPEC, RID_DOUBLE},
       {"",}, 
       {"id",  OBJECTNAME, RID_ID},
       {"",}, {"",}, {"",}, {"",}, 
       {"default",  DEFAULT, NORID},
       {"@compatibility_alias",  ALIAS, NORID},
       {"unsigned",  TYPESPEC, RID_UNSIGNED},
       {"enum",  ENUM, NORID},
       {"",}, {"",}, {"",}, {"",}, 
       {"__imag",  IMAGPART, NORID},
       {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, 
       {"float",  TYPESPEC, RID_FLOAT},
       {"inout",  TYPE_QUAL, RID_INOUT},
       {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, 
       {"do",  DO, NORID},
       {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, 
       {"signed",  TYPESPEC, RID_SIGNED},
       {"",}, {"",}, {"",}, 
       {"goto",  GOTO, NORID},
       {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, {"",}, 
       {"void",  TYPESPEC, RID_VOID},
       {"",}, {"",}, {"",}, 
       {"asm",  ASM_KEYWORD, NORID},
  };

#ifdef __GNUC__
inline
#endif
struct resword *
is_reserved_word (str, len)
     register char *str;
     register unsigned int len;
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register char *s = wordlist[key].name;

          if (*s == *str && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
