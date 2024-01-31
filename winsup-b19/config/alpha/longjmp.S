#define v0 $0                   // return value register
#define t0 $1                   // caller saved (temporary) registers
#define t1 $2                   //
#define t2 $3                   //
#define t3 $4                   //
#define t4 $5                   //
#define t5 $6                   //
#define t6 $7                   //
#define t7 $8                   //
#define s0 $9                   // callee saved (nonvolatile) registers
#define s1 $10                  //
#define s2 $11                  //
#define s3 $12                  //
#define s4 $13                  //
#define s5 $14                  //
#define fp $15                  // frame pointer register, or s6
#define a0 $16                  // argument registers
#define a1 $17                  //
#define a2 $18                  //
#define a3 $19                  //
#define a4 $20                  //
#define a5 $21                  //
#define t8 $22                  // caller saved (temporary) registers
#define t9 $23                  //
#define t10 $24                 //
#define t11 $25                 //
#define ra $26                  // return address register
#define t12 $27                 // caller saved (temporary) registers
#define AT $28                  // assembler temporary register
#define gp $29                  // global pointer register
#define sp $30                  // stack pointer register
#define zero $31                // zero register

//
// Define standard floating point registers.
//

#define f0 $f0                  // return value register
#define f1 $f1                  // return value register
#define f2 $f2                  // callee saved (nonvolatile) registers
#define f3 $f3                  //
#define f4 $f4                  //
#define f5 $f5                  //
#define f6 $f6                  //
#define f7 $f7                  //
#define f8 $f8                  //
#define f9 $f9                  //
#define f10 $f10                // caller saved (temporary) registers
#define f11 $f11                //
#define f12 $f12                //
#define f13 $f13                //
#define f14 $f14                //
#define f15 $f15                //
#define f16 $f16                // argument registers
#define f17 $f17                //
#define f18 $f18                //
#define f19 $f19                //
#define f20 $f20                //
#define f21 $f21                //
#define f22 $f22                // caller saved (temporary) registers
#define f23 $f23                //
#define f24 $f24                //
#define f25 $f25                //
#define f26 $f26                //
#define f27 $f27                //
#define f28 $f28                //
#define f29 $f29                //
#define f30 $f30                //
#define f31 $f31                // floating zero register
#define fzero $f31              // floating zero register (alias)

/*        .align 4
        .globl longjmp
        .ent longjmp */

	.set noreorder
	.set volatile
	.set noat
.text
	.align 3
	.def	longjmp;	.val	longjmp;	.scl	2;	.type	0x20;	.endef
	.globl longjmp
	.ent longjmp
longjmp:
	.eflag 48
        .frame  sp, 0, ra,0
	.prologue 0
	ldil    t0, 1                   // force nonzero value, if
        cmoveq  a1, t0, a1              //   given return value is zero
        mov     a1, v0                  // set return value

        /* restore integer registers */
        ldq     a1, ( 0 * 8)(a0)                /* return address */
        ldq     s0, ( 1 * 8)(a0)                /* callee-saved registers */
        ldq     s1, ( 2 * 8)(a0)
        ldq     s2, ( 3 * 8)(a0)
        ldq     s3, ( 4 * 8)(a0)
        ldq     s4, ( 5 * 8)(a0)
        ldq     s5, ( 6 * 8)(a0)
        ldq     fp, ( 7 * 8)(a0)
        ldq     ra, ( 8 * 8)(a0)                /* RA after return */
        ldq     sp, ( 9 * 8)(a0)
	/* restore FP registers */
        ldt     f2, (10 * 8)(a0)                /* callee-saved registers */
        ldt     f3, (11 * 8)(a0)
        ldt     f4, (12 * 8)(a0)
        ldt     f5, (13 * 8)(a0)
        ldt     f6, (14 * 8)(a0)
        ldt     f7, (15 * 8)(a0)
        ldt     f8, (16 * 8)(a0)
        ldt     f9, (17 * 8)(a0)
	ldt     f10, (18 * 8)(a0)
        mt_fpcr f10                            /* and FP control reg */
	jmp     zero, (a1)              // jump back to setjmp site
        .end longjmp
