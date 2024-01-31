/* Definitions to make GDB run on an Alpha box under OpenNT.  The
   definitions here are used when the _target_ system is running OpenNT.
   Copyright 1996 Free Software Foundation, Inc.

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

#ifndef TM_OPENNTALPHA_H
#define TM_OPENNTALPHA_H

#include "alpha/tm-alpha.h"

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
#else
#define BFD_HOST_64_BIT __int64
#define BFD_HOST_U_64_BIT unsigned __int64
#endif
#define LONGEST BFD_HOST_64_BIT
#define ULONGEST BFD_HOST_U_64_BIT

#undef TARGET_PTR_BIT
#define TARGET_PTR_BIT 32

/* Number of traps that happen between exec'ing the shell to run an
   inferior, and when we finally get to the inferior code.  This is 2
   on OpenNT and most implementations.  */

#undef START_INFERIOR_TRAPS_EXPECTED
#define START_INFERIOR_TRAPS_EXPECTED 2

/* Change gp to t13 */
#undef REGISTER_NAMES
#define REGISTER_NAMES 	\
    {	"v0",	"t0",	"t1",	"t2",	"t3",	"t4",	"t5",	"t6", \
	"t7",	"s0",	"s1",	"s2",	"s3",	"s4",	"s5",	"fp", \
	"a0",	"a1",	"a2",	"a3",	"a4",	"a5",	"t8",	"t9", \
	"t10",	"t11",	"ra",	"t12",	"at",	"t13",	"sp",	"zero", \
	"f0",   "f1",   "f2",   "f3",   "f4",   "f5",   "f6",   "f7", \
	"f8",   "f9",   "f10",  "f11",  "f12",  "f13",  "f14",  "f15", \
	"f16",  "f17",  "f18",  "f19",  "f20",  "f21",  "f22",  "f23",\
	"f24",  "f25",  "f26",  "f27",  "f28",  "f29",  "f30",  "f31",\
	"pc",	"vfp",						\
    }

/* Amount PC must be decremented by after a breakpoint.  This is often the
   number of bytes in BREAKPOINT but not always (such as now). */

#undef DECR_PC_AFTER_BREAK
#define DECR_PC_AFTER_BREAK 0

extern CORE_ADDR tramp_start;
extern CORE_ADDR tramp_end;
extern CORE_ADDR null_start;
extern CORE_ADDR null_end;

#undef IN_SIGTRAMP
#define IN_SIGTRAMP(p,f) ((((p)>=tramp_start && (p)<tramp_end)) \
   || (((p)>=null_start && (p)<null_end)))

/* We cheat a little; it's not dynamic, but it's not quite static either,
   but this test does the right thing. */
#undef DYNAMIC_SIGTRAMP_OFFSET
#define DYNAMIC_SIGTRAMP_OFFSET(p) (((p>=tramp_start && (p)<tramp_end))?0:-1)

#undef SKIP_TRAMPOLINE_CODE
#define IN_SOLIB_CALL_TRAMPOLINE(pc, name) skip_trampoline_code (pc, name)
#define SKIP_TRAMPOLINE_CODE(pc)           skip_trampoline_code (pc, 0)
extern CORE_ADDR skip_trampoline_code PARAMS ((CORE_ADDR pc, char *name));

#undef INIT_EXTRA_FRAME_INFO
#define INIT_EXTRA_FRAME_INFO(fromleaf, prev) \
    init_extra_frame_info(prev);

#define FIND_SAVED_REGS(fi) alpha_find_saved_regs(fi)

#define SIGTRAMP_START_ADDR tramp_start
#define SIGTRAMP_END_ADDR   tramp_end
#define SIGTRAMP_FRAME_SIZE 0  /* calculated by opennt_alpha_find_saved_regs */

/* This value is determined by the size of PdxNullApiCaller, and by
   what it takes top pass the a1-selftest regression (unoptimized) */
#define HEURISTIC_FENCE_POST 280

/* Used to determine if a heuristic to find the beginning of a proc should
   be used, or whether the current guess is good enough.   If we have a
   decent start address, we don't care if HEURISTIC_FENCE_POST is set
   or not, we'll use the decent start address.  However, with no
   start address we want a non-zero HEURISTIC_FENCE_POST, so the default
   test is no good. */
#define FIND_HEURISTIC_START (0)

#undef VM_MIN_ADDRESS
#define VM_MIN_ADDRESS ((CORE_ADDR)0)

/* For NT we need to get to the NT pdata structure type, which we
   translate into a PDR; for that we need the type and a couple of
   support functions. */

typedef struct _runtime_function {
    unsigned long begin;
    unsigned long end;
    void *eh;
    unsigned long handler_data;
    unsigned long prolog_end;
} runtime_function;

runtime_function find_pdata_entry(CORE_ADDR);
CORE_ADDR proc_allocation_base(CORE_ADDR);

#endif /* TM_OPENNTALPHA_H */
