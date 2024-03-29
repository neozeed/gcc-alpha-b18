/* Subroutines for insn-output.c for Matsushita MN10300 series
   Copyright (C) 1996, 1997 Free Software Foundation, Inc.
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

/* Global registers known to hold the value zero.

   Normally we'd depend on CSE and combine to put zero into a
   register and re-use it.

   However, on the mn10x00 processors we implicitly use the constant
   zero in tst instructions, so we might be able to do better by
   loading the value into a register in the prologue, then re-useing
   that register throughout the function.

   We could perform similar optimizations for other constants, but with
   gcse due soon, it doesn't seem worth the effort.

   These variables hold a rtx for a register known to hold the value
   zero throughout the entire function, or NULL if no register of
   the appropriate class has such a value throughout the life of the
   function.  */
rtx zero_dreg;
rtx zero_areg;

void
asm_file_start (file)
     FILE *file;
{
  fprintf (file, "#\tGCC For the Matsushita MN10300\n");
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
     
      /* These are the least significant word in a 64bit value.  */
      case 'L':
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
	      {
		long val[2];
		REAL_VALUE_TYPE rv;

		switch (GET_MODE (x))
		  {
		    case DFmode:
		      REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
		      REAL_VALUE_TO_TARGET_DOUBLE (rv, val);
		      print_operand_address (file, GEN_INT (val[0]));
		      break;;
		    case SFmode:
		      REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
		      REAL_VALUE_TO_TARGET_SINGLE (rv, val[0]);
		      print_operand_address (file, GEN_INT (val[0]));
		      break;;
		    case VOIDmode:
		    case DImode:
		      print_operand_address (file,
					     GEN_INT (CONST_DOUBLE_LOW (x)));
		      break;
		  }
		break;
	      }

	  case CONST_INT:
	    print_operand_address (file, x);
	    break;

	  default:
	    abort ();
	  }
	break;

      /* Similarly, but for the most significant word.  */
      case 'H':
	switch (GET_CODE (x))
	  {
	  case MEM:
	    fputc ('(', file);
	    x = adj_offsettable_operand (x, 4);
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
	      {
		long val[2];
		REAL_VALUE_TYPE rv;

		switch (GET_MODE (x))
		  {
		    case DFmode:
		      REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
		      REAL_VALUE_TO_TARGET_DOUBLE (rv, val);
		      print_operand_address (file, GEN_INT (val[1]));
		      break;;
		    case SFmode:
		      abort ();
		    case VOIDmode:
		    case DImode:
		      print_operand_address (file, 
					     GEN_INT (CONST_DOUBLE_HIGH (x)));
		      break;
		  }
		break;
	      }

	  case CONST_INT:
	    if (INTVAL (x) < 0)
	      print_operand_address (file, GEN_INT (-1));
 	    else
	      print_operand_address (file, GEN_INT (0));
	    break;
	  default:
	    abort ();
	  }
	break;

      case 'A':
	fputc ('(', file);
	if (GET_CODE (XEXP (x, 0)) == REG)
	  output_address (gen_rtx (PLUS, SImode, XEXP (x, 0), GEN_INT (0)));
	else
	  output_address (XEXP (x, 0));
	fputc (')', file);
	break;

      case 'N':
	output_address (GEN_INT ((~INTVAL (x)) & 0xff));
	break;

      default:
	switch (GET_CODE (x))
	  {
	  case MEM:
	    fputc ('(', file);
	    output_address (XEXP (x, 0));
	    fputc (')', file);
	    break;

	  case PLUS:
	    output_address (x);
	    break;

	  case REG:
	    fprintf (file, "%s", reg_names[REGNO (x)]);
	    break;

	  case SUBREG:
	    fprintf (file, "%s",
		     reg_names[REGNO (SUBREG_REG (x)) + SUBREG_WORD (x)]);
	    break;

	  /* This will only be single precision....  */
	  case CONST_DOUBLE:
	    {
	      unsigned long val;
	      REAL_VALUE_TYPE rv;

	      REAL_VALUE_FROM_CONST_DOUBLE (rv, x);
	      REAL_VALUE_TO_TARGET_SINGLE (rv, val);
	      print_operand_address (file, GEN_INT (val));
	      break;
	    }

	  case CONST_INT:
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
      if (addr == stack_pointer_rtx)
	print_operand_address (file, gen_rtx (PLUS, SImode,
					      stack_pointer_rtx,
					      GEN_INT (0)));
      else
	print_operand (file, addr, 0);
      break;
    case PLUS:
      {
	rtx base, index;
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

int
can_use_return_insn ()
{
  /* size includes the fixed stack space needed for function calls.  */
  int size = get_frame_size () + current_function_outgoing_args_size;

  /* And space for the return pointer.  */
  size += current_function_outgoing_args_size ? 4 : 0;

  return (reload_completed
	  && size == 0
	  && !regs_ever_live[2]
	  && !regs_ever_live[3]
	  && !regs_ever_live[6]
	  && !regs_ever_live[7]
	  && !frame_pointer_needed);
}

/* Count the number of tst insns which compare a data or address
   register with zero.  */
static void 
count_tst_insns (dreg_countp, areg_countp)
     int *dreg_countp;
     int *areg_countp;
{
  rtx insn;

  /* Assume no tst insns exist.  */
  *dreg_countp = 0;
  *areg_countp = 0;

  /* If not optimizing, then quit now.  */
  if (!optimize)
    return;

  /* Walk through all the insns.  */
  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      rtx pat;

      /* Ignore anything that is not a normal INSN.  */
      if (GET_CODE (insn) != INSN)
	continue;

      /* Ignore anything that isn't a SET.  */
      pat = PATTERN (insn);
      if (GET_CODE (pat) != SET)
	continue;

      /* Check for a tst insn.  */
      if (SET_DEST (pat) == cc0_rtx
	  && GET_CODE (SET_SRC (pat)) == REG)
	{
	  if (REGNO_REG_CLASS (REGNO (SET_SRC (pat))) == DATA_REGS)
	    (*dreg_countp)++;
    
	  if (REGNO_REG_CLASS (REGNO (SET_SRC (pat))) == ADDRESS_REGS)
	    (*areg_countp)++;
	}

      /* Setting an address register to zero can also be optimized,
	 so count it just like a tst insn.  */
      if (GET_CODE (SET_DEST (pat)) == REG
	  && GET_CODE (SET_SRC (pat)) == CONST_INT
	  && INTVAL (SET_SRC (pat)) == 0
	  && REGNO_REG_CLASS (REGNO (SET_DEST (pat))) == ADDRESS_REGS)
	(*areg_countp)++;
    }
}

void
expand_prologue ()
{
  unsigned int size;

  /* Determine if it is profitable to put the value zero into a register
     for the entire function.  If so, set ZERO_DREG and ZERO_AREG.  */
  if (regs_ever_live[2] || regs_ever_live[3]
       || regs_ever_live[6] || regs_ever_live[7]
       || frame_pointer_needed)
    {
      int dreg_count, areg_count;

      /* Get a count of the number of tst insns which use address and
	 data registers.  */
      count_tst_insns (&dreg_count, &areg_count);

      /* If there's more than one tst insn using a data register, then
	 this optimization is a win.  */
      if (dreg_count > 1
	  && (!regs_ever_live[2] || !regs_ever_live[3]))
	{
 	  if (!regs_ever_live[2])
	    {
	      regs_ever_live[2] = 1;
	      zero_dreg = gen_rtx (REG, SImode, 2);
	    }
	  else
	    {
	      regs_ever_live[3] = 1;
	      zero_dreg = gen_rtx (REG, SImode, 3);
	    }
	}
      else
	zero_dreg = NULL_RTX;

      /* If there's more than two tst insns using an address register,
	 then this optimization is a win.  */
      if (areg_count > 2
	  && (!regs_ever_live[6] || !regs_ever_live[7]))
	{
 	  if (!regs_ever_live[6])
	    {
	      regs_ever_live[6] = 1;
	      zero_areg = gen_rtx (REG, SImode, 6);
	    }
	  else
	    {
	      regs_ever_live[7] = 1;
	      zero_areg = gen_rtx (REG, SImode, 7);
	    }
	}
      else
	zero_areg = NULL_RTX;
    }
  else
    {
      zero_dreg = NULL_RTX;
      zero_areg = NULL_RTX;
    }

  /* SIZE includes the fixed stack space needed for function calls.  */
  size = get_frame_size () + current_function_outgoing_args_size;
  size += (current_function_outgoing_args_size ? 4 : 0);

  /* If this is an old-style varargs function, then its arguments
     need to be flushed back to the stack.  */
  if (current_function_varargs)
    {
      emit_move_insn (gen_rtx (MEM, SImode,
			       gen_rtx (PLUS, Pmode, stack_pointer_rtx,
					GEN_INT (4))),
		      gen_rtx (REG, SImode, 0));
      emit_move_insn (gen_rtx (MEM, SImode,
			       gen_rtx (PLUS, Pmode, stack_pointer_rtx,
					GEN_INT (8))),
		      gen_rtx (REG, SImode, 1));
    }

  /* And now store all the registers onto the stack with a
     single two byte instruction.  */
  if (regs_ever_live[2] || regs_ever_live[3]
      || regs_ever_live[6] || regs_ever_live[7]
      || frame_pointer_needed)
    emit_insn (gen_store_movm ());

  /* Now put the frame pointer into the frame pointer register.  */
  if (frame_pointer_needed)
    emit_move_insn (frame_pointer_rtx, stack_pointer_rtx);

  /* Allocate stack for this frame.  */
  if (size)
    emit_insn (gen_addsi3 (stack_pointer_rtx,
			   stack_pointer_rtx,
			   GEN_INT (-size)));

  /* Load zeros into registers as needed.  */
  if (zero_dreg)
    emit_move_insn (zero_dreg, const0_rtx);

  if (zero_areg)
    emit_move_insn (zero_areg, const0_rtx);
}

void
expand_epilogue ()
{
  unsigned int size;

  /* SIZE includes the fixed stack space needed for function calls.  */
  size = get_frame_size () + current_function_outgoing_args_size;
  size += (current_function_outgoing_args_size ? 4 : 0);

  /* Cut back the stack.  */
  if (frame_pointer_needed)
    {
      emit_move_insn (stack_pointer_rtx, frame_pointer_rtx);
      size = 0;
    }
  else if ((regs_ever_live[2] || regs_ever_live[3]
	    || regs_ever_live[6] || regs_ever_live[7])
	   && size > 255)
    {
      emit_insn (gen_addsi3 (stack_pointer_rtx,
			     stack_pointer_rtx,
			     GEN_INT (size)));
      size = 0;
    }

  /* For simplicity, we just movm all the callee saved registers to
     the stack with one instruction.

     ?!? Only save registers which are actually used.  Reduces
     stack requireents and is faster.  */
  if (regs_ever_live[2] || regs_ever_live[3]
      || regs_ever_live[6] || regs_ever_live[7]
      || frame_pointer_needed)
    emit_jump_insn (gen_return_internal_regs (GEN_INT (size)));
  else
    {
      if (size)
	{
	  emit_insn (gen_addsi3 (stack_pointer_rtx,
				 stack_pointer_rtx,
				 GEN_INT (size)));
	  emit_jump_insn (gen_return_internal ());
	}
      else
	{
	  emit_jump_insn (gen_return ());
	}
    }
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
	 V is always set to 0.  C may or may not be set to 0 but that's ok
	 because alter_cond will change tests to use EQ/NE.  */
      CC_STATUS_INIT;
      cc_status.flags |= CC_NO_OVERFLOW | CC_OVERFLOW_UNUSABLE;
      cc_status.value1 = recog_operand[0];
      break;

    case CC_TST:
      /* The insn sets all the condition codes, except v is bogus.  */
      CC_STATUS_INIT;
      cc_status.value1 = recog_operand[0];
      break;

    case CC_COMPARE:
      /* The insn is a compare instruction.  */
      CC_STATUS_INIT;
      cc_status.value1 = SET_SRC (body);
      break;

    case CC_INVERT:
      /* The insn is a compare instruction.  */
      CC_STATUS_INIT;
      cc_status.value1 = SET_SRC (body);
      cc_status.flags |= CC_INVERTED;
      break;

    case CC_CLOBBER:
      /* Insn doesn't leave CC in a usable state.  */
      CC_STATUS_INIT;
      break;

    default:
      abort ();
    }
}

