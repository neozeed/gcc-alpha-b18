# Generated automatically from Makefile.in by configure.
# Copyright (C) 1992 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.

# You should have received a copy of the GNU Library General Public
# License along with the GNU C Library; see the file COPYING.LIB.  If
# not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.

#
# Makefile for mmalloc directory
#

# Directory containing source files.  Don't clean up the spacing,
# this exact string is matched for by the "configure" script.

srcdir = .

prefix =	/usr/local
exec_prefix =	${prefix}

bindir =	${exec_prefix}/bin
libdir =	${exec_prefix}/lib

datadir =	${prefix}/share
mandir =	${prefix}/man
man1dir =	$(mandir)/man1
man2dir =	$(mandir)/man2
man3dir =	$(mandir)/man3
man4dir =	$(mandir)/man4
man5dir =	$(mandir)/man5
man6dir =	$(mandir)/man6
man7dir =	$(mandir)/man7
man8dir =	$(mandir)/man8
man9dir =	$(mandir)/man9
infodir =	${prefix}/info
includedir =	${prefix}/include

SHELL =		/bin/sh

INSTALL =	/GCC-MS/CYGWIN/ginstall -c
INSTALL_PROGRAM=${INSTALL}
INSTALL_DATA =	${INSTALL} -m 644

AR =		ar
AR_FLAGS =	qv
CFLAGS =	-g
MAKEINFO =	makeinfo
RANLIB =	ranlib
RM =		rm

# where to find makeinfo
MAKEINFO=makeinfo

SET_TEXINPUTS = TEXINPUTS=${TEXIDIR}:.:$(srcdir):$(READLINE_DIR):$$TEXINPUTS

# The TeX formatter
TEX = tex

TARGETLIB =	libmmalloc.a

CFILES =	mcalloc.c mfree.c mmalloc.c mmcheck.c mmemalign.c mmstats.c \
		mmtrace.c mrealloc.c mvalloc.c mmap-sup.c attach.c detach.c \
		keys.c sbrk-sup.c mm.c

HFILES =	mmalloc.h

OFILES =	mcalloc.o mfree.o mmalloc.o mmcheck.o mmemalign.o mmstats.o \
		mmtrace.o mrealloc.o mvalloc.o mmap-sup.o attach.o detach.o \
		keys.o sbrk-sup.o

DEFS =		 -DHAVE_GETPAGESIZE=1 -DHAVE_LIMITS_H=1 -DHAVE_STDDEF_H=1 

# The current default is to build a single object module with all the mmalloc
# functions.  To build a more traditional library, flip this macro definition.
#TARGETOBJS =	$(OFILES)
TARGETOBJS =	mm.o

.c.o:
		$(CC) -c $(CFLAGS) $(DEFS) -I. -I$(srcdir)/../include $<

# Do we want/need any config overrides?
#	 

STAGESTUFF =	$(TARGETLIB) *.o

all:		$(TARGETLIB)

info: mmalloc.info
dvi: mmalloc.dvi
clean-info:
installcheck:

mmalloc.info: mmalloc.texi
	$(MAKEINFO) -I $(srcdir) -o ./mmalloc.info mmalloc.texi

# This file doesn't need texindex currently.
mmalloc.dvi: mmalloc.texi
	$(SET_TEXINPUTS) $(TEX) mmalloc.texi
	rm -f mmalloc.?? mmalloc.??s mmalloc.log mmalloc.aux mmalloc.toc

install-info: info
	if test ! -f mmalloc.info ; then cd $(srcdir); fi; \
	$(INSTALL_DATA) mmalloc.info $(infodir)/mmalloc.info

check: test1.c
#	$(CC) -g $(srcdir)/test1.c libmmalloc.a
# This loses for Canadian cross (building mmalloc with a cross-compiler).
# There is probably some dejagnu-ish solution (such as what we are doing
# for gdb, perhaps).
#	./a.out

install:	all
		$(INSTALL_DATA) $(TARGETLIB) $(libdir)/$(TARGETLIB).n
		$(RANLIB) $(libdir)/$(TARGETLIB).n
		mv -f $(libdir)/$(TARGETLIB).n $(libdir)/$(TARGETLIB)

$(TARGETLIB):	$(TARGETOBJS)
		$(RM) -rf $@
		$(AR) $(AR_FLAGS) $@ $(TARGETOBJS)
		$(RANLIB) $@

$(OFILES) :	$(HFILES) Makefile

mm.o:		$(HFILES) $(CFILES)
		$(CC) -c $(CFLAGS) $(DEFS) -I. -I$(srcdir)/../include $(srcdir)/mm.c

.always.:
# Do nothing.

.PHONEY: all etags tags ls clean stage1 stage2 .always.

stage1:		force
		-mkdir stage1
		-mv -f $(STAGESTUFF) stage1

stage2:		force
		-mkdir stage2
		-mv -f $(STAGESTUFF) stage2

stage3:		force
		-mkdir stage3
		-mv -f $(STAGESTUFF) stage3

stage4:		force
		-mkdir stage4
		-mv -f $(STAGESTUFF) stage4

against=stage2

comparison:	force
		for i in *.o ; do cmp $$i $(against)/$$i || exit 1 ; done

de-stage1:	force
		-(cd stage1 ; mv -f * ..)
		-rmdir stage1

de-stage2:	force
		-(cd stage2 ; mv -f * ..)
		-rmdir stage2

de-stage3:	force
		-(cd stage3 ; mv -f * ..)
		-rmdir stage3

de-stage4:	force
		-(cd stage4 ; mv -f * ..)
		-rmdir stage4

etags tags:	TAGS

TAGS:		$(CFILES)
	etags `for i in $(HFILES) $(CFILES); do echo $(srcdir)/$$i ; done`

ls:
		@echo Makefile $(HFILES) $(CFILES)

# Need to deal with profiled libraries, too.

mostlyclean clean:
		rm -f *.a *.o core errs *~ \#* TAGS *.E a.out errors 

distclean:	clean 
		rm -f config.cache config.log config.status
		rm -f Makefile depend

maintainer-clean realclean: distclean clean
		@echo "This command is intended for maintainers to use;"
		@echo "it deletes files that may require special tools to rebuild."
		rm -f mmalloc.info

force:

Makefile:	Makefile.in config.status
		$(SHELL) config.status

config.status:	configure
		$(SHELL) config.status --recheck
