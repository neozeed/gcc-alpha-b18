/* Assembly support functions for libgcc1.
 *
 *   Copyright (C) 1996 Free Software Foundation, Inc.
 *   Contributed by Cygnus Support
 * 
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 * 
 * In addition to the permissions in the GNU General Public License, the
 * Free Software Foundation gives you unlimited permission to link the
 * compiled version of this file with other programs, and to distribute
 * those programs without any restriction coming from the use of this
 * file.  (The General Public License restrictions do apply in other
 * respects; for example, they cover modification of the file, and
 * distribution when not linked into another program.)
 * 
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 *    As a special exception, if you link this library with files
 *    compiled with GCC to produce an executable, this does not cause
 *    the resulting executable to be covered by the GNU General Public License.
 *    This exception does not however invalidate any other reasons why
 *    the executable file might be covered by the GNU General Public License.
 */


#ifdef L_ashlsi3
	.file	"_ashlsi3.s"
	.text
	.globl	__ashlsi3
	.type	__ashlsi3,@function
__ashlsi3:
	mv2wfac r6,a0				/* preserve accumulator & guard digits */
	mvfacg	r12,a0
	mv2wtac r2,a0
	cmpui	r4,16
	and3	r2,r4,15
	exef0f || slli a0,16
	sll	a0,r2
	mv2wfac r2,a0
	mv2wtac	r6,a0
	mvtacg	r12,a0
	jmp	r13
	.size	__ashlsi3,.-__ashlsi3
#endif

#ifdef L_ashrsi3
	.file	"_ashrsi3.s"
	.text
	.globl	__ashrsi3
	.type	__ashrsi3,@function
__ashrsi3:
	mv2wfac r6,a0				/* preserve accumulator & guard digits */
	mvfacg	r12,a0
	mv2wtac r2,a0
	cmpui	r4,16
	and3	r2,r4,15
	exef0f || srai a0,16
	sra	a0,r2
	mv2wfac r2,a0
	mv2wtac	r6,a0
	mvtacg	r12,a0
	jmp	r13
	.size	__ashrsi3,.-__ashrsi3
#endif

#ifdef L_lshrsi3
	.file	"_lshrsi3.s"
	.text
	.globl	__lshrsi3
	.type	__lshrsi3,@function
__lshrsi3:
	mv2wfac r6,a0				/* preserve accumulator & guard digits */
	mvfacg	r12,a0
	mv2wtac r2,a0
	mvtacg	r0,a0				/* zero guard digits */
	cmpui	r4,16
	and3	r2,r4,15
	exef0f || srli a0,16
	srl	a0,r2
	mv2wfac r2,a0
	mv2wtac	r6,a0
	mvtacg	r12,a0
	jmp	r13
	.size	__lshrsi3,.-__lshrsi3
#endif

#ifdef L_mulsi3
	.file	"_mulsi3.s"
	.text
	.globl	__mulsi3
	.type	__mulsi3,@function
__mulsi3:
	mv2wfac r6,a0				/* preserve accumulator & guard digits */
	mvfacg	r12,a0
	mulxu	a0,r2,r5
	macu	a0,r3,r4
	slli	a0,16
	macu	a0,r3,r5
	mv2wfac r2,a0
	mv2wtac	r6,a0
	mvtacg	r12,a0
	jmp	r13
	.size	__mulsi3,.-__mulsi3
#endif


#ifdef L_udivmodhi4
	.file	"_udivmodhi4.s"
	.text
	.globl	__udivmodhi4
	.type	__udivmodhi4,@function
	.globl	__umodhi3
	.type	__umodhi3,@function
__udivmodhi4:
__umodhi3:
	mv	r4,r3 -> mv r3,r2	/* move divisor to safe register & create 32-bit value for dividend */
	ldi	r2,0			/* high part of dividend */
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	jmp	r13
	.size	__udivmodhi4,.-__udivmodhi4
	.size	__umodhi3,.-__umodhi3

	.globl	__udivhi3
	.type	__udivhi3,@function
__udivhi3:
	st	r13,@-sp
	bl	__udivmodhi4
	mv	r2,r3
	ld	r13,@sp+
	jmp	r13
	.size	__udivhi3,.-__udivhi3
#endif


#ifdef L_divmodhi4
	.file	"_divmodhi4.s"
	.text
	.globl	__divmodhi4
	.type	__divmodhi4,@function
	.globl	__modhi3
	.type	__modhi3,@function
__divmodhi4:
__modhi3:
	mv	r4,r3 -> mv r3,r2	/* move divisor to safe register & create 32-bit value for dividend */
	ldi	r2,0			/* high part of dividend */
	abs	r3 -> abs r4		/* make sure divisor & dividend are positive (F0/F1 indicate if args were negative) */
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	divs	r2,r4
	exef1t || neg r2
	exef0t || neg r3
	exef1t || neg r3
	jmp	r13
	.size	__divmodhi4,.-__divmodhi4
	.size	__modhi3,.-__modhi3

	.globl	__divhi3
	.type	__divhi3,@function
