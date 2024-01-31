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
# Makefile for newlib/libc/stdio.
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

OFILES= \
	clearerr.o 			\
	fclose.o 			\
	fdopen.o 			\
	feof.o 				\
	ferror.o 			\
	fflush.o 			\
	fgetc.o 			\
	fgetpos.o 			\
	fgets.o 			\
	fileno.o			\
	findfp.o 			\
	fiprintf.o 			\
	flags.o 			\
	fopen.o 			\
	fprintf.o 			\
	fputc.o 			\
	fputs.o 			\
	fread.o 			\
	freopen.o 			\
	fscanf.o 			\
	fseek.o 			\
	fsetpos.o 			\
	ftell.o 			\
	fvwrite.o 			\
	fwalk.o 			\
	fwrite.o 			\
	getc.o 				\
	getchar.o 			\
	gets.o 				\
	iprintf.o 			\
	makebuf.o			\
	mktemp.o 			\
	perror.o 			\
	printf.o 			\
	putc.o 				\
	putchar.o 			\
	puts.o 				\
	refill.o 			\
	remove.o 			\
	rename.o 			\
	rewind.o 			\
	rget.o 				\
	scanf.o 			\
	setbuf.o 			\
	setvbuf.o 			\
	siprintf.o 			\
	sprintf.o 			\
	sscanf.o 			\
	stdio.o 			\
	tmpfile.o 			\
	tmpnam.o 			\
	ungetc.o 			\
	vfiprintf.o 			\
	vfprintf.o 			\
	vfscanf.o 			\
	vprintf.o 			\
	vsprintf.o 			\
	wbuf.o 				\
	wsetup.o 


CHEWOUT_FILES=\
	clearerr.def		\
	fclose.def		\
	fdopen.def		\
	feof.def		\
	ferror.def		\
	fflush.def		\
	fgetc.def		\
	fgetpos.def		\
	fgets.def		\
	fileno.def		\
	fiprintf.def		\
	fopen.def		\
	fputc.def		\
	fputs.def		\
	fread.def		\
	freopen.def		\
	fseek.def		\
	fsetpos.def		\
	ftell.def		\
	fwrite.def		\
	getc.def		\
	getchar.def		\
	gets.def		\
	iprintf.def		\
	mktemp.def		\
	perror.def		\
	putc.def		\
	putchar.def		\
	puts.def		\
	remove.def		\
	rename.def		\
	rewind.def		\
	setbuf.def		\
	setvbuf.def		\
	siprintf.def		\
	sprintf.def		\
	sscanf.def		\
	tmpfile.def		\
	tmpnam.def		\
	vfprintf.def


all: lib.a
lib.a: $(OFILES)
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $(OFILES)

vfiprintf.o: vfprintf.c
	cp $(srcdir)/vfprintf.c vfiprintf.c
	$(CC) $(CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) $(NEWLIB_CFLAGS) $(INCLUDES) -DINTEGER_ONLY -I$(srcdir) -c vfiprintf.c

doc: $(CHEWOUT_FILES)
	cat $(srcdir)/stdio.tex >> $(TARGETDOC)

clean mostlyclean:
	$(RM) $(OFILES) *~ core $(CHEWOUT_FILES) *.o.* *.ref
	$(RM) vfiprintf.c lib.a

distclean maintainer-clean realclean: clean
	rm -f Makefile config.status

Makefile: Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) config.status

# to support SunOS VPATH
clearerr.o: clearerr.c
fclose.o: fclose.c local.h
fdopen.o: fdopen.c local.h
feof.o: feof.c
ferror.o: ferror.c
fflush.o: fflush.c local.h
fgetc.o: fgetc.c
fgetpos.o: fgetpos.c
fgets.o: fgets.c
fileno.o: fileno.c
findfp.o: findfp.c local.h
fiprintf.o: fiprintf.c
flags.o: flags.c
fopen.o: fopen.c local.h
fprintf.o: fprintf.c
fputc.o: fputc.c
fputs.o: fputs.c fvwrite.h
fread.o: fread.c local.h
freopen.o: freopen.c local.h
fscanf.o: fscanf.c
fseek.o: fseek.c local.h
fsetpos.o: fsetpos.c
ftell.o: ftell.c local.h
fvwrite.o: fvwrite.c local.h fvwrite.h
fwalk.o: fwalk.c local.h
fwrite.o: fwrite.c local.h fvwrite.h
getc.o: getc.c
getchar.o: getchar.c
gets.o: gets.c
iprintf.o: iprintf.c
makebuf.o: makebuf.c local.h
mktemp.o: mktemp.c
perror.o: perror.c
printf.o: printf.c
putc.o: putc.c
putchar.o: putchar.c
puts.o: puts.c fvwrite.h
refill.o: refill.c local.h
remove.o: remove.c
rename.o: rename.c
rewind.o: rewind.c
rget.o: rget.c
scanf.o: scanf.c local.h
setbuf.o: setbuf.c local.h
setvbuf.o: setvbuf.c local.h
siprintf.o: siprintf.c local.h
sprintf.o: sprintf.c local.h
sscanf.o: sscanf.c local.h
stdio.o: stdio.c local.h
tmpfile.o: tmpfile.c
tmpnam.o: tmpnam.c
ungetc.o: ungetc.c local.h
vfiprintf.o: vfprintf.c local.h
vfprintf.o: vfprintf.c local.h
vfscanf.o: vfscanf.c local.h floatio.h
vprintf.o: vprintf.c
vsprintf.o: vsprintf.c
wbuf.o: wbuf.c local.h fvwrite.h
wsetup.o: wsetup.c local.h

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
