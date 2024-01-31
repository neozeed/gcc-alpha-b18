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
host_makefile_frag = ../host/any
# Makefile for newlib/libc.
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

VERSION=1.8-B19

srcdir = .

prefix = /usr/local

exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib

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

# Used for docn; upper-level Makefile may clear this in some configs
signal_dir = signal

SHELL = sh

INSTALL = install -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL)

AR_FLAGS = qv
MAKEINFO = makeinfo
TEXI2DVI = texi2dvi
TEXIDIR=$(srcdir)/../../texinfo
SET_TEXINPUTS = TEXINPUTS=${TEXIDIR}:.:$(srcdir):$$TEXINPUTS

TOP = ..
SRCTOP = ..
TARGETDOC = `echo $${rootpre}./targetdep.tex`

.NOEXPORT:
MAKEOVERRIDES=

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

# These are roughly topologically sorted in order to make porting more
# streamlined.
FLAGS_TO_PASS = \
	"CC=$(CC)" \
	"CFLAGS=$(CFLAGS)" \
	"AR=$(AR)" \
	"AR_FLAGS=$(AR_FLAGS)" \
	"AS=$(AS)" \
	"DLLTOOL=$(DLLTOOL)" \
	"CROSS_CFLAGS=$(CROSS_CFLAGS)" \
	"TARGET_CFLAGS=$(TARGET_CFLAGS)" \
	"TARGET_ASFLAGS=$(TARGET_ASFLAGS)" \
	"INCLUDES=$(INCLUDES)"

# The order of SUBDIRS is very important to the integrated documentation;
# DO NOT CHANGE this order without considering doc impact.
#
LIBC_SIGNAL_LIB = signal/lib.a
LIBC_SYS_LIB = sys/lib.a
LIBC_MACHINE_LIB = machine/lib.a
LIBC_UNIX_LIB = 
LIBC_POSIX_LIB = posix/lib.a
LIBC_SYSCALL_LIB = syscalls/lib.a
CRT0 = crt0.o

SUBDIRS = stdlib ctype stdio string signal time locale sys reent errno \
	misc machine unix posix syscalls

SUBLIBS = \
	stdlib/lib.a \
	ctype/lib.a \
	stdio/lib.a \
	string/lib.a \
	$(LIBC_SIGNAL_LIB) \
	time/lib.a \
	locale/lib.a \
	$(LIBC_SYS_LIB) \
	reent/lib.a \
	errno/lib.a \
	misc/lib.a \
	$(LIBC_MACHINE_LIB) \
	$(LIBC_UNIX_LIB) \
	$(LIBC_POSIX_LIB) \
	$(LIBC_SYSCALL_LIB)

all: libc.a $(CRT0)
libc.a: $(SUBLIBS)
	rm -f $@
	rm -rf tmp
	mkdir tmp
	rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre ; \
	cd tmp ; \
		for i in $(SUBLIBS) ; do \
			$(AR) x ../$$i ; \
		done ; \
		$(AR) $(AR_FLAGS) ../$@ *.o
	$(RANLIB) $@
	rm -rf tmp

crt0.o: sys/crt0.o
	rm -f $@
	ln sys/crt0.o $@ >/dev/null 2>/dev/null || cp sys/crt0.o $@

sys/crt0.o: $(LIBC_SYS_LIB)

$(SUBLIBS): force
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	(cd `echo $@ | sed -e 's:/[^/]*$$::'` ; \
		$(MAKE) $(FLAGS_TO_PASS) all) \
	|| exit 1

clean-here:
	rm -f core *~ libc.a crt0.o
	rm -f libc.cp libc.dvi targetdep.tex libc.log libc.cps
	rm -f libc.aux libc.toc libc.fn libc.vr libc.tp libc.ky
	rm -f libc.pg libc.fns libc.kys libc.pgs libc.tps libc.vrs

clean mostlyclean: clean-here
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for i in $(SUBDIRS); do \
	  if [ -f ./$$i/Makefile ] ; then \
	    (cd $$i ; $(MAKE) $(FLAGS_TO_PASS) $@) || exit 1 ; \
	  else true ; fi ; \
	done

distclean maintainer-clean realclean: clean-here
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for i in $(SUBDIRS); do \
	  if [ -f ./$$i/Makefile ] ; then \
	    (cd $$i ; $(MAKE) $(FLAGS_TO_PASS) $@) || exit 1 ; \
	  else true ; fi ; \
	done
	rm -f Makefile config.status

info:
	-rm -f targetdep.tex
	if [ -n "$(signal_dir)" ]; then \
	  echo "@set SIGNALS" >sigset.texi ; else \
	  echo "@clear SIGNALS" >sigset.texi ; fi
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) "CHEW=$(CHEW)" "TARGETDOC=$(TARGETDOC)" targetdep.tex
	$(MAKEINFO) -o libc.info $(srcdir)/libc.texinfo

targetdep.tex:
	touch targetdep.tex
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	for i in $(SUBDIRS); do \
	  if [ -f ./$$i/Makefile ] ; then \
	    (cd $$i ; $(MAKE) "CHEW=$(CHEW)" "TARGETDOC=$(TARGETDOC)" doc) \
	    || exit 1 ; \
	  else true ; fi ; \
	done
	cat $(srcdir)/sys.tex >> $(TARGETDOC)

docs: dvi

dvi:
	-rm -f targetdep.tex
	@rootpre=`pwd`/; export rootpre; \
	srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	$(MAKE) $(FLAGS_TO_PASS) "CHEW=$(CHEW)" "TARGETDOC=$(TARGETDOC)" \
	     targetdep.tex
	$(SET_TEXINPUTS) $(TEXI2DVI) $(srcdir)/libc.texinfo

install:

install-info:
	-for i in libc.info*; do \
	    $(INSTALL_DATA) $$i $(infodir)/$$i; \
	  done

force:

Makefile: Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) config.status

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
