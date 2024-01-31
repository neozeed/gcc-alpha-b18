# This file was generated automatically by configure.  Do not edit.
VPATH = .
links = 
host_alias = i386-cygwin32
host_cpu = i386
host_vendor = pc
host_os = cygwin32
host_canonical = i386-pc-cygwin32
target_alias = i386-cygwin32
target_cpu = i386
target_vendor = pc
target_os = cygwin32
target_canonical = i386-pc-cygwin32
build_alias = i386-cygwin32
build_cpu = i386
build_vendor = pc
build_os = cygwin32
build_canonical = i386-pc-cygwin32
host_makefile_frag = host/any
# Makefile for newlib.
# Copyright (c) 1994, 1995, 1997 Cygnus Support.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# at Cygnus Support, Inc.  Cygnus Support, Inc. may not be used to
# endorse or promote products derived from this software without
# specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

# This copy of $(VERSION) is used when building net newlib releases.
VERSION=1.8-B19

srcdir = .

prefix = /usr/local

exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib
tooldir = $(exec_prefix)/i386-cygwin32

datadir = $(prefix)/share

mandir = $(prefix)/man
man1dir = $(mandir)/man1
man2dir = $(mandir)/man2
man3dir = $(mandir)/man3
man4dir = $(mandir)/man4
man5dir = $(mandir)/man5
man6dir = $(mandir)/man6
man7dir = $(mandir)/man7
man8dir = $(mandir)/man8
man9dir = $(mandir)/man9
infodir = $(prefix)/info
includedir = $(prefix)/include

SHELL = sh

# Multilib support variables.
# TOP is used instead of MULTI{BUILD,SRC}TOP.
MULTISRCTOP = ../
MULTIBUILDTOP = 
MULTIDIRS = 
MULTISUBDIR = 
MULTIDO = $(MAKE)
MULTICLEAN = $(MAKE)

INSTALL = $$srcrootpre/../install-sh -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL)

AR_FLAGS = qv
MAKEINFO = makeinfo

# We must compile makedoc with a program that runs on the build
# environment.
CC_FOR_BUILD = cc
CFLAGS_FOR_BUILD =

TOP = .
SRCTOP = .

machine_dir = i386
sys_dir = cygwin32
CRT0_DIR = libc
CRT0 = crt0.o

#### Host, target, and site specific Makefile fragments come in here.
# These are set by configure.
program_transform_name = 

# Find the tools used to build newlib.
# ${rootpre} should be set to the name of the top level newlib build directory
# followed by a '/'.  Likewise with ${srcrootpre}.  If ${rootpre} is not set,
# we use program_transform_name to guess the name of the program.
# Each Makefile must define $(TOP) and $(SRCTOP); they will usually be the
# same, but they are different when building multiple versions with
# different compilation flags: $(TOP) will typically contain extra ../'s.
CC = gcc
AS = `if [ -f $${rootpre}$(TOP)/../../gas/as.new ] ; \
	then echo $${rootpre}$(TOP)/../../gas/as.new ; \
	else t='$(program_transform_name)'; echo as | sed -e '' $$t ; fi`
DLLTOOL = `if [ -f $${rootpre}$(TOP)/../../binutils/dlltool ] ; \
	then echo $${rootpre}$(TOP)/../../binutils/dlltool ; \
	else t='$(program_transform_name)'; echo dlltool | sed -e '' $$t ; fi`
AR = `if [ -f $${rootpre}$(TOP)/../../binutils/ar ] ; \
	then echo $${rootpre}$(TOP)/../../binutils/ar ; \
	else t='$(program_transform_name)'; echo ar | sed -e '' $$t ; fi`
AR_FLAGS = qc
RANLIB = `if [ -f $${rootpre}$(TOP)/../../binutils/ranlib ] ; \
	then echo $${rootpre}$(TOP)/../../binutils/ranlib ; \
	else t='$(program_transform_name)'; echo ranlib | sed -e '' $$t ; fi`

# CFLAGS is the general CFLAGS.  CROSS_CFLAGS is for special newlib
# flags.  TARGET_CFLAGS is for target specific flags, and is
# initialized by the configure script.  NEWLIB_CFLAGS is for flags we
# must always pass to gcc.
CFLAGS = -g
CROSS_CFLAGS =
TARGET_CFLAGS = -O2 -DHAVE_OPENDIR -DHAVE_RENAME -DSIGNAL_PROVIDED
NEWLIB_CFLAGS = -fno-builtin

