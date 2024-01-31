
/* @(#)w_hypot.c 5.1 93/09/24 */
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
	<<hypot>>, <<hypotf>>---distance from origin
INDEX
	hypot
INDEX
	hypotf

ANSI_SYNOPSIS
	#include <math.h>
	double hypot(double <[x]>, double <[y]>);
	float hypotf(float <[x]>, float <[y]>);

TRAD_SYNOPSIS
	double hypot(<[x]>, <[y]>)
	double <[x]>, <[y]>;

	float hypotf(<[x]>, <[y]>)
	float <[x]>, <[y]>;

DESCRIPTION
	<<hypot>> calculates the Euclidean distance
	@tex
	$\sqrt{x^2+y^2}$
	@end tex
	@ifinfo
	<<sqrt(<[x]>*<[x]> + <[y]>*<[y]>)>>
	@end ifinfo
	between the origin (0,0) and a point represented by the
	Cartesian coordinates (<[x]>,<[y]>).  <<hypotf>> differs only
	in the type of its arguments and result.

RETURNS
	Normally, the distance value is returned.  On overflow,
	<<hypot>> returns <<HUGE_VAL>> and sets <<errno>> to
	<<ERANGE>>.

	You can change the error treatment with <<matherr>>.

PORTABILITY
	<<hypot>> and <<hypotf>> are not ANSI C.  */

/*
 * wrapper hypot(x,y)
 */

#include "fdlibm.h"

#ifndef _DOUBLE_IS_32BITS

#ifdef __STDC__
	double hypot(double x, double y)/* wrapper hypot */
#else
	double hypot(x,y)		/* wrapper hypot */
	double x,y;
#endif
{
#ifdef _IEEE_LIBM
	return __ieee754_hypot(x,y);
#else
	double z;
	z = __ieee754_hypot(x,y);
	if(_LIB_VERSION == _IEEE_) return z;
	if((!finite(z))&&finite(x)&&finite(y))
	    return __kernel_standard(x,y,4); /* hypot overflow */
	else
	    return z;
#endif
}

#endif /* defined(_DOUBLE_IS_32BITS) */
