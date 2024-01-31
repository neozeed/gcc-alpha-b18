/* CYGNUS LOCAL entire file/law */
/* Subroutines for insn-output.c for Matsushita MN10200 series
   Copyright (C) 1997 Free Software Foundation, Inc.
   Contributed by Jeff Law (law@cygnus.com).

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include <stdio.h>
#include "config.h"
#include "rtl.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "real.h"
#include "insn-config.h"
#include "conditions.h"
#include "insn-flags.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"
#include "recog.h"
#include "expr.h"
#include "tree.h"
#include "obstack.h"

/* Indicate this file was compiled by gcc and what optimization
   level was used.  */
void
asm_file_start (file)
     FILE *file;
{
  fprintf (file, "#\tGCC For the Matsushita MN10200\n");
  if (optimize)
    fprintf (file, "# -O%d\n", optimize);
  else
    fprintf (file, "\n\n");
  output_file_directive (file, main_input_filename);
}

/* Print operand X using operand code CODE to assembly language output file
   FILE.  */

void
print_operand (file, x, code)
     FILE *file;
     rtx x;
     int code;
{
  switch (code)
    {
      case 'b':
      case 'B':
	/* These are normal and reversed branches.  */
	switch (code == 'b' ? GET_CODE (x) : reverse_condition (GET_CODE (x)))
	  {
	  case NE:
	    fprintf (file, "ne");
	    break;
	  case EQ:
	    fprintf (file, "eq");
	    break;
	  case GE:
	    fprintf (file, "ge");
	    break;
	  case GT:
	    fprintf (file, "gt");
	    break;
	  case LE:
	    fprintf (file, "le");
	    break;
	  case LT:
	    fprintf (file, "lt");
	    break;
	  case GEU:
	    fprintf (file, "cc");
	    break;
	  case GTU:
	    fprintf (file, "hi");
	    break;
	  case LEU:
	    fprintf (file, "ls");
	    break;
	  case LTU:
	    fprintf (file, "cs");
	    break;
	  default:
	    abort ();
	  }
	break;
      case 'C':
	/* This is used for the operand to a call instruction;
	   if it's a REG, enclose it in parens, else output
	   the operand normally.  */
	if (GET_CODE (x) == REG)
	  {
	    fputc ('(', file);
	    print_operand (file, x, 0);
	    fputc (')', file);
	  }
	else
	  print_operand (file, x, 0);
	break;
     
      /* These are the least significant word in a 32bit value.
	 'o' allows us to sign extend a constant if doing so
	 makes for more compact code.  */
      case 'L':
      case 'o':
	switch (GET_CODE (x))
	  {
	  case MEM:
	    fputc ('(', file);
	    output_address (XEXP (x, 0));
	    fputc (')', file);
	    break;

	  case REG:
	    fprintf (file, "%s", reg_names[REGNO (x)]);
	    break;

	  case SUBREG:
	    fprintf (file, "%s",
		     reg_names[REGNO (SUBREG_REG (x)) + SUBREG_WORD (x)]);
	    break;

	  case CONST_DOUBLE:
	    if (code == 'L')
	      {
		long val;
		REAL_VALUE_TYPE rv;

		REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
		REAL_VALUE_TO_TARGET_SINGLE (rv, val);
		print_operand_address (file, GEN_INT (val & 0xffff));
	      }
	    else
	      {
		long val;
		REAL_VALUE_TYPE rv;

		REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
		REAL_VALUE_TO_TARGET_SINGLE (rv, val);

		val &= 0xffff;
		val = (((val) & 0xffff) ^ (~0x7fff)) + 0x8000;
		print_operand_address (file, GEN_INT (val));
	      }
	    break;

	  case CONST_INT:
	    if (code == 'L')
	      print_operand_address (file, GEN_INT ((INTVAL (x) & 0xffff)));
	    else
	      {
	        unsigned int val = INTVAL (x) & 0xffff;
		val = (((val) & 0xffff) ^ (~0x7fff)) + 0x8000;
		print_operand_address (file, GEN_INT (val));
	      }
	    break;
	  default:
	    abort ();
	  }
	break;

      /* Similarly, but for the most significant word.  */
      case 'H':
      case 'h':
	switch (GET_CODE (x))
	  {
	  case MEM:
	    fputc ('(', file);
	    x = adj_offsettable_operand (x, 2);
	    output_address (XEXP (x, 0));
	    fputc (')', file);
	    break;

	  case REG:
	    fprintf (file, "%s", reg_names[REGNO (x) + 1]);
	    break;

	  case SUBREG:
	    fprintf (file, "%s",
		     reg_names[REGNO (SUBREG_REG (x)) + SUBREG_WORD (x)] + 1);
	    break;

	  case CONST_DOUBLE:
	    if (code == 'H')
	      {
		long val;
		REAL_VALUE_TYPE rv;

		REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
		REAL_VALUE_TO_TARGET_SINGLE (rv, val);

		print_operand_address (file, GEN_INT ((val >> 16) & 0xffff));
	      }
	    else
	      {
		long val;
		REAL_VALUE_TYPE rv;

		REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
		REAL_VALUE_TO_TARGET_SINGLE (rv, val);

		val = (val >> 16) & 0xffff;
		val = (((val) & 0xffff) ^ (~0x7fff)) + 0x8000;

		print_operand_address (file, GEN_INT (val));
	      }
	    break;

	  case CONST_INT:
	    if (code == 'H')
	      print_operand_address (file,
				     GEN_INT ((INTVAL (x) >> 16) & 0xffff));
	    else
	      {
	        unsigned int val = (INTVAL (x) >> 16) & 0xffff;
		val = (((val) & 0xffff) ^ (~0x7fff)) + 0x8000;

		print_operand_address (file, GEN_INT (val));
	      }
	    break;
	  default:
	    abort ();
	  }
	break;

      /* Output ~CONST_INT.  */
      case 'N':
	if (GET_CODE (x) != CONST_INT)
	  abort ();
        fprintf (file, "%d", ~INTVAL (x));
        break;

      /* An address which can not be register indirect, if it is
	 register indirect, then turn it into reg + disp.  */
      case 'A':
	if (GET_CODE (x) != MEM)
	  abort ();
	if (GET_CODE (XEXP (x, 0)) == REG)
	  x = gen_rtx (PLUS, PSImode, XEXP (x, 0), GEN_INT (0));
	else
	  x = XEXP (x, 0);
	fputc ('(', file);
	output_address (x);
	fputc (')', file);
	break;

      /* More cases where we can sign-extend a CONST_INT if it
	 results in more compact code.  */
      case 's':
      case 'S':
	if (GET_CODE (x) == CONST_INT)
	  {
	    int val = INTVAL (x);

	    if (code == 's')
	      x = GEN_INT (((val & 0xffff) ^ (~0x7fff)) + 0x8000);
	    else
	      x = GEN_INT (((val & 0xff) ^ (~0x7f)) + 0x80);
	  }
        /* FALL THROUGH */
      default:
	switch (GET_CODE (x))
	  {
	  case MEM:
	    fputc ('(', file);
	    output_address (XEXP (x, 0));
	    fputc (')', file);
	    break;

	  case REG:
	    fprintf (file, "%s", reg_names[REGNO (x)]);
	    break;

	  case SUBREG:
	    fprintf (file, "%s",
		     reg_names[REGNO (SUBREG_REG (x)) + SUBREG_WORD (x)]);
	    break;

	  case CONST_INT:
	  case CONST_DOUBLE:
	  case SYMBOL_REF:
	  case CONST:
	  case LABEL_REF:
	  case CODE_LABEL:
	    print_operand_address (file, x);
	    break;
	  default:
	    abort ();
	  }
	break;
   }
}

