/* BFD back-end for Alpha COFF files.
   Copyright 1990, 1991, 1992, 1993, 1994, 1995 Free Software Foundation, Inc.
   Written by Cygnus Support.

This file is part of BFD, the Binary File Descriptor library.

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

#include "bfd.h"
#include "sysdep.h"
#include "libbfd.h"
#include "obstack.h"

#include "coff/nt_alpha.h"

#include "coff/internal.h"

#ifdef COFF_WITH_PE
#include "coff/pe.h"
#endif

#include "libcoff.h"

/* A type to hold an instruction */
typedef unsigned long insn_word;

static reloc_howto_type *coff_nt_alpha_rtype_to_howto
  PARAMS ((bfd *, asection *, struct internal_reloc *,
	   struct coff_link_hash_entry *, struct internal_syment *,
	   bfd_vma *));

static boolean alpha_relocate_section
  PARAMS ((bfd *, struct bfd_link_info *, bfd *, asection *, bfd_byte *,
	     struct internal_reloc *, struct internal_syment *, asection **));

static void alpha_find_stubs 
  PARAMS((bfd *, struct bfd_link_info *, asection *));

static boolean alpha_emit_stubs 
  PARAMS((bfd *, struct bfd_link_info *, asection *, struct bfd_link_order *));

/* How to process the various reloc types.  */

static reloc_howto_type *alpha_bfd_reloc_type_lookup
 PARAMS ((bfd *, bfd_reloc_code_real_type));

static bfd_reloc_status_type
reloc_nil PARAMS ((bfd *, arelent *, asymbol *, PTR,
		   asection *, bfd *, char **));

static bfd_reloc_status_type 
   alpha_inline_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));

static bfd_reloc_status_type 
   alpha_refhi_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));

static bfd_reloc_status_type 
   alpha_reflo_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));

static bfd_reloc_status_type
   alpha_pair_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));


static bfd_reloc_status_type 
   alpha_match_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));
static bfd_reloc_status_type 
   alpha_section_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));
static bfd_reloc_status_type 
   alpha_secrel_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));
static bfd_reloc_status_type 
   alpha_longnb_reloc PARAMS ((bfd *abfd, arelent *reloc,
			       asymbol *symbol, PTR data,
			       asection *section, bfd *output_bfd,
			       char **error));

static bfd_reloc_status_type
reloc_nil (abfd, reloc, sym, data, sec, output_bfd, error_message)
     bfd *abfd;
     arelent *reloc;
     asymbol *sym;
     PTR data;
     asection *sec;
     bfd *output_bfd;
     char **error_message;
{
  return bfd_reloc_ok;
}

#define COFF_DEFAULT_SECTION_ALIGNMENT_POWER (2)

/* This is a somewhat educated guess; for the linker it wants to 
   be 0x2000 aligned before it will work, but the MS tools seem
   happy with 0x1000... why???? */
#define COFF_PAGE_SIZE 0x2000

#if 0 /* unused, but for reference */
/* For some reason when using nt_alpha COFF the value stored in the .text
   section for a reference to a common symbol is the value itself plus
   any desired offset.  Ian Taylor, Cygnus Support.  */

/* If we are producing relocateable output, we need to do some
   adjustments to the object file that are not done by the
   bfd_perform_relocation function.  This function is called by every
   reloc type to make any required adjustments.  */

static bfd_reloc_status_type coff_nt_alpha_reloc 
  PARAMS ((bfd *, arelent *, asymbol *, PTR, asection *, bfd *, char **));

