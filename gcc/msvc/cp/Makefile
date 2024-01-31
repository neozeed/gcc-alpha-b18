# Makefile for GNU C++ compiler.
#   Copyright (C) 1987, 88, 90-4, 1995 Free Software Foundation, Inc.

#This file is part of GNU CC.

#GNU CC is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2, or (at your option)
#any later version.

#GNU CC is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with GNU CC; see the file COPYING.  If not, write to
#the Free Software Foundation, 59 Temple Place - Suite 330,
#Boston, MA 02111-1307, USA.

# The makefile built from this file lives in the language subdirectory.
# Its purpose is to provide support for:
#
# 1) recursion where necessary, and only then (building .o's), and
# 2) building and debugging cc1.exe from the language subdirectory, and
# 3) nothing else.
#
# The parent makefile handles all other chores, with help from the
# language makefile fragment, of course.
#
# The targets for external use are:
# all, TAGS, ???mostlyclean, ???clean.

# Suppress smart makes who think they know how to automake Yacc files
.y.c:

# Variables that exist for you to override.
# See below for how to change them for certain systems.

ALLOCA = alloca.obj

# Various ways of specifying flags for compilations:  
# CFLAGS is for the user to override to, e.g., do a bootstrap with -O2.
# BOOT_CFLAGS is the value of CFLAGS to pass
# to the stage2 and stage3 compilations
# XCFLAGS is used for most compilations but not when using the GCC just built.
XCFLAGS =
CFLAGS = -O2
BOOT_CFLAGS = -O $(CFLAGS)
# These exists to be overridden by the x-* and t-* files, respectively.
X_CFLAGS =
T_CFLAGS =

X_CPPFLAGS =
T_CPPFLAGS =

CC = cl
# CYGNUS LOCAL: we use byacc instead of bison
BISON = `if [ -f ../../byacc/byacc ] ; then echo ../../byacc/byacc ;  else echo byacc ; fi`
BISONFLAGS =
LEX = `if [ -f ../../flex/flex ] ; then echo ../../flex/flex ;  else echo flex ; fi`
LEXFLAGS =
AR = ar
AR_FLAGS = rc
SHELL =
MAKEINFO = makeinfo
TEXI2DVI = texi2dvi

# Define this as & to perform parallel make on a Sequent.
# Note that this has some bugs, and it seems currently necessary 
# to compile all the gen* files first by hand to avoid erroneous results.
P =

# This is used in the definition of SUBDIR_USE_ALLOCA.
# ??? Perhaps it would be better if it just looked for *gcc*.
OLDCC = cl

# This is used instead of ALL_CFLAGS when compiling with GCC_FOR_TARGET.
# It omits XCFLAGS, and specifies -B./.
# It also specifies -B$(tooldir)/ to find as and ld for a cross compiler.
GCC_CFLAGS=$(INTERNAL_CFLAGS) $(X_CFLAGS) $(T_CFLAGS) $(CFLAGS)

# Tools to use when building a cross-compiler.
# These are used because `configure' appends `cross-make'
# to the makefile when making a cross-compiler.

# CYGNUS LOCAL: we don't use cross-make.  Instead we use the tools
# from the build tree, if they are available.
# program_transform_name and objdir are set by configure.in.
program_transform_name =
objdir = .

target=winnt3.5
#version=`sed -e 's/.*\"\([^ \"]*\)[ \"].*/\1/' < $(srcdir)\version.c`
#mainversion=`sed -e 's/.*\"\([0-9]*\.[0-9]*\).*/\1/' < $(srcdir)\version.c`

# Directory where sources are, from where we are.
srcdir = .

# Additional system libraries to link with.
CLIB=

# Change this to a null string if obstacks are installed in the
# system library.
OBSTACK=obstack.obj

# Choose the real default target.
ALL=all

# End of variables for you to override.

# Definition of `all' is here so that new rules inserted by sed
# do not specify the default target.
all: all.indirect

# This tells GNU Make version 3 not to put all variables in the environment.
.NOEXPORT:

# sed inserts variable overrides after the following line.
CC = cl 
CLIB = libc.lib kernel32.lib 
CFLAGS = -Dalpha -DWIN32 -D_WIN32 -D_ALPHA_ -D_M_ALPHA \
 -DALMOST_STDC -O2