/* Output assembly language output for the address ADDR to FILE.  */

void
print_operand_address (file, addr)
     FILE *file;
     rtx addr;
{
  switch (GET_CODE (addr))
    {
    case REG:
      print_operand (file, addr, 0);
      break;
    case PLUS:
      {
	rtx base, index;
	/* The base and index could be in any order, so we have
	   to figure out which is the base and which is the index.
	   Uses the same code as GO_IF_LEGITIMATE_ADDRESS.  */
	if (REG_P (XEXP (addr, 0))
	    && REG_OK_FOR_BASE_P (XEXP (addr, 0)))
	  base = XEXP (addr, 0), index = XEXP (addr, 1);
	else if (REG_P (XEXP (addr, 1))
	    && REG_OK_FOR_BASE_P (XEXP (addr, 1)))
	  base = XEXP (addr, 1), index = XEXP (addr, 0);
      	else
	  abort ();
	print_operand (file, index, 0);
	fputc (',', file);
	print_operand (file, base, 0);;
	break;
      }
    case SYMBOL_REF:
      output_addr_const (file, addr);
      break;
    default:
      output_addr_const (file, addr);
      break;
    }
}

/* Return the total size (in bytes) of the current function's frame.
   This is the size of the register save area + the size of locals,
   spills, etc.  */
