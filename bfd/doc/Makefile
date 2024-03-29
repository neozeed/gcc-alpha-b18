# Generated automatically from Makefile.in by configure.
#
# Makefile
#   Copyright (C) 1990, 1991, 1992, 1993 Free Software Foundation
#
# This file is free software; you can redistribute it and/or modify
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
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
#

srcdir = .

prefix = /usr/local

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

MKDOC=./chew
SHELL = sh

INSTALL = /GCC-MS/CYGWIN/ginstall -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

MAKEINFO = makeinfo
TEXI2DVI = texi2dvi
CFLAGS = -g

CC_FOR_BUILD = $(CC)

#### Host, target, and site specific Makefile fragments come in here.
###

.c.o:
	$(CC) -c -I.. -I$(srcdir)/.. -I$(srcdir)/../../include $(H_CFLAGS) $(CFLAGS) $<

DOCFILES = aoutx.texi  archive.texi archures.texi \
	bfd.texi  cache.texi coffcode.texi \
	core.texi elf.texi elfcode.texi  format.texi  libbfd.texi  \
	opncls.texi  reloc.texi  section.texi  \
	syms.texi  targets.texi init.texi hash.texi linker.texi

PROTOS = archive.p archures.p bfd.p \
	 core.p format.p \
	libbfd.p opncls.p reloc.p \
	section.p syms.p targets.p  \
	format.p  core.p init.p

IPROTOS = cache.ip libbfd.ip reloc.ip init.ip archures.ip coffcode.ip

# SRCDOC, SRCPROT, SRCIPROT only used to sidestep Sun Make bug in interaction 
# between VPATH and suffix rules.  If you use GNU Make, perhaps other Makes,
# you don't need these three:
SRCDOC = $(srcdir)/../aoutx.h  $(srcdir)/../archive.c \
	$(srcdir)/../archures.c $(srcdir)/../bfd.c \
	$(srcdir)/../cache.c $(srcdir)/../coffcode.h \
	$(srcdir)/../corefile.c $(srcdir)/../elf.c \
	$(srcdir)/../elfcode.h  $(srcdir)/../format.c \
	$(srcdir)/../libbfd.c $(srcdir)/../opncls.c \
	$(srcdir)/../reloc.c  $(srcdir)/../section.c \
	$(srcdir)/../syms.c  $(srcdir)/../targets.c \
	$(srcdir)/../hash.c $(srcdir)/../linker.c

SRCPROT = $(srcdir)/../archive.c $(srcdir)/../archures.c \
	$(srcdir)/../bfd.c $(srcdir)/../coffcode.h $(srcdir)/../corefile.c \
	$(srcdir)/../format.c $(srcdir)/../libbfd.c \
	$(srcdir)/../opncls.c $(srcdir)/../reloc.c \
	$(srcdir)/../section.c $(srcdir)/../syms.c \
	$(srcdir)/../targets.c $(srcdir)/../init.c

SRCIPROT = $(srcdir)/../cache.c $(srcdir)/../libbfd.c \
	$(srcdir)/../reloc.c $(srcdir)/../cpu-h8300.c \
	$(srcdir)/../cpu-i960.c $(srcdir)/../archures.c \
	$(srcdir)/../init.c

STAGESTUFF = $(DOCFILES) *.info*

TEXIDIR = $(srcdir)/../../texinfo/fsf

all install:

info: bfd.info

dvi: bfd.dvi

install-info: info
	if [ -r bfd.info ]; then \
	  dir=.; \
	else \
	  dir=$(srcdir); \
	fi; \
	for i in `cd $$dir; echo *.info*`; do \
	  $(INSTALL_DATA) $$dir/$$i $(infodir)/$$i; \
	done

docs: $(MKDOC) protos bfd.info bfd.dvi bfd.ps

$(MKDOC): chew.o
	$(CC_FOR_BUILD) -o $(MKDOC) chew.o $(LOADLIBES) $(LDFLAGS)

chew.o: chew.c
	$(CC_FOR_BUILD) -c -I.. -I$(srcdir)/.. -I$(srcdir)/../../include $(H_CFLAGS) $(CFLAGS) $(srcdir)/chew.c

protos: libbfd.h libcoff.h bfd.h


# We can't replace these rules with an implicit rule, because
# makes without VPATH support couldn't find the .h files in `..'.

# We use stamp-XXX targets so that we can distribute the info files,
# and permit people to rebuild them, without requiring the makeinfo
# program.  If somebody tries to rebuild info, but none of the .texi
# files have changed, then this Makefile will build chew, and will
# build all of the stamp files, but will not actually have to rebuild
# bfd.info.