/* Return true if OP is a valid call operand.  */

int
call_address_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  return (GET_CODE (op) == SYMBOL_REF || GET_CODE (op) == REG);
}

/* What (if any) secondary registers are needed to move IN with mode
   MODE into a register from in register class CLASS. 

   We might be able to simplify this.  */
enum reg_class
secondary_reload_class (class, mode, in)
     enum reg_class class;
     enum machine_mode mode;
     rtx in;
{
  int regno;

  /* Memory loads less than a full word wide can't have an
     address or stack pointer destination.  They must use
     a data register as an intermediate register.  */
  if (GET_CODE (in) == MEM
      && (mode == QImode || mode == HImode)
      && (class == ADDRESS_REGS || class == SP_REGS))
    return DATA_REGS;

  /* We can't directly load sp + const_int into a data register;
     we must use an address register as an intermediate.  */
  if (class != SP_REGS
      && class != ADDRESS_REGS
      && class != SP_OR_ADDRESS_REGS
      && (in == stack_pointer_rtx
	  || (GET_CODE (in) == PLUS
	      && (XEXP (in, 0) == stack_pointer_rtx
		  || XEXP (in, 1) == stack_pointer_rtx))))
    return ADDRESS_REGS;

  /* Otherwise assume no secondary reloads are needed.  */
  return NO_REGS;
}