__divhi3:
	st	r13,@-sp
	bl	__divmodhi4
	mv	r2,r3
	ld	r13,@sp+
	jmp	r13
	.size	__divhi3,.-__divhi3
#endif


#ifdef L_udivmodsi4
	.file	"_udivmodsi4.s"
	.text
	.globl	__udivmodsi4
	.type	__udivmodsi4,@function
	.globl	__udivsi3
	.type	__udivsi3,@function
	/* input:	r2-r3 = dividend, r4-r5 = divisor */
	/* output:	r2-r3 = quotient, r4-r5 = remainder */
__udivmodsi4:
__udivsi3:
	cmpeqi	r2,0 ->	brf0f.s	.Llong	/* if we are doing short/short do it with divs */
	cmpeqi	r4,0 -> brf0f.s	.Llong

	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	divs	r2,r5
	mv	r5,r2
	ldi	r2,0
	jmp	r13

.Llong:
	st2w	r8,@-sp
	st2w	r10,@-sp
	mv2w	r6,r4			/* divisor (b) */
	ldi	r4,0			/* high part of dividend (ah) */
	ldi	r5,0
	ldi	r12,32			/* number of iterations */
.Lloop:
	mv2w	r8,r4			/* tmp1 = (ah << 1) | (al >> 31) */
	add2w	r8,r8
	cmpi	r2,0
	exef0t || addi r9,1

	mv2w	r10,r8			/* tmp2 = tmp1 - b */
	sub2w	r10,r6

	cmpeq	r8,r6			/* tmpf = (tmp1 >= b), ie f0 = !(tmp1 < b) */
	cmpu	r8,r6
	exef1t || cmpu r9,r7

	mv2w	r4,r8			/* ah = (tmpf) ? tmp1 : tmp2 */
	exef0f || mv2w r4,r10

	add2w	r2,r2			/* al = (al << 1) | tmpf */
	exef0f || addi r3,1

	subi	r12,1			/* decrement and loop */
	cmpeqi	r12,0
	brf0f.s	.Lloop			/* work around simulator bug with .s version of brf0f */

	ld2w	r10,@sp+
	ld2w	r8,@sp+
	jmp	r13
	.size	__udivmodsi4,.-__udivmodsi4
	.size	__udivsi3,.-__udivsi3

	.globl	__umodsi3
	.type	__umodsi3,@function
__umodsi3:
	st	r13,@-sp
	bl	__udivmodsi4
	mv2w	r2,r4
	ld	r13,@sp+
	jmp	r13
	.size	__modvsi3,.-__modvsi3
#endif


#ifdef L_divmodsi4
	.file	"_divmodsi4.s"
	.text
	.globl	__divmodsi4
	.type	__divmodsi4,@function
	.globl	__divsi3
	.type	__divsi3,@function
__divmodsi4:
__divsi3:
	cmpi	r2,0				/* divisor negative? */
	brf0t.s	.Lneg1

	cmpi	r4,0				/* dividend negative? */
	brf0t.s	.Lneg3

	bra	__udivmodsi4			/* both positive, just do division, __udivmodsi4 will return to caller */

.Lneg1:						/* divisor negative, dividend sign not yet checked */
	st	r13,@-sp
	not	r2				/* negate divisor */
	neg	r3
	cmpeqi	r3,0
	exef0t || addi r2,1

	cmpi	r4,0				/* dividend negative? */
	brf0t.s	.Lneg2

	bl	__udivmodsi4			/* do division */

	not	r2				/* negate quotient */
	neg	r3
	cmpeqi	r3,0
	exef0t || addi r2,1

	not	r4				/* negate remainder */
	neg	r5
	cmpeqi	r5,0
	exef0t || addi r4,1
	ld	r13,@sp+
	jmp	r13

.Lneg2:						/* divisor & dividend negative */
	not	r4				/* negate dividend */
	neg	r5
	cmpeqi	r5,0
	exef0t || addi r4,1

	bl	__udivmodsi4			/* do division */

	not	r4				/* negate remainder */
	neg	r5
	cmpeqi	r5,0
	exef0t || addi r4,1
	ld	r13,@sp+
	jmp	r13

.Lneg3:						/* divisor positive, dividend negative */
	st	r13,@-sp
	not	r4				/* negate dividend */
	neg	r5
	cmpeqi	r5,0
	exef0t || addi r4,1

	bl	__udivmodsi4			/* do division */	

	not	r2				/* negate quotient */
	neg	r3
	cmpeqi	r3,0
	exef0t || addi r2,1
	ld	r13,@sp+
	jmp	r13
	.size	__divmodsi4,.-__divmodsi4
	.size	__divsi3,.-__divsi3

	.globl	__modsi3
	.type	__modsi3,@function
__modsi3:
	st	r13,@-sp
	bl	__divmodsi4
	mv2w	r2,r4
	ld	r13,@sp+
	jmp	r13
	.size	__modsi3,.-__modsi3
#endif


