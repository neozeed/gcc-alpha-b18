
/* @(#)w_sqrt.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/*
FUNCTION
	<<sqrt>>, <<sqrtf>>---positive square root

INDEX
	sqrt
INDEX
	sqrtf

ANSI_SYNOPSIS
	#include <math.h>
	double sqrt(double <[x]>);
	float  sqrtf(float <[x]>);

TRAD_SYNOPSIS
	#include <math.h>
	double sqrt(<[x]>);
	float  sqrtf(<[x]>);

DESCRIPTION
	<<sqrt>> computes the positive square root of the argument.
	You can modify error handling for this function with
	<<matherr>>.

RETURNS
	On success, the square root is returned. If <[x]> is real and
	positive, then the result is positive.  If <[x]> is real and
	negative, the global value <<errno>> is set to <<EDOM>> (domain error).


PORTABILITY
	<<sqrt>> is ANSI C.  <<sqrtf>> is an extension.
*/

/* 
 * wrapper sqrt(x)
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double sqrt(double x)		/* wrapper sqrt */
#else
	double sqrt(x)			/* wrapper sqrt */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_sqrt(x);
#else
	double z;
	z = __ieee754_sqrt(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x)) return z;
	if(x<0.0) {
	    return __kernel_standard(x,x,26); /* sqrt(negative) */
	} else
	    return z;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
