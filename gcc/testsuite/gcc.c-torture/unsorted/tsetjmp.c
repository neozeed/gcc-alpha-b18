#include <setjmp.h>

jmp_buf buff;
int a=0;

sub3() {
	a=222;
	longjmp(buff,0);
}

sub2() {
	a=1;
	longjmp(buff,4321);
	a=2;
}

sub1() {
	a=3;
	sub2();
	a=4;
}

main() {
	int k;
	int l = 43;

	/* basic operational test, making sure it goes where it should */
	if ((k = setjmp(buff)) == 4321) {
		if (a!=1 || l!=43) abort();
	}
	else if (k == 0) {
		a=5;
		sub1();
		a=6;
	}
	else abort();

	/* Make sure that it can't return 0 even if longjmp() asks it to */
	a=1;
	if ((k = setjmp(buff)) == 0) {
		if (a == 222) abort();
		sub3();
	}
	else {
		if (a != 222) abort();
	}

	exit(0);
}
