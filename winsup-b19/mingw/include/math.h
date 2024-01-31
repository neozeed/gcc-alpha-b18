/* 
 * math.h
 *
 * Mathematical functions.
 *
 * This header file is meant for use with CRTDLL.DLL as included with
 * Windows 95(tm) and Windows NT(tm). In conjunction with other versions
 * of the standard C library things may or may not work so well.
 *
 * Contributors:
 *  Created by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 *
 *  THIS SOFTWARE IS NOT COPYRIGHTED
 *
 *  This source code is offered for use in the public domain. You may
 *  use, modify or distribute it freely.
 *
 *  This code is distributed in the hope that it will be useful but
 *  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAMED. This includes but is not limited to warranties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef _MATH_H_
#define _MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * HUGE_VAL is returned by strtod when the value would overflow the
 * representation of 'double'. There are other uses as well.
 * The definition of __caHugeVal is in libmingw32.a, because I could figure
 * out no other way of getting the appropriate bytes into memory.
 *
 * It is defined like this in hugeval.c:
 *	const unsigned char	__caHugeVal[] =
 *		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f };
 */

extern const unsigned char	__caHugeVal[sizeof(double)];

#define	HUGE_VAL	(*((double*)__caHugeVal))


struct _exception
{
	int	type;
	char	*name;
	double	arg1;
	double	arg2;
	double	retval;
};

/*
 * Types for the above _exception structure.
 */

#define	_DOMAIN		1	/* domain error in argument */
#define	_SING		2	/* singularity */
#define	_OVERFLOW	3	/* range overflow */
#define	_UNDERFLOW	4	/* range underflow */
#define	_TLOSS		5	/* total loss of precision */
#define	_PLOSS		6	/* partial loss of precision */

/*
 * Exception types with non-ANSI names for compatibility.
 */

#ifndef	_STRICT_ANSI
#ifndef	_NO_OLDNAMES

#define	DOMAIN		_DOMAIN
#define	SING		_SING
#define	OVERFLOW	_OVERFLOW
#define	UNDERFLOW	_UNDERFLOW
#define	TLOSS		_TLOSS
#define	PLOSS		_PLOSS

#endif	/* Not _NO_OLDNAMES */
#endif	/* Not _STRICT_ANSI */


double	sin (double x);
double	cos (double x);
double	tan (double x);
double	sinh (double x);
double	cosh (double x);
double	tanh (double x);
double	asin (double x);
double	acos (double x);
double	atan (double x);
double	atan2 (double y, double x);
double	exp (double x);
double	log (double x);
double	log10 (double x);
double	pow (double x, double y);
double	sqrt (double x);
double	ceil (double x);
double	floor (double x);
double	fabs (double x);
double	ldexp (double x, int n);
double	frexp (double x, int* exp);
double	modf (double x, double* ip);
double	fmod (double x, double y);


#ifndef	_STRICT_ANSI

/* Complex number (for cabs) */
struct _complex
{
	double	x;	/* Real part */
	double	y;	/* Imaginary part */
};

double	_cabs (struct _complex x);
double	_hypot (double x, double y);
double	_j0 (double x);
double	_j1 (double x);
double	_jn (int n, double x);
double	_y0 (double x);
double	_y1 (double x);
double	_yn (int n, double x);

#ifndef	_NO_OLDNAMES

/*
 * Non-underscored versions of non-ANSI functions. These reside in
 * liboldnames.a. Provided for extra portability.
 */
double cabs (struct _complex x);
double hypot (double x, double y);
double j0 (double x);
double j1 (double x);
double jn (int n, double x);
double y0 (double x);
double y1 (double x);
double yn (int n, double x);

#endif	/* Not _NO_OLDNAMES */

#endif	/* Not _STRICT_ANSI */

#ifdef __cplusplus
}
#endif

#endif /* Not _MATH_H_ */

