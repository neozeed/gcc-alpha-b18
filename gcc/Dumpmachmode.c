#define  DEF_MACHMODE(a,b,c,d,e,f) \
printf("%3d: %-10.10s %-5.5s %-10.10s %2d %2d %s\n", i++, #a, #b, #c, d, e, #f);

main()
{
int i = 0;
#include <machmode.def>
}
