# Generated automatically from Makefile.in by configure.
# Makefile for GNU Assembler documentation
#   Copyright (C) 1987-1993 Free Software Foundation, Inc.

#This file is part of GNU GAS.

#GNU GAS is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2, or (at your option)
#any later version.

#GNU GAS is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with GNU GAS; see the file COPYING.  If not, write to
#the Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# The targets for external use include:
# all, doc, proto, install, uninstall, includes, TAGS,
# clean, cleanconfig, realclean, stage1, stage2, stage3, stage4.

# Variables that exist for you to override.

srcdir = .

prefix = /usr/local

program_transform_name = s,x,x,
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib

datadir = ${prefix}/share
mandir = ${prefix}/man
man1dir = $(mandir)/man1
man2dir = $(mandir)/man2
man3dir = $(mandir)/man3
man4dir = $(mandir)/man4
man5dir = $(mandir)/man5
man6dir = $(mandir)/man6
man7dir = $(mandir)/man7
man8dir = $(mandir)/man8
man9dir = $(mandir)/man9
infodir = ${prefix}/info
includedir = ${prefix}/include

SHELL = /bin/sh

INSTALL = /GCC-MS/CYGWIN/ginstall -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_XFORM1 = $(INSTALL) -b $(program_transform_name) .1

AR = ar
AR_FLAGS = qv
BISON = bison
MAKEINFO = makeinfo
TEXI2DVI = texi2dvi
DVIPS = dvips
RANLIB = ranlib

# What version of the manual you want; "all" includes everything
CONFIG=all

# Where to find texinfo.tex to format docn with TeX
TEXIDIR = $(srcdir)/../../texinfo

##

all:
install:
	$(INSTALL_XFORM1) $(srcdir)/as.1 $(man1dir)/as.1

info: as.info gasp.info
dvi: as.dvi gasp.dvi
ps: as.ps gasp.ps

asconfig.texi: $(CONFIG).texi
	rm -f asconfig.texi
	ln -s $(srcdir)/$(CONFIG).texi ./asconfig.texi || \
	ln $(srcdir)/$(CONFIG).texi ./asconfig.texi || \
	cp $(srcdir)/$(CONFIG).texi ./asconfig.texi

as.info: $(srcdir)/as.texinfo asconfig.texi
	$(MAKEINFO) -I$(TEXIDIR) -I$(srcdir) -o as.info $(srcdir)/as.texinfo

gasp.info: $(srcdir)/gasp.texi
	$(MAKEINFO) -o gasp.info $(srcdir)/gasp.texi

install-info: install-info-as install-info-gasp
install-info-as: as.info
	if [ -r as.info ]; then \
	  dir=. ; \
	else \
	  dir=$(srcdir) ; \
	fi ; \
	for i in `cd $$dir ; echo as.info*` ; do \
		$(INSTALL_DATA) $$dir/$$i $(infodir)/$$i ; \
	done
install-info-gasp: gasp.info
	if [ -r gasp.info ]; then \
	  dir=. ; \
	else \
	  dir=$(srcdir) ; \
	fi ; \
	for i in `cd $$dir ; echo gasp.info*` ; do \
		$(INSTALL_DATA) $$dir/$$i $(infodir)/$$i ; \
	done

as.dvi:	$(srcdir)/as.texinfo asconfig.texi
	TEXINPUTS=$(srcdir):$(TEXIDIR):$$TEXINPUTS MAKEINFO='$(MAKEINFO) -I$(srcdir)' \
	$(TEXI2DVI) $(srcdir)/as.texinfo

as.ps:	as.dvi
	$(DVIPS) -o $@ $?

gasp.dvi: $(srcdir)/gasp.texi
	TEXINPUTS=$(srcdir):$(TEXIDIR):$$TEXINPUTS MAKEINFO='$(MAKEINFO) -I$(srcdir)' \
	$(TEXI2DVI) $(srcdir)/gasp.texi

gasp.ps: gasp.dvi
	$(DVIPS) -o $@ $?

# This one isn't ready for prime time yet.  Not even a little bit.

internals.info: $(srcdir)/internals.texi
	$(MAKEINFO) -o $@ $?

internals.dvi: $(srcdir)/internals.texi
	TEXINPUTS=$(srcdir):$(TEXIDIR):$$TEXINPUTS MAKEINFO='$(MAKEINFO) -I$(srcdir)' \
	$(TEXI2DVI) $(srcdir)/internals.texi

internals.ps: internals.dvi
	$(DVIPS) -o $@ $?

internals.ps4: internals.ps
	psnup -4 <$? >$@

# ROFF doc targets as.ms, as.mm, as.me
# (we don't use a variable because we don't trust all makes to handle
# a var in the target name right).
# roff output (-ms)
# THESE ARE PROBABLY BROKEN until texi2roff extended for Texinfo conditionals
as.ms: $(srcdir)/as.texinfo asconfig.texi
	sed -e '/\\input texinfo/d' \
		-e '/@c TEXI2ROFF-KILL/,/@c END TEXI2ROFF-KILL/d' \
		-e 's/{.*,,/{/' \
		$(srcdir)/as.texinfo | \
	texi2roff -ms >as.ms 

# roff output (-mm)
as.mm: $(srcdir)/as.texinfo asconfig.texi
	sed -e '/\\input texinfo/d' \
		-e '/@c TEXI2ROFF-KILL/,/@c END TEXI2ROFF-KILL/d' \
		-e 's/{.*,,/{/' \
		-e '/@noindent/d' \
		$(srcdir)/as.texinfo | \
	texi2roff -mm | \
	sed -e 's/---/\\(em/g' \
	>as.mm 

# roff output (-me)
as.me: $(srcdir)/as.texinfo asconfig.texi
	sed -e '/\\input texinfo/d' \
		-e '/@c TEXI2ROFF-KILL/,/@c END TEXI2ROFF-KILL/d' \
		-e 's/{.*,,/{/' \
		$(srcdir)/as.texinfo | \
	texi2roff -me >as.me 

clean mostlyclean: clean-dvi clean-info
	rm -f asconfig.texi core *~

distclean:
	rm -f Makefile config.status asconfig.texi \
		as.?? as.??s as.aux as.log as.toc \
		internals.?? internals.??s internals.aux internals.log internals.toc \
		gasp.?? gasp.??s gasp.aux gasp.log gasp.toc

clean-dvi:
	rm -f as.?? as.??? gasp.?? gasp.??? internals.?? internals.???

clean-info:
	rm -f as.info* gasp.info*

maintainer-clean realclean: clean-info distclean

force:

Makefile: $(srcdir)/Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	(cd .. ; $(SHELL) ./config.status)
