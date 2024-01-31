#define NATIVE   /* as nothing */
#include "bittest.h"
#include <stddef.h>
#define poffset(a,b) printf("   %s: %d\n", #b, offsetof(struct a,b));

struct a_type a;
struct b_type b;
struct c_type c;
struct d_type d;

int a_offsets[]={offsetof(struct a_type,b),
	     offsetof(struct a_type,d),
	     offsetof(struct a_type,h),
	     sizeof(struct a_type)};

int b_offsets[]={offsetof(struct b_type,b),
	     offsetof(struct b_type,d),
	     offsetof(struct b_type,h),
	     sizeof(struct b_type)};

int c_offsets[]={offsetof(struct c_type,b),
	     offsetof(struct c_type,d),
	     offsetof(struct c_type,h),
	     sizeof(struct c_type)};

main()
{

    a.a=1;
    a.b=2;
    a.c=3;
    a.d=4;
    a.e=5;
    a.f=6;
    a.g=7;
    a.h=8;
    a.i=9;
    a.j=10;

    b.a=1;
    b.b=2;
    b.c=3;
    b.d=4;
    b.e=5;
    b.f=6;
    b.g=7;
    b.h=8;
    b.i=9;
    b.j=10;

    c.a=1;
    c.b=2;
    c.c=3;
    c.d=4;
    c.e=5;
    c.f=6;
    c.g=7;
    c.h=8;
    c.i=9;
    c.j=10;

    d.a=1;
    d.b=2;
    d.c=3;
    d.d=4;
    d.e=5;
    d.f=6;
    d.g=7;

    check_results();
}