static bfd_reloc_status_type
coff_nt_alpha_reloc (abfd, reloc_entry, symbol, data, input_section, output_bfd,
		 error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{
  symvalue diff;

  if (output_bfd == (bfd *) NULL)
    return bfd_reloc_continue;


  if (bfd_is_com_section (symbol->section))
    {
      /* We are relocating a common symbol.  The current value in the
	 object file is ORIG + OFFSET, where ORIG is the value of the
	 common symbol as seen by the object file when it was compiled
	 (this may be zero if the symbol was undefined) and OFFSET is
	 the offset into the common symbol (normally zero, but may be
	 non-zero when referring to a field in a common structure).
	 ORIG is the negative of reloc_entry->addend, which is set by
	 the CALC_ADDEND macro below.  We want to replace the value in
	 the object file with NEW + OFFSET, where NEW is the value of
	 the common symbol which we are going to put in the final
	 object file.  NEW is symbol->value.  */
      diff = symbol->value + reloc_entry->addend;
    }
  else
    {
      /* For some reason bfd_perform_relocation always effectively
	 ignores the addend for a COFF target when producing
	 relocateable output.  This seems to be always wrong for 386
	 COFF, so we handle the addend here instead.  */
      diff = reloc_entry->addend;
    }


#ifdef COFF_WITH_PE
  if (reloc_entry->howto->type == IMAGE_REL_ALPHA_REFLONGNB)
    {
/*      diff -= coff_data(output_bfd)->link_info->pe_info.image_base.value;*/
      abort();
    }
#endif

#define DOIT(x) \
  x = ((x & ~howto->dst_mask) | (((x & howto->src_mask) + diff) & howto->dst_mask))

    if (diff != 0)
      {
	reloc_howto_type *howto = reloc_entry->howto;
	unsigned char *addr = (unsigned char *) data + reloc_entry->address;

	switch (howto->size)
	  {
	  case 0:
	    {
	      char x = bfd_get_8 (abfd, addr);
	      DOIT (x);
	      bfd_put_8 (abfd, x, addr);
	    }
	    break;

	  case 1:
	    {
	      short x = bfd_get_16 (abfd, addr);
	      DOIT (x);
	      bfd_put_16 (abfd, x, addr);
	    }
	    break;

	  case 2:
	    {
	      long x = bfd_get_32 (abfd, addr);
	      DOIT (x);
	      bfd_put_32 (abfd, x, addr);
	    }
	    break;

	  default:
	    abort ();
	  }
      }

  /* Now let bfd_perform_relocation finish everything up.  */
  return bfd_reloc_continue;
}
#endif

#ifdef COFF_WITH_PE
/* Return true if this relocation should
   appear in the output .reloc section. */

static boolean in_reloc_p PARAMS((bfd *, reloc_howto_type *));
static boolean in_reloc_p(abfd, howto)
     bfd * abfd;
     reloc_howto_type *howto;
{
  /* ??? This is highly questionable */
  return ! howto->pc_relative && howto->type != IMAGE_REL_ALPHA_REFLONGNB;
}     
#endif

#ifndef PCRELOFFSET
#define PCRELOFFSET false
#endif

/* In case we're on a 32-bit machine, construct a 64-bit "-1" value
   from smaller values.  Start with zero, widen, *then* decrement.  */
#define MINUS_ONE	(((bfd_vma)0) - 1)

#undef HOWTO
#define HOWTO(C, R,S,B, P, BI, O, SF, NAME, INPLACE, MASKSRC, MASKDST, PC,SIV) \
  {(unsigned)C,R,S,B, P, BI, O,SF,NAME,INPLACE,MASKSRC,MASKDST,PC,SIV}
static reloc_howto_type alpha_howto_table[] =
{
  /* Reloc type 0 is ignored by itself.  However, it appears after a
     GPDISP reloc to identify the location where the low order 16 bits
     of the gp register are loaded.  */
  HOWTO (ALPHA_R_IGNORE,	/* type */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 8,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 reloc_nil,		/* special_function */
	 "IGNORE",		/* name */
	 true,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 true,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* A 32 bit reference to a symbol.  #1 */
  HOWTO (ALPHA_R_REFLONG,	/* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 0,			/* special_function */
	 "REFLONG",		/* name */
	 true,			/* partial_inplace */
	 0xffffffff,		/* src_mask */
	 0xffffffff,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* A 64 bit reference to a symbol.  #2 */
  HOWTO (ALPHA_R_REFQUAD,	/* type */
	 0,			/* rightshift */
	 4,			/* size (0 = byte, 1 = short, 2 = long) */
	 64,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 0,			/* special_function */
	 "REFQUAD",		/* name */
	 true,			/* partial_inplace */
	 MINUS_ONE,		/* src_mask */
	 MINUS_ONE,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* A 32 bit GP relative offset.  This is just like REFLONG except
     that when the value is used the value of the gp register will be
     added in.  */
  HOWTO (ALPHA_R_GPREL32,	/* type #3 */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 0,			/* special_function */
	 "GPREL32",		/* name */
	 true,			/* partial_inplace */
	 0xffffffff,		/* src_mask */
	 0xffffffff,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* Used for an instruction that refers to memory off the GP
     register.  The offset is 16 bits of the 32 bit instruction.  This
     reloc always seems to be against the .lita section.  */
  HOWTO (ALPHA_R_LITERAL,	/* type #4 */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 16,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 0,			/* special_function */
	 "LITERAL",		/* name */
	 true,			/* partial_inplace */
	 0xffff,		/* src_mask */
	 0xffff,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* This reloc only appears immediately following a LITERAL reloc.
     It identifies a use of the literal.  It seems that the linker can
     use this to eliminate a portion of the .lita section.  The symbol
     index is special: 1 means the literal address is in the base
     register of a memory format instruction; 2 means the literal
     address is in the byte offset register of a byte-manipulation
     instruction; 3 means the literal address is in the target
     register of a jsr instruction.  This does not actually do any
     relocation.  */
  HOWTO (ALPHA_R_LITUSE,	/* type #5 */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 reloc_nil,		/* special_function */
	 "LITUSE",		/* name */
	 false,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* Load the gp register.  This is always used for a ldah instruction
     which loads the upper 16 bits of the gp register.  The next reloc
     will be an IGNORE reloc which identifies the location of the lda
     instruction which loads the lower 16 bits.  The symbol index of
     the GPDISP instruction appears to actually be the number of bytes
     between the ldah and lda instructions.  This gives two different
     ways to determine where the lda instruction is; I don't know why
     both are used.  The value to use for the relocation is the
     difference between the GP value and the current location; the
     load will always be done against a register holding the current
     address.  */
  HOWTO (ALPHA_R_GPDISP,	/* type #6 */
	 16,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 16,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 reloc_nil,		/* special_function */
	 "GPDISP",		/* name */
	 true,			/* partial_inplace */
	 0xffff,		/* src_mask */
	 0xffff,		/* dst_mask */
	 true,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* A 21 bit branch.  The native assembler generates these for
     branches within the text segment, and also fills in the PC
     relative offset in the instruction.  */
  HOWTO (ALPHA_R_BRADDR,	/* type #7 */
	 2,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 21,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 0,			/* special_function */
	 "BRADDR",		/* name */
	 true,			/* partial_inplace */
	 0x1fffff,		/* src_mask */
	 0x1fffff,		/* dst_mask */
	 true,			/* pcrel_offset; different on NT */
	 false),                /* symndx is value */

  /* A hint for a jump to a register.  */
  HOWTO (ALPHA_R_HINT,		/* type #8 */
	 2,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 14,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "HINT",		/* name */
	 true,			/* partial_inplace */
	 0x3fff,		/* src_mask */
	 0x3fff,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

#ifndef COFF_WITH_PE  /* [ */
  /* 16 bit PC relative offset.  */
  HOWTO (ALPHA_R_SREL16,	/* type #9 */
	 0,			/* rightshift */
	 1,			/* size (0 = byte, 1 = short, 2 = long) */
	 16,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 0,			/* special_function */
	 "SREL16",		/* name */
	 true,			/* partial_inplace */
	 0xffff,		/* src_mask */
	 0xffff,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* 32 bit PC relative offset.  */
  HOWTO (ALPHA_R_SREL32,	/* type #10 */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 0,			/* special_function */
	 "SREL32",		/* name */
	 true,			/* partial_inplace */
	 0xffffffff,		/* src_mask */
	 0xffffffff,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* A 64 bit PC relative offset.  #11 */
  HOWTO (ALPHA_R_SREL64,	/* type */
	 0,			/* rightshift */
	 4,			/* size (0 = byte, 1 = short, 2 = long) */
	 64,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 0,			/* special_function */
	 "SREL64",		/* name */
	 true,			/* partial_inplace */
	 MINUS_ONE,		/* src_mask */
	 MINUS_ONE,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* Push a value on the reloc evaluation stack.  */
  HOWTO (ALPHA_R_OP_PUSH,	/* type #12 */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 0,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "OP_PUSH",		/* name */
	 false,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* Store the value from the stack at the given address.  Store it in
     a bitfield of size r_size starting at bit position r_offset.  */
  HOWTO (ALPHA_R_OP_STORE,	/* type #13 */
	 0,			/* rightshift */
	 4,			/* size (0 = byte, 1 = short, 2 = long) */
	 64,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "OP_STORE",		/* name */
	 false,			/* partial_inplace */
	 0,			/* src_mask */
	 MINUS_ONE,		/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* Subtract the reloc address from the value on the top of the
     relocation stack.  */
  HOWTO (ALPHA_R_OP_PSUB,	/* type #14 */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 0,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "OP_PSUB",		/* name */
	 false,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* Shift the value on the top of the relocation stack right by the
     given value.  */
  HOWTO (ALPHA_R_OP_PRSHIFT,	/* type #15 */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 0,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "OP_PRSHIFT",		/* name */
	 false,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 false,			/* pcrel_offset */
	 false),                /* symndx is value */

  /* Adjust the GP value for a new range in the object file.  */
  HOWTO (ALPHA_R_GPVALUE,	/* type #16 */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 0,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "GPVALUE",		/* name */
	 false,			/* partial_inplace */
	 0,			/* src_mask */
	 0,			/* dst_mask */
	 false			/* pcrel_offset */
	 false),                /* symndx is value */

#else /* ][ */  /* COFF_WITH_PE (==NT) */

  /* 32-bit address spread over 2 instructions; see absolute or match */
  HOWTO (IMAGE_REL_ALPHA_INLINE_REFLONG,   /* type #9 */             
	 0,	                /* rightshift */                           
	 1,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 16,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_signed, /* complain_on_overflow */
	 alpha_inline_reloc,	/* special_function */                     
	 "INLINE",              /* name */
	 true,	                /* partial_inplace */                      
	 0xffffffff,	        /* src_mask */                             
	 0xffffffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 false),                /* symndx is value */

  /* High portion of a 32 bit address */
  HOWTO (IMAGE_REL_ALPHA_REFHI,   /* type #10 */             
	 0,	                /* rightshift */                           
	 1,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 16,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_signed, /* complain_on_overflow */
	 alpha_refhi_reloc,	/* special_function */                     
	 "REFHI",               /* name */
	 true,	                /* partial_inplace */                      
	 0xffffffff,	        /* src_mask */                             
	 0xffffffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 false),                /* symndx is value */

  /* Low portion of a 32 bit address; the high part comes in with REFHI */
  HOWTO (IMAGE_REL_ALPHA_REFLO, /* type #11 */             
	 0,	                /* rightshift */                           
	 1,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 16,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_dont, /* complain_on_overflow */
	 alpha_reflo_reloc,	/* special_function */                     
	 "REFLO",               /* name */
	 true,	                /* partial_inplace */                      
	 0xffff,	        /* src_mask */                             
	 0xffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 false),                /* symndx is value */

  /* Connects REFHI and REFLO; REFHI is mostly a placeholder in this
     table; this entry does the work */
  HOWTO (IMAGE_REL_ALPHA_PAIR,  /* type #12 */             
	 16,	                /* rightshift */                           
	 1,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 16,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_unsigned, /* complain_on_overflow */
	 alpha_pair_reloc,        /* special_function */                     
	 "PAIR",                /* name */
	 true,	                /* partial_inplace */                      
	 0xffff,	        /* src_mask */                             
	 0xffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 true),                 /* symndx is value */

  /* Connects with INLINE_REFLOG */
  HOWTO (IMAGE_REL_ALPHA_MATCH, /* type #13 */             
	 0,	                /* rightshift */                           
	 1,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 16,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_signed, /* complain_on_overflow */
	 alpha_match_reloc,     /* special_function */                     
	 "MATCH",               /* name */
	 true,	                /* partial_inplace */                      
	 0xffffffff,	        /* src_mask */                             
	 0xffffffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 false),                /* symndx is value */

  /* section header number */
  HOWTO (IMAGE_REL_ALPHA_SECTION,/* type #14 */             
	 0,	                /* rightshift */                           
	 2,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 32,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_signed, /* complain_on_overflow */
	 alpha_section_reloc,     /* special_function */                     
	 "SECTION",             /* name */
	 true,	                /* partial_inplace */                      
	 0xffffffff,	        /* src_mask */                             
	 0xffffffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 false),                /* symndx is value */

  /* va of containing section (as in an image sectionhdr) */
  HOWTO (IMAGE_REL_ALPHA_SECREL,/* type #15 */             
	 0,	                /* rightshift */                           
	 2,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 32,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_signed, /* complain_on_overflow */
	 alpha_secrel_reloc,    /* special_function */                     
	 "SECREL",              /* name */
	 true,	                /* partial_inplace */                      
	 0xffffffff,	        /* src_mask */                             
	 0xffffffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 false),                /* symndx is value */


  /* 32-bit addr w/ image base */
  HOWTO (IMAGE_REL_ALPHA_REFLONGNB,/* type */             
	 0,	                /* rightshift */                           
	 2,	                /* size (0 = byte, 1 = short, 2 = long) */ 
	 32,	                /* bitsize */                   
	 false,	                /* pc_relative */                          
	 0,	                /* bitpos */                               
	 complain_overflow_signed, /* complain_on_overflow */
	 alpha_longnb_reloc,    /* special_function */
	 "ADDR32NB",            /* name */
	 true,	                /* partial_inplace */                      
	 0xffffffff,	        /* src_mask */                             
	 0xffffffff,        	/* dst_mask */                             
	 false,                 /* pcrel_offset */
	 false),                /* symndx is value */
#endif /* ] */
};

/* Turn a howto into a reloc  nunmber */

#define SELECT_RELOC(x,howto) { x.r_type = howto->type; }
#define BADMAG(x) NT_ALPHABADMAG(x)
#define NT_ALPHA 1			/* Customize coffcode.h */

#define RTYPE2HOWTO(cache_ptr, dst) \
	    (cache_ptr)->howto = alpha_howto_table + (dst)->r_type;

/* For 386 COFF a STYP_NOLOAD | STYP_BSS section is part of a shared
   library.  On some other COFF targets STYP_BSS is normally
   STYP_NOLOAD.  */
#define BSS_NOLOAD_IS_SHARED_LIBRARY

/* Compute the addend of a reloc.  If the reloc is to a common symbol,
   the object file contains the value of the common symbol.  By the
   time this is called, the linker may be using a different symbol
   from a different object file with a different value.  Therefore, we
   hack wildly to locate the original symbol from this file so that we
   can make the correct adjustment.  This macro sets coffsym to the
   symbol from the original file, and uses it to set the addend value
   correctly.  If this is not a common symbol, the usual addend
   calculation is done, except that an additional tweak is needed for
   PC relative relocs.
   FIXME: This macro refers to symbols and asect; these are from the
   calling function, not the macro arguments.  */

#define CALC_ADDEND(abfd, ptr, reloc, cache_ptr)		\
  {								\
    coff_symbol_type *coffsym = (coff_symbol_type *) NULL;	\
    if (ptr && bfd_asymbol_bfd (ptr) != abfd)			\
      coffsym = (obj_symbols (abfd)				\
	         + (cache_ptr->sym_ptr_ptr - symbols));		\
    else if (ptr)						\
      coffsym = coff_symbol_from (abfd, ptr);			\
    if (coffsym != (coff_symbol_type *) NULL			\
	&& coffsym->native->u.syment.n_scnum == 0)		\
      cache_ptr->addend = - coffsym->native->u.syment.n_value;	\
    else if (ptr && bfd_asymbol_bfd (ptr) == abfd		\
	     && ptr->section != (asection *) NULL)		\
      cache_ptr->addend = - (ptr->section->vma + ptr->value);	\
    else							\
      cache_ptr->addend = 0;					\
    if (ptr && alpha_howto_table[reloc.r_type].pc_relative)	\
      cache_ptr->addend += asect->vma;				\
  }

/* we use our own relocate section */
#define coff_relocate_section alpha_relocate_section

/* Our own branch stubs analysis and emitting routine, too */
#define coff_bfd_find_stubs alpha_find_stubs
#define coff_bfd_emit_stubs alpha_emit_stubs

static reloc_howto_type *
coff_nt_alpha_rtype_to_howto (abfd, sec, rel, h, sym, addendp)
     bfd *abfd;
     asection *sec;
     struct internal_reloc *rel;
     struct coff_link_hash_entry *h;
     struct internal_syment *sym;
     bfd_vma *addendp;
{

  reloc_howto_type *howto;

  if ( rel->r_type > sizeof(alpha_howto_table)/sizeof(reloc_howto_type))
      abort();
  howto = alpha_howto_table + rel->r_type;

#ifdef COFF_WITH_PE
  *addendp = 0;
#endif

  if (howto->pc_relative)
    *addendp += sec->vma;

  if (sym != NULL && sym->n_scnum == 0 && sym->n_value != 0)
    {
      /* This is a common symbol.  The section contents include the
	 size (sym->n_value) as an addend.  The relocate_section
	 function will be adding in the final value of the symbol.  We
	 need to subtract out the current size in order to get the
	 correct result.  */
 
      BFD_ASSERT (h != NULL);


#ifndef COFF_WITH_PE
      /* I think we *do* want to bypass this.  If we don't, I have seen some data
	 parameters get the wrong relcation address.  If I link two versions
	 with and without this section bypassed and then do a binary comparison,
	 the addresses which are different can be looked up in the map.  The 
	 case in which this section has been bypassed has addresses which correspond
	 to values I can find in the map */
      *addendp -= sym->n_value;
#endif
    }

  /* If the output symbol is common (in which case this must be a
     relocateable link), we need to add in the final size of the
     common symbol.  */
  if (h != NULL && h->root.type == bfd_link_hash_common) 
    *addendp += h->root.u.c.size;


#ifdef COFF_WITH_PE
  if (howto->pc_relative)
    *addendp -= sizeof(insn_word);

  if (rel->r_type == IMAGE_REL_ALPHA_REFLONGNB)
    {
      *addendp -= pe_data(sec->output_section->owner)->pe_opthdr.ImageBase;
    }
#endif

  return howto;
}


#define coff_bfd_reloc_type_lookup alpha_bfd_reloc_type_lookup

static reloc_howto_type *alpha_bfd_reloc_type_lookup PARAMS((bfd*, bfd_reloc_code_real_type));

static reloc_howto_type *
alpha_bfd_reloc_type_lookup (abfd, code)
     bfd *abfd;
     bfd_reloc_code_real_type code;
{
  int alpha_type;

  switch (code)
    {
    case BFD_RELOC_32:
    case BFD_RELOC_CTOR:   /* refers to constructor table size */
      alpha_type = ALPHA_R_REFLONG;
      break;
    case BFD_RELOC_64:
      alpha_type = ALPHA_R_REFQUAD;
      break;
    case BFD_RELOC_GPREL32:
      alpha_type = ALPHA_R_GPREL32;
      break;
    case BFD_RELOC_ALPHA_LITERAL:
      alpha_type = ALPHA_R_LITERAL;
      break;
    case BFD_RELOC_ALPHA_LITUSE:
      alpha_type = ALPHA_R_LITUSE;
      break;
    case BFD_RELOC_ALPHA_GPDISP_HI16:
      alpha_type = ALPHA_R_GPDISP;
      break;
    case BFD_RELOC_ALPHA_GPDISP_LO16:
      alpha_type = ALPHA_R_IGNORE;
      break;
    case BFD_RELOC_23_PCREL_S2:
      alpha_type = ALPHA_R_BRADDR;
      break;
    case BFD_RELOC_ALPHA_HINT:
      alpha_type = ALPHA_R_HINT;
      break;
#ifdef COFF_WITH_PE
    case BFD_RELOC_ALPHA_PAIR:
      alpha_type = IMAGE_REL_ALPHA_PAIR;
      break;
    case BFD_RELOC_ALPHA_REFHI:
      alpha_type = IMAGE_REL_ALPHA_REFHI;
      break;
    case BFD_RELOC_ALPHA_REFLO:
      alpha_type = IMAGE_REL_ALPHA_REFLO;
      break;
    case BFD_RELOC_RVA:  /* added bob@guiduck.com 09-30-98 */
      alpha_type = IMAGE_REL_ALPHA_REFLONGNB;
      break;
    /* There are others, but no indication yet that they are used */
#else
    case BFD_RELOC_16_PCREL:
      alpha_type = ALPHA_R_SREL16;
      break;
    case BFD_RELOC_32_PCREL:
      alpha_type = ALPHA_R_SREL32;
      break;
    case BFD_RELOC_64_PCREL:
      alpha_type = ALPHA_R_SREL64;
      break;
#if 0
    case ???:
      alpha_type = ALPHA_R_OP_PUSH;
      break;
    case ???:
      alpha_type = ALPHA_R_OP_STORE;
      break;
    case ???:
      alpha_type = ALPHA_R_OP_PSUB;
      break;
    case ???:
      alpha_type = ALPHA_R_OP_PRSHIFT;
      break;
    case ???:
      alpha_type = ALPHA_R_GPVALUE;
      break;
#endif
#endif
    default:
      return (reloc_howto_type *) NULL;
    }

  return &alpha_howto_table[alpha_type];
}


#define coff_rtype_to_howto coff_nt_alpha_rtype_to_howto

#include "coffcode.h"

static const bfd_target * nt_alpha_coff_object_p PARAMS((bfd *));

static const bfd_target *
nt_alpha_coff_object_p(a)
     bfd *a;
{
  return coff_object_p(a);
}

/* The length, in words, of a stub branch */
#define STUB_WORDS 4

const bfd_target
#ifdef TARGET_SYM
  TARGET_SYM =
#else
  nt_alpha_vec =
#endif
{
#ifdef TARGET_NAME
  TARGET_NAME,
#else
  "coff-alpha",			/* name */
#endif
  bfd_target_coff_flavour,
  BFD_ENDIAN_LITTLE,		/* data byte order is little */
  BFD_ENDIAN_LITTLE,		/* header byte order is little */
  0x3ffffb,			/* Jump span; since the span is w.r.t.						   the updated PC, we back off one instruction
				   so backwards branches are always in range.
				   (Not worth the trouble to fix it inline,
				   and makes the code less general.) */
  STUB_WORDS*sizeof(insn_word),	/* size of stub branch */
				/* 12 bytes generated, but to preserve
				   cache alignment, call it 16 */
  4,				/* alignment of first stub (power of 2) */
  COFF_PAGE_SIZE,		/* page size */

  (HAS_RELOC | EXEC_P |		/* object flags */
   HAS_LINENO | HAS_DEBUG |
   HAS_SYMS | HAS_LOCALS | WP_TEXT | D_PAGED),

  (SEC_HAS_CONTENTS | SEC_ALLOC /* section flags */
     | SEC_LOAD | SEC_RELOC | SEC_READ
     | SEC_READONLY | SEC_CODE | SEC_DATA | SEC_EXEC | SEC_WRITE),
  /* COFF_WITH_PE added
   * | SEC_LINK_ONCE | SEC_LINK_DUPLICATES),
   * but there doesn't seem to be any reason for that; removed because
   * it was causing problems, and it certainly doesn't apear to be
   * needed */

#ifdef TARGET_UNDERSCORE
  TARGET_UNDERSCORE,		/* leading underscore */
#else
  0,				/* leading underscore */
#endif
  '/',				/* ar_pad_char */
  15,				/* ar_max_namelen */

  bfd_getl64, bfd_getl_signed_64, bfd_putl64,
     bfd_getl32, bfd_getl_signed_32, bfd_putl32,
     bfd_getl16, bfd_getl_signed_16, bfd_putl16, /* data */
  bfd_getl64, bfd_getl_signed_64, bfd_putl64,
     bfd_getl32, bfd_getl_signed_32, bfd_putl32,
     bfd_getl16, bfd_getl_signed_16, bfd_putl16, /* hdrs */

/* Note that we allow an object file to be treated as a core file as well. */
    {_bfd_dummy_target, nt_alpha_coff_object_p, /* bfd_check_format */
       bfd_generic_archive_p, nt_alpha_coff_object_p},
    {bfd_false, coff_mkobject, _bfd_generic_mkarchive, /* bfd_set_format */
       bfd_false},
    {bfd_false, coff_write_object_contents, /* bfd_write_contents */
       _bfd_write_archive_contents, bfd_false},

     BFD_JUMP_TABLE_GENERIC (coff),
     BFD_JUMP_TABLE_COPY (coff),
     BFD_JUMP_TABLE_CORE (_bfd_nocore),
     BFD_JUMP_TABLE_ARCHIVE (_bfd_archive_coff),
     BFD_JUMP_TABLE_SYMBOLS (coff),
     BFD_JUMP_TABLE_RELOCS (coff),
     BFD_JUMP_TABLE_WRITE (coff),
     BFD_JUMP_TABLE_LINK (coff),
     BFD_JUMP_TABLE_DYNAMIC (_bfd_nodynamic),

  COFF_SWAP_TABLE,
};


/* We assume that REFHI is always immediately followed by a PAIR, and
   PAIR only follows a REFHI */
static bfd_vma lastrefhi_relocation;
static bfd_byte *lastrefhi_addr = 0;

static bfd_reloc_status_type
alpha_refhi_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{
  bfd_reloc_status_type ret;
  bfd_vma relocation;

  /* If we're relocating, and this an external symbol, we don't want
     to change anything.  */
  if (output_bfd != (bfd *) NULL
      && (symbol->flags & BSF_SECTION_SYM) == 0
      && reloc_entry->addend == 0)
    {
      lastrefhi_addr = (bfd_byte *) -1;
      return bfd_reloc_ok;
    }

  if (reloc_entry->address > input_section->_cooked_size)
    {
      lastrefhi_addr = (bfd_byte *) -1;
      return bfd_reloc_outofrange;
    }

  ret = bfd_reloc_ok;
  if (bfd_is_und_section (symbol->section)
      && output_bfd == (bfd *) NULL)
    ret = bfd_reloc_undefined;

  if (bfd_is_com_section (symbol->section))
    relocation = 0;
  else
    relocation = symbol->value;

  relocation += symbol->section->output_section->vma;
  relocation += symbol->section->output_offset;
  /* we ignore addend here... both REFHI and PAIR will get whatever addend
     modifications apply; if we used THIS addend, we'd apply the addend
     modifications twice.  (Since relocations coming from a .o file have
     the symbol encoded in the REFHI and the offset in the PAIR, 
     it's the REFHI addend we should ignore.) */
  /* relocation += reloc_entry->addend; */
  /* Save the information, and let REFLO do the actual relocation.  */
  lastrefhi_addr = (bfd_byte *)data + reloc_entry->address;
  lastrefhi_relocation = relocation;

  reloc_entry->addend = 0;  /* just for sanity's sake */

  return ret;
}

static bfd_reloc_status_type
alpha_pair_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{

  insn_word insn;
  bfd_vma val;

  if (lastrefhi_addr == (bfd_byte *)-1) 
    {
      /* we skipped the last REFHI, so skip this too */
      lastrefhi_addr = NULL;
      return bfd_reloc_ok;
    }

  if (lastrefhi_addr != (bfd_byte *)data + reloc_entry->address) 
    {
      abort();
    }

  /* Do the REFHI relocation.  Note that we actually don't
     need to know anything about the REFLO itself, except
     where to find the low 16 bits of the addend needed by the
     REFHI.  */

  insn = bfd_get_32 (abfd, lastrefhi_addr);
  val = ((insn & 0xffff) << 16) + reloc_entry->addend + lastrefhi_relocation;

  /* If the calculation above yeilds a number that when decaputated
     to 16 bits would be negative, we need to bump the high order
     portion by 1 so that when the instructions are executed,
     the result is right because second instruction will do signed
     arithmetic on the value loaded by the first one.  The
     REFLO relocation will perform the same calculation as above
     (but inside _bfd_final_link_relocate) except that the high
     order portion from this instruction won't be there.  However,
     the result will also be trimmed to 16 bits, and the resulting
     low 16 bits should be the same as those computed here */

  if ((val & 0x8000) != 0)
    val = val + 0x10000;

  insn = (insn &~ 0xffff) | ((val >> 16) & 0xffff);
  bfd_put_32 (abfd, insn, lastrefhi_addr);

  /* We took care of the REFHI here, so the caller needn't do anything
     to it.  As far as the PAIR relocation, we need to adjust the 
     relocation itself to contain the new offset */

  reloc_entry->addend = val&0xffff;;

  return bfd_reloc_ok;
}

static bfd_reloc_status_type
alpha_reflo_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{

  insn_word insn;
  bfd_vma val;
  unsigned long relocation;

  /* REFLO and PAIR are VERY similar; the major difference is that
     the whole idea of a "high part" is just ignored, and the result
     goes back into the instruction */

  /* If we're relocating, and this an external symbol, we don't want
     to change anything.  */
  if (output_bfd != (bfd *) NULL
      && (symbol->flags & BSF_SECTION_SYM) == 0
      && reloc_entry->addend == 0)
    {
      return bfd_reloc_ok;
    }

  if (reloc_entry->address > input_section->_cooked_size)
    return bfd_reloc_outofrange;

  if (bfd_is_com_section (symbol->section))
    relocation = 0;
  else
    relocation = symbol->value;

  relocation += symbol->section->output_section->vma;
  relocation += symbol->section->output_offset;
  relocation += reloc_entry->addend;

  insn = bfd_get_32 (abfd, (bfd_byte *)data + reloc_entry->address);
  val = (insn & 0xffff) + relocation;

  insn = (insn &~ 0xffff) | (val & 0xffff);
  bfd_put_32 (abfd, insn, (bfd_byte *)data + reloc_entry->address);

  reloc_entry->addend = 0;

  return bfd_reloc_ok;
}

static bfd_reloc_status_type
alpha_section_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{
    /* ??? */
    abort();
    return 0;  /* shut up the compiler */
}

static bfd_reloc_status_type
alpha_secrel_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{
    abort();
    return 0;  /* shut up the compiler */
}

static bfd_reloc_status_type
alpha_longnb_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{
    /* it may be that in this case, no function is the right answer, but... */
    /* ??? */
#if 0  /* bob@guiduck.com 09/30/98 */
    abort();
#endif
    return 0;  /* shut up the compiler */
}

static bfd_reloc_status_type
alpha_inline_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{
    /* ??? */
    abort();
    return 0;  /* shut up the compiler */
}

static bfd_reloc_status_type
alpha_match_reloc (abfd,
		  reloc_entry,
		  symbol,
		  data,
		  input_section,
		  output_bfd,
		  error_message)
     bfd *abfd;
     arelent *reloc_entry;
     asymbol *symbol;
     PTR data;
     asection *input_section;
     bfd *output_bfd;
     char **error_message;
{
    /* ??? */
    abort();
    return 0;  /* shut up the compiler */
}

/* Check if values are in range.  Conceptually: abs(a-b)<d, but works
   for unsigned */
#define INRANGE(a,b,d) (((a)<(b)?((b)-(a)):((a)-(b))) < (d))

/* Relocate a section; we can't use bfd_generic_relocate_section because
   of REFHI/REFLO/PAIR and long branches */

static boolean
alpha_relocate_section (output_bfd, info, input_bfd,
				    input_section, contents, relocs, syms,
				    sections)
     bfd *output_bfd;
     struct bfd_link_info *info;
     bfd *input_bfd;
     asection *input_section;
     bfd_byte *contents;
     struct internal_reloc *relocs;
     struct internal_syment *syms;
     asection **sections;
{
  struct internal_reloc *rel;
  struct internal_reloc *relend;
  long refhi_symndx = -1;
  bfd_vma ImageBase = pe_data(output_bfd)->pe_opthdr.ImageBase;

  rel = relocs;
  relend = rel + input_section->reloc_count;
  for (; rel < relend; rel++)
    {
      long symndx;
      struct coff_link_hash_entry *h;
      struct internal_syment *sym;
      bfd_vma addend;
      bfd_vma val;
      reloc_howto_type *howto;
      bfd_reloc_status_type rstat;
      int symclass;
      asection *sec;
      boolean has_ext;

      switch (rel->r_type)
	{
        case IMAGE_REL_ALPHA_PAIR:
	  BFD_ASSERT(refhi_symndx != -1);
	  symndx = refhi_symndx;
	  /* just to add to the excitement....  _bfd_coff_link_input_bfd
	     needs to know that the relocation's symndx value isn't really
	     a symndx if it's going to write the relocations out.  We
	     tell it here (and update the synndx at the same time).  See
	     cofflink.c for more on this.  Also, since this could occur
	     in a relocateable link, and we might simply skip some
	     relocations, we need to do it here */
	  rel->r_size = 1;
	  break;
        case IMAGE_REL_ALPHA_REFHI:
	  refhi_symndx = rel->r_symndx;
	  continue;  /* That's all we need to do for this time! */
	default:
	  symndx = rel->r_symndx;
	  break;
	}

      if (symndx == -1)
	{
	  h = NULL;
	  sym = NULL;
	}
      else
	{    
          symclass = bfd_coff_sym_is_global(input_bfd, &syms[symndx]);
	  if (symclass == SYM_SECTION_DEFINITION) 
	    {
	      /* a ref to a section definition wants to just use the section
		 information.  All other references want to proceed by
		 getting the hash.  Here we have the ref to def'n;
		 this issue becomes critical after section $-name sorts,
		 because we really want the section beginning, not some
		 random chunk of the section. */
	      h = NULL;
	    }
	  else
	    {
	      /* If this is a relocateable link, and we're dealing with
		 a relocation against a symbol (rather than a section),
		 leave it alone */
	      if (info->relocateable)
		continue;
	      /* not a ref to a section definition */
	      h = obj_coff_sym_hashes (input_bfd)[symndx];
	    }
	    sym = syms + symndx;
	}

      /* COFF treats common symbols in one of two ways.  Either the
         size of the symbol is included in the section contents, or it
         is not.  We assume that the size is not included, and force
         the rtype_to_howto function to adjust the addend as needed.  */

      if (sym != NULL && sym->n_scnum != 0)
	addend = - sym->n_value;
      else
	addend = 0;

      howto = bfd_coff_rtype_to_howto (input_bfd, input_section, rel, h,
				       sym, &addend);
      if (howto == NULL)
	return false;

      /* If we are doing a relocateable link, then we can just ignore
         a PC relative reloc that is pcrel_offset.  It will already
         have the correct value.  If this is not a relocateable link,
         then we should ignore the symbol value.  */
      if (howto->pc_relative && howto->pcrel_offset)
	{
	  if (info->relocateable)
	    continue;
#if 0 /* see comment above... rtype_to_howto should do this as needed */
/* ???  Adding/subtracting/adding/subtracting... sym->n_value seems
        rather pointless; someone at FSF or Cygnus who understands most
	of the relocatable formats should try to find a better way
	because not only is this wasteful, its VERY fragile.  */
	  if (sym != NULL && sym->n_scnum != 0)
	    addend += sym->n_value;
#endif
	}

      has_ext = false;

      val = 0;

      if (h == NULL)
	{
	  if (symndx == -1)
	    {
	      sec = bfd_abs_section_ptr;
	      val = 0;
	    }
	  else
	    {
	      sec = sections[symndx];
              val = (sec->output_section->vma
		     + sec->output_offset
		     + sym->n_value
		     - sec->vma);
	    }
	}
      else
	{
	  if (h->root.type == bfd_link_hash_defined_ext
	      || h->root.type == bfd_link_hash_defweak_ext)
	    {
	      sec = h->root.u.defext.perm->section;
	      val = (h->root.u.defext.perm->value
		 + sec->output_section->vma
		 + sec->output_offset);
	      has_ext = true;
	    }

	  else if (h->root.type == bfd_link_hash_defined
	      || h->root.type == bfd_link_hash_defweak
	      || h->root.type == bfd_link_hash_section)
	    {
	      sec = h->root.u.def.section;
	      val = (h->root.u.def.value
		 + sec->output_section->vma
		 + sec->output_offset);
	    }

	  else if (! info->relocateable)
	    {
	      if (! ((*info->callbacks->undefined_symbol)
		     (info, h->root.root.string, input_bfd, input_section,
		      rel->r_vaddr - input_section->vma)))
		return false;
	    }
	}

      /* Branches have limited spans, and if the target is out of range
	 we need to jump to an in-range stub.  Eariler passes should
	 have created in-range stubs for every branch.  If the real
	 value is out of range, we search for a stub, and substitute its
	 address into VAL.  (It's an internal error for a branch to be
	 out of range.)   This only makes sense for final links,
	 and when has_ext is set (if not relocatable, has_ext can't
	 be set, so we only need one test).  If has_ext didn't get
	 set when it should have been, we have an internal error that will
	 show up as an unreachable branch.  We put has_ext first, because
	 for most (statistical) cases it will be false. */
      if (has_ext && rel->r_type == ALPHA_R_BRADDR)
	{
	   bfd_vma currPC;
	   insn_word insn;

	   /* There's a possiblity that somehow, someway, someone generated
	      a BRADDR with an offset... we can't handle that, but failing
	      silently would be really nasty. */

	   insn = bfd_get_32 (input_bfd, 
	            contents + rel->r_vaddr - input_section->vma);

	   if ((insn & 0x1fffff) != 0 || addend != -4) /* -4 for adjusted PC */
	     {
		  (*_bfd_error_handler)
		    ("%s: branch at 0x%lx in section `%s' has offset",
		     bfd_get_filename (input_bfd),
		     (unsigned long) rel->r_vaddr,
		     bfd_get_section_name (input_bfd, input_section));
	     }

	   currPC = rel->r_vaddr + input_section->output_section->vma
	                         + input_section->output_offset;
	   /* A branch address... it could be out of range and we have
	      to hunt up a stub. ...careful, unsigned distances... */
	   if (!INRANGE(currPC, val, info->jump_span))
	     {
		struct extra_addresses *s;

		/* out of range; we have to find an in-range stub */
		s = h->root.u.defext.perm->extras;
		while (s != NULL)
		  {
		    if (INRANGE(currPC, s->addr, info->jump_span))
		      {
			 val = s->addr;
			 goto match; /* that is, continue outer loop */;
		      }
		    s=s->next;
		  }
		/* there's always supposed to be one!  (Prior stages are
		   buggy if not.) */
		abort();
	     }
	     match:;
	}

      if (!howto->pc_relative && !bfd_is_abs_section(sec->output_section))
          addend += ImageBase;

      if (info->base_file)
	{
	  /* Emit a reloc if the backend thinks it needs it. */
	  if (sym && pe_data(output_bfd)->in_reloc_p(output_bfd, howto))
	    {
	      /* relocation to a symbol in a section which
		 isn't absolute - we output the address here 
		 to a file; however, to do this right we need a type */
	      bfd_vma addr = rel->r_vaddr 
		- input_section->vma 
		+ input_section->output_offset 
		+ input_section->output_section->vma;
	      fwrite (&addr, 1, sizeof(bfd_vma), (FILE *) info->base_file);
	    }
	}

      switch(rel->r_type)
	{
	case IMAGE_REL_ALPHA_REFHI:
	  abort();  /* shouldn't get here because of switch above */

	case IMAGE_REL_ALPHA_PAIR:
	  /* the symndx (and conseuently val) being used came from the 
	     prior REFHI; we contribute the low-order bits of the addend
	     via the content of the symbol table index field */
          {
	  insn_word insn;

	  insn = bfd_get_32 (input_bfd, 
	            contents + rel->r_vaddr - input_section->vma);

	  val = val + ((insn & 0xffff) << 16) + rel->r_symndx + addend;

	  /* If the calculation above yields a number that when decaputated
	     to 16 bits would be negative, we need to bump the high order
	     portion by 1 so that when the instructions are executed,
	     the result is right because second instruction will do signed
	     arithmetic on the value loaded by the first one.  The
	     REFLO relocation will perform the same calculation as above
	     (but inside _bfd_final_link_relocate) except that the high
	     order portion from this instruction won't be there.  However,
	     the result will also be trimmed to 16 bits, and the resulting
	     low 16 bits should be the same as those computed here */

	  if ((val & 0x8000) != 0)
	    val += 0x10000;

	  insn = (insn &~ 0xffff) | ((val >> 16) & 0xffff);
	  bfd_put_32 (input_bfd, (bfd_vma) insn,
		      contents + rel->r_vaddr - input_section->vma);

	  rel->r_symndx = ((val & 0xffff)<<16)>>16;  /* the new low order bits */

	  rstat = bfd_reloc_ok;
	  }
	  break;

        default:
          rstat = _bfd_final_link_relocate (howto, input_bfd, input_section,
					contents,
					rel->r_vaddr - input_section->vma,
					val, addend);
	  break;
	}

      switch (rstat)
	{
	default:
	  abort ();
	case bfd_reloc_ok:
	  break;
	case bfd_reloc_outofrange:
	  (*_bfd_error_handler)
	    ("%s: bad reloc address 0x%lx in section `%s'",
	     bfd_get_filename (input_bfd),
	     (unsigned long) rel->r_vaddr,
	     bfd_get_section_name (input_bfd, input_section));
	  return false;
	case bfd_reloc_overflow:
	  {
	    const char *name;
	    char buf[SYMNMLEN + 1];

	    if (symndx == -1)
	      name = "*ABS*";
	    else if (h != NULL)
	      name = h->root.root.string;
	    else
	      {
		name = _bfd_coff_internal_syment_name (input_bfd, sym, buf);
		if (name == NULL)
		  return false;
	      }

	    if (! ((*info->callbacks->reloc_overflow)
		   (info, name, howto->name, (bfd_vma) 0, input_bfd,
		    input_section, rel->r_vaddr - input_section->vma)))
	      return false;
	  }
	}
    }
  return true;
}

/*  Parse relocations looking for out of range branches */
static void
alpha_find_stubs (output_bfd, info, input_section)
     bfd *output_bfd;
     struct bfd_link_info *info;
     asection *input_section;
{ 
  struct internal_reloc *rel;
  struct internal_reloc *relend;
  bfd *input_bfd = input_section->owner;
  bfd_vma lastseen = 0;
  static struct extended_def_vol *stub_list_tail;

  if ((input_section->flags & SEC_RELOC) == 0
      || input_section->reloc_count == 0)
     /* nothing to do */
     return;

  rel = _bfd_coff_read_internal_relocs 
           (input_bfd, input_section, true, NULL, false, NULL);

  relend = rel + input_section->reloc_count;
  for (; rel < relend; rel++)
    {
      long symndx;
      struct coff_link_hash_entry *h;
      bfd_vma val;
      asection *sec;
      bfd_vma currPC;
      boolean has_ext;

      /* Ignore uninteresting stuff */
      if (rel->r_type != ALPHA_R_BRADDR)
	  continue;

      BFD_ASSERT(lastseen <= rel->r_vaddr);
      lastseen=rel->r_vaddr;

      symndx = rel->r_symndx;

      /* If an absolute section or a section symbol, we'll ignore it.
	 A branch to these seems rather unlikely. */
      if (symndx == -1)
	 continue;
  
      h = obj_coff_sym_hashes (input_bfd)[symndx];
      if (h == NULL)
	 continue;

      /* There's some space-saving magic going on with .vol and .perm;
	 see bfdlink.h for more details. */
      if (h->root.type == bfd_link_hash_defined_ext
	  || h->root.type == bfd_link_hash_defweak_ext)
	{
	  sec = h->root.u.defext.perm->section;
	  val = (h->root.u.defext.perm->value
	     + sec->output_section->vma
	     + sec->output_offset);
	  has_ext = true;
	}
      else if (h->root.type == bfd_link_hash_defined
	  || h->root.type == bfd_link_hash_defweak)
	  /* we'll never branch to a section symbol */
	{
	  sec = h->root.u.def.section;
	  val = (h->root.u.def.value
	     + sec->output_section->vma
	     + sec->output_offset);
          has_ext = false;
	}
      else 
	/* undefined; let someone else handle complaining. */
	continue;

      currPC = input_section->output_offset
	       + input_section->output_section->vma 
	       + rel->r_vaddr;

      /* Already in the chain, we don't need to worry about it for now,
	 in that there's already a branch scheduled that we're sure to
	 be able to reach */
      if (has_ext && h->root.u.defext.vol != NULL)
          continue;

      /* At this point, val is the target address of the branch.
	 If it's lower than the end of this section, it's an accurate
	 address.  If it's higher (forward), it's inaccurate.
	 We'll assume forwards are out-of-range until proven otherwise */

      if (val 
	  < input_section->output_offset 
	    + input_section->output_section->vma
	    + input_section->_cooked_size)
	{
	  /* Backwards branch; is it in range? (Addresses in the same
	     input section are presumed to be in range (this is where
	     currPC might be below val).  If not, we can't save it anyway!) */
	  struct extra_addresses *s;
	  if (INRANGE(val, currPC, info->jump_span))
	       /* in range; nothing to do */
	      continue;

	  /* out of range; is there already an in-range one added
	     to the symbol table? */

	  if (has_ext)
	    {
	      s = h->root.u.defext.perm->extras;
	      while (s != NULL)
		{
		  if (INRANGE(s->addr, currPC, info->jump_span))
		    {
		       goto no_action /* that is, continue outer loop */;
		    }
		  s=s->next;
		}
	    }
	}

      /* There's an ugly little special case of adjacent calls forcing
	 us out of available headroom.  That's handled elsewhere */

      /* No branch in range; schedule one by threading thru the symbol table;
	 we assume the relocs are in r_vaddr order */
      if (!has_ext)
	{
	   /* This symbol has not been involved in the branch stub stuff
	      before; convert to a ..._ext type symbol, and create
	      the permanent part. */
	   struct extended_def_perm *p = 
	      (struct extended_def_perm *)
	       bfd_malloc(sizeof(struct extended_def_perm));

	   p->value = h->root.u.def.value;
	   p->section = h->root.u.def.section;
	   p->extras = NULL;
	   if (h->root.type == bfd_link_hash_defined)
	       h->root.type = bfd_link_hash_defined_ext;
	   if (h->root.type == bfd_link_hash_defweak)
	       h->root.type = bfd_link_hash_defweak_ext;
	   h->root.u.defext.perm = p;
	}

      /* Now the volatile part; we assured that when has_ext is true
	 (that is, it had been involved in stubs before) that the 
	 volatile part was null, above.  First, get it from the
	 cache or make a new one.  */
      if (info->stub_vol_cache != NULL) 
	{
	   h->root.u.defext.vol = info->stub_vol_cache;
	   info->stub_vol_cache=h->root.u.defext.vol->ref_chain;
	}
      else
	{
	   h->root.u.defext.vol = (struct extended_def_vol *)
		bfd_malloc(sizeof(struct extended_def_vol));
	}

      /* Fill it in */
      h->root.u.defext.vol->referencing_address = currPC;
      h->root.u.defext.vol->referencing_section = input_section;
      h->root.u.defext.vol->hash_entry = &h->root;
      h->root.u.defext.vol->ref_chain = NULL;

      if (info->stub_list_head != NULL) 
	{
          stub_list_tail->ref_chain = h->root.u.defext.vol;
          stub_list_tail = h->root.u.defext.vol;
	}
      else
	{
          stub_list_tail = info->stub_list_head = h->root.u.defext.vol;
	}

    no_action:;
  }
}

/* Given the appropriate link order, generate branch stub instructions */
/*ARGSUSED*/
static boolean
alpha_emit_stubs (output_bfd, info, output_section, link_order)
     bfd *output_bfd;
     struct bfd_link_info *info;
     asection *output_section;
     struct bfd_link_order *link_order;
{
  insn_word *space;
  int i;
  boolean result;
  int count;
  struct bfd_link_hash_entry *h;
  asection *sec;
  bfd_vma val;
  bfd_vma ImageBase = pe_data(output_bfd)->pe_opthdr.ImageBase;

  BFD_ASSERT ((output_section->flags & SEC_HAS_CONTENTS) != 0);

  space = (long *) bfd_malloc (link_order->size);

  if (space == NULL)
    return false;

  count = link_order->u.stubs.s->entries_count;

  /* Usually... Emit 3 instruction sequence (in 4 word chunk)
     ldah  $27,<high part>
     lda   $27,($27)<low part>
     jmp   ($27)

     This is fine for NT on the alpha (32 bit addresses), but won't cut it 
     for bigger configurations.

     If the branch proves to be in range (from here) of a short branch,
     use one.  It doesn't end up saving any space, but it will be faster.
  */
  for (i = 0; i < count; i++)
    {
       bfd_vma currPC;

       h = link_order->u.stubs.s->stublist[i];
       if (h->type == bfd_link_hash_defined_ext
	  || h->type == bfd_link_hash_defweak_ext)
	 {
	   sec = h->u.defext.perm->section;
	   val = (h->u.defext.perm->value
	      + sec->output_section->vma
	      + sec->output_offset);
	 }
       else
	   abort();

       currPC = link_order->offset
		+ output_section->vma
	        + STUB_WORDS*i*sizeof(insn_word);

       if (INRANGE(val, currPC, info->jump_span))
	 {
	    long disp;

	    disp = (long)((val >> 2) & 0x3fffffff) 
		 - (long)((currPC >> 2) & 0x3fffffff)
		 - 1;
	    space[STUB_WORDS*i] = 0xc3e00000 | (disp & 0x1fffff);
	    space[STUB_WORDS*i+1] = 0;
	    space[STUB_WORDS*i+2] = 0;
	    space[STUB_WORDS*i+3] = 0;
	 }
       else
	 {
           val += ImageBase;
	   /* Tweak the value to deal with sign extension (see REFHI above) */
	   if ((val & 0x8000) != 0)
	      val += 0x10000;
	   space[STUB_WORDS*i]   = 0x277f0000 + ((val >> 16) & 0xffff);
	   space[STUB_WORDS*i+1] = 0x237b0000 + (val&0xffff);
	   space[STUB_WORDS*i+2] = 0x6bfb0000;
	   space[STUB_WORDS*i+3] = 0;

	   if (info->base_file)
	     {
	       /* Emit a reloc if the backend thinks it needs it.
		  In this case, it always does because we know it's a branch */
	       if (sec)
		 {
		   /* relocation to a symbol in a section which
		      isn't absolute - we output the address here 
		      to a file; however, to do this right we need a type */
		   bfd_vma addr = sizeof(insn_word)*(STUB_WORDS*i)
		     - sec->vma 
		     + sec->output_offset 
		     + sec->output_section->vma;
		   fwrite (&addr, 1, sizeof(bfd_vma), (FILE *) info->base_file);

		   addr = sizeof(insn_word)*(STUB_WORDS*i+1)
		     - sec->vma 
		     + sec->output_offset 
		     + sec->output_section->vma;
		   fwrite (&addr, 1, sizeof(bfd_vma), (FILE *) info->base_file);
		 }
	     }
	 }
     }

  result = bfd_set_section_contents (output_bfd, output_section, space,
				     (file_ptr) link_order->offset,
				     link_order->size);
  free (space);
  return result;
}
