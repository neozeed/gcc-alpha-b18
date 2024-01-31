#include <stdarg.h>
#include <stdio.h>

/* outsmart the optimizer a bit */
dummy_int(int i)
{
}

dummy_string(char *s)
{
}

dummy_float(float f)
{
}

void step(int i){};

varargs_func (char *list, ...)
{
   int i, j;
   int a[4];
   char *xxxxx="abcde";
   float f=3.1415;
   va_list args;
   char *s;

   va_start (args, list);
   s = list;
   i=0;
   while (1)
     {
       j = va_arg(args, int);
       if (j == 0) break;
       a[i++] = j;
     }
   dummy_int(a[0]);
   step(1);
   va_end(args);
   dummy_string(s);
   dummy_string(xxxxx);
   dummy_float(f);
}

main()
{
   varargs_func("pqrs", 1,2,3,4,0);
}
