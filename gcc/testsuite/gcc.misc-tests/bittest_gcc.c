#define NATIVE 
//#define NATIVE __attribute__((__native_struct__))
#include "bittest.h"
#include <stddef.h>
#define check(s,f,v) if (s.f != v) { \
	printf(#s"."#f " was %d not " #v "\n", s.f); exit_code = 1;}
#define ckoff(a) for (i=0; i<3; i++) { \
		if (a##_offsets[i] != my_##a##_offsets[i]) {\
		    printf(#a" offset #%d did not match: nat: %d v gcc: %d\n", \
			i, a##_offsets[i], my_##a##_offsets[i]); \
			exit_code = 1; } }

extern int a_offsets[];
extern int b_offsets[];
extern int c_offsets[];

int my_a_offsets[]={offsetof(struct a_type,b),
	     offsetof(struct a_type,d),
	     offsetof(struct a_type,h),
	     sizeof(struct a_type)};

int my_b_offsets[]={offsetof(struct b_type,b),
	     offsetof(struct b_type,d),
	     offsetof(struct b_type,h),
	     sizeof(struct b_type)};

int my_c_offsets[]={offsetof(struct c_type,b),
	     offsetof(struct c_type,d),
	     offsetof(struct c_type,h),
	     sizeof(struct c_type)};

extern struct a_type a;
extern struct b_type b;
extern struct c_type c;
extern struct d_type d;

check_results()
{
    int i;
    int exit_code = 0;

    ckoff(a);
    ckoff(b);
    ckoff(c);

    check(a,a,1);
    check(a,b,2);
    check(a,c,3);
    check(a,d,4);
    check(a,e,5);
    check(a,f,6);
    check(a,g,7);
    check(a,h,8);
    check(a,i,9);
    check(a,j,10);

    check(b,a,1);
    check(b,b,2);
    check(b,c,3);
    check(b,d,4);
    check(b,e,5);
    check(b,f,6);
    check(b,g,7);
    check(b,h,8);
    check(b,i,9);
    check(b,j,10);

    check(c,a,1);
    check(c,b,2);
    check(c,c,3);
    check(c,d,4);
    check(c,e,5);
    check(c,f,6);
    check(c,g,7);
    check(c,h,8);
    check(c,i,9);
    check(c,j,10);

    check(d,a,1);
    check(d,b,2);
    check(d,c,3);
    check(d,d,4);
    check(d,e,5);
    check(d,f,6);
    check(d,g,7);

    exit(exit_code);
}