int
total_frame_size ()
{
  unsigned int size = get_frame_size ();
  int i;

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
      if (regs_ever_live[i] && !call_used_regs[i] && ! fixed_regs[i]
	  || (i == FRAME_POINTER_REGNUM && frame_pointer_needed))
	size += 4;
    }

  return size;
}

/* Expand the prologue into RTL.  */
void
expand_prologue ()
{
  unsigned int size = total_frame_size ();
  int offset, i;


  /* Temporarily stuff the static chain onto the stack so we can
     use a0 as a scratch register during the prologue.  */
  if (current_function_needs_context)
    {
      emit_insn (gen_addpsi3 (stack_pointer_rtx, stack_pointer_rtx,
			      GEN_INT (-4)));
      emit_move_insn (gen_rtx (MEM, PSImode, stack_pointer_rtx),
		      gen_rtx (REG, PSImode, STATIC_CHAIN_REGNUM));
    }

  if (frame_pointer_needed)
    {
      /* Store a2 into a0 temporarily.  */
      emit_move_insn (gen_rtx (REG, PSImode, 4), frame_pointer_rtx);

      /* Set up the frame pointer.  */
      emit_move_insn (frame_pointer_rtx, stack_pointer_rtx);
    }

  /* Make any necessary space for the saved registers and local frame.  */
  if (size)
    emit_insn (gen_addpsi3 (stack_pointer_rtx, stack_pointer_rtx,
			    GEN_INT (-size)));

  /* Save the callee saved registers.  They're saved into the top
     of the frame, using the stack pointer.  */
  for (i = 0, offset = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
      if (regs_ever_live[i] && !call_used_regs[i] && ! fixed_regs[i]
	  || (i == FRAME_POINTER_REGNUM && frame_pointer_needed))
	{
	  int regno;

	  /* If we're saving the frame pointer, then it will be found in
	     register 4 (a0).  */
	  regno = (i == FRAME_POINTER_REGNUM && frame_pointer_needed) ? 4 : i;
	
	  emit_move_insn (gen_rtx (MEM, PSImode,
				   gen_rtx (PLUS, Pmode,
					    stack_pointer_rtx,
					    GEN_INT (offset))),
			  gen_rtx (REG, PSImode, regno));
	  offset += 4;
	}
    }

  /* Now put the static chain back where the rest of the function
     expects to find it.  */
  if (current_function_needs_context)
    {
      emit_move_insn (gen_rtx (REG, PSImode, STATIC_CHAIN_REGNUM),
		      gen_rtx (MEM, PSImode,
			       gen_rtx (PLUS, PSImode, stack_pointer_rtx,
					GEN_INT (size))));
    }
}

