#include <stdlib.h>
#include <_ansi.h>

float
_DEFUN (atoff, (s),
	_CONST char *s)
{
  return strtodf (s, NULL);
}
