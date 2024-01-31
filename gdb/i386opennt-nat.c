/* Native-dependent code for Opennt running on i386's, for GDB.
   Copyright 1988, 1989, 1991, 1992, 1996 Free Software Foundation, Inc.

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include "defs.h"

#ifdef HAVE_SYS_PROCFS_H

#include <sys/procfs.h>
#include <ucontext.h>
#include <frame.h>
#include <inferior.h>

/* See procfs.c and *opennt*.h in config/[alpha,i386] */
CORE_ADDR tramp_start;
CORE_ADDR tramp_end;
CORE_ADDR null_start;
CORE_ADDR null_end;

/*  The /proc interface divides the target machine's register set up into
    two different sets, the general register set (gregset) and the floating
    point register set (fpregset).  For each set, there is an ioctl to get
    the current register set and another ioctl to set the current values.

    The actual structure passed through the ioctl interface is, of course,
    naturally machine dependent, and is different for each set of registers.
    For the i386 for example, the general register set is typically defined
    by:

	typedef int gregset_t[19];		(in <sys/regset.h>)

	#define GS	0			(in <sys/reg.h>)
	#define FS	1
	...
	#define UESP	17
	#define SS	18

    and the floating point set by:

	typedef struct fpregset
	  {
	    union
	      {
		struct fpchip_state	// fp extension state //
		{
		  int state[27];	// 287/387 saved state //
		  int status;		// status word saved at exception //
		} fpchip_state;
		struct fp_emul_space	// for emulators //
		{
		  char fp_emul[246];
		  char fp_epad[2];
		} fp_emul_space;
		int f_fpregs[62];	// union of the above //
	      } fp_reg_set;
	    long f_wregs[33];		// saved weitek state //
	} fpregset_t;

    These routines provide the packing and unpacking of gregset_t and
    fpregset_t formatted data.

 */

#ifdef HAVE_GREGSET_T

/* This is a duplicate of the table in i386-xdep.c. */

static int regmap[] = 
{
  EAX, ECX, EDX, EBX,
  UESP, EBP, ESI, EDI,
  EIP, EFL, CS, SS,
  DS, ES, FS, GS,
};


/*  FIXME:  These routine absolutely depends upon (NUM_REGS - NUM_FREGS)
    being less than or equal to the number of registers that can be stored
    in a gregset_t.  Note that with the current scheme there will typically
    be more registers actually stored in a gregset_t that what we know
    about.  This is bogus and should be fixed. */

/*  Given a pointer to a general register set in /proc format (gregset_t *),
    unpack the register contents and supply them as gdb's idea of the current
    register values. */

void
supply_gregset (gregsetp)
     gregset_t *gregsetp;
{
  register int regi;
  register ulong *regp = (ulong *) &gregsetp->gregs;
  extern int regmap[];

  for (regi = 0 ; regi < (NUM_REGS - NUM_FREGS) ; regi++)
    {
      supply_register (regi, (char *) (regp + regmap[regi]));
    }
}

void
fill_gregset (gregsetp, regno)
     gregset_t *gregsetp;
     int regno;
{
  int regi;
  register ulong *regp = (ulong *) &gregsetp->gregs;
  extern char registers[];
  extern int regmap[];

  for (regi = 0 ; regi < (NUM_REGS - NUM_FREGS) ; regi++)
    {
      if ((regno == -1) || (regno == regi))
	{
	  *(regp + regmap[regi]) = *(int *) &registers[REGISTER_BYTE (regi)];
	}
    }
}

#endif	/* HAVE_GREGSET_T */

#if defined (FP0_REGNUM) && defined (HAVE_FPREGSET_T)

/*  Given a pointer to a floating point register set in /proc format
    (fpregset_t *), unpack the register contents and supply them as gdb's
    idea of the current floating point register values. */

void 
supply_fpregset (fpregsetp)
     fpregset_t *fpregsetp;
{
  register int regi;
  register char *fpregs = (char *) &fpregsetp->fpstate.fpregs;
  
  for (regi = 0; regi < 8; regi++)
    supply_register (regi + FP0_REGNUM, fpregs+(regi*10));
}

/*  Given a pointer to a floating point register set in /proc format
    (fpregset_t *), update the register specified by REGNO from gdb's idea
    of the current floating point register set.  If REGNO is -1, update
    them all. */

void
fill_fpregset (fpregsetp, regno)
     fpregset_t *fpregsetp;
     int regno;
{
  int regi;
  extern char registers[];
  register char *fpregs = (char *) &fpregsetp->fpstate.fpregs;

  for (regi = 0; regi < 8; regi++)
    {
      if ((regno == -1) || (regno == FP0_REGNUM + regi))
	{
	  memcpy(
	    (char *) (fpregs+(regi*10)),
	    (char *) &registers[REGISTER_BYTE (FP0_REGNUM + regi)],
	    REGISTER_RAW_SIZE(FP0_REGNUM + regi));

	}
    }
}