/* Expand the epilogue into RTL.  */
void
expand_epilogue ()
{
  unsigned int size;
  int offset, i;
  rtx basereg;

  size = total_frame_size ();

  /* Registers are restored from the frame pointer if we have one,
     else they're restored from the stack pointer.  Figure out
     the appropriate offset to the register save area for both cases.  */
  if (frame_pointer_needed)
    {
      basereg = frame_pointer_rtx;
      offset = -size;
    }
  else
    {
      basereg = stack_pointer_rtx;
      offset = 0;
    }

  /* Restore each register.  */
  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
      if (regs_ever_live[i] && !call_used_regs[i] && ! fixed_regs[i]
	  || (i == FRAME_POINTER_REGNUM && frame_pointer_needed))
	{
	  int regno;

	  /* Restore the frame pointer (if it exists) into a temporary
	     register.  */
	  regno = (i == FRAME_POINTER_REGNUM && frame_pointer_needed) ? 4 : i;
	
	  emit_move_insn (gen_rtx (REG, PSImode, regno),
			  gen_rtx (MEM, PSImode,
				   gen_rtx (PLUS, Pmode,
					    basereg,
					    GEN_INT (offset))));
	  offset += 4;
	}
    }

  if (frame_pointer_needed)
    {
      /* Deallocate this frame's stack.  */
      emit_move_insn (stack_pointer_rtx, frame_pointer_rtx);
      /* Restore the old frame pointer.  */
      emit_move_insn (frame_pointer_rtx, gen_rtx (REG, PSImode, 4));
    }
  else if (size)
    {
      /* Deallocate this function's stack.  */
      emit_insn (gen_addpsi3 (stack_pointer_rtx, stack_pointer_rtx,
			      GEN_INT (size)));
    }

  /* If we had to allocate a slot to save the context pointer,
     then it must be deallocated here.  */
  if (current_function_needs_context)
    emit_insn (gen_addpsi3 (stack_pointer_rtx, stack_pointer_rtx, GEN_INT (4)));

  /* Emit the return insn, if this function had no stack, then we
     can use the standard return (which allows more optimizations),
     else we have to use the special one which inhibits optimizations.  */
  if (size == 0 && !current_function_needs_context)
    emit_jump_insn (gen_return ());
  else
    emit_jump_insn (gen_return_internal ());
}

/* Update the condition code from the insn.  */

void
notice_update_cc (body, insn)
     rtx body;
     rtx insn;
{
  switch (get_attr_cc (insn))
    {
    case CC_NONE:
      /* Insn does not affect CC at all.  */
      break;

    case CC_NONE_0HIT:
      /* Insn does not change CC, but the 0'th operand has been changed.  */
      if (cc_status.value1 != 0
	  && reg_overlap_mentioned_p (recog_operand[0], cc_status.value1))
	cc_status.value1 = 0;
      break;

    case CC_SET_ZN_C0:
      /* Insn sets the Z,N flags of CC to recog_operand[0].
	 V is in an unusable state.  C may or may not be set to 0 but that's ok
	 because alter_cond will change tests to use EQ/NE.  */
      CC_STATUS_INIT;
      cc_status.flags |= CC_OVERFLOW_UNUSABLE | CC_NO_OVERFLOW;
      cc_status.value1 = recog_operand[0];
      break;

    case CC_TST:
      /* Insn is a tst instruction.  */
      CC_STATUS_INIT;
      cc_status.value1 = recog_operand[0];
      break;

    case CC_COMPARE:
      /* The insn is a compare instruction.  */
      CC_STATUS_INIT;
      cc_status.value1 = SET_SRC (body);
      break;

    case CC_CLOBBER:
      /* Insn doesn't leave CC in a usable state.  */
      CC_STATUS_INIT;
      break;

    default:
      CC_STATUS_INIT;
      break;
    }
}

/* Return true if OP is a valid call operand.  Valid call operands
   are SYMBOL_REFs and REGs.  */
int
call_address_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  return (GET_CODE (op) == SYMBOL_REF || GET_CODE (op) == REG);
}

/* Return true if OP is an indirect memory operand, the "bset" and "bclr"
   insns use this predicate.  */
int
indirect_memory_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  return (GET_CODE (op) == MEM && GET_CODE (XEXP (op, 0)) == REG);
}

/* Return true if OP is a memory operand with a constant address.
   A special PSImode move pattern uses this predicate.  */
