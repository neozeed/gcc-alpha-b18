__inline__ 
static unsigned int
hash (str, len)
     register char *str;
     register int unsigned len;
{
  static unsigned char asso_values[] =
    {
     203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
    };
  register int hval = len;
  switch (hval)
    {
      default:
      case 7:
        hval += asso_values[str[6]];
      case 6:
      case 5:
      case 4:
        hval += asso_values[str[3]];
      case 3:
      case 2:
      case 1:
        hval += asso_values[str[0]];
        break;
    }
  return hval + asso_values[str[len - 1]];
}
__inline__ 
int is_reserved_word (str, len)
     register char *str;
     register unsigned int len;
{
  if (len <= 16  && len >= 2 )
    {
      register int key = hash (str, len);
      if (key <= 202  && key >= 0)
        {
        }
    }
  return 0;
}
 
int
init_lex ()
{
    int s = is_reserved_word ( "xor_eq" , sizeof ( "xor_eq" ) - 1); 
    return s;
}
