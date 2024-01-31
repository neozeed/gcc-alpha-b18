#define v0 $0                   // return value register
#define ra $26                  // return address register
#define sp $30                  // stack pointer register
#define zero $31                // zero register
	
/*        .align 4
        .globl getsp
        .ent getsp */

	.set noreorder
	.set volatile
	.set noat
.text
	.align 3
	.def	getsp;	.val	getsp;	.scl	2;	.type	0x20;	.endef
	.globl getsp
	.ent getsp
getsp:
	.eflag 48
        .frame  sp, 0, ra,0
	.prologue 0
	mov	sp,v0		// return stack pointer in v0
	ret	zero,(ra)		// return
				// end of routine
	.end    getsp