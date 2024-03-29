/*
FUNCTION
	<<memset>>---set an area of memory

INDEX
	memset

ANSI_SYNOPSIS
	#include <string.h>
	void *memset(const void *<[dst]>, int <[c]>, size_t <[length]>);

TRAD_SYNOPSIS
	#include <string.h>
	void *memset(<[dst]>, <[c]>, <[length]>)
	void *<[dst]>;
	int <[c]>;
	size_t <[length]>;

DESCRIPTION
	This function converts the argument <[c]> into an unsigned
	char and fills the first <[length]> characters of the array
	pointed to by <[dst]> to the value.

RETURNS
	<<memset>> returns the value of <[m]>.

PORTABILITY
<<memset>> is ANSI C.

    <<memset>> requires no supporting OS subroutines.

QUICKREF
	memset ansi pure
*/

#include <string.h>

#define LBLOCKSIZE (sizeof(long))
#define UNALIGNED(X)   ((long)X & (LBLOCKSIZE - 1))
#define TOO_SMALL(LEN) ((LEN) < LBLOCKSIZE)

_PTR 
_DEFUN (memset, (m, c, n),
	_PTR m _AND
	int c _AND
	size_t n)
{
#ifdef PREFER_SIZE_OVER_SPEED
  char *s = (char *) m;

  while (n-- != 0)
    {
      *s++ = (char) c;
    }

  return m;
#else
  char *s = (char *) m;
  int count, i;
  unsigned long buffer;
  unsigned long *aligned_addr;
  unsigned char *unaligned_addr;

  if (TOO_SMALL (n) || UNALIGNED (m))
    {
      while (n-- != 0)
        {
          *s++ = (char) c;
        }
      return m;
    }

  /* If we get this far, we know that n is large and m is word-aligned. */

  aligned_addr = (unsigned long*)m;

  /* Store C into each char sized location in BUFFER so that
     we can set large blocks quickly.  */
  c &= 0xff;
  if (LBLOCKSIZE == 4)
    {
      buffer = (c << 8) | c;
      buffer |= (buffer << 16);
    }
  else
    {
      buffer = 0;
      for (i = 0; i < LBLOCKSIZE; i++)
	buffer = (buffer << 8) | c;
    }

  while (n >= LBLOCKSIZE*4)
    {
      *aligned_addr++ = buffer;
      *aligned_addr++ = buffer;
      *aligned_addr++ = buffer;
      *aligned_addr++ = buffer;
      n -= 4*LBLOCKSIZE;
    }

  while (n >= LBLOCKSIZE)
    {
      *aligned_addr++ = buffer;
      n -= LBLOCKSIZE;
    }

  /* Pick up the remainder with a bytewise loop.  */
  unaligned_addr = (unsigned char*)aligned_addr;
  while (n)
    {
      *unaligned_addr++ = (char)c;
      n--;
    }

  return m;
#endif /* not PREFER_SIZE_OVER_SPEED */
}