int
constant_memory_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  return GET_CODE (op) == MEM && CONSTANT_ADDRESS_P (XEXP (op, 0));
}

/* What (if any) secondary registers are needed to move IN with mode
   MODE into a register from in register class CLASS. 

   We might be able to simplify this.  */
enum reg_class
secondary_reload_class (class, mode, in, input)
     enum reg_class class;
     enum machine_mode mode;
     rtx in;
     int input;
{
  int regno;

  /* Memory loads less than a full word wide can't have an
     address or stack pointer destination.  They must use
     a data register as an intermediate register.  */
  if (input
      && GET_CODE (in) == MEM
      && (mode == QImode)
      && class == ADDRESS_REGS)
    return DATA_REGS;

  /* Address register stores which are not PSImode need a scrach register.  */
  if (! input
      && GET_CODE (in) == MEM
      && (mode != PSImode)
      && class == ADDRESS_REGS)
    return DATA_REGS;

  /* Otherwise assume no secondary reloads are needed.  */
  return NO_REGS;
}


/* Shifts.

   We devote a fair bit of code to getting efficient shifts since we can only
   shift one bit at a time, and each single bit shift may take multiple
   instructions.

   The basic shift methods:

     * loop shifts -- emit a loop using one (or two on H8/S) bit shifts;
     this is the default.  SHIFT_LOOP

     * inlined shifts -- emit straight line code for the shift; this is
     used when a straight line shift is about the same size or smaller
     than a loop.  We allow the inline version to be slightly longer in
     some cases as it saves a register.  SHIFT_INLINE

     * There other oddballs.  Not worth explaining.  SHIFT_SPECIAL


   HImode shifts:

     1-4    do them inline

     5-7    If ashift, then multiply, else loop.
	
     8-14 - If ashift, then multiply, if lshiftrt, then divide, else loop.
     15   - rotate the bit we want into the carry, clear the destination,
	    (use mov 0,dst, not sub as sub will clobber the carry), then
	    move bit into place.

 
   PSImode shifts:
     All right shifts are done via promotion to SImode, shifting, then
     truncating the result.  Shifts by 23 could be handled better, but
     I don't believe they're worth the effort.

     Left shifts are common (for address computations), so we try to
     handle them reasonably efficiently.

     For left shifts:
     1-7    do them inline

     8-15 - loop

   SImode shifts:
     We need to handle these reasonably efficiently too, they occur
     often naturally, as well as due to PSImode promotions.

     1-3    do them inline.
     4-15   loop
     16-31  Leave it to the machine independent code which handles
	    these cases well.

   Don't Panic, it's not nearly as bad as the H8 shifting code!!!  */

int
nshift_operator (x, mode)
     rtx x;
     enum machine_mode mode;
{
  switch (GET_CODE (x))
    {
    case ASHIFTRT:
    case LSHIFTRT:
    case ASHIFT:
      return 1;

    default:
      return 0;
    }
}

/* Called from the .md file to emit code to do shifts.
   Returns a boolean indicating success
   (currently this is always TRUE).  */

int
expand_a_shift (mode, code, operands)
     enum machine_mode mode;
     int code;
     rtx operands[];
{
  emit_move_insn (operands[0], operands[1]);

  /* need a loop to get all the bits we want  - we generate the
     code at emit time, but need to allocate a scratch reg now  */

  emit_insn (gen_rtx
	     (PARALLEL, VOIDmode,
	      gen_rtvec (2,
			 gen_rtx (SET, VOIDmode, operands[0],
				  gen_rtx (code, mode, operands[0], operands[2])),
			 gen_rtx (CLOBBER, VOIDmode, gen_rtx (SCRATCH, HImode, 0)))));

  return 1;
}

/* Shift algorithm determination.

   There are various ways of doing a shift:
   SHIFT_INLINE: If the amount is small enough, just generate as many one-bit
                 shifts as we need.
   SHIFT_SPECIAL: Hand crafted assembler.
   SHIFT_LOOP:    If the above methods fail, just loop.  */