stamp-aoutx: $(MKDOC) $(srcdir)/../aoutx.h $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../aoutx.h >aoutx.tmp
	$(srcdir)/../../move-if-change aoutx.tmp aoutx.texi
	touch stamp-aoutx
aoutx.texi: stamp-aoutx

stamp-archive: $(MKDOC) $(srcdir)/../archive.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../archive.c >archive.tmp
	$(srcdir)/../../move-if-change archive.tmp archive.texi
	touch stamp-archive
archive.texi: stamp-archive

stamp-archures: $(MKDOC) $(srcdir)/../archures.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str < $(srcdir)/../archures.c >archures.tmp
	$(srcdir)/../../move-if-change archures.tmp archures.texi
	touch stamp-archures
archures.texi: stamp-archures

stamp-bfd: $(MKDOC) $(srcdir)/../bfd.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str < $(srcdir)/../bfd.c >bfd.tmp
	$(srcdir)/../../move-if-change bfd.tmp bfd.texi
	touch stamp-bfd
bfd.texi: stamp-bfd

stamp-cache: $(MKDOC) $(srcdir)/../cache.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str < $(srcdir)/../cache.c >cache.tmp
	$(srcdir)/../../move-if-change cache.tmp cache.texi
	touch stamp-cache
cache.texi: stamp-cache

stamp-coffcode: $(MKDOC) $(srcdir)/../coffcode.h $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../coffcode.h >coffcode.tmp
	$(srcdir)/../../move-if-change coffcode.tmp coffcode.texi
	touch stamp-coffcode
coffcode.texi: stamp-coffcode

stamp-core: $(MKDOC) $(srcdir)/../corefile.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../corefile.c >core.tmp
	$(srcdir)/../../move-if-change core.tmp core.texi
	touch stamp-core
core.texi: stamp-core

stamp-elf: $(MKDOC) $(srcdir)/../elf.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../elf.c >elf.tmp
	$(srcdir)/../../move-if-change elf.tmp elf.texi
	touch stamp-elf
elf.texi: stamp-elf

stamp-elfcode: $(MKDOC) $(srcdir)/../elfcode.h $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../elfcode.h >elfcode.tmp
	$(srcdir)/../../move-if-change elfcode.tmp elfcode.texi
	touch stamp-elfcode
elfcode.texi: stamp-elfcode

stamp-format: $(MKDOC) $(srcdir)/../format.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../format.c >format.tmp
	$(srcdir)/../../move-if-change format.tmp format.texi
	touch stamp-format
format.texi: stamp-format

stamp-libbfd: $(MKDOC) $(srcdir)/../libbfd.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str < $(srcdir)/../libbfd.c >libbfd.tmp
	$(srcdir)/../../move-if-change libbfd.tmp libbfd.texi
	touch stamp-libbfd
libbfd.texi: stamp-libbfd

stamp-opncls: $(MKDOC) $(srcdir)/../opncls.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str  <$(srcdir)/../opncls.c >opncls.tmp
	$(srcdir)/../../move-if-change opncls.tmp opncls.texi
	touch stamp-opncls
opncls.texi: stamp-opncls

stamp-reloc: $(MKDOC) $(srcdir)/../reloc.c
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../reloc.c >reloc.tmp
	$(srcdir)/../../move-if-change reloc.tmp reloc.texi
	touch stamp-reloc
reloc.texi: stamp-reloc

stamp-section: $(MKDOC) $(srcdir)/../section.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../section.c >section.tmp
	$(srcdir)/../../move-if-change section.tmp section.texi
	touch stamp-section
section.texi: stamp-section

stamp-syms: $(MKDOC) $(srcdir)/../syms.c
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../syms.c >syms.tmp
	$(srcdir)/../../move-if-change syms.tmp syms.texi
	touch stamp-syms
syms.texi: stamp-syms

stamp-targets: $(MKDOC) $(srcdir)/../targets.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../targets.c >targets.tmp
	$(srcdir)/../../move-if-change targets.tmp targets.texi
	touch stamp-targets
targets.texi: stamp-targets

stamp-init: $(MKDOC) $(srcdir)/../init.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../init.c >init.tmp
	$(srcdir)/../../move-if-change init.tmp init.texi
	touch stamp-init
init.texi: stamp-init

stamp-hash: $(MKDOC) $(srcdir)/../hash.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../hash.c >hash.tmp
	$(srcdir)/../../move-if-change hash.tmp hash.texi
	touch stamp-hash
hash.texi: stamp-hash

stamp-linker: $(MKDOC) $(srcdir)/../linker.c $(srcdir)/doc.str
	$(MKDOC) -f $(srcdir)/doc.str <$(srcdir)/../linker.c >linker.tmp
	$(srcdir)/../../move-if-change linker.tmp linker.texi
	touch stamp-linker