int
initial_offset (from, to)
     int from, to;
{
  /* The difference between the argument pointer and the frame pointer
     is the size of the callee register save area.  */
  if (from == ARG_POINTER_REGNUM && to == FRAME_POINTER_REGNUM)
    {
      if (regs_ever_live[2] || regs_ever_live[3]
	  || regs_ever_live[6] || regs_ever_live[7]
	  || frame_pointer_needed)
	return 16;
      else
	return 0;
    }

  /* The difference between the argument pointer and the stack pointer is
     the sum of the size of this function's frame, the callee register save
     area, and the fixed stack space needed for function calls (if any).  */
  if (from == ARG_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    {
      if (regs_ever_live[2] || regs_ever_live[3]
	  || regs_ever_live[6] || regs_ever_live[7]
	  || frame_pointer_needed)
	return (get_frame_size () + 16 
		+ (current_function_outgoing_args_size
		   ? current_function_outgoing_args_size + 4 : 0)); 
      else
	return (get_frame_size ()
		+ (current_function_outgoing_args_size
		   ? current_function_outgoing_args_size + 4 : 0)); 
    }

  /* The difference between the frame pointer and stack pointer is the sum
     of the size of this function's frame and the fixed stack space needed
     for function calls (if any).  */
  if (from == FRAME_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    return (get_frame_size ()
	    + (current_function_outgoing_args_size
	       ? current_function_outgoing_args_size + 4 : 0)); 

  abort ();
}

/* Flush the argument registers to the stack for a stdarg function;
   return the new argument pointer.  */
rtx
mn10300_builtin_saveregs (arglist)
     tree arglist;
{
  rtx offset;
  tree fntype = TREE_TYPE (current_function_decl);
  int argadj = ((!(TYPE_ARG_TYPES (fntype) != 0
                   && (TREE_VALUE (tree_last (TYPE_ARG_TYPES (fntype)))
                       != void_type_node)))
                ? UNITS_PER_WORD : 0);

  if (argadj)
    offset = plus_constant (current_function_arg_offset_rtx, argadj);
  else
    offset = current_function_arg_offset_rtx;

  emit_move_insn (gen_rtx (MEM, SImode, current_function_internal_arg_pointer),
		  gen_rtx (REG, SImode, 0));
  emit_move_insn (gen_rtx (MEM, SImode,
			   plus_constant
			     (current_function_internal_arg_pointer, 4)),
		  gen_rtx (REG, SImode, 1));
  return copy_to_reg (expand_binop (Pmode, add_optab,
				    current_function_internal_arg_pointer,
				    offset, 0, 0, OPTAB_LIB_WIDEN));
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

  /* Figure out the size of the object to be passed.  */
  if (mode == BLKmode)
    size = int_size_in_bytes (type);
  else
    size = GET_MODE_SIZE (mode);

  /* Figure out the alignment of the object to be passed.  */
  align = size;

  cum->nbytes = (cum->nbytes + 3) & ~3;

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

/* Return the number of registers to use for an argument passed partially
   in registers and partially in memory.  */

int
function_arg_partial_nregs (cum, mode, type, named)
     CUMULATIVE_ARGS *cum;
     enum machine_mode mode;
     tree type;
     int named;
{
  int size, align;

  /* We only support using 2 data registers as argument registers.  */
  int nregs = 2;

  /* Figure out the size of the object to be passed.  */
  if (mode == BLKmode)
    size = int_size_in_bytes (type);
  else
    size = GET_MODE_SIZE (mode);

  /* Figure out the alignment of the object to be passed.  */
  align = size;

  cum->nbytes = (cum->nbytes + 3) & ~3;

  /* Don't pass this arg via a register if all the argument registers
     are used up.  */
  if (cum->nbytes > nregs * UNITS_PER_WORD)
    return 0;

  if (cum->nbytes + size <= nregs * UNITS_PER_WORD)
    return 0;

  /* Don't pass this arg via a register if it would be split between
     registers and memory.  */
  if (type == NULL_TREE
      && cum->nbytes + size > nregs * UNITS_PER_WORD)
    return 0;

  return (nregs * UNITS_PER_WORD - cum->nbytes) / UNITS_PER_WORD;
}

/* Output a tst insn.  */
char *
output_tst (operand, insn)
     rtx operand, insn;
{
  rtx temp;
  int past_call = 0;

  /* If we have a data register which is known to be zero throughout
     the function, then use it instead of doing a search.  */
  if (zero_dreg && REGNO_REG_CLASS (REGNO (operand)) == DATA_REGS)
    {
      rtx xoperands[2];
      xoperands[0] = operand;
      xoperands[1] = zero_dreg;

      output_asm_insn ("cmp %1,%0", xoperands);
      return "";
    }

  /* Similarly for address registers.  */
  if (zero_areg && REGNO_REG_CLASS (REGNO (operand)) == ADDRESS_REGS)
    {
      rtx xoperands[2];
      xoperands[0] = operand;
      xoperands[1] = zero_areg;

      output_asm_insn ("cmp %1,%0", xoperands);
      return "";
    }

  /* We can save a byte if we can find a register which has the value
     zero in it.  */
  temp = PREV_INSN (insn);
  while (optimize && temp)
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

	 If it's a call clobbered register, have we past a call?

	 Make sure the register we find isn't the same as ourself;
	 the mn10300 can't encode that.  */
      if (REG_P (SET_DEST (set))
	  && SET_SRC (set) == CONST0_RTX (GET_MODE (SET_DEST (set)))
	  && !reg_set_between_p (SET_DEST (set), temp, insn)
	  && (REGNO_REG_CLASS (REGNO (SET_DEST (set)))
	      == REGNO_REG_CLASS (REGNO (operand)))
	  && REGNO (SET_DEST (set)) != REGNO (operand)
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

int
impossible_plus_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  extern rtx *reg_equiv_mem;
  rtx reg1, reg2;
  
  if (GET_CODE (op) != PLUS)
    return 0;

  if ((XEXP (op, 0) == stack_pointer_rtx)
      && ((REG_P (XEXP (op, 1)) && reg_equiv_mem [REGNO (XEXP (op, 1))])
	  || (GET_CODE (XEXP (op, 1)) == SUBREG
	      && GET_CODE (SUBREG_REG (XEXP (op, 1))) == MEM)))
    return 1;

  if ((XEXP (op, 1) == stack_pointer_rtx)
      && ((REG_P (XEXP (op, 0)) && reg_equiv_mem [REGNO (XEXP (op, 0))])
	  || (GET_CODE (XEXP (op, 0)) == SUBREG
	      && GET_CODE (SUBREG_REG (XEXP (op, 0))) == MEM)))
    return 1;
  return 0;
}
