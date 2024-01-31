/* stuff needed for libgcc1 on win32. */

#ifdef L_chkstk

	.global ___chkstk
	.global	__alloca
___chkstk:
__alloca:
	pushl  %ecx		/* save temp */
	movl   %esp,%ecx	/* get sp */
	addl   $0x8,%ecx	/* and point to return addr */

probe: 	cmpl   $0x1000,%eax	/* > 4k ?*/
	jb    done		

	subl   $0x1000,%ecx  		/* yes, move pointer down 4k*/
	orl    $0x0,(%ecx)   		/* probe there */
	subl   $0x1000,%eax  	 	/* decrement count */
	jmp    probe           	 	/* and do it again */

done: 	subl   %eax,%ecx	   
	orl    $0x0,(%ecx)	/* less that 4k, just peek here */

	movl   %esp,%eax
	movl   %ecx,%esp	/* decrement stack */

	movl   (%eax),%ecx	/* recover saved temp */
	movl   4(%eax),%eax	/* get return address */
	jmp    *%eax	


#endif

#ifdef L_floatunsdidf
/* Convert unsigned DI to float.  This routine exists because NT sets the 
   floating point precision to 2 (53 bit mantissa) rather than to 3 (64 bit
   mantissa).  (This is for some reason associated with backwards
   compatability).  However, to get proper rounding of certain
   double integers, the computation needs to be carried out in 64
   bit mantissa mode.  We change and restore the precision to
   perform the conversion.  (It's the add of 2^64 that's the problem;
   all other operations are done in the size specified by the
   instruction, but the add is done in the precision set in the
   control word, and low order bits that would participate in
   rounding the value correctly are discarded before they get their
   chance.)

   We need to force a round to the required precision before returning,
   because if the value is taken directly from the register in subsequent
   code (with a smaller precision), it will have the low order bits we so
   carefully preserved truncated (discarded) rather than rounded according
   to the current rounding mode.

   Given the code previously generated in line (which entails a function
   call anyway) this is actually fewer instructions executed than inline.
   (In principle, this code could be inlined, but there are limits!) 
   (Regression ieee/rbug.c and compare.c test this; it must pass both.) */
   
.section	.rdata,"x"
	.align 2
LC1:
	.long 0x0,0x80000000,0x403f  /* 2^64 as a float. */
.text

	.global	___floatunsdidf
___floatunsdidf:
	pushl %ebp
	movl %esp,%ebp
	subl $8,%esp			/* temp for ctl words, then DF */
	fstcw 2(%esp) 			/* make 2 copies of current ctl wrd */
	fstcw 0(%esp) 
	orw $0x300,0(%esp)		/* set one to pmode of 3 (64 bit) */
	fldcw 0(%esp)			/* and load it */
	fildq 8(%ebp)			/* load the value to be converted */
	ftst				/*   as signed, and check the sign */
	fnstsw %ax
	andb $69,%ah
	cmpb $1,%ah
	jne L9
	fldt LC1			/* add 2^64 if it was negative */
	faddp %st(1)
L9:
	fldcw 2(%esp)
	fstpl 0(%esp)			/* force a round to DF (via mem) */
	fldl 0(%esp)

	movl %ebp,%esp
	popl %ebp
	ret
#endif

#ifdef L_floatunsdisf
/* see comments above */

.section	.rdata,"x"
	.align 2
LC1:
	.long 0x0,0x80000000,0x403f  /* 2^64 as a float. */
.text

	.global	___floatunsdisf
___floatunsdisf:
	pushl %ebp
	movl %esp,%ebp
	subl $4,%esp			/* temp for ctl wrd, then SF */
	fstcw 2(%esp) 
	fstcw 0(%esp) 
	orw $0x300,0(%esp)
	fldcw 0(%esp)
	fildq 8(%ebp)
	ftst
	fnstsw %ax
	andb $69,%ah
	cmpb $1,%ah
	jne L10
	fldt LC1
	faddp %st(1)
L10:
	fldcw 2(%esp)
	fstps 0(%esp)			/* force a round to SF */
	flds 0(%esp)

	movl %ebp,%esp
	popl %ebp
	ret

#endif

#ifdef L_floatunsdixf
.section	.rdata,"x"
	.align 2
LC1:
	.long 0x0,0x80000000,0x403f  /* 2^64 as a float. */
.text

	.global	___floatunsdixf
___floatunsdixf:
	pushl %ebp
	movl %esp,%ebp
	subl $8,%esp
	fstcw 2(%esp) 
	fstcw 0(%esp) 
	orw $0x300,0(%esp)
	fldcw 0(%esp)
	fildq 8(%ebp)
	ftst
	fnstsw %ax
	andb $69,%ah
	cmpb $1,%ah
	jne L9
	fldt LC1
	faddp %st(1)
L9:
	fldcw 2(%esp)
	/* no need to round these */

	movl %ebp,%esp
	popl %ebp
	ret
#endif

#if defined(L_floatunsditf) && (LONG_DOUBLE_TYPE_SIZE == 128)
/* This can't happen(?), but for completeness sake... */
.section	.rdata,"x"
	.align 2
LC1:
	.long 0x0,0x80000000,0x403f  /* 2^64 as a float. */
.text

	.global	___floatunsditf
___floatunsditf:
	pushl %ebp
	movl %esp,%ebp
	subl $8,%esp
	fstcw 2(%esp) 
	fstcw 0(%esp) 
	orw $0x300,0(%esp)
	fldcw 0(%esp)
	fildq 8(%ebp)
	ftst
	fnstsw %ax
	andb $69,%ah
	cmpb $1,%ah
	jne L9
	fldt LC1
	faddp %st(1)
L9:
	fldcw 2(%esp)
	/* no need to round these */

	movl %ebp,%esp
	popl %ebp
	ret
#endif

#ifdef L_setjmp
/* On OpenNT we want to use system-provided setjmp3 to implement setjmp. 
   Rather than dink with headers or the compiler, we'll just jump to it here.
   setjmp3 takes a second arg associated with MS Structured Exception
   Handling, but which can be zero for our (gcc) purposes. */

	.globl __setjmp
__setjmp:
	movl (%esp),%eax	/* RA */
	movl 4(%esp),%ecx	/* arg */
	movl $0,4(%esp)		/* 'push' 0 */
	movl %ecx,(%esp)	/* 'push' arg */
	pushl %eax		/* push RA */
	jmp  __setjmp3		/* and lie! */

#endif
