#define TE_OPENNT
/* OPENNT is mostly PEI, which in turn... */
#define TE_PEI
/* PEI is mostly PE, so PEI is used to condition the few
   real differences, rather than defining a new symbol */
#define TE_PE
#define LEX_AT 1 /* can have @'s inside labels */

/* The PE format supports long section names.  */
#define COFF_LONG_SECTION_NAMES

#include "obj-format.h"