enum shift_alg
{
  SHIFT_INLINE,
  SHIFT_SPECIAL,
  SHIFT_LOOP,
  SHIFT_MAX
};

/* Symbols of the various shifts which can be used as indices.  */

enum shift_type
  {
    SHIFT_ASHIFT, SHIFT_LSHIFTRT, SHIFT_ASHIFTRT
  };

/* Symbols of the various modes which can be used as indices.  */

enum shift_mode
  {
    HIshift, SIshift, PSIshift
  };

/* For single bit shift insns, record assembler and what bits of the
   condition code are valid afterwards (represented as various CC_FOO
   bits, 0 means CC isn't left in a usable state).  */

struct shift_insn
{
  char *assembler;
  int cc_valid;
};

/* Assembler instruction shift table.

   These tables are used to look up the basic shifts.
   They are indexed by cpu, shift_type, and mode.
*/

static const struct shift_insn shift_one[3][3] =
{
  {
/* SHIFT_ASHIFT */
      { "add\t%0,%0", CC_CLOBBER },
      { "add\t%L0,%L0\n\taddc\t%H0,%H0", CC_CLOBBER },
      { "add\t%0,%0", CC_CLOBBER },
  },
/* SHIFT_LSHIFTRT */
  {
      { "lsr\t%0", CC_CLOBBER },
      { "lsr\t%H0\n\tror\t%L0", CC_CLOBBER },
      { "bad psimode shift", CC_CLOBBER },
  },
/* SHIFT_ASHIFTRT */
  {
      { "asr\t%0", CC_CLOBBER },
      { "asr\t%H0\n\tror\t%L0", CC_CLOBBER },
      { "bad psimode shift", CC_CLOBBER },
  },
};

/* Given CPU, MODE, SHIFT_TYPE, and shift count COUNT, determine the best
   algorithm for doing the shift.  The assembler code is stored in ASSEMBLER.
   We don't achieve maximum efficiency in all cases, but the hooks are here
   to do so.

   For now we just use lots of switch statements.  Since we don't even come
   close to supporting all the cases, this is simplest.  If this function ever
   gets too big, perhaps resort to a more table based lookup.  Of course,
   at this point you may just wish to do it all in rtl.  */

static enum shift_alg
get_shift_alg (shift_type, mode, count, assembler_p, cc_valid_p)
     enum shift_type shift_type;
     enum machine_mode mode;
     int count;
     const char **assembler_p;
     int *cc_valid_p;
{
  /* The default is to loop.  */
  enum shift_alg alg = SHIFT_LOOP;
  enum shift_mode shift_mode;

  /* We don't handle negative shifts or shifts greater than the word size,
     they should have been handled already.  */

  if (count < 0 || count > GET_MODE_BITSIZE (mode))
    abort ();

  switch (mode)
    {
    case HImode:
      shift_mode = HIshift;
      break;
    case SImode:
      shift_mode = SIshift;
      break;
    case PSImode:
      shift_mode = PSIshift;
      break;
    default:
      abort ();
    }

  /* Assume either SHIFT_LOOP or SHIFT_INLINE.
     It is up to the caller to know that looping clobbers cc.  */
  *assembler_p = shift_one[shift_type][shift_mode].assembler;
  *cc_valid_p = shift_one[shift_type][shift_mode].cc_valid;

  /* Now look for cases we want to optimize.  */

  switch (shift_mode)
    {
    case HIshift:
      if (count <= 4)
	return SHIFT_INLINE;
      else if (count < 15 && shift_type != SHIFT_ASHIFTRT)
	{
	  switch (count)
	    {
	    case 5:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 32,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 32,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 6:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 64,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 64,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 7:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 128,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 128,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 8:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 256,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 256,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 9:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 512,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 512,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 10:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 1024,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 1024,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 11:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 2048,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 2048,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 12:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 4096,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 4096,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 13:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 8192,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 8192,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    case 14:
	      if (shift_type == SHIFT_ASHIFT)
		*assembler_p = "mov 16384,%4\n\tmul %4,%0";
	      else if (shift_type == SHIFT_LSHIFTRT)
		*assembler_p = "sub %4,%4\n\tmov %4,mdr\n\tmov 16384,%4\n\tdivu %4,%0";
	      *cc_valid_p = 0;
	      return SHIFT_SPECIAL;
	    }
	}
      else if (count == 15 && shift_mode != PSIshift)
	{
          if (shift_type == SHIFT_ASHIFTRT)
            {
              *assembler_p = "add\t%0,%0\n\tsubc\t%0,%0\n";
              *cc_valid_p = 0;
              return SHIFT_SPECIAL;
	    }
          if (shift_type == SHIFT_LSHIFTRT)
            {
              *assembler_p = "add\t%0,%0\n\tmov 0,%0\n\trol %0\n";
              *cc_valid_p = 0;
              return SHIFT_SPECIAL;
	    }
          if (shift_type == SHIFT_ASHIFT)
            {
              *assembler_p = "ror\t%0\n\tmov 0,%0\n\tror %0\n";
              *cc_valid_p = 0;
              return SHIFT_SPECIAL;
	    }
	}
      break;

    case SIshift:
      if (count <= 3)
	return SHIFT_INLINE;
      break;

    default:
      abort ();
    }

  return alg;
}

