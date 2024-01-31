# Generated automatically from Makefile.in by configure.
# Makefile for Cygwin32 utilities
# Copyright 1996, 1997, 1998 Cygnus Solutions.

# This file is part of Cygwin32.

# This software is a copyrighted work licensed under the terms of the
# Cygwin32 license.  Please consult the file "CYGWIN32_LICENSE" for
# details.

SHELL = /bin/sh

srcdir = .
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
etcdir = $(exec_prefix)/etc
program_transform_name = s,x,x,

INSTALL = /gcc-ms/CYGWIN/ginstall -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

EXEEXT = 
EXEEXT_FOR_BUILD = @EXEEXT_FOR_BUILD@

CC = gcc

CFLAGS = -O2
CXXFLAGS = -O2

INCLUDES = -I$(srcdir)/.. -I$(srcdir)/../include

ALL_CFLAGS = $(CFLAGS) $(INCLUDES)
ALL_CXXFLAGS = $(CXXFLAGS) $(INCLUDES)

# Passed in from ../Makefile.
EXE_LDFLAGS = -s

PROGS = mount$(EXEEXT) umount$(EXEEXT) ps$(EXEEXT) kill$(EXEEXT) \
	cygwin$(EXEEXT) mkpasswd$(EXEEXT) mkgroup$(EXEEXT)

WINSUP_DEPS = $(srcdir)/../winsup.h

all: $(PROGS)

mount$(EXEEXT): mount.cc $(WINSUP_DEPS)
	$(CC) -o $@ $(srcdir)/mount.cc $(ALL_CXXFLAGS) $(EXE_LDFLAGS)

umount$(EXEEXT): umount.cc $(WINSUP_DEPS)
	$(CC) -o $@ $(srcdir)/umount.cc $(ALL_CXXFLAGS) $(EXE_LDFLAGS)

ps$(EXEEXT): ps.cc $(WINSUP_DEPS)
	$(CC) -o $@ $(srcdir)/ps.cc $(ALL_CXXFLAGS) $(EXE_LDFLAGS)

kill$(EXEEXT): kill.cc  $(WINSUP_DEPS)
	$(CC) -o $@ $(srcdir)/kill.cc $(ALL_CXXFLAGS) $(EXE_LDFLAGS)

cygwin$(EXEEXT): cygwin.cc $(WINSUP_DEPS)
	$(CC) -o $@ $(srcdir)/cygwin.cc $(ALL_CXXFLAGS) $(EXE_LDFLAGS)

mkpasswd$(EXEEXT): mkpasswd.c $(WINSUP_DEPS)
	$(CC) -o $@ $(srcdir)/mkpasswd.c $(ALL_CXXFLAGS) $(EXE_LDFLAGS) -lnetapi32 -ladvapi32

mkgroup$(EXEEXT): mkgroup.c $(WINSUP_DEPS)
	$(CC) -o $@ $(srcdir)/mkgroup.c $(ALL_CXXFLAGS) $(EXE_LDFLAGS) -lnetapi32 -ladvapi32

clean:
	rm -f *.o $(PROGS)

realclean: clean
	rm -f  Makefile config.cache 

install: installdirs
	for i in $(PROGS) ; do \
	  n=`echo $$i | sed '$(program_transform_name)'`; \
	  $(INSTALL_PROGRAM) $$i $(bindir)/$$n; \
	done
	$(INSTALL_DATA) $(srcdir)/termcap $(etcdir)

installdirs:
	$(SHELL) $(srcdir)/../../mkinstalldirs $(bindir) $(etcdir)

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
