#include <varargs.h>

struct s { int x, y; };

f (va_alist)
     va_dcl
{
  struct s va_values;
  va_list va;
  int attr;
  int i;

  va_start (va);

  attr = va_arg (va, int);
  if (attr != 2)
    abort ();

  va_values = va_arg (va, struct s);
  if (va_values.x != 0xaaaa || va_values.y != 0x5555)
    abort ();

  attr = va_arg (va, int);
  if (attr != 3)
    abort ();

  va_values = va_arg (va, struct s);
  if (va_values.x != 0xffff || va_values.y != 0x1111)
    abort ();

  va_end (va);
}

main ()
{
  struct s a, b;

  a.x = 0xaaaa;
  a.y = 0x5555;
  b.x = 0xffff;
  b.y = 0x1111;

  f (2, a, 3, b);
  exit (0);
}
