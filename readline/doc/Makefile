# This file was generated automatically by configure.  Do not edit.
VPATH = .
links = 
host_alias = alpha-cygwin32
host_cpu = alpha
host_vendor = unknown
host_os = cygwin32
host_canonical = alpha-unknown-cygwin32
target_alias = alpha-cygwin32
target_cpu = alpha
target_vendor = unknown
target_os = cygwin32
target_canonical = alpha-unknown-cygwin32
build_alias = alpha-cygwin32
build_cpu = alpha
build_vendor = unknown
build_os = cygwin32
build_canonical = alpha-unknown-cygwin32
## Copyright (C) 1993 Free Software Foundation, Inc.

# Makefile for Readline documentation.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

srcdir = .

prefix = /usr/local

infodir = $(prefix)/info

SHELL = sh

INSTALL = install -c
INSTALL_DATA = $(INSTALL)

# where to find texinfo
TEXIDIR=$(srcdir)/../../texinfo

# where to find makeinfo, preferably one designed for texinfo-2
MAKEINFO=makeinfo

# auxiliary program for sorting Texinfo indices
TEXINDEX=texindex

# Don Knuth's TeX formatter
TEX=tex

#### Host, target, and site specific Makefile fragments come in here.
###

all: info dvi

install: install-info

info: history.info readline.info

dvi: history.dvi readline.dvi

install-info: info
	-parent=`echo $(infodir)|sed -e 's@/[^/]*$$@@'`; \
	if [ -d $$parent ] ; then true ; else mkdir $$parent ; fi
	-if [ -d $(infodir) ] ; then true ; else mkdir $(infodir) ; fi
	for i in *.info* ; do \
		$(INSTALL_DATA) $$i $(infodir)/$$i ; \
	done

history.info: hist.texinfo hsuser.texinfo hstech.texinfo
	$(MAKEINFO) -I $(srcdir) -o ./history.info $(srcdir)/hist.texinfo

history.dvi: hist.texinfo hsuser.texinfo hstech.texinfo $(TEXIDIR)/texinfo.tex
	TEXINPUTS=${TEXIDIR}:$(srcdir):$$TEXINPUTS $(TEX) hist.texinfo
	$(TEXINDEX) hist.??
	TEXINPUTS=${TEXIDIR}:$(srcdir):$$TEXINPUTS $(TEX) hist.texinfo

readline.info: rlman.texinfo rluser.texinfo rltech.texinfo
	$(MAKEINFO) -I $(srcdir) -o ./readline.info $(srcdir)/rlman.texinfo

readline.dvi: rlman.texinfo rluser.texinfo rltech.texinfo
	TEXINPUTS=${TEXIDIR}:$(srcdir):$$TEXINPUTS $(TEX) rlman.texinfo
	$(TEXINDEX) rlman.??
	TEXINPUTS=${TEXIDIR}:$(srcdir):$$TEXINPUTS $(TEX) rlman.texinfo

distclean: clean
	rm -f Makefile config.status

mostlyclean: clean

realclean maintainer-clean: distclean

clean: clean-info clean-dvi

clean-info:
	rm -f history.info* readline.info*

clean-dvi:
	rm -f hist.?? hist.???
	rm -f rlman.?? rlman.???

Makefile: $(srcdir)/Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) ./config.status
