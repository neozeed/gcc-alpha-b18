/*
 * hugeval.c
 *
 * This was the best way I could figure out to make it possible to define
 * HUGE_VAL in the standard header files. See math.h.
 *
 * NOTE: Eyah! What a wack hack! But it does work. Super-ultra-utterly
 *       unportable.
 */

const unsigned char	__caHugeVal[sizeof(double)] =
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f };