#ifdef L_cmpdi
	.file	"__cmpdi.s"
	.text
	.globl	__cmpdi
	.type	__cmpdi,@function
	/* input:	r2 pointer to DImode op0, r3 pointer to DImode op1 */
	/* output:	r2 is 0 if op0 < op1, 1 if op0 == op1, 2 if op0 > op1 */
__cmpdi:
	ld2w	r4,@r2+			/* compare first word */
	ld2w	r6,@r3+
	cmp	r4,r6
	brf0t.s	.Lneg
	cmp	r6,r4
	brf0t.s	.Lpos

	cmpu	r5,r7			/* compare second word */
	brf0t.s	.Lneg
	cmpu	r7,r5
	brf0t.s	.Lpos
	
	ld2w	r4,@r2			/* compare third word */
	ld2w	r6,@r3
	cmpu	r4,r6
	brf0t.s	.Lneg
	cmpu	r6,r4
	brf0t.s	.Lpos
	
	cmpu	r5,r7			/* compare fourth word */
	brf0t.s	.Lneg
	cmpu	r7,r5
	brf0t.s	.Lpos

	ldi	r2,1			/* op1 == op2 */
	jmp	r13

.Lneg:
	ldi	r2,0			/* op1 < op2 */
	jmp	r13

.Lpos:
	ldi	r2,2			/* op1 > op2 */
	jmp	r13
	.size	__cmpdi,.-__cmpdi
#endif


#ifdef L_cmpdi0
	.file	"__cmpdi0.s"
	.text
	.globl	__cmpdi0
	.type	__cmpdi0,@function
	/* input:	r2 pointer to DImode op0 */
	/* output:	r2 is -1 if op0 < 0, 0 if op0 == 0, 1 if op0 > 0 */
__cmpdi0:
	ld2w	r4,@r2+			/* compare first word */
	cmpi	r4,0
	brf0t.s	.Lneg
	cmpeqi	r4,0
	brf0f.s	.Lpos

	cmpeqi	r5,0			/* compare second word */
	brf0f.s	.Lpos

	ld2w	r4,@r2			/* compare third word */
	cmpeqi	r4,0
	brf0f.s	.Lpos

	cmpeqi	r5,0			/* compare fourth word */
	brf0f.s	.Lpos
	
	ldi	r2,1			/* op1 == 0 */
	jmp	r13

.Lneg:
	ldi	r2,0			/* op1 < 0 */
	jmp	r13

.Lpos:
	ldi	r2,2			/* op1 > 0 */
	jmp	r13
	.size	__cmpdi0,.-__cmpdi0
#endif


#ifdef L_ucmpdi
	.file	"__ucmpdi.s"
	.text
	.globl	__ucmpdi
	.type	__ucmpdi,@function
	/* input:	r2 pointer to DImode op0, r3 pointer to DImode op1 */
	/* output:	r2 is -1 if (unsigned)op0 < (unsigned)op1, 0 if op0 == op1, 1 if (unsigned)op0 > (unsigned)op1 */
__ucmpdi:
	ld2w	r4,@r2+			/* compare first word */
	ld2w	r6,@r3+
	cmpu	r4,r6
	brf0t.s	.Lneg
	cmpu	r6,r4
	brf0t.s	.Lpos

	cmpu	r5,r7			/* compare second word */
	brf0t.s	.Lneg
	cmpu	r7,r5
	brf0t.s	.Lpos
	
	ld2w	r4,@r2			/* compare third word */
	ld2w	r6,@r3
	cmpu	r4,r6
	brf0t.s	.Lneg
	cmpu	r6,r4
	brf0t.s	.Lpos
	
	cmpu	r5,r7			/* compare fourth word */
	brf0t.s	.Lneg
	cmpu	r7,r5
	brf0t.s	.Lpos

	ldi	r2,1			/* op1 == op2 */
	jmp	r13

.Lneg:
	ldi	r2,0			/* op1 < op2 */
	jmp	r13

.Lpos:
	ldi	r2,2			/* op1 > op2 */
	jmp	r13
	.size	__ucmpdi,.-__ucmpdi
#endif


#ifdef L_ucmpdi0
	.file	"__ucmpdi0.s"
	.text
	.globl	__ucmpdi0
	.type	__ucmpdi0,@function
	/* input:	r2 pointer to DImode op0 */
	/* output:	r2 is 0 if op0 == 0, 1 if op0 > 0 */
__ucmpdi0:
	ld2w	r4,@r2+			/* compare first word */
	cmpeqi	r4,0
	brf0f.s	.Lpos

	cmpeqi	r5,0			/* compare second word */
	brf0f.s	.Lpos

	ld2w	r4,@r2			/* compare third word */
	cmpeqi	r4,0
	brf0f.s	.Lpos

	cmpeqi	r5,0			/* compare fourth word */
	brf0f.s	.Lpos
	
	ldi	r2,1			/* op1 == 0 */
	jmp	r13

.Lpos:
	ldi	r2,2			/* op1 > 0 */
	jmp	r13
	.size	__ucmpdi0,.-__ucmpdi0
#endif
