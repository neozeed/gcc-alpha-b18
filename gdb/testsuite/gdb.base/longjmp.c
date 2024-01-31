#include <setjmp.h>
#include <stdio.h>

int v1, v2;

setjmp_f(jmp_buf jb)
{
   longjmp(jb, 99);
   fprintf(stderr, "shouldn't get here\n");
}

sigsetjmp_f(jmp_buf jb)
{
   siglongjmp(jb, 98);
   fprintf(stderr, "shouldn't get here\n");
}

dummy(){}

int i=0;

main()
{
    jmp_buf env;
    int val;

    if ((val = setjmp(env)) == 0) {
	setjmp_f(env);
        fprintf(stderr, "shouldn't get here, either\n");
    }
    else {
	v1 = val;
    }

    if ((val = sigsetjmp(env,1)) == 0) {
	sigsetjmp_f(env);
        fprintf(stderr, "shouldn't get here, either\n");
    }
    else {
	v2 = val;
    }

    dummy();
    exit(0);
}
