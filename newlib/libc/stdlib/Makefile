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
host_makefile_frag = ../../host/any
# Makefile for newlib/libc/stdlib.
# Copyright (c) 1994 Cygnus Support.
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

srcdir = .

SHELL = sh

TOP = ../..
SRCTOP = ../..
TARGETDOC = ../targetdep.tex

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

OFILES=	__adjust.o 	\
	__exp10.o 	\
	__ten_mu.o 	\
	abort.o  	\
	abs.o 		\
	assert.o  	\
	atexit.o	\
	atof.o 		\
	atoff.o		\
	atoi.o  	\
	atol.o		\
	bsearch.o	\
	calloc.o	\
	callocr.o	\
	cfreer.o	\
	div.o  		\
	dtoa.o 		\
	dtoastub.o 	\
	ecvtbuf.o 	\
	efgcvt.o 	\
	environ.o	\
	eprintf.o	\
	exit.o 		\
	freer.o		\
	getenv.o  	\
	getopt.o	\
	labs.o 		\
	ldiv.o  	\
	malign.o	\
	malignr.o	\
	mallinfor.o	\
	malloc.o  	\
	mallocr.o	\
	malloptr.o	\
	mallstatsr.o	\
	mblen.o		\
	mbstowcs.o	\
	mbtowc.o	\
	mlock.o		\
	mprec.o		\
	msize.o		\
	msizer.o	\
	mstats.o	\
	mtrim.o		\
	putenv.o	\
	pvallocr.o	\
	qsort.o		\
	rand.o		\
	rand_r.o	\
	realloc.o	\
	reallocr.o	\
	setenv.o	\
	strdup.o	\
	strtod.o	\
	strtol.o	\
	strtoul.o	\
	system.o	\
	valloc.o	\
	vallocr.o	\
	wcstombs.o	\
	wctomb.o


CHEWOUT_FILES=\
	abort.def	\
	abs.def		\
	assert.def	\
	atexit.def	\
	atof.def 	\
	ecvtbuf.def	\
	atoi.def 	\
	bsearch.def	\
	calloc.def	\
	div.def		\
	efgcvt.def 	\
	exit.def	\
	getenv.def	\
	labs.def	\
	ldiv.def	\
	malloc.def	\
	mallocr.def	\
	mbtowc.def	\
	mlock.def	\
	mstats.def	\
	qsort.def	\
	rand.def	\
	strtod.def 	\
	strtol.def 	\
	strtoul.def 	\
	system.def	\
	wctomb.def	

all: lib.a
lib.a: $(OFILES)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $(OFILES)

MALLOC_CFLAGS = -DINTERNAL_NEWLIB $(CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) $(NEWLIB_CFLAGS) $(INCLUDES)

mallocr.o: mallocr.c
	$(CC) -DDEFINE_MALLOC $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

freer.o: mallocr.c
	$(CC) -DDEFINE_FREE $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

reallocr.o: mallocr.c
	$(CC) -DDEFINE_REALLOC $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

callocr.o: mallocr.c
	$(CC) -DDEFINE_CALLOC $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

cfreer.o: mallocr.c
	$(CC) -DDEFINE_CFREE $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

malignr.o: mallocr.c
	$(CC) -DDEFINE_MEMALIGN $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

vallocr.o: mallocr.c
	$(CC) -DDEFINE_VALLOC $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

pvallocr.o: mallocr.c
	$(CC) -DDEFINE_PVALLOC $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

mallinfor.o: mallocr.c
	$(CC) -DDEFINE_MALLINFO $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

mallstatsr.o: mallocr.c
	$(CC) -DDEFINE_MALLOC_STATS $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

msizer.o: mallocr.c
	$(CC) -DDEFINE_MALLOC_USABLE_SIZE $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

malloptr.o: mallocr.c
	$(CC) -DDEFINE_MALLOPT $(MALLOC_CFLAGS) -c $(srcdir)/mallocr.c -o $@

doc: $(CHEWOUT_FILES)
	cat $(srcdir)/stdlib.tex >> $(TARGETDOC)

clean mostlyclean:
	$(RM) $(OFILES) $(CHEWOUT_FILES) *~ *.ref *.def *.o.* lib.a

distclean maintainer-clean realclean: clean
	rm -f Makefile config.status

Makefile: Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) config.status

# to support SunOS VPATH
__adjust.o: __adjust.c
__exp10.o: __exp10.c
__ten_mu.o: __ten_mu.c
abort.o: abort.c
abs.o: abs.c
assert.o: assert.c
atexit.o: atexit.c
atof.o: atof.c
atoff.o: atoff.c
atoi.o: atoi.c
atol.o: atol.c
bsearch.o: bsearch.c
calloc.o: calloc.c
div.o: div.c
dtoa.o: dtoa.c mprec.h
dtoastub.o: dtoastub.c
ecvtbuf.o: ecvtbuf.c mprec.h
efgcvt.o: efgcvt.c
environ.o: environ.c
eprintf.o: eprintf.c
exit.o: exit.c
getenv.o: getenv.c
getopt.o: getopt.c
labs.o: labs.c
ldiv.o: ldiv.c
malign.o: malign.c
malloc.o: malloc.c
mblen.o: mblen.c
mbstowcs.o: mbstowcs.c
mbtowc.o: mbtowc.c
mlock.o: mlock.c
mprec.o: mprec.c mprec.h
msize.o: msize.c
mstats.o: mstats.c
mtrim.o: mtrim.c
putenv.o: putenv.c
qsort.o: qsort.c
rand.o: rand.c
rand_r.o : rand_r.c
realloc.o: realloc.c
setenv.o: setenv.c
strdup.o: strdup.c
strtod.o: strtod.c mprec.h
strtol.o: strtol.c
strtoul.o: strtoul.c
system.o: system.c
valloc.o: valloc.c
wcstombs.o: wcstombs.c
wctomb.o: wctomb.c

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