linker.texi: stamp-linker

libbfd.h: $(srcdir)/../libbfd-in.h	\
	$(srcdir)/../init.c		\
	$(srcdir)/../libbfd.c		\
	$(srcdir)/../cache.c		\
	$(srcdir)/../reloc.c		\
	$(srcdir)/../cpu-h8300.c	\
	$(srcdir)/../cpu-i960.c		\
	$(srcdir)/../archures.c		\
	$(srcdir)/../elfcode.h		\
	$(srcdir)/proto.str		\
	$(MKDOC)
	rm -f libbfd.h
	cat $(srcdir)/../libbfd-in.h >libbfd.h 
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../init.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../libbfd.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../cache.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../reloc.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../cpu-h8300.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../cpu-i960.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../archures.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../elf.c >>libbfd.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../elfcode.h >>libbfd.h

libcoff.h: $(srcdir)/../libcoff-in.h	\
	$(srcdir)/../coffcode.h		\
	$(srcdir)/proto.str		\
	$(MKDOC)
	rm -f libcoff.h
	cat $(srcdir)/../libcoff-in.h >libcoff.h
	$(MKDOC) -i -f $(srcdir)/proto.str  < $(srcdir)/../coffcode.h >>libcoff.h

bfd.h: $(srcdir)/../bfd-in.h 		\
	$(srcdir)/../init.c 		\
	$(srcdir)/../opncls.c 		\
	$(srcdir)/../libbfd.c 		\
	$(srcdir)/../section.c 		\
	$(srcdir)/../archures.c		\
	$(srcdir)/../reloc.c		\
	$(srcdir)/../syms.c		\
	$(srcdir)/../bfd.c		\
	$(srcdir)/../archive.c		\
	$(srcdir)/../corefile.c		\
	$(srcdir)/../targets.c		\
	$(srcdir)/../format.c		\
	$(srcdir)/proto.str		\
	$(MKDOC)
	rm -f bfd.h
	cat $(srcdir)/../bfd-in.h >bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../init.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../opncls.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../libbfd.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../section.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../archures.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../reloc.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../syms.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../bfd.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../archive.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../corefile.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../targets.c >>bfd.h
	$(MKDOC) -f $(srcdir)/proto.str<$(srcdir)/../format.c >>bfd.h	
	echo "#ifdef __cplusplus" >>bfd.h
	echo "}" >>bfd.h
	echo "#endif" >>bfd.h
	echo "#endif" >>bfd.h


clean-info: clean

mostlyclean:
	rm -rf *.log *.ps *~* *.dvi *# $(MKDOC) *.o

clean: mostlyclean
	rm -rf $(STAGESTUFF) stamp-*
	rm -f *.p *.ip  bfd.?? bfd.??? bfd.h libbfd.h libcoff.h texput.log 

distclean: mostlyclean
	rm -f *.p *.ip  bfd.?? bfd.??? bfd.h libbfd.h libcoff.h texput.log 
	rm -f stamp-*
	rm -f Makefile config.status

maintainer-clean realclean: clean
	rm -f Makefile config.status

bfd.info: $(DOCFILES) bfdsumm.texi bfd.texinfo
	$(MAKEINFO) -I$(srcdir) -o bfd.info $(srcdir)/bfd.texinfo

bfd.dvi: $(DOCFILES) bfdsumm.texi bfd.texinfo
	$(TEXI2DVI) $(srcdir)/bfd.texinfo

bfd.ps: bfd.dvi
	dvips bfd -o

quickdoc: $(DOCFILES) bfdsumm.texi bfd.texinfo
	TEXINPUTS=${TEXIDIR}:.:$$TEXINPUTS tex bfd.texinfo

stage1: force
	- mkdir stage1
	- mv -f $(STAGESTUFF) stage1

stage2: force
	- mkdir stage2
	- mv -f $(STAGESTUFF) stage2

stage3: force
	- mkdir stage3
	- mv -f $(STAGESTUFF) stage3

against=stage2

comparison: force
	for i in $(STAGESTUFF) ; do cmp $$i $(against)/$$i || exit 1 ; done

de-stage1: force
	- (cd stage1 ; mv -f $(STAGESTUFF) ..)
	- rmdir stage1

de-stage2: force
	- (cd stage2 ; mv -f $(STAGESTUFF) ..)
	- rmdir stage2

de-stage3: force
	- (cd stage3 ; mv -f $(STAGESTUFF) ..)
	- rmdir stage3

force:

Makefile: $(srcdir)/Makefile.in
	cd .. && CONFIG_FILES=doc/$@ CONFIG_HEADERS= $(SHELL) ./config.status