# Get the include directories.  Note that in subdirectories, the
# string passed down from the top newlib Makefile will override this
# expression.

# If we are doing a cygwin32 build, we need to add a -I for the winsup
# header files.  We can't check whether winsup has been configured at
# this point, because newlib is normally built before winsup is
# configured.

INCLUDES = ` \
  srcrootpre=$${srcrootpre-$(srcdir)/}; \
  if [ x$(target_os) = xcygwin32 ]; then \
    echo -I$${rootpre}$(TOP)/targ-include -I$${srcrootpre}$(SRCTOP)/libc/include -I$${srcrootpre}$(SRCTOP)/../winsup/include; \
  else \
    echo -I$${rootpre}$(TOP)/targ-include -I$${srcrootpre}$(SRCTOP)/libc/include; \
  fi`

# Using CFLAGS here may be confusing if the user has given a special
# CFLAGS intended for use on the host, since we are passing it to the
# cross-compiler; I'm not sure what to do about this.  INCLUDES is
# from the top level Makefile.
.c.o:
	$(CC) $(CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) $(NEWLIB_CFLAGS) $(INCLUDES) -c $<

.s.o:
	$(AS) $(INCLUDES) -o $*.o $<

.S.o:
	$(CC) $(CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) $(NEWLIB_CFLAGS) $(INCLUDES) -c $<

# Build documentation from a .c file.
CHEW = `srcrootpre=$${srcrootpre-$(srcdir)/}; echo $${rootpre}$(TOP)/doc/makedoc -f $${srcrootpre}$(SRCTOP)/doc/doc.str`

.c.def:
	$(CHEW) < $< >$*.def 2>$*.ref
###

SUBDIRS = libc libm doc testsuite

# These are roughly topologically sorted in order to make porting more
# streamlined.
FLAGS_TO_PASS = \
	"prefix=$(prefix)" \
	"exec_prefix=$(exec_prefix)" \
	"infodir=$(infodir)" \
	"tooldir=$(tooldir)" \
	"CC=$(CC)" \
	"CFLAGS=$(CFLAGS)" \
	"AR=$(AR)" \
	"AR_FLAGS=$(AR_FLAGS)" \
	"DLLTOOL=$(DLLTOOL)" \
	"RANLIB=$(RANLIB)" \
	"MAKEINFO=$(MAKEINFO)" \
	"INSTALL=$(INSTALL)" \
	"INSTALL_DATA=$(INSTALL_DATA)" \
	"INSTALL_PROGRAM=$(INSTALL_PROGRAM)" \
	"AS=$(AS)" \
	"CROSS_CFLAGS=$(CROSS_CFLAGS)" \
	"TARGET_CFLAGS=$(TARGET_CFLAGS)" \
	"INCLUDES=$(INCLUDES)"

# The functions ldexp, frexp and modf are traditionally supplied in
# both libc.a and libm.a.  We build them in libm.a and copy them over,
# along with some required supporting routines.
MATHOBJS_IN_LIBC = \
	s_isinf.o sf_isinf.o \
	s_isnan.o sf_isnan.o \
	s_ldexp.o sf_ldexp.o \
	s_frexp.o sf_frexp.o s_modf.o sf_modf.o \
	s_scalbn.o sf_scalbn.o s_finite.o sf_finite.o \
	s_copysign.o sf_copysign.o s_infconst.o

all: stmp-targ-include libm.a libc.a $(CRT0) force
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre ; \
	$(MULTIDO) $(FLAGS_TO_PASS) multi-do DO=all

libc.a: libc/libc.a libm.a
	rm -rf libc.a libg.a tmp
	mkdir tmp
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre ; \
	cd tmp ; \
		$(AR) x ../libm.a $(MATHOBJS_IN_LIBC) ; \
		$(AR) x ../libc/libc.a ; \
		$(AR) $(AR_FLAGS) ../$@ *.o
	$(RANLIB) libc.a
	ln libc.a libg.a
	rm -rf tmp

libc/libc.a: stmp-targ-include force
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	cd libc; $(MAKE) $(FLAGS_TO_PASS) all

libm.a: libm/libm.a
	rm -f $@
	ln libm/libm.a $@ >/dev/null 2>/dev/null || cp libm/libm.a $@

libm/libm.a: stmp-targ-include force
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	cd libm; $(MAKE) $(FLAGS_TO_PASS)