/* the name of the proc status struct depends on the implementation */
#ifdef HAVE_PSTATUS_T
  typedef pstatus_t gdb_prstatus_t;
#else
  typedef prstatus_t gdb_prstatus_t;
#endif

gdb_prstatus_t *procfs_read_current_status();

i386_float_info ()
{
  int regi;
  extern char registers[];
  double mydouble;
  int i;
  char *fptr;
  int top;
  fpregset_t *fpregs;

  fpregs = (fpregset_t *)&(procfs_read_current_status())->pr_lwp.pr_context.uc_mcontext.gregs;

  print_387_status_word (fpregs->fpstate.status & 0xffff);
  print_387_control_word (fpregs->fpstate.control & 0xffff);
  printf_unfiltered ("last exception: ");
  /* It appears that the context structure doesn't explicitly contain the
     opcode; however it appears to have been squrreled away (in the MS
     context struct) as the high (unused) half of the errorselector field.
     It appears there's nothing in the high half of the other 16 bit fields,
     and that the (low 16 bits of) the ...selector fields are meaningless here.
     */
  printf_unfiltered ("opcode %s; ", local_hex_string(fpregs->fpstate.errorselector>>16));
  printf_unfiltered ("pc %s; ", local_hex_string(fpregs->fpstate.erroroffset));
  printf_unfiltered ("operand %s\n", local_hex_string(fpregs->fpstate.dataoffset));

  top = ((fpregs->fpstate.status >> 11) & 7);

  printf_unfiltered("      80-bit register-----  64-bit equiv --------------------------\n\n");
  for (regi = 7; regi >= 0 ; regi--)
    {
	int slot = (8-(top-regi))%8;
        printf_unfiltered ("%s %d: ", regi == top ? "=>" : "  ", regi);

	for (i=9; i >= 0; i--) printf_unfiltered("%02.2x", 
	    (int)((char *) &registers[REGISTER_BYTE (FP0_REGNUM + slot)])[i] & 0xff);
	
	/* We'll munge the 80-bit format into a double via asms;
	   floatformat_to_double() purports to do the same thing, but it
	   doesn't do exactly the same thing (e.g. it loses NaNs).  Since
	   this is Intel-specific anyway, why not use inlines?
	   MSVC doesn't have an 80-bit type, so that won't work.
	   */
 
#ifdef __GNUC__
	__asm__ ("fldt %0" : "=g"
	    (*((char *) &registers[REGISTER_BYTE (FP0_REGNUM + slot)])) );
	__asm__ ("fstpl %0" : "=g" (mydouble));
#else
	/* MSVC inlines */
	fptr = (char *) &registers[REGISTER_BYTE (FP0_REGNUM + slot)];
	__asm {
	   fld tbyte ptr [eax]
	   fstp  mydouble
	}
#endif

	for (i=7; i >= 0; i--) printf_unfiltered("%02.2x", 
	    (int)((char *) &mydouble)[i] & 0xff);
	printf_unfiltered("  %#- 24.20g ", mydouble);

        switch ((fpregs->fpstate.tag >> ((regi) * 2)) & 3) 
	  {
	  case 0: printf_unfiltered ("valid "); break;
	  case 1: printf_unfiltered ("zero  "); break;
	  case 2: printf_unfiltered ("trap  "); break;
	  case 3: printf_unfiltered ("empty "); break;
	  }
	printf_unfiltered("\n");
    }
}
#endif	/* defined (FP0_REGNUM) && defined (HAVE_FPREGSET_T) */

#endif	/* HAVE_SYS_PROCFS_H */

/* We want to find the previous frame, which on NT is tricky when signals
   are involved; set frame->frame appropriately, and also get the pc
   and tweak signal_handler_caller; this replaces a boatload of nested
   macros, as well. */
void
opennt_back_one_frame (fromleaf, frame)
     int fromleaf;
     struct frame_info *frame;
{
  CORE_ADDR ra;
  CORE_ADDR fm;
  CORE_ADDR context;
  long t;

  if (frame == NULL)
      abort();
  
  if (fromleaf)
    {
       frame->pc = SAVED_PC_AFTER_CALL (frame->next);
       return;
    }

  if (!frame->next)
    {
       frame->pc = read_pc();

       /* part of the signal stuff... see below */
       if (stopped_by_random_signal)
	 {
	   /* we know we're in a system call mini-frame; was it
	      NullApi or something else? */
           ra = SAVED_PC_AFTER_CALL (frame);
           if (ra >= null_start && ra < null_end)
	      frame->signal_handler_caller = 1;
	 }
       return;
    }

  if (!frame->next->signal_handler_caller)
    {
      frame->pc = (CORE_ADDR)read_memory_integer (frame->next->frame + 4, 4);
      return;
    }