LDFLAGS = -subsystem:console -entry:mainCRTStartup \
 -stack:5000000,500000 

STMP_FIXPROTO = 
OTHER_FIXINCLUDES_DIRS=. 
RANLIB = : 
RANLIB_TEST = false 
OLDCC = cl 
MAKE = nmake 
SYMLINK = copy 
INSTALL = $(srcdir)/install.sh -c 
exeext = .exe 
objext = .obj 
oldobjext = .obj 

EXTRA_PROGRAMS=ld.exe 

ld.obj: $(srcdir)/config/winnt/ld.c 
	$(CC) $(CFLAGS) \
 	-I. -I$(srcdir) -I$(srcdir)/config -c $(srcdir)/config/winnt/ld.c 

ld.exe: ld.obj 
	link -out:ld.exe ld.obj $(LDFLAGS) $(CLIB) 

EXTRA_GCC_OBJS= oldnames.obj 
spawnv.obj: $(srcdir)/config/winnt/spawnv.c 
	$(CC) $(CFLAGS) \
 	-I. -I$(srcdir) -I$(srcdir)/config -c $(srcdir)/config/winnt/spawnv.c 

oldnames.obj: $(srcdir)/config/winnt/oldnames.c 
	$(CC) $(CFLAGS) \
 	-I. -I$(srcdir) -I$(srcdir)/config -c $(srcdir)/config/winnt/oldnames.c
####target overrides
####host overrides
####cross overrides
####build overrides
####site overrides

# Now figure out from those variables how to compile and link.

all.indirect: Makefile ../cc1plus

# IN_GCC tells obstack.h that we are using gcc's <stddef.h> file.
INTERNAL_CFLAGS = $(CROSS) -DIN_GCC

# This is the variable actually used when we compile.
ALL_CFLAGS = $(INTERNAL_CFLAGS) $(X_CFLAGS) $(T_CFLAGS) $(CFLAGS) $(XCFLAGS)

# Likewise.
ALL_CPPFLAGS = $(CPPFLAGS) $(X_CPPFLAGS) $(T_CPPFLAGS)

# CYGNUS LOCAL: SUBDIR_USE_ALLOCA is different from FSF.
# Even if ALLOCA is set, don't use it if compiling with GCC.

SUBDIR_OBSTACK = ../obstack.obj
#SUBDIR_USE_ALLOCA = `case "${CC}" in "${OLDCC}") if [ x$(ALLOCA) != x ]; then echo ../$(ALLOCA); else true; fi ;; esac`
SUBDIR_USE_ALLOCA =
SUBDIR_MALLOC =

# How to link with both our special library facilities
# and the system's installed libraries.
LIBS = $(SUBDIR_OBSTACK) $(SUBDIR_USE_ALLOCA) $(SUBDIR_MALLOC) $(CLIB)

# Specify the directories to be searched for header files.
# Both . and srcdir are used, in that order,
# so that tm.h and config.h will be found in the compilation
# subdirectory rather than in the source directory.
INCLUDES = -I. -I.. -I$(srcdir) -I$(srcdir)/.. -I$(srcdir)/../config

# Always use -I$(srcdir)/config when compiling.
.c.obj :
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $<

# This tells GNU make version 3 not to export all the variables
# defined in this file into the environment.
.NOEXPORT:

# Lists of files for various purposes.

# Language-specific object files for g++

CXX_OBJS = call.obj decl.obj errfn.obj expr.obj pt.obj sig.obj typeck2.obj \
 class.obj decl2.obj error.obj lex.obj parse.obj ptree.obj rtti.obj spew.obj typeck.obj cvt.obj \
 except.obj friend.obj init.obj method.obj search.obj tree.obj xref.obj repo.obj

# Language-independent object files.
OBJS = @../stamp-objlist ../c-common.obj ../c-pragma.obj
OBJDEPS = ../stamp-objlist ../c-common.obj ../c-pragma.obj

compiler: ../cc1plus
../cc1plus: $(P) $(CXX_OBJS) $(OBJDEPS) $(LIBDEPS)
	link $(LDFLAGS) -out:$@ \
	      $(CXX_OBJS) $(OBJS) $(LIBS)