crt0.o: $(CRT0_DIR)/$(CRT0)
	rm -f $@
	ln $(CRT0_DIR)/$(CRT0) $@ >/dev/null 2>/dev/null \
	 || cp $(CRT0_DIR)/$(CRT0) $@

$(CRT0_DIR)/$(CRT0): force
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	(cd $(CRT0_DIR) ; \
		$(MAKE) $(FLAGS_TO_PASS) $(CRT0)) \
	|| exit 1

# The targ-include directory just holds the includes files for the
# particular system and machine we have been configured for.  It is
# used while building.
stmp-targ-include: config.status
	-rm -rf targ-include stmp-targ-include
	mkdir targ-include targ-include/sys targ-include/machine
	-for i in $(srcdir)/libc/machine/$(machine_dir)/machine/*.h; do \
	    if [ -f $$i ]; then \
	      cp $$i targ-include/machine/`basename $$i`; \
	    else true; fi ; \
	  done
	-for i in $(srcdir)/libc/sys/$(sys_dir)/include/*.h; do \
	    if [ -f $$i ]; then \
	      cp $$i targ-include/`basename $$i`; \
	    else true; fi ; \
	  done
	-for i in $(srcdir)/libc/sys/$(sys_dir)/sys/*.h; do \
	    if [ -f $$i ]; then \
	      cp $$i targ-include/sys/`basename $$i`; \
	    else true; fi ; \
	  done
	touch $@

testsuite:
	if [ -d testsuite ]; then \
		(rootme=`pwd`/ ; export rootme ; \
		 rootsrc=`cd $(srcdir); pwd`/ ; export rootsrc ; \
		 cd testsuite; $(MAKE) FLAGS_TO_PASS=$(FLAGS_TO_PASS)); \
	else true ; fi

check: force
	if [ -d testsuite ]; then \
	  rootme=`pwd`; export rootme; cd testsuite; \
	  $(MAKE) $(FLAGS_TO_PASS) check; \
	else true; fi

.PHONY: clean-info

subdir_do:
	@for i in $(DODIRS); do \
		if [ -f ./$$i/Makefile ] ; then \
			if (cd ./$$i; $(MAKE) $(FLAGS_TO_PASS) $(DO)) ; \
			then true ; \
			else exit 1 ; \
			fi ; \
		else true; \
		fi ; \
	done

info dvi docs:
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	(cd ./doc; $(MAKE) "CC_FOR_BUILD=$(CC_FOR_BUILD)" \
		"CFLAGS_FOR_BUILD=$(CFLAGS_FOR_BUILD)" \
		$(FLAGS_TO_PASS) all);
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for i in $(SUBDIRS); do \
		if [ -f ./$$i/Makefile ] ; then \
			if (cd ./$$i; $(MAKE) "CHEW=$(CHEW)" \
				$(FLAGS_TO_PASS) $@) ; \
			then true ; \
			else exit 1 ; \
			fi ; \
		else true; \
		fi ; \
	done

clean-here:
	rm -f *.a TEMP errs core *.o *~ \#* TAGS *.E 
	rm -rf targ-include stmp-targ-include

clean: clean-here
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do
	@$(MULTICLEAN) multi-clean DO=$@

mostlyclean:
	rm -f TEMP errs core *.o *~ \#* TAGS *.E 
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do
	@$(MULTICLEAN) multi-clean DO=$@

distclean maintainer-clean realclean: clean-here
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=$@ DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do
	@$(MULTICLEAN) multi-clean DO=$@
	rm -f Makefile config.status

install:
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=install DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do
	# install all the libraries we find
	for i in *.a ; do \
		$(INSTALL_PROGRAM) $$i $(tooldir)/lib$(MULTISUBDIR)/$$i ; \
	done
	# but libg.a is a copy of libc.a
	-rm -f $(tooldir)/lib$(MULTISUBDIR)/libg.a
	ln $(tooldir)/lib$(MULTISUBDIR)/libc.a $(tooldir)/lib$(MULTISUBDIR)/libg.a	
	# ranlibize them all
	for i in  $(tooldir)/lib$(MULTISUBDIR)/*.a ; do \
		$(RANLIB) $$i ; \
	done
	# now crt0
	-if [ -f crt0.o ] ; then \
	    $(INSTALL_PROGRAM) crt0.o $(tooldir)/lib$(MULTISUBDIR)/crt0.o; \
	  else true; fi
	# and all the headers
	@$(MULTIDO) $(FLAGS_TO_PASS) multi-do DO=install
	-if [ -z "$(MULTISUBDIR)" ]; then \
	  for i in $(srcdir)/libc/include/*.h; do \
	    $(INSTALL_DATA) $$i $(tooldir)/include/`basename $$i`; \
	  done; \
	  for i in $(srcdir)/libc/include/machine/*.h; do \
	    $(INSTALL_DATA) $$i $(tooldir)/include/machine/`basename $$i`; \
	  done; \
	  for i in $(srcdir)/libc/machine/$(machine_dir)/machine/*.h; do \
	    if [ -f $$i ]; then \
	      $(INSTALL_DATA) $$i $(tooldir)/include/machine/`basename $$i`; \
	    else true; fi ; \
	  done; \
	  for i in $(srcdir)/libc/include/sys/*.h; do \
	    $(INSTALL_DATA) $$i $(tooldir)/include/sys/`basename $$i`; \
	  done; \
	  for i in $(srcdir)/libc/sys/$(sys_dir)/sys/*.h; do \
	    if [ -f $$i ]; then \
	      $(INSTALL_DATA) $$i $(tooldir)/include/sys/`basename $$i`; \
	    else true; fi ; \
	  done ; \
	  for i in $(srcdir)/libc/sys/$(sys_dir)/include/*.h; do \
	    if [ -f $$i ]; then \
	      $(INSTALL_DATA) $$i $(tooldir)/include/`basename $$i`; \
	    else true; fi ; \
	  done ; \
	else true; fi

install-info:
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=install-info DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do

clean-info:
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) DO=clean-info DODIRS="$(SUBDIRS)" $(FLAGS_TO_PASS) subdir_do

norecurse etags tags: TAGS

TAGS: force
	etags `make ls`

ls:
	@echo Makefile
	@for i in $(SUBDIRS); \
	do \
		(cd $$i; \
			pwd=`pwd`; \
			wd=`basename $$pwd`; \
			for j in `make ls`; \
			do \
				echo $$wd/$$j; \
			done) \
	done

.PHONY: force
force:

## This is ugly, but I don't want GNU make to put these variables in
## the environment.  They are not used here, but are sometimes passed
## in from the top level Makefile.  Older makes will see this as a set
## of targets with no dependencies and no actions.
unexport CXX CXX_FOR_TARGET BISON :

.NOEXPORT:
MAKEOVERRIDES=


# with the gnu make, this is done automatically.

Makefile: Makefile.in configure.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) config.status

# end of Makefile.in

# FIXME: There should be an @-sign in front of the `if'.
# Leave out until this is tested a bit more.
multi-do:
	if [ -z "$(MULTIDIRS)" ]; then \
	  true; \
	else \
	  rootpre=`pwd`/; export rootpre; \
	  srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	  lib=`echo $${rootpre} | sed -e 's,^.*/\([^/][^/]*\)/$$,\1,'`; \
	  compiler="$(CC)"; \
	  for i in `$${compiler} --print-multi-lib 2>/dev/null`; do \
	    dir=`echo $$i | sed -e 's/;.*$$//'`; \
	    if [ "$${dir}" = "." ]; then \
	      true; \
	    else \
	      if [ -d ../$${dir}/$${lib} ]; then \
		flags=`echo $$i | sed -e 's/^[^;]*;//' -e 's/@/ -/g'`; \
		if (cd ../$${dir}/$${lib}; $(MAKE) $(FLAGS_TO_PASS) \
				CFLAGS="$(CFLAGS) $${flags}" \
				CXXFLAGS="$(CXXFLAGS) $${flags}" \
				LIBCFLAGS="$(LIBCFLAGS) $${flags}" \
				LIBCXXFLAGS="$(LIBCXXFLAGS) $${flags}" \
				$(DO)); then \
		  true; \
		else \
		  exit 1; \
		fi; \
	      else true; \
	      fi; \
	    fi; \
	  done; \
	fi

# FIXME: There should be an @-sign in front of the `if'.
# Leave out until this is tested a bit more.
multi-clean:
	if [ -z "$(MULTIDIRS)" ]; then \
	  true; \
	else \
	  lib=`pwd | sed -e 's,^.*/\([^/][^/]*\)$$,\1,'`; \
	  for dir in Makefile $(MULTIDIRS); do \
	    if [ -f ../$${dir}/$${lib}/Makefile ]; then \
	      if (cd ../$${dir}/$${lib}; $(MAKE) $(FLAGS_TO_PASS) $(DO)); \
	      then true; \
	      else exit 1; \
	      fi; \
	    else true; \
	    fi; \
	  done; \
	fi