  /* This is messy... (actually AWFUL) the "trampoline" might be 2, 3 
     or all 5 entities on the frame. 

     Chunk 1 will be present when we're actually in a signal handler.
     Chunk 2 will be present when an asynchronous signal (one that
	didn't come in with a system call) is present.
	We may not (yet) be in the handler, if we're just returning
	from the call.
     When we're actually in a handler taken from an asynchronous
     signal, both will be present.

     Chunk 1:
	PdxSignalDeliverer's frame 
      + Context struct    -- not accounted for in any frame

     Chunk 2:
      + PdxNullPosixApi's frame 
      + PdxNullApiCaller's frame
      + Context struct = 0x230  not accounted for in any frame

     The symbol names come from examining objdumps of psxdll.dll;
     they don't appear in the runtime image.

     For gdb's purposes, we can pile all this into one frame.
  */

  ra = frame->next->pc;
  /* Are we already pointing at PdxNullPosixApi?  We are if
     this is a signal frame, we're at next-to-top, and were stopped
     by a random signal.  (If it wasn't the right address under
     these circumstances, we wouldn't be here at all by tests above
     on the prior frame.) */
  if (frame->next->next == NULL && stopped_by_random_signal) 
    {
      /* We're pointing at the frame FOR PdxNullApi */
      fm = frame->frame;
    }
  else
    {
      /* No... we must be pointing at the frame that
	 was called by PdxSignalDeliverer; back up across the
	 whole mess */

      /* extract the frame for PdxSignalDeliverer; note...FRAME_CHAIN
	 used the "old" frame pointer because we were a deliverer.
	 Get the address of the context record that's on here frameless */
      context = read_memory_integer (frame->frame, 4);  /* an Arg */

      /* Now extract the frame pointer contained in the context */
      fm = (CORE_ADDR)read_memory_integer 
	 (context + offsetof(mcontext_t, gregs.gregs[EBP]), 4);

      ra = (CORE_ADDR)read_memory_integer 
	 (context + offsetof(mcontext_t, gregs.gregs[EIP]), 4);

      /* We need to know if we're in a system call because we'll be
	 in a syscall mini-frame, if so, and the rules are different;
	 reserved[1] contains 0 if running free, 1 if blocked on a system
	 call, and 2 if blocked on an exception message (e.g. a trap);
	 we don't expect to get here with a 2. */
      t = (long)read_memory_integer 
	 (context + offsetof(mcontext_t, gregs.reserved[1]), 4);
      if (t != 1)
	{
	   /* not at a system call, therefore it can't be NullApi */
	   frame->pc = ra;
	   frame->frame = fm;
	   return;
	}

      /* It's a system call... mini frame, then look for NullApi */
      /* Get the RA (on the stack) associated with this... it's
	 a system call mini-frame */
      ra = (CORE_ADDR)read_memory_integer 
	 (context + offsetof(mcontext_t, gregs.gregs[UESP]), 4);
      ra = (CORE_ADDR)read_memory_integer(ra,4);

      /* We might be done (no Null API if so) */
      if (!(ra >= null_start && ra < null_end))
	{
	   /* No Null API present; we're done */
	   frame->pc = ra;
	   frame->frame = fm;
	   return;
	}
    }
  /* At this point, we're looking at the frame for PdxNullPosixApi,
     in either case. */

  /* extract the frame for PdxNullPosixApi */
  fm = read_memory_integer (fm, 4);

  /* extract the frame for PdxNullApiCaller */
  /* The saved frame register for PdxNullApiCaller skips us over the
     saved context, which is the wrong thing to do, because it skips
     the interrrupted routine!  Instead, get the arg that was passed
     which has the address of the context (which is really in no frame) */

  fm = (CORE_ADDR)read_memory_integer (fm + 8, 4);

  /* THIS context is accounted for in a frame */
  /* Extract the second context record */

  ra = (CORE_ADDR)read_memory_integer 
     (fm + offsetof(mcontext_t, gregs.gregs[EIP]), 4);
  fm = (CORE_ADDR)read_memory_integer 
     (fm + offsetof(mcontext_t, gregs.gregs[EBP]), 4);

  frame->frame = fm;
  frame->pc = ra;

  return;
}

/* Figure out where the longjmp will land.
   We expect the first arg to be a pointer to the jmp_buf structure from which
   we extract the pc that we will land at.  The pc is copied into PC.
   This routine returns true on success. */

#include <setjmp.h>

int
get_longjmp_target (pc)
     CORE_ADDR *pc;
{
  CORE_ADDR sp, jb_addr;
  char raw_buffer[MAX_REGISTER_RAW_SIZE];

  sp = read_register (SP_REGNUM);

  if (target_read_memory (sp + SP_ARG0, /* Offset of first arg on stack */
			  raw_buffer,
			  TARGET_PTR_BIT / TARGET_CHAR_BIT))
    return 0;

  jb_addr = extract_address (raw_buffer, TARGET_PTR_BIT / TARGET_CHAR_BIT);

  if (target_read_memory(jb_addr + offsetof(_JUMP_BUFFER,Eip), raw_buffer,
			 sizeof(CORE_ADDR)))
    return 0;

  *pc = extract_address (raw_buffer, sizeof(CORE_ADDR));
  return 1;
}
