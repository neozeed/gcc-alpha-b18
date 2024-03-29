/* 
Copyright (C) 1993 Free Software Foundation

This file is part of the GNU IO Library.  This library is free
software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option)
any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this library; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

As a special exception, if you link this library with files
compiled with a GNU compiler to produce an executable, this does not cause
the resulting executable to be covered by the GNU General Public License.
This exception does not however invalidate any other reasons why
the executable file might be covered by the GNU General Public License. */

#include "libioP.h"
#include <limits.h>

char*
DEFUN(_IO_gets, (buf),
      char* buf)
{
  _IO_size_t count;
  int ch = _IO_getc (_IO_stdin);
  if (ch == EOF)
    return NULL;
  if (ch == '\n')
    count = 0;
  else
    {
      buf[0] = (char)ch;
      count = _IO_getline(_IO_stdin, buf + 1, INT_MAX, '\n', 0) + 1;
      if (_IO_stdin->_IO_file_flags & _IO_ERR_SEEN)
	return NULL;
    }
  buf[count] = 0;
  return buf;
}
