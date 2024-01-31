/* Macro definitions for i386 running under OpenNT
   Copyright 1998 Free Software Foundation, Inc.

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

#ifndef TM_OPENNT_H
#define TM_OPENNT_H

#include "i386/tm-i386.h"

#undef TARGET_LONG_BIT
#define TARGET_LONG_BIT 32

/* this is a no-op change, but for the record... */
#undef TARGET_LONG_LONG_BIT
#define TARGET_LONG_LONG_BIT 64

/* configure can't be expected to noodle out MS's alternate spelling for
   64-bit integers, so we'll tell it. */
#define PRINTF_HAS_LONG_LONG 1
#ifdef __GNUC__
#define BFD_HOST_64_BIT long long
#define BFD_HOST_U_64_BIT unsigned long long
#elif defined(_MSC_VER)
#define BFD_HOST_64_BIT __int64
#define BFD_HOST_U_64_BIT unsigned __int64
#else
#error... OK what compiler is this?
#endif

#define LONGEST BFD_HOST_64_BIT
#define ULONGEST BFD_HOST_U_64_BIT

#undef TARGET_PTR_BIT
#define TARGET_PTR_BIT 32

/* Amount PC must be decremented by after a breakpoint.  This is often the
   number of bytes in BREAKPOINT but not always (such as now). */


#undef DECR_PC_AFTER_BREAK
#define DECR_PC_AFTER_BREAK 0


/* This stuff interacts tightly with the gcc macro DBX_REGISTER_NUMBER */
#undef NUM_REGS
#undef NUM_FREGS
#define NUM_FREGS 8			/* Number of FP regs */
#define NUM_REGS (16 + NUM_FREGS)	/* Basic i*86 regs + FP regs */

/* Nonzero if register N requires conversion
   from raw format to virtual format.  */

#define REGISTER_CONVERTIBLE(N) \
  ((N < FP0_REGNUM) ? 0 : 1)

/* Convert data from raw format for register REGNUM in buffer FROM
   to virtual format with type TYPE in buffer TO.  */
extern void
i387_to_double PARAMS ((char *, char *));


#define REGISTER_CONVERT_TO_VIRTUAL(REGNUM,TYPE,FROM,TO) \
{ \
  double val; \
  i387_to_double ((FROM), (char *)&val); \
  store_floating ((TO), TYPE_LENGTH (TYPE), val); \
}

extern void
double_to_i387 PARAMS ((char *, char *));

#define REGISTER_CONVERT_TO_RAW(TYPE,REGNUM,FROM,TO) \
{ \
  double val = extract_floating ((FROM), TYPE_LENGTH (TYPE)); \
  double_to_i387((char *)&val, (TO)); \
}

#undef IN_SIGTRAMP
/* SIGTRAMP is in a DLL where we don't have any symbols. However,
   procfs tells us where it is. */

extern CORE_ADDR tramp_start;
extern CORE_ADDR tramp_end;
extern CORE_ADDR null_start;
extern CORE_ADDR null_end;

/* This is sufficient, where used, but is NOT a complete test; there's more
   in INIT_EXTRA_FRAME_INFO (a.k.a. opennt_back_one_frame) */
#define IN_SIGTRAMP(p,f) ((((p)>=tramp_start && (p)<tramp_end)) \
		|| (((p)>=null_start && (p)<null_end)))

#define IN_SOLIB_CALL_TRAMPOLINE(pc, name) skip_trampoline_code (pc, name)
#define SKIP_TRAMPOLINE_CODE(pc)           skip_trampoline_code (pc, 0)
extern CORE_ADDR skip_trampoline_code PARAMS ((CORE_ADDR pc, char *name));

/* Actually... do a full unwind */
#define INIT_EXTRA_FRAME_INFO(fromleaf, prev) \
	opennt_back_one_frame(fromleaf, prev);

/* This becomes a no-op because of the above */
#define INIT_FRAME_PC

/* INIT_EXTRA_FRAME_INFO set pc (always), so this is a no-op. */
#undef FRAME_SAVED_PC
#define FRAME_SAVED_PC(FRAME) ((FRAME)->pc)

/* Figure out where the longjmp will land.  Slurp the args out of the stack.
   We expect the first arg to be a pointer to the jmp_buf structure from which
   we extract the pc  that we will land at.  The pc is copied into ADDR.
   This routine returns true on success */

extern int
get_longjmp_target PARAMS ((CORE_ADDR *));

#define GET_LONGJMP_TARGET(ADDR) get_longjmp_target(ADDR)

#endif /* TM_OPENNT_H */