/* Emit the assembler code for doing shifts.  */

char *
emit_a_shift (insn, operands)
     rtx insn;
     rtx *operands;
{
  static int loopend_lab;
  char *assembler;
  int cc_valid;
  rtx inside = PATTERN (insn);
  rtx shift = operands[3];
  enum machine_mode mode = GET_MODE (shift);
  enum rtx_code code = GET_CODE (shift);
  enum shift_type shift_type;
  enum shift_mode shift_mode;

  loopend_lab++;

  switch (mode)
    {
    case HImode:
      shift_mode = HIshift;
      break;
    case SImode:
      shift_mode = SIshift;
      break;
    case PSImode:
      shift_mode = PSIshift;
      break;
    default:
      abort ();
    }

  switch (code)
    {
    case ASHIFTRT:
      shift_type = SHIFT_ASHIFTRT;
      break;
    case LSHIFTRT:
      shift_type = SHIFT_LSHIFTRT;
      break;
    case ASHIFT:
      shift_type = SHIFT_ASHIFT;
      break;
    default:
      abort ();
    }

  if (GET_CODE (operands[2]) != CONST_INT)
    {
      /* Indexing by reg, so have to loop and test at top */
      output_asm_insn ("mov	%2,%4", operands);
      output_asm_insn ("cmp	0,%4", operands);
      fprintf (asm_out_file, "\tble	.Lle%d\n", loopend_lab);

      /* Get the assembler code to do one shift.  */
      get_shift_alg (shift_type, mode, 1, &assembler, &cc_valid);
    }
  else
    {
      int n = INTVAL (operands[2]);
      enum shift_alg alg;

      /* If the count is negative, make it 0.  */
      if (n < 0)
	n = 0;
      /* If the count is too big, truncate it.
         ANSI says shifts of GET_MODE_BITSIZE are undefined - we choose to
	 do the intuitive thing.  */
      else if (n > GET_MODE_BITSIZE (mode))
	n = GET_MODE_BITSIZE (mode);

      alg = get_shift_alg (shift_type, mode, n, &assembler, &cc_valid);

      switch (alg)
	{
	case SHIFT_INLINE:
	  /* Emit one bit shifts.  */
	  while (n > 0)
	    {
	      output_asm_insn (assembler, operands);
	      n -= 1;
	    }

#if 0
	  /* Keep track of CC.  */
	  if (cc_valid)
	    {
	      cc_status.value1 = operands[0];
	      cc_status.flags |= cc_valid;
	    }
#endif
	  return "";

	case SHIFT_SPECIAL:
	  output_asm_insn (assembler, operands);
	  return "";
	}

	{
	  fprintf (asm_out_file, "\tmov	%d,%s\n", n,
		   reg_names[REGNO (operands[4])]);
	  fprintf (asm_out_file, ".Llt%d:\n", loopend_lab);
	  output_asm_insn (assembler, operands);
	  output_asm_insn ("add	-1,%4", operands);
	  fprintf (asm_out_file, "\tbne	.Llt%d\n", loopend_lab);
	  return "";
	}
    }

  fprintf (asm_out_file, ".Llt%d:\n", loopend_lab);
  output_asm_insn (assembler, operands);
  output_asm_insn ("add	-1,%4", operands);
  fprintf (asm_out_file, "\tbne	.Llt%d\n", loopend_lab);
  fprintf (asm_out_file, ".Lle%d:\n", loopend_lab);

  return "";
}

