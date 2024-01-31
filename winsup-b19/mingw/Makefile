# Generated automatically from Makefile.in by configure.
# Makefile.in for the winsup/mingw directory.
# Copyright (c) 1995, 1996, 1997 Cygnus Solutions

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
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

# This makefile requires GNU make.

srcdir = .
objdir = .

target_alias = alpha-cygwin32
prefix = /usr/local

program_transform_name = s,x,x,
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
tooldir = $(exec_prefix)/$(target_alias)
datadir = ${prefix}/share
infodir = ${prefix}/info
includedir = ${prefix}/include

SHELL = /bin/sh

INSTALL = /gcc-ms/CYGWIN/ginstall -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
mkinstalldirs = $(SHELL) $(srcdir)/../../mkinstalldirs

CC = cc
# FIXME: Which is it, CC or CC_FOR_TARGET?
CC_FOR_TARGET = $(CC)
AS_FOR_TARGET = $(AS_FOR_TARGET)
CFLAGS = 
CXXFLAGS = 

INCLUDES = -I$(srcdir)/include -I$(srcdir)/include/nonansi -I$(srcdir)/../include/ -nostdinc++
LIBGCC=`$(CC) -print-libgcc-file-name`
ALL_CFLAGS = $(CFLAGS) $(INCLUDES)
ALL_CXXFLAGS = $(CXXFLAGS) $(INCLUDES)

AS = as
AR = ar
LD = ld
AR_FLAGS = rcv
RANLIB = ranlib
DLLTOOL = dlltool
DLLTOOLFLAGS = 

CRT0S = mcrt0.o dllcrt0.o crt_noglob.o
MING_OBJS = hugeval.o main.o dllmain.o crtglob.o dirent.o
MOLD_OBJS = ctype_old.o string_old.o # oldnames.o 
LIBS = libmingw32.a libmoldnames.a moldnames.dll libcrtdll.a
LIBGCC=`$(CC) -print-libgcc-file-name`

all: $(CRT0S) $(LIBS)

libcrtdll.a: $(srcdir)/crtdll.def
crtdll.dll: libcrtdll.a

libmoldnames.a: $(srcdir)/moldnames.def $(MOLD_OBJS)
#	$(AR) $(AR_FLAGS) libtemp.a $(MOLD_OBJS)

#moldnames.def: libmoldnames.a
#moldnames.dll: $(srcdir)/moldnames.def 

libmingw32.a: $(MING_OBJS)
	$(AR) $(AR_FLAGS) libmingw32.a $(MING_OBJS)

info: $(DOC)

info-html: $(DOC) $(HTMLDOC)

install-info: info

install: all
	$(mkinstalldirs) $(bindir) $(tooldir)/lib 
	for i in $(LIBS); do \
		$(INSTALL_DATA) $$i $(tooldir)/lib/$$i ; \
	done
	for i in $(CRT0S); do \
		$(INSTALL_DATA) $$i $(tooldir)/lib/$$i ; \
	done
	for sub in . nonansi nonansi/sys sys ; do \
		$(mkinstalldirs) $(tooldir)/include/mingw32/$$sub ; \
		for i in $(srcdir)/include/$$sub/*.h ; do \
		  $(INSTALL_DATA) $$i $(tooldir)/include/mingw32/$$sub/`basename $$i` ; \
		done ; \
	done


.SUFFIXES: .y $(SUFFIXES) .cc .def .a

%.def: lib%.a
	echo EXPORTS > $@
#	echo $(IMPURE_PTR) = _impure_ptr >> $@
	nm libtemp.a | sed -n '/^........ [BCDRT] _/s/[^_]*_//p' >> $@

%.exp: %.def
	$(DLLTOOL) $(DLLTOOLFLAGS) $(DLLTOOLFLAGS-$*)		\
		--as=$(AS) -k					\
		--def $<					\
		--dllname $*.dll				\
		--output-exp $*.exp	 		        \
		--base-file $*.base

%.dll: %.def
	$(LD) --base-file=$*.base -dll -o $*.dll -e _dll_entry@12 $(LIBGCC) -U lib$*.a
	$(DLLTOOL) $(DLLTOOLFLAGS)			\
		--as=$(AS)				\
		--def $(srcdir)/$*.def			\
		--dllname $*.dll			\
		--output-exp $*.exp			\
		--base-file $*.base			\
		--output-lib lib$*.a
	$(LD) --base-file=$*.base $*.exp -dll -o $*.dll -e_dll_entry@12 $(LIBGCC) -U lib$*.a
	$(DLLTOOL) --as=$(AS)				\
		--def $(srcdir)/$*.def			\
 		--dllname $*.dll		        \
		--output-exp $*.exp			\
		--base-file $*.base			\
		--output-lib lib$*.a
	$(LD) $*.exp -dll -o $*.dll -e _dll_entry@12 $(LIBGCC) -U lib$*.a
	rm -f lib$*.a

lib%.a:%.def
	$(DLLTOOL) --as=$(AS) -k --dllname $*.dll --output-lib lib$*.a --def $<

.cc.o:
	$(CC) -c -fno-rtti $(ALL_CXXFLAGS) $<

.c.o:
	$(CC) -c $(ALL_CFLAGS) $<

clean:
	-rm -f *.o *.dll *.a *.exp junk *.base *.def

maintainer-clean realclean: clean 
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."
	-rm -fr configure

Makefile: Makefile.in config.status configure
	$(SHELL) config.status

config.status: configure
	$(SHELL) config.status --recheck

mcrt0.o: $(srcdir)/mcrt0.c
dllcrt0.o: $(srcdir)/dllcrt0.c
crt_noglob.o: $(srcdir)/crt_noglob.c
crtglob.o: $(srcdir)/crtglob.c
ctype_old.o: $(srcdir)/ctype_old.c
dirent.o: $(srcdir)/dirent.c
dllmain.o: $(srcdir)/dllmain.c
init.o: $(srcdir)/init.c
string_old.o: $(srcdir)/string_old.c
main.o: $(srcdir)/main.c
hugeval.o: $(srcdir)/hugeval.c
oldnames.o: $(srcdir)/oldnames.c
