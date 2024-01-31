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
# Makefile for newlib.
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

INSTALL = install -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL)

AR_FLAGS = qv
MAKEINFO = makeinfo

# We must compile makedoc with a program that runs on the build
# environment.  This isn't really supported yet.
CC_FOR_BUILD = cc
CFLAGS_FOR_BUILD =

TOP = ..
SRCTOP = ..

.NOEXPORT:

#### Host, target, and site specific Makefile fragments come in here.
###

OFILES = makedoc.o

all: makedoc

makedoc: makedoc.o
	$(CC_FOR_BUILD) $(CFLAGS) $(CFLAGS_FOR_BUILD) -o makedoc makedoc.o

makedoc.o: $(srcdir)/makedoc.c
	$(CC_FOR_BUILD) $(CFLAGS) $(CFLAGS_FOR_BUILD) -c $(srcdir)/makedoc.c

doc:
docs:
info:
install:
install-info:
dvi:

clean mostlyclean:
	rm -f $(OFILES) makedoc *.o.* *.ref

distclean maintainer-clean realclean: clean
	rm -f Makefile config.status

Makefile: Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) config.status