/* Return an RTX to represent where a value with mode MODE will be returned
   from a function.  If the result is 0, the argument is pushed.  */

rtx
function_arg (cum, mode, type, named)
     CUMULATIVE_ARGS *cum;
     enum machine_mode mode;
     tree type;
     int named;
{
  rtx result = 0;
  int size, align;

  /* We only support using 2 data registers as argument registers.  */
  int nregs = 2;

  /* Only pass named arguments in registers.  */
  if (!named)
    return NULL_RTX;

  /* Figure out the size of the object to be passed.  We lie and claim
     PSImode values are only two bytes since they fit in a single
     register.  */
  if (mode == BLKmode)
    size = int_size_in_bytes (type);
  else if (mode == PSImode)
    size = 2;
  else
    size = GET_MODE_SIZE (mode);

  /* Figure out the alignment of the object to be passed.  */
    align = size;

  cum->nbytes = (cum->nbytes + align - 1) &~(align - 1);

  /* Don't pass this arg via a register if all the argument registers
     are used up.  */
  if (cum->nbytes > nregs * UNITS_PER_WORD)
    return 0;

  /* Don't pass this arg via a register if it would be split between
     registers and memory.  */
  if (type == NULL_TREE
      && cum->nbytes + size > nregs * UNITS_PER_WORD)
    return 0;

  switch (cum->nbytes / UNITS_PER_WORD)
    {
    case 0:
      result = gen_rtx (REG, mode, 0);
      break;
    case 1:
      result = gen_rtx (REG, mode, 1);
      break;
    default:
      result = 0;
    }

  return result;
}

char *
output_tst (operand, insn)
     rtx operand, insn;
{
  
  rtx temp;
  int past_call = 0;

  /* We can save a byte if we can find a register which has the value
     zero in it.  */
  temp = PREV_INSN (insn);
  while (temp)
    {
      rtx set;

      /* We allow the search to go through call insns.  We record
	 the fact that we've past a CALL_INSN and reject matches which
	 use call clobbered registers.  */
      if (GET_CODE (temp) == CODE_LABEL
	  || GET_CODE (temp) == JUMP_INSN
	  || GET_CODE (temp) == BARRIER)
	break;

      if (GET_CODE (temp) == CALL_INSN)
	past_call = 1;

      if (GET_CODE (temp) == NOTE)
	{
	  temp = PREV_INSN (temp);
	  continue;
	}

      /* It must be an insn, see if it is a simple set. */
      set = single_set (temp);
      if (!set)
	{
	  temp = PREV_INSN (temp);
	  continue;
	}

      /* Are we setting a data register to zero (this does not win for
	 address registers)? 

	 If it's a call clobbered register, have we past a call?  */
      if (REG_P (SET_DEST (set))
	  && SET_SRC (set) == CONST0_RTX (GET_MODE (SET_DEST (set)))
	  && !reg_set_between_p (SET_DEST (set), temp, insn)
	  && REGNO_REG_CLASS (REGNO (SET_DEST (set))) == DATA_REGS
	  && (!past_call 
	      || !call_used_regs[REGNO (SET_DEST (set))]))
	{
	  rtx xoperands[2];
	  xoperands[0] = operand;
	  xoperands[1] = SET_DEST (set);

	  output_asm_insn ("cmp %1,%0", xoperands);
	  return "";
	}
      temp = PREV_INSN (temp);
    }
  return "cmp 0,%0";
}
/* END CYGNUS LOCAL */
