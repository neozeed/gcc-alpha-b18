# Generated automatically from Makefile.in by configure.
# Makefile for winsup/regexp
# Copyright (c) 1997 Cygnus Solutions.

# This file is part of Cygwin32.

# This software is a copyrighted work licensed under the terms of the
# Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
# details.

SHELL = /bin/sh
srcdir = .
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
tooldir = $(exec_prefix)/$(target_alias)
etcdir = $(exec_prefix)/etc
program_transform_name = s,x,x,

INSTALL = /gcc-ms/CYGWIN/ginstall -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

CC = gcc

CFLAGS = -g -O2
CXXFLAGS = 

INCLUDES = -I. -I$(srcdir)/.. -I$(srcdir)/../include

ALL_CFLAGS = $(CFLAGS) $(INCLUDES)
ALL_CXXFLAGS = $(CXXFLAGS) $(INCLUDES)

# Passed in from ../Makefile.
EXE_LDFLAGS =

all: regexp.o regerror.o regsub.o

regexp.o: regexp.c regexp.h regmagic.h
#	$(CC) $(srcdir)/regexp.c $(ALL_CFLAGS) $(EXE_LDFLAGS)

regerror.o: regerror.c regexp.h

regsub.o: regsub.c regexp.h regmagic.h

clean:
	rm -f *.o $(PROGS)

realclean: clean
	rm -f  Makefile config.cache 

install:
	$(INSTALL_DATA) $(srcdir)/regexp.h $(tooldir)/include/regexp.h

installdirs:

Makefile: Makefile.in $(srcdir)/configure.in config.status
	$(SHELL) config.status

config.status: configure
	$(SHELL) config.status --recheck

.NOEXPORT:

.SUFFIXES: .cc .c .o

.c.o:
	$(CC) -c $(ALL_CFLAGS) $<

.cc.o:
	$(CC) -c $(ALL_CXXFLAGS) $<
