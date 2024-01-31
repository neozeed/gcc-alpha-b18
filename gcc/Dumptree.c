#define  DEFTREECODE(a,b,c,d) \
printf("%3d: %-20.20s %-20.20s %s %d\n", i++, #a, b, c, d);

main()
{
int i = 0;
#include <tree.def>
}
