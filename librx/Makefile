# Generated automatically from Makefile.in by configure.
# Makefile for librx
# Copyright (C) 1994 Free Software Foundation, Inc.
# 
# This file is part of GNU Rx
# 
# GNU Rx is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
# 
# GNU Rx is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU SED; see the file COPYING.  If not, write to
# the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

SHELL = /bin/sh

srcdir = .

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
includedir = ${prefix}/include
infodir = ${prefix}/info

#### Start of system configuration section. ####

CC = gcc
INSTALL = /GCC-MS/CYGWIN/ginstall -c
INSTALL_DATA = ${INSTALL} -m 644
DEFS =  -DHAVE_ALLOCA=1 -DSTDC_HEADERS=1 -DHAVE_STRING_H=1 
CFLAGS = -g 
LIBCFLAGS = $(CFLAGS)
AR = ar
AR_FLAGS = rc
RANLIB = ranlib
PICFLAG =

# 

source=rx.c
headers=rx.h
ancillery=configure.in Makefile.in configure \
	  COPYING.LIB INSTALL INSTALL.rx ChangeLog DOC 
distfiles=$(source) $(headers) $(ancillery)
libobjs=rx.o

COMPILE.c = $(CC) -c $(LIBCFLAGS) $(DEFS) -I$(srcdir)
.c.o:
	if [ -n "$(PICFLAG)" ]; then \
	  $(COMPILE.c) $(PICFLAG) $< -o pic/$@; \
	else true; fi
	$(COMPILE.c) $<

all: librx.a

install: all
	$(INSTALL_DATA) librx.a $(libdir)/librx.a
	$(RANLIB) $(libdir)/librx.a
	$(INSTALL_DATA) $(srcdir)/rx.h $(includedir)/rx.h


uninstall:
	rm $(libdir)/librx.a
	rm $(includedir)/rx.h

clean:
	-rm -rf $(libobjs) librx.a pic stamp-picdir

distclean: clean
	-rm Makefile config.status config.cache config.log multilib.out

mostlyclean: clean

maintainer-clean realclean: distclean

TAGS:
	etags $(source)

info:

install-info:

clean-info:

dvi:

check:

dist:	$(distfiles)
	echo rx-`sed -e '/version_string/!d' -e 's/[^0-9.]*\([0-9.]*\).*/\1/' -e q rx.c` > .fname
	rm -rf `cat .fname`
	mkdir `cat .fname`
	ln $(distfiles) `cat .fname`
	tar chzf `cat .fname`.tar.gz `cat .fname`
	rm -rf `cat .fname` .fname


librx.a: $(libobjs)
	rm -f librx.a
	$(AR) $(AR_FLAGS) librx.a rx.o
	$(RANLIB) librx.a

rx.o: stamp-picdir rx.c rx.h

stamp-picdir:
	if [ -n "$(PICFLAG)" ] && [ ! -d pic ]; then \
	  mkdir pic; \
	else true; fi
	touch stamp-picdir
