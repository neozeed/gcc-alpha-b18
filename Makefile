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
host_makefile_frag = config/mh-cygwin32
#
# Makefile for directory with subdirs to build.
#   Copyright (C) 1990, 91, 92, 93, 94, 95, 96, 1997 Free Software Foundation
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
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#

srcdir = .

prefix = /usr/local

exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib
tooldir = $(exec_prefix)/i386-cygwin32

program_transform_name = 

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
GDB_NLM_DEPS = 

SHELL = sh

INSTALL = $$s/install-sh -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
INSTALL_XFORM = $(INSTALL) -t='$(program_transform_name)'

INSTALL_DOSREL = install-dosrel-fake

AS = as
AR = ar
AR_FLAGS = rc
CC = gcc

# Special variables passed down in EXTRA_GCC_FLAGS.  They are defined
# here so that they can be overridden by Makefile fragments.
HOST_CC = $(CC_FOR_BUILD)
HOST_PREFIX = 
HOST_PREFIX_1 = loser-

# We don't specify -g -O because many compilers don't support -g -O,
# and/or -O is broken in and of itself.
CFLAGS = -g
LIBCFLAGS = $(CFLAGS)
CFLAGS_FOR_TARGET = $(CFLAGS)
LDFLAGS_FOR_TARGET = 
LIBCFLAGS_FOR_TARGET = $(CFLAGS_FOR_TARGET)
PICFLAG = 
PICFLAG_FOR_TARGET = 

CXX = gcc

# Use -O2 to stress test the compiler.
CXXFLAGS = -g -O2
LIBCXXFLAGS = $(CXXFLAGS) -fno-implicit-templates
CXXFLAGS_FOR_TARGET = $(CXXFLAGS)
LIBCXXFLAGS_FOR_TARGET = $(CXXFLAGS_FOR_TARGET) -fno-implicit-templates

RANLIB = ranlib

DLLTOOL = dlltool

NM = nm
# Not plain GZIP, since gzip looks there for extra command-line options.
GZIPPROG = gzip

# These values are substituted by configure.
DEFAULT_YACC = bison -y
DEFAULT_LEX = flex

# BISON: This line sed'ed to BISON = bison -y for FSF releases, don't remove.
BISON = `if [ -f $$r/byacc/byacc ] ; \
	    then echo $$r/byacc/byacc ; \
	    else echo ${DEFAULT_YACC} ; \
	fi`

LEX = `if [ -f $$r/flex/flex ] ; \
	then echo $$r/flex/flex ; \
	else echo ${DEFAULT_LEX} ; fi`

M4 = `if [ -f $$r/m4/m4 ] ; \
	then echo $$r/m4/m4 ; \
	else echo m4 ; fi`

MAKEINFO = `if [ -f $$r/texinfo/makeinfo/Makefile ] ; \
	then echo $$r/texinfo/makeinfo/makeinfo ; \
	else echo makeinfo ; fi`

# This just becomes part of the MAKEINFO definition passed down to
# sub-makes.  It lets flags be given on the command line while still
# using the makeinfo from the object tree.
MAKEINFOFLAGS =

EXPECT = `if [ -f $$r/expect/expect ] ; \
	then echo $$r/expect/expect ; \
	else echo expect ; fi`

RUNTEST = `if [ -f $$s/dejagnu/runtest ] ; \
	then echo $$s/dejagnu/runtest ; \
	else echo runtest ; fi`


# compilers to use to create programs which must be run in the build
# environment.
CC_FOR_BUILD = $(CC)
CXX_FOR_BUILD = $(CXX)

SUBDIRS = newlib
OTHERS = 

# This is set by the configure script to the list of directories which
# should be built using the target tools.
TARGET_CONFIGDIRS = 

# Target libraries are put under this directory:
# Changed by configure to $(target_alias) if cross.
TARGET_SUBDIR = .

# This is set by the configure script to the arguments passed to configure.
CONFIG_ARGUMENTS = --host=i386-cygwin32  --build=i386-cygwin32   --verbose

# This is set by configure to REALLY_SET_LIB_PATH if --enable-shared
# was used.
SET_LIB_PATH =

# This is the name of the environment variable used for the path to
# the libraries.  This may be changed by configure.in.
RPATH_ENVVAR = LD_LIBRARY_PATH

# configure.in sets SET_LIB_PATH to this if --enable-shared was used.
REALLY_SET_LIB_PATH = \
  $(RPATH_ENVVAR)=$$r/bfd:$$r/opcodes:$$$(RPATH_ENVVAR); \
  export $(RPATH_ENVVAR);

ALL = all.normal
INSTALL_TARGET = install-dirs \
	$(INSTALL_MODULES) \
	$(INSTALL_TARGET_MODULES) \
	$(INSTALL_X11_MODULES) \
	install-gcc \
	$(INSTALL_DOSREL)


CC_FOR_TARGET = ` \
  if [ -f $$r/gcc/xgcc ] ; then \
    if [ -f $$r/$(TARGET_SUBDIR)/newlib/Makefile ] ; then \
      if [ -f $$r/$(TARGET_SUBDIR)/winsup/Makefile ] ; then \
        echo $$r/gcc/xgcc -B$$r/gcc/ -B$$r/newlib/ -L$$r/winsup -idirafter $$r/$(TARGET_SUBDIR)/newlib/targ-include -idirafter $$s/newlib/libc/include -nostdinc; \
      else \
        echo $$r/gcc/xgcc -B$$r/gcc/ -idirafter $$r/$(TARGET_SUBDIR)/newlib/targ-include -idirafter $$s/newlib/libc/include -nostdinc; \
      fi; \
    else \
      echo $$r/gcc/xgcc -B$$r/gcc/; \
    fi; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(CC); \
    else \
      t='$(program_transform_name)'; echo gcc | sed -e 's/x/x/' $$t; \
    fi; \
  fi`

# If CC_FOR_TARGET is not overriden on the command line, then this
# variable is passed down to the gcc Makefile, where it is used to
# build libgcc2.a.  We define it here so that it can itself be
# overridden on the command line.
GCC_FOR_TARGET = $$r/gcc/xgcc -B$$r/gcc/


CXX_FOR_TARGET = ` \
  if [ -f $$r/gcc/xgcc ] ; then \
    if [ -f $$r/$(TARGET_SUBDIR)/newlib/Makefile ] ; then \
      if [ -f $$r/$(TARGET_SUBDIR)/winsup/Makefile ] ; then \
        echo $$r/gcc/xgcc -B$$r/gcc/ -B$$r/newlib/ -L$$r/winsup -idirafter $$r/$(TARGET_SUBDIR)/newlib/targ-include -idirafter $$s/newlib/libc/include -nostdinc; \
      else \
        echo $$r/gcc/xgcc -B$$r/gcc/ -idirafter $$r/$(TARGET_SUBDIR)/newlib/targ-include -idirafter $$s/newlib/libc/include -nostdinc; \
      fi; \
    else \
      echo $$r/gcc/xgcc -B$$r/gcc/; \
    fi; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(CXX); \
    else \
      t='$(program_transform_name)'; echo gcc | sed -e 's/x/x/' $$t; \
    fi; \
  fi`

AS_FOR_TARGET = ` \
  if [ -f $$r/gas/as.new ] ; then \
    echo $$r/gas/as.new ; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(AS); \
    else \
       t='$(program_transform_name)'; echo as | sed -e 's/x/x/' $$t ; \
    fi; \
  fi`

LD_FOR_TARGET = ` \
  if [ -f $$r/ld/ld.new ] ; then \
    echo $$r/ld/ld.new ; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(LD); \
    else \
       t='$(program_transform_name)'; echo ld | sed -e 's/x/x/' $$t ; \
    fi; \
  fi`

DLLTOOL_FOR_TARGET = ` \
  if [ -f $$r/binutils/dlltool ] ; then \
    echo $$r/binutils/dlltool ; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(DLLTOOL); \
    else \
       t='$(program_transform_name)'; echo dlltool | sed -e 's/x/x/' $$t ; \
    fi; \
  fi`

AR_FOR_TARGET = ` \
  if [ -f $$r/binutils/ar ] ; then \
    echo $$r/binutils/ar ; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(AR); \
    else \
       t='$(program_transform_name)'; echo ar | sed -e 's/x/x/' $$t ; \
    fi; \
  fi`

RANLIB_FOR_TARGET = ` \
  if [ -f $$r/binutils/ranlib ] ; then \
    echo $$r/binutils/ranlib ; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(RANLIB); \
    else \
       t='$(program_transform_name)'; echo ranlib | sed -e 's/x/x/' $$t ; \
    fi; \
  fi`

NM_FOR_TARGET = ` \
  if [ -f $$r/binutils/nm.new ] ; then \
    echo $$r/binutils/nm.new ; \
  else \
    if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
      echo $(NM); \
    else \
       t='$(program_transform_name)'; echo nm | sed -e 's/x/x/' $$t ; \
    fi; \
  fi`

#### host and target specific makefile fragments come in here.
# custom installation rules for cygwin32 (append .exe to binaries, etc.)
INSTALL_DOSREL=install-dosrel
###

# Flags to pass down to all sub-makes.
# Please keep these in alphabetical order.
BASE_FLAGS_TO_PASS = \
	"AR_FLAGS=$(AR_FLAGS)" \
	"AR_FOR_TARGET=$(AR_FOR_TARGET)" \
	"AS_FOR_TARGET=$(AS_FOR_TARGET)" \
	"BISON=$(BISON)" \
	"CC_FOR_BUILD=$(CC_FOR_BUILD)" \
	"CC_FOR_TARGET=$(CC_FOR_TARGET)" \
	"CFLAGS=$(CFLAGS)" \
	"CFLAGS_FOR_TARGET=$(CFLAGS_FOR_TARGET)" \
	"CXX_FOR_BUILD=$(CXX_FOR_BUILD)" \
	"CXXFLAGS=$(CXXFLAGS)" \
	"CXXFLAGS_FOR_TARGET=$(CXXFLAGS_FOR_TARGET)" \
	"CXX_FOR_TARGET=$(CXX_FOR_TARGET)" \
	"DLLTOOL_FOR_TARGET=$(DLLTOOL_FOR_TARGET)" \
	"INSTALL=$(INSTALL)" \
	"INSTALL_DATA=$(INSTALL_DATA)" \
	"INSTALL_PROGRAM=$(INSTALL_PROGRAM)" \
	"INSTALL_XFORM=$(INSTALL_XFORM)" \
	"LDFLAGS=$(LDFLAGS)" \
	"LEX=$(LEX)" \
	"LD_FOR_TARGET=$(LD_FOR_TARGET)" \
	"LIBCFLAGS=$(LIBCFLAGS)" \
	"LIBCFLAGS_FOR_TARGET=$(LIBCFLAGS_FOR_TARGET)" \
	"LIBCXXFLAGS=$(LIBCXXFLAGS)" \
	"LIBCXXFLAGS_FOR_TARGET=$(LIBCXXFLAGS_FOR_TARGET)" \
	"M4=$(M4)" \
	"MAKE=$(MAKE)" \
	"MAKEINFO=$(MAKEINFO) $(MAKEINFOFLAGS)" \
	"NM_FOR_TARGET=$(NM_FOR_TARGET)" \
	"PICFLAG=$(PICFLAG)" \
	"PICFLAG_FOR_TARGET=$(PICFLAG_FOR_TARGET)" \
	"RANLIB_FOR_TARGET=$(RANLIB_FOR_TARGET)" \
	"SHELL=$(SHELL)" \
	"EXPECT=$(EXPECT)" \
	"RUNTEST=$(RUNTEST)" \
	"RUNTESTFLAGS=$(RUNTESTFLAGS)" \
	"YACC=$(BISON)" \
	"exec_prefix=$(exec_prefix)" \
	"prefix=$(prefix)" \
	"tooldir=$(tooldir)" 

# Flags to pass down to most sub-makes, in which we're building with
# the host environment.
# If any variables are added here, they must be added to do-*, below.
EXTRA_HOST_FLAGS = \
	'AR=$(AR)' \
	'AS=$(AS)' \
	'CC=$(CC)' \
	'CXX=$(CXX)' \
	'DLLTOOL=$(DLLTOOL)' \
	'NM=$(NM)' \
	'RANLIB=$(RANLIB)' 


FLAGS_TO_PASS = $(BASE_FLAGS_TO_PASS) $(EXTRA_HOST_FLAGS)

# Flags that are concerned with the location of the X11 include files
# and library files
#
# NOTE: until the top-level is getting the values via autoconf, it only
# causes problems to have this top-level Makefile overriding the autoconf-set
# values in child directories.  Only variables that don't conflict with
# autoconf'ed ones should be passed by X11_FLAGS_TO_PASS for now.
#
X11_FLAGS_TO_PASS = \
	'X11_EXTRA_CFLAGS=$(X11_EXTRA_CFLAGS)' \
	'X11_EXTRA_LIBS=$(X11_EXTRA_LIBS)'

# Flags to pass down to makes which are built with the target environment.
# The double $ decreases the length of the command line; the variables
# are set in BASE_FLAGS_TO_PASS, and the sub-make will expand them.
# If any variables are added here, they must be added to do-*, below.
EXTRA_TARGET_FLAGS = \
	'AR=$$(AR_FOR_TARGET)' \
	'AS=$$(AS_FOR_TARGET)' \
	'CC=$$(CC_FOR_TARGET)' \
	'CFLAGS=$$(CFLAGS_FOR_TARGET)' \
	'CXX=$$(CXX_FOR_TARGET)' \
	'CXXFLAGS=$$(CXXFLAGS_FOR_TARGET)' \
	'DLLTOOL=$$(DLLTOOL_FOR_TARGET)' \
	'LD=$$(LD_FOR_TARGET)' \
	'LIBCFLAGS=$$(LIBCFLAGS_FOR_TARGET)' \
	'LIBCXXFLAGS=$$(LIBCXXFLAGS_FOR_TARGET)' \
	'NM=$$(NM_FOR_TARGET)' \
	'PICFLAG=$$(PICFLAG_FOR_TARGET)' \
	'RANLIB=$$(RANLIB_FOR_TARGET)'

TARGET_FLAGS_TO_PASS = $(BASE_FLAGS_TO_PASS) $(EXTRA_TARGET_FLAGS)

# Flags to pass down to gcc.  gcc builds a library, libgcc.a, so it
# unfortunately needs the native compiler and the target ar and
# ranlib.
# If any variables are added here, they must be added to do-*, below.
# The HOST_* variables are a special case, which are used for the gcc
# cross-building scheme.
EXTRA_GCC_FLAGS = \
	'AR=$$(AR_FOR_TARGET)' \
	'AS=$(AS)' \
	'CC=$(CC)' \
	'CXX=$(CXX)' \
	'DLLTOOL=$$(DLLTOOL_FOR_TARGET)' \
	'HOST_CC=$(CC_FOR_BUILD)' \
	'HOST_PREFIX=$(HOST_PREFIX)' \
	'HOST_PREFIX_1=$(HOST_PREFIX_1)' \
	'NM=$(NM)' \
	'RANLIB=$$(RANLIB_FOR_TARGET)' \
	"GCC_FOR_TARGET=$(GCC_FOR_TARGET)" \
	`if test x"$(LANGUAGES)" != x; then echo "LANGUAGES=$(LANGUAGES)"; fi` \
	`if test x"$(STMP_FIXPROTO)" != x; then echo "STMP_FIXPROTO=$(STMP_FIXPROTO)"; fi` \
	`if test x"$(LIMITS_H_TEST)" != x; then echo "LIMITS_H_TEST=$(LIMITS_H_TEST)"; fi` \
	`if test x"$(LIBGCC1_TEST)" != x; then echo "LIBGCC1_TEST=$(LIBGCC1_TEST)"; fi` \
	`if test x"$(LIBGCC2_CFLAGS)" != x; then echo "LIBGCC2_CFLAGS=$(LIBGCC2_CFLAGS)"; fi` \
	`if test x"$(LIBGCC2_DEBUG_CFLAGS)" != x; then echo "LIBGCC2_DEBUG_CFLAGS=$(LIBGCC2_DEBUG_CFLAGS)"; fi` \
	`if test x"$(LIBGCC2_INCLUDES)" != x; then echo "LIBGCC2_INCLUDES=$(LIBGCC2_INCLUDES)"; fi` \
	`if test x"$(ENQUIRE)" != x; then echo "ENQUIRE=$(ENQUIRE)"; fi` \
	`if test x"$(BOOT_CFLAGS)" != x; then echo "BOOT_CFLAGS=$(BOOT_CFLAGS)"; fi`

GCC_FLAGS_TO_PASS = $(BASE_FLAGS_TO_PASS) $(EXTRA_GCC_FLAGS)

# This is a list of the targets for all of the modules which are compiled
# using $(FLAGS_TO_PASS).
ALL_MODULES = \
	all-apache \
	all-autoconf \
	all-bash \
	all-bfd \
	all-binutils \
	all-byacc \
	all-cvs \
	all-db \
	all-dejagnu \
	all-diff \
	all-dosutils \
	all-etc \
	all-fileutils \
	all-findutils \
	all-find \
	all-flex \
	all-gas \
	all-gawk \
	all-gprof \
	all-grep \
	all-grez \
	all-gzip \
	all-hello \
	all-indent \
	all-inet \
	all-ispell \
	all-itcl \
	all-ld \
	all-libiberty \
	all-m4 \
	all-make \
	all-mmalloc \
	all-opcodes \
	all-patch \
	all-perl \
	all-prms \
	all-rcs \
	all-readline \
	all-release \
	all-recode \
	all-sed \
	all-send-pr \
	all-shellutils \
	all-sim \
	all-sn \
	all-tar \
	all-tcl \
	all-texinfo \
	all-textutils \
	all-tgas \
	all-time \
	all-uudecode \
	all-wdiff 

# This is a list of the check targets for all of the modules which are
# compiled using $(FLAGS_TO_PASS).
#
# The list is in two parts.  The first lists those tools which
# are tested as part of the host's native tool-chain, and not
# tested in a cross configuration.
NATIVE_CHECK_MODULES = \
	check-byacc \
	check-flex

CROSS_CHECK_MODULES = \
	check-apache \
	check-autoconf \
	check-bash \
	check-bfd \
	check-binutils \
	check-cvs \
	check-db \
	check-dejagnu \
	check-diff \
	check-etc \
	check-fileutils \
	check-findutils \
	check-find \
	check-gas \
	check-gawk \
	check-gprof \
	check-grep \
	check-gzip \
	check-hello \
	check-indent \
	check-inet \
	check-ispell \
	check-itcl \
	check-ld \
	check-libiberty \
	check-m4 \
	check-make \
	check-mmcheckoc \
	check-opcodes \
	check-patch \
	check-perl \
	check-prms \
	check-rcs \
	check-readline \
	check-recode \
	check-sed \
	check-send-pr \
	check-shellutils \
	check-sn \
	check-sim \
	check-tar \
	check-tcl \
	check-texinfo \
	check-textutils \
	check-tgas \
	check-time \
	check-uudecode \
	check-wdiff

CHECK_MODULES=$(NATIVE_CHECK_MODULES) $(CROSS_CHECK_MODULES)

# This is a list of the install targets for all of the modules which are
# compiled using $(FLAGS_TO_PASS).
INSTALL_MODULES = \
	install-apache \
	install-autoconf \
	install-bash \
	install-bfd \
	install-binutils \
	install-byacc \
	install-cvs \
	install-db \
	install-dejagnu \
	install-diff \
	install-dosutils \
	install-etc \
	install-fileutils \
	install-findutils \
	install-find \
	install-flex \
	install-gas \
	install-gawk \
	install-gprof \
	install-grep \
	install-grez \
	install-gzip \
	install-hello \
	install-indent \
	install-inet \
	install-ispell \
	install-itcl \
	install-ld \
	install-libiberty \
	install-m4 \
	install-make \
	install-mmalloc \
	install-opcodes \
	install-patch \
	install-perl \
	install-prms \
	install-rcs \
	install-readline \
	install-recode \
	install-sed \
	install-send-pr \
	install-shellutils \
	install-sim \
	install-sn \
	install-tar \
	install-tcl \
	install-texinfo \
	install-textutils \
	install-tgas \
	install-time \
	install-uudecode \
	install-wdiff

# This is a list of the targets for all of the modules which are compiled
# using $(X11_FLAGS_TO_PASS).
ALL_X11_MODULES = \
	all-emacs \
	all-emacs19 \
	all-gdb \
	all-expect \
	all-gash \
	all-guile \
	all-tclX \
	all-tk

# This is a list of the check targets for all of the modules which are
# compiled using $(X11_FLAGS_TO_PASS).
CHECK_X11_MODULES = \
	check-emacs \
	check-gdb \
	check-guile \
	check-expect \
	check-gash \
	check-tclX

# This is a list of the install targets for all the modules which are
# compiled using $(X11_FLAGS_TO_PASS).
INSTALL_X11_MODULES = \
	install-emacs \
	install-emacs19 \
	install-gdb \
	install-guile \
	install-expect \
	install-gash \
	install-tclX \
	install-tk

# This is a list of the targets for all of the modules which are compiled
# using $(TARGET_FLAGS_TO_PASS).
ALL_TARGET_MODULES = \
	all-target-libio \
	all-target-libstdc++ \
	all-target-librx \
	all-target-libg++ \
	all-target-newlib \
	all-target-winsup \
	all-target-libgloss \
	all-target-libiberty \
	all-target-examples

# This is a list of the configure targets for all of the modules which
# are compiled using the target tools.
CONFIGURE_TARGET_MODULES = \
	configure-target-libio \
	configure-target-libstdc++ \
	configure-target-librx \
	configure-target-libg++ \
	configure-target-newlib \
	configure-target-winsup \
	configure-target-libgloss \
	configure-target-libiberty \
	configure-target-examples

# This is a list of the check targets for all of the modules which are
# compiled using $(TARGET_FLAGS_TO_PASS).
CHECK_TARGET_MODULES = \
	check-target-libio \
	check-target-libstdc++ \
	check-target-libg++ \
	check-target-newlib \
	check-target-winsup \
	check-target-libiberty

# This is a list of the install targets for all of the modules which are
# compiled using $(TARGET_FLAGS_TO_PASS).
INSTALL_TARGET_MODULES = \
	install-target-libio \
	install-target-libstdc++ \
	install-target-libg++ \
	install-target-newlib \
	install-target-winsup \
	install-target-libgloss \
	install-target-libiberty

# This is a list of the targets for which we can do a clean-{target}.
CLEAN_MODULES = \
	clean-apache \
	clean-autoconf \
	clean-bash \
	clean-bfd \
	clean-binutils \
	clean-byacc \
	clean-cvs \
	clean-db \
	clean-dejagnu \
	clean-diff \
	clean-dosutils \
	clean-etc \
	clean-fileutils \
	clean-findutils \
	clean-find \
	clean-flex \
	clean-gas \
	clean-gawk \
	clean-gprof \
	clean-grep \
	clean-grez \
	clean-gzip \
	clean-hello \
	clean-indent \
	clean-inet \
	clean-ispell \
	clean-itcl \
	clean-ld \
	clean-libiberty \
	clean-m4 \
	clean-make \
	clean-mmalloc \
	clean-opcodes \
	clean-patch \
	clean-perl \
	clean-prms \
	clean-rcs \
	clean-readline \
	clean-release \
	clean-recode \
	clean-sed \
	clean-send-pr \
	clean-shellutils \
	clean-sim \
	clean-sn \
	clean-tar \
	clean-tcl \
	clean-texinfo \
	clean-textutils \
	clean-tgas \
	clean-time \
	clean-uudecode \
	clean-wdiff

# All of the target modules that can be cleaned
CLEAN_TARGET_MODULES = \
	clean-target-libio \
	clean-target-libstdc++ \
	clean-target-librx \
	clean-target-libg++ \
	clean-target-newlib \
	clean-target-winsup \
	clean-target-libgloss \
	clean-target-libiberty \
	clean-target-examples

# All of the x11 modules that can be cleaned
CLEAN_X11_MODULES = \
	clean-emacs \
	clean-emacs19 \
	clean-gdb \
	clean-expect \
	clean-gash \
	clean-guile \
	clean-tclX \
	clean-tk

# The first rule in the file had better be this one.  Don't put any above it.
all: all.normal
.PHONY: all

# The target built for a native build.
.PHONY: all.normal
all.normal: \
	$(ALL_MODULES) \
	$(ALL_X11_MODULES) \
	$(ALL_TARGET_MODULES) \
	all-gcc

# Do a target for all the subdirectories.  A ``make do-X'' will do a
# ``make X'' in all subdirectories (because, in general, there is a
# dependency (below) of X upon do-X, a ``make X'' will also do this,
# but it may do additional work as well).
# This target ensures that $(BASE_FLAGS_TO_PASS) appears only once,
# because it is so large that it can easily overflow the command line
# length limit on some systems.
DO_X = \
	do-clean \
	do-distclean \
	do-dvi \
	do-info \
	do-install-info \
	do-installcheck \
	do-mostlyclean \
	do-maintainer-clean \
	do-TAGS
.PHONY: $(DO_X)
$(DO_X):
	@target=`echo $@ | sed -e 's/^do-//'`; \
	r=`pwd`; export r; \
	s=`cd $(srcdir); pwd`; export s; \
	$(SET_LIB_PATH) \
	for i in $(SUBDIRS) -dummy-; do \
	  if [ -f ./$$i/Makefile ]; then \
	    case $$i in \
	    gcc) \
	      for flag in $(EXTRA_GCC_FLAGS); do \
		eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'|"`; \
	      done; \
	      ;; \
	    *) \
	      for flag in $(EXTRA_HOST_FLAGS); do \
		eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'|"`; \
	      done; \
	      ;; \
	    esac ; \
	    export AR AS CC CXX NM RANLIB DLLTOOL; \
	    if (cd ./$$i; \
	        $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
			"CC=$${CC}" "CXX=$${CXX}" "NM=$${NM}" \
			"RANLIB=$${RANLIB}" \
			"DLLTOOL=$${DLLTOOL}" \
			$${target}); \
	    then true; else exit 1; fi; \
	  else true; fi; \
	done
	@target=`echo $@ | sed -e 's/^do-//'`; \
	r=`pwd`; export r; \
	s=`cd $(srcdir); pwd`; export s; \
	$(SET_LIB_PATH) \
	for i in $(TARGET_CONFIGDIRS) -dummy-; do \
	  if [ -f $(TARGET_SUBDIR)/$$i/Makefile ]; then \
	    for flag in $(EXTRA_TARGET_FLAGS); do \
		eval `echo "$$flag" | sed -e "s|^\([^=]*\)=\(.*\)|\1='\2'|"`; \
	    done; \
	    export AR AS CC CXX NM RANLIB DLLTOOL; \
	    if (cd $(TARGET_SUBDIR)/$$i; \
	        $(MAKE) $(BASE_FLAGS_TO_PASS) "AR=$${AR}" "AS=$${AS}" \
			"CC=$${CC}" "CXX=$${CXX}" "NM=$${NM}" \
			"RANLIB=$${RANLIB}" \
			"DLLTOOL=$${DLLTOOL}" \
			$${target}); \
	    then true; else exit 1; fi; \
	  else true; fi; \
	done

# Here are the targets which correspond to the do-X targets.

.PHONY: info installcheck dvi install-info
.PHONY: clean distclean mostlyclean maintainer-clean realclean
.PHONY: local-clean local-distclean local-maintainer-clean
info: do-info
installcheck: do-installcheck
dvi: do-dvi

# Make sure makeinfo is built before we do a `make info'.
do-info: all-texinfo

install-info: do-install-info dir.info
	s=`cd $(srcdir); pwd`; export s; \
	if [ -f dir.info ] ; then \
	  $(INSTALL_DATA) dir.info $(infodir)/dir.info ; \
	else true ; fi

local-clean:
	-rm -f *.a TEMP errs core *.o *~ \#* TAGS *.E

local-distclean:
	-rm -f Makefile config.status config.cache
	-if [ "$(TARGET_SUBDIR)" != "." ]; then \
	  rm -rf $(TARGET_SUBDIR); \
	else true; fi

local-maintainer-clean:
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

clean: do-clean local-clean
mostlyclean: do-mostlyclean local-clean
distclean: do-distclean local-clean local-distclean
maintainer-clean: local-maintainer-clean do-maintainer-clean local-clean 
maintainer-clean: local-distclean
realclean: maintainer-clean

# This rule is used to clean specific modules.
.PHONY: $(CLEAN_MODULES) $(CLEAN_X11_MODULES) clean-gcc
$(CLEAN_MODULES) $(CLEAN_X11_MODULES) clean-gcc:
	@dir=`echo $@ | sed -e 's/clean-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; $(MAKE) $(FLAGS_TO_PASS) clean); \
	else \
	  true; \
	fi

.PHONY: $(CLEAN_TARGET_MODULES)
$(CLEAN_TARGET_MODULES):
	@dir=`echo $@ | sed -e 's/clean-target-//'`; \
	rm -f $(TARGET_SUBDIR)/$${dir}/multilib.out $(TARGET_SUBDIR)/$${dir}/tmpmulti.out; \
	if [ -f $(TARGET_SUBDIR)/$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $(TARGET_SUBDIR)/$${dir}; $(MAKE) $(TARGET_FLAGS_TO_PASS) clean); \
	else \
	  true; \
	fi

clean-target: $(CLEAN_TARGET_MODULES)

# Check target.

.PHONY: check
check: $(CHECK_MODULES) \
	$(CHECK_TARGET_MODULES) \
	$(CHECK_X11_MODULES) \
	check-gcc

# Installation targets.

.PHONY: install uninstall source-vault binary-vault vault-install
install: $(INSTALL_TARGET) 

uninstall:
	@echo "the uninstall target is not supported in this tree"

source-vault:
	$(MAKE) -f ./release/Build-A-Release \
		host=$(host_alias) source-vault

binary-vault:
	$(MAKE) -f ./release/Build-A-Release \
		host=$(host_alias) target=$(target_alias)

vault-install:
	@if [ -f ./release/vault-install ] ; then \
	  ./release/vault-install $(host_alias) $(target_alias) ; \
	else \
	  true ; \
	fi

.PHONY: install.all
install.all: install-no-fixedincludes
	@if [ -f ./gcc/Makefile ] ; then \
		r=`pwd` ; export r ; \
		$(SET_LIB_PATH) \
		(cd ./gcc; \
		$(MAKE) $(FLAGS_TO_PASS) install-headers) ; \
	else \
		true ; \
	fi

# inet-install is used because the I*Net wants DejaGNU installed but
# not built.  Similarly, gzip is built but not installed.
inet-install:
	$(MAKE) INSTALL_MODULES="`echo $(INSTALL_MODULES) | sed -e 's/install-dejagnu//' -e 's/install-gzip//'`" install

# install-no-fixedincludes is used because Cygnus can not distribute
# the fixed header files.
.PHONY: install-no-fixedincludes
install-no-fixedincludes: \
	install-dirs \
	$(INSTALL_MODULES) \
	$(INSTALL_TARGET_MODULES) \
	$(INSTALL_X11_MODULES) \
	gcc-no-fixedincludes 

# Install the gcc headers files, but not the fixed include files,
# which Cygnus is not allowed to distribute.  This rule is very
# dependent on the workings of the gcc Makefile.in.
.PHONY: gcc-no-fixedincludes
gcc-no-fixedincludes:
	@if [ -f ./gcc/Makefile ]; then \
	  rm -rf gcc/tmp-include; \
	  mv gcc/include gcc/tmp-include 2>/dev/null; \
	  mkdir gcc/include; \
	  cp $(srcdir)/gcc/gsyslimits.h gcc/include/syslimits.h; \
	  touch gcc/stmp-fixinc gcc/include/fixed; \
	  rm -f gcc/stmp-headers gcc/stmp-int-hdrs; \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd` ; export s; \
	  $(SET_LIB_PATH) \
	  (cd ./gcc; \
	   $(MAKE) $(GCC_FLAGS_TO_PASS) install); \
	  rm -rf gcc/include; \
	  mv gcc/tmp-include gcc/include 2>/dev/null; \
	else true; fi

# This rule is used to build the modules which use FLAGS_TO_PASS.  To
# build a target all-X means to cd to X and make all.
#
# all-gui, and all-libproc are handled specially because
# they are still experimental, and if they fail to build, that
# shouldn't stop "make all".
.PHONY: $(ALL_MODULES) all-gui all-libproc
$(ALL_MODULES) all-gui all-libproc:
	@dir=`echo $@ | sed -e 's/all-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; $(MAKE) $(FLAGS_TO_PASS) all); \
	else \
	  true; \
	fi

# These rules are used to check the modules which use FLAGS_TO_PASS.
# To build a target check-X means to cd to X and make check.  Some
# modules are only tested in a native toolchain.

.PHONY: $(CHECK_MODULES) $(NATIVE_CHECK_MODULES) $(CROSS_CHECK_MODULES)
$(NATIVE_CHECK_MODULES):
	@if [ "$(host_canonical)" = "$(target_canonical)" ] ; then \
	  dir=`echo $@ | sed -e 's/check-//'`; \
	  if [ -f ./$${dir}/Makefile ] ; then \
	    r=`pwd`; export r; \
	    s=`cd $(srcdir); pwd`; export s; \
	    $(SET_LIB_PATH) \
	    (cd $${dir}; $(MAKE) $(FLAGS_TO_PASS) check); \
	  else \
	    true; \
	  fi; \
	fi

$(CROSS_CHECK_MODULES):
	@dir=`echo $@ | sed -e 's/check-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; $(MAKE) $(FLAGS_TO_PASS) check); \
	else \
	  true; \
	fi

# This rule is used to install the modules which use FLAGS_TO_PASS.
# To build a target install-X means to cd to X and make install.
.PHONY: $(INSTALL_MODULES)
$(INSTALL_MODULES): install-dirs
	@dir=`echo $@ | sed -e 's/install-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; $(MAKE) $(FLAGS_TO_PASS) install); \
	else \
	  true; \
	fi

# This rule is used to configure the modules which are built with the
# target tools.
.PHONY: $(CONFIGURE_TARGET_MODULES)
$(CONFIGURE_TARGET_MODULES):
	@dir=`echo $@ | sed -e 's/configure-target-//'`; \
	if [ -d $(TARGET_SUBDIR)/$${dir} ]; then \
	  r=`pwd`; export r; \
	  $(CC_FOR_TARGET) --print-multi-lib > $(TARGET_SUBDIR)/$${dir}/tmpmulti.out 2> /dev/null; \
	  if [ -s $(TARGET_SUBDIR)/$${dir}/tmpmulti.out ]; then \
	    if [ -f $(TARGET_SUBDIR)/$${dir}/multilib.out ]; then \
	      if cmp $(TARGET_SUBDIR)/$${dir}/multilib.out $(TARGET_SUBDIR)/$${dir}/tmpmulti.out > /dev/null; then \
		rm -f $(TARGET_SUBDIR)/$${dir}/tmpmulti.out; \
	      else \
		echo "Multilibs changed for $${dir}, reconfiguring"; \
		rm -f $(TARGET_SUBDIR)/$${dir}/multilib.out $(TARGET_SUBDIR)/$${dir}/Makefile; \
		mv $(TARGET_SUBDIR)/$${dir}/tmpmulti.out $(TARGET_SUBDIR)/$${dir}/multilib.out; \
	      fi; \
	    else \
	      mv $(TARGET_SUBDIR)/$${dir}/tmpmulti.out $(TARGET_SUBDIR)/$${dir}/multilib.out; \
	    fi; \
	  fi; \
	fi; exit 0	# break command into two pieces
	@dir=`echo $@ | sed -e 's/configure-target-//'`; \
	if [ ! -d $(TARGET_SUBDIR) ]; then \
	  true; \
	elif [ -f $(TARGET_SUBDIR)/$${dir}/Makefile ] ; then \
	  true; \
	elif echo " $(TARGET_CONFIGDIRS) " | grep " $${dir} " >/dev/null 2>&1; then \
	  if [ -d $(srcdir)/$${dir} ]; then \
	    [ -d $(TARGET_SUBDIR)/$${dir} ] || mkdir $(TARGET_SUBDIR)/$${dir};\
	    r=`pwd`; export r; \
	    s=`cd $(srcdir); pwd`; export s; \
	    $(SET_LIB_PATH) \
	    AR="$(AR_FOR_TARGET)"; export AR; \
	    AS="$(AS_FOR_TARGET)"; export AS; \
	    CC="$(CC_FOR_TARGET)"; export CC; \
	    CFLAGS="$(CFLAGS_FOR_TARGET)"; export CFLAGS; \
	    CXX="$(CXX_FOR_TARGET)"; export CXX; \
	    CXXFLAGS="$(CXXFLAGS_FOR_TARGET)"; export CXXFLAGS; \
	    DLLTOOL="$(DLLTOOL_FOR_TARGET)"; export DLLTOOL; \
	    LD="$(LD_FOR_TARGET)"; export LD; \
            LDFLAGS="$(LDFLAGS_FOR_TARGET)"; export LDFLAGS; \
	    NM="$(NM_FOR_TARGET)"; export NM; \
	    RANLIB="$(RANLIB_FOR_TARGET)"; export RANLIB; \
	    echo Configuring in $(TARGET_SUBDIR)/$${dir}; \
	    cd $(TARGET_SUBDIR)/$${dir}; \
	    case $(srcdir) in \
	    /*) \
	      topdir=$(srcdir) ;; \
	    *) \
	      case "$(TARGET_SUBDIR)" in \
	      .) topdir="../$(srcdir)" ;; \
	      *) topdir="../../$(srcdir)" ;; \
	      esac ;; \
	    esac; \
	    if [ "$(srcdir)" = "." ] ; then \
	      if [ "$(TARGET_SUBDIR)" != "." ] ; then \
		if $(SHELL) $$s/symlink-tree $${topdir}/$${dir} "no-such-file" ; then \
		  if [ -f Makefile ]; then \
		    if $(MAKE) distclean; then \
		      true; \
		    else \
		      exit 1; \
		    fi; \
		  else \
		    true; \
		  fi; \
		else \
		  exit 1; \
		fi; \
	      else \
		true; \
	      fi; \
	      srcdiroption="--srcdir=."; \
	      libsrcdir="."; \
	    else \
	      srcdiroption="--srcdir=$${topdir}/$${dir}"; \
	      libsrcdir="$$s/$${dir}"; \
	    fi; \
	    if [ -f $${libsrcdir}/configure ] ; then \
	      $(SHELL) $${libsrcdir}/configure \
		$(CONFIG_ARGUMENTS) $${srcdiroption} \
		--with-target-subdir="$(TARGET_SUBDIR)"; \
	    else \
	      $(SHELL) $$s/configure \
		$(CONFIG_ARGUMENTS) $${srcdiroption} \
		--with-target-subdir="$(TARGET_SUBDIR)"; \
	    fi; \
	  else \
	    true; \
	  fi; \
	else \
	  true; \
	fi

# This rule is used to build the modules which use TARGET_FLAGS_TO_PASS.
# To build a target all-X means to cd to X and make all.
.PHONY: $(ALL_TARGET_MODULES)
$(ALL_TARGET_MODULES):
	@dir=`echo $@ | sed -e 's/all-target-//'`; \
	if [ -f $(TARGET_SUBDIR)/$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $(TARGET_SUBDIR)/$${dir}; $(MAKE) $(TARGET_FLAGS_TO_PASS) all); \
	else \
	  true; \
	fi

# This rule is used to check the modules which use TARGET_FLAGS_TO_PASS.
# To build a target install-X means to cd to X and make install.
.PHONY: $(CHECK_TARGET_MODULES)
$(CHECK_TARGET_MODULES):
	@dir=`echo $@ | sed -e 's/check-target-//'`; \
	if [ -f $(TARGET_SUBDIR)/$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $(TARGET_SUBDIR)/$${dir};$(MAKE) $(TARGET_FLAGS_TO_PASS) check);\
	else \
	  true; \
	fi

# This rule is used to install the modules which use
# TARGET_FLAGS_TO_PASS.  To build a target install-X means to cd to X
# and make install.
.PHONY: $(INSTALL_TARGET_MODULES)
$(INSTALL_TARGET_MODULES): install-dirs
	@dir=`echo $@ | sed -e 's/install-target-//'`; \
	if [ -f $(TARGET_SUBDIR)/$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $(TARGET_SUBDIR)/$${dir}; \
	    $(MAKE) $(TARGET_FLAGS_TO_PASS) install); \
	else \
	  true; \
	fi

# This rule is used to build the modules which use X11_FLAGS_TO_PASS.
# To build a target all-X means to cd to X and make all.
.PHONY: $(ALL_X11_MODULES)
$(ALL_X11_MODULES):
	@dir=`echo $@ | sed -e 's/all-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; \
	   $(MAKE) $(FLAGS_TO_PASS) $(X11_FLAGS_TO_PASS) all); \
	else \
	  true; \
	fi

# This rule is used to check the modules which use X11_FLAGS_TO_PASS.
# To build a target check-X means to cd to X and make all.
.PHONY: $(CHECK_X11_MODULES)
$(CHECK_X11_MODULES):
	@dir=`echo $@ | sed -e 's/check-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; \
	   $(MAKE) $(FLAGS_TO_PASS) $(X11_FLAGS_TO_PASS) check); \
	else \
	  true; \
	fi

# This rule is used to install the modules which use X11_FLAGS_TO_PASS.
# To build a target install-X means to cd to X and make install.
.PHONY: $(INSTALL_X11_MODULES)
$(INSTALL_X11_MODULES):
	@dir=`echo $@ | sed -e 's/install-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; \
	   $(MAKE) $(FLAGS_TO_PASS) $(X11_FLAGS_TO_PASS) install); \
	else \
	  true; \
	fi

# gcc is the only module which uses GCC_FLAGS_TO_PASS.
.PHONY: all-gcc
all-gcc:
	@if [ -f ./gcc/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd gcc; $(MAKE) $(GCC_FLAGS_TO_PASS) all); \
	else \
	  true; \
	fi

.PHONY: all-bootstrap
all-bootstrap:
	@if [ -f ./gcc/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd gcc; $(MAKE) $(GCC_FLAGS_TO_PASS) bootstrap); \
	else \
	  true; \
	fi

.PHONY: check-gcc
check-gcc:
	@if [ -f ./gcc/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd gcc; $(MAKE) $(GCC_FLAGS_TO_PASS) check); \
	else \
	  true; \
	fi

.PHONY: install-gcc
install-gcc:
	@if [ -f ./gcc/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd gcc; $(MAKE) $(GCC_FLAGS_TO_PASS) install); \
	else \
	  true; \
	fi


# EXPERIMENTAL STUFF
# This rule is used to install the modules which use FLAGS_TO_PASS.
# To build a target install-X means to cd to X and make install.
.PHONY: install-dosrel
install-dosrel: install-dirs info
	@dir=`echo $@ | sed -e 's/install-//'`; \
	if [ -f ./$${dir}/Makefile ] ; then \
	  r=`pwd`; export r; \
	  s=`cd $(srcdir); pwd`; export s; \
	  $(SET_LIB_PATH) \
	  (cd $${dir}; $(MAKE) $(FLAGS_TO_PASS) install); \
	else \
	  true; \
	fi

install-dosrel-fake:


# This is a list of inter-dependencies among modules.
all-apache:
all-autoconf: all-m4
all-bash:
all-bfd:
all-binutils: all-libiberty all-opcodes all-bfd all-flex all-byacc
all-byacc:
all-cvs:
all-db:
all-dejagnu: all-tcl all-expect all-tk
all-diff: all-libiberty
all-emacs:
all-emacs19: all-byacc
all-etc:
configure-target-examples: $(ALL_GCC)
all-target-examples: configure-target-examples
all-expect: all-tcl all-tk
all-fileutils: all-libiberty
all-findutils:
all-find:
all-flex: all-libiberty all-byacc
all-gas: all-libiberty all-opcodes all-bfd
all-gash: all-tcl
all-gawk:
ALL_GCC = all-gcc
all-gcc: all-libiberty all-byacc all-binutils all-gas all-ld
all-bootstrap: all-libiberty all-byacc all-binutils all-gas all-ld
GDB_TK = 
all-gdb: all-libiberty all-opcodes all-bfd all-mmalloc all-readline all-byacc all-sim $(gdbnlmrequirements) $(GDB_TK)
all-gprof: all-libiberty all-bfd all-opcodes
all-grep: all-libiberty
all-grez: all-libiberty all-bfd all-opcodes
all-gui: all-gdb all-libproc all-target-librx
all-guile:
all-gzip: all-libiberty
all-hello: all-libiberty
all-indent:
all-inet: all-tcl all-send-pr all-perl
all-ispell: all-emacs19
all-itcl: all-tcl all-tk
all-ld: all-libiberty all-bfd all-opcodes all-byacc all-flex
configure-target-libg++: $(ALL_GCC) configure-target-librx
all-target-libg++: configure-target-libg++ all-gas all-ld all-gcc all-target-libiberty all-target-newlib all-target-libio all-target-librx all-target-libstdc++
configure-target-libgloss: $(ALL_GCC)
all-target-libgloss: configure-target-libgloss configure-target-newlib
configure-target-libio: $(ALL_GCC)
all-target-libio: configure-target-libio all-gas all-ld all-gcc all-target-libiberty all-target-newlib
all-libiberty:
configure-target-librx: $(ALL_GCC) configure-target-newlib
all-target-librx: configure-target-librx
configure-target-libstdc++: $(ALL_GCC)
all-target-libstdc++: configure-target-libstdc++ all-gas all-ld all-gcc all-target-libiberty all-target-newlib all-target-libio
all-m4: all-libiberty
all-make: all-libiberty
all-mmalloc:
configure-target-newlib: $(ALL_GCC)
all-target-newlib: configure-target-newlib all-binutils all-gas all-gcc
all-opcodes: all-bfd all-libiberty
all-patch: all-libiberty
all-perl:
all-prms: all-libiberty
all-rcs:
all-readline:
all-recode: all-libiberty
all-sed: all-libiberty
all-send-pr: all-prms
all-shellutils:
all-sim: all-libiberty all-bfd all-opcodes
all-sn: all-tcl all-tk all-itcl all-db
all-tar: all-libiberty
all-tcl:
all-tclX: all-tcl all-tk
all-tk: all-tcl
all-texinfo: all-libiberty
all-textutils:
all-tgas: all-libiberty all-bfd all-opcodes
all-time:
all-wdiff:
all-target-winsup: all-target-newlib all-target-libiberty all-target-librx all-target-libio configure-target-winsup 
configure-target-winsup: configure-target-newlib
all-uudecode: all-libiberty
configure-target-libiberty: $(ALL_GCC)
all-target-libiberty: configure-target-libiberty all-gcc all-ld all-target-newlib
all-target: $(ALL_TARGET_MODULES)
install-target: $(INSTALL_TARGET_MODULES)

### other supporting targets

MAKEDIRS= \
	$(prefix) \
	$(exec_prefix)
.PHONY: install-dirs
install-dirs:
	@for i in .. $(MAKEDIRS) ; do \
	    if [ x$$i != x.. ]; then \
		echo Making $$i... ; \
		parent=`echo $$i | sed -e 's@/[^/]*$$@@' | sed -e 's@^$$@/@'`; \
		if [ -d $$parent ] ; then true ; else mkdir $$parent ; fi ; \
		if [ ! -d $$i ] ; then \
			if mkdir $$i ; then \
				true ; \
			else \
				exit 1 ; \
			fi ; \
		else \
			true ; \
		fi ; \
	    else true; fi; \
	done

dir.info: do-install-info
	if [ -f $(srcdir)/texinfo/gen-info-dir ] ; then \
	  $(srcdir)/texinfo/gen-info-dir $(infodir) $(srcdir)/texinfo/dir.info-template > dir.info.new ; \
	  mv -f dir.info.new dir.info ; \
	else true ; \
	fi

dist:
	@echo "Building a full distribution of this tree isn't done"
	@echo "via 'make dist'.  Check out the etc/ subdirectory" 

etags tags: TAGS

# Right now this just builds TAGS in each subdirectory.  emacs19 has the
# ability to use several tags files at once, so there is probably no need
# to combine them into one big TAGS file (like CVS 1.3 does).  We could
# (if we felt like it) have this Makefile write a piece of elisp which
# the user could load to tell emacs19 where all the TAGS files we just
# built are.
TAGS: do-TAGS

# with the gnu make, this is done automatically.

Makefile: Makefile.in configure.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) ./config.status

#
# Support for building net releases

# Files in devo used in any net release.
# ChangeLog omitted because it may refer to files which are not in this
# distribution (perhaps it would be better to include it anyway).
DEVO_SUPPORT= README Makefile.in configure configure.in \
	config.guess config.sub config move-if-change \
	mpw-README mpw-build.in mpw-config.in mpw-configure \
	COPYING COPYING.LIB install-sh config-ml.in symlink-tree

# Files in devo/etc used in any net release.
# ChangeLog omitted because it may refer to files which are not in this
# distribution (perhaps it would be better to include it anyway).
ETC_SUPPORT= Makefile.in configure configure.in standards.texi \
	make-stds.texi standards.info*

# When you use `make setup-dirs' or `make taz' you should always redefine
# this macro.
SUPPORT_FILES = list-of-support-files-for-tool-in-question
# Files where "byacc" (Cygnus version) should be changed to "bison -y" (FSF).
DISTBISONFILES= binutils/Makefile.in gas/Makefile.in gdb/Makefile.in

.PHONY: taz

taz: $(DEVO_SUPPORT) $(SUPPORT_FILES) \
  texinfo/texinfo.tex texinfo/gpl.texinfo texinfo/lgpl.texinfo
	# Make sure "diststuff" files get built properly.
	for f in $(DISTBISONFILES) ; do \
	  if [ -r $$f ]; then \
	    sed '/^BISON *=.*$$/s/.*/BISON = bison -y/' <$$f >tmp ; \
	    mv -f tmp $$f ; \
	  else true; fi ; \
	done
	# Take out texinfo from a few places; make simple BISON=bison line.
	sed -e '/^all\.normal: /s/\all-texinfo //' \
	    -e '/^	install-texinfo /d' \
	    -e '/^BISON = /,/^$$/d' \
	    -e '/^# BISON:/s/.*/BISON = bison -y/' \
	<Makefile.in >tmp
	mv -f tmp Makefile.in
	#
	./configure sun4
	[ -z "$(CONFIGURE_TARGET_MODULES)" ] \
	  || $(MAKE) $(CONFIGURE_TARGET_MODULES) ALL_GCC="" \
	    CC_FOR_TARGET="$(CC)" CXX_FOR_TARGET="$(CXX)"
	# Make links, and run "make diststuff" or "make info" when needed.
	rm -rf proto-toplev ; mkdir proto-toplev
	set -e ; dirs="$(TOOL) $(DEVO_SUPPORT) $(SUPPORT_FILES)" ; \
	for d in $$dirs ; do \
	  if [ -d $$d ]; then \
	    if [ ! -f $$d/Makefile ] ; then true ; \
	    elif grep '^diststuff:' $$d/Makefile >/dev/null ; then \
		(cd $$d ; $(MAKE) diststuff ) || exit 1 ; \
	    elif grep '^info:' $$d/Makefile >/dev/null ; then \
	        (cd $$d ; $(MAKE) info ) || exit 1 ; \
	    fi ; \
	    if [ -d $$d/proto-$$d.dir ]; then \
	      ln -s ../$$d/proto-$$d.dir proto-toplev/$$d ; \
	    else \
	      ln -s ../$$d proto-toplev/$$d ; \
	    fi ; \
	  else ln -s ../$$d proto-toplev/$$d ; fi ; \
	done
	cd etc ; $(MAKE) info
	$(MAKE) distclean
	#
	mkdir proto-toplev/etc
	(cd proto-toplev/etc; \
	 for i in $(ETC_SUPPORT); do \
		ln -s ../../etc/$$i . ; \
	 done)
	#
	# Take out texinfo from configurable dirs
	rm proto-toplev/configure.in
	sed -e '/^host_tools=/s/texinfo //' \
	    <configure.in >proto-toplev/configure.in
	#
	mkdir proto-toplev/texinfo
	ln -s ../../texinfo/texinfo.tex		proto-toplev/texinfo/
	ln -s ../../texinfo/gpl.texinfo		proto-toplev/texinfo/
	ln -s ../../texinfo/lgpl.texinfo	proto-toplev/texinfo/
	if test -r texinfo/util/tex3patch ; then \
	  mkdir proto-toplev/texinfo/util && \
	  ln -s ../../../texinfo/util/tex3patch	proto-toplev/texinfo/util ; \
	else true; fi
	chmod og=u `find . -print`
	$(MAKE) -f Makefile.in do-tar-gz TOOL=$(TOOL) \
		VER=`sed <$(TOOL)/Makefile.in -n 's/^VERSION *= *//p'`

do-tar-gz:
	echo "==> Making $(TOOL)-$(VER).tar.gz"
	-rm -f $(TOOL)-$(VER)
	ln -s proto-toplev $(TOOL)-$(VER)
	tar cfh $(TOOL)-$(VER).tar $(TOOL)-$(VER)
	$(GZIPPROG) -v -9 $(TOOL)-$(VER).tar

TEXINFO_SUPPORT= texinfo/texinfo.tex texinfo/gpl.texinfo texinfo/lgpl.texinfo
DIST_SUPPORT= $(DEVO_SUPPORT) $(TEXINFO_SUPPORT)

.PHONY: gas.tar.gz
GAS_SUPPORT_DIRS= bfd include libiberty opcodes setup.com makefile.vms
gas.tar.gz: $(DIST_SUPPORT) $(GAS_SUPPORT_DIRS) gas
	$(MAKE) -f Makefile.in taz TOOL=gas \
		SUPPORT_FILES="$(GAS_SUPPORT_DIRS)"

# The FSF "binutils" release includes gprof and ld.
.PHONY: binutils.tar.gz
BINUTILS_SUPPORT_DIRS= bfd gas include libiberty opcodes ld gprof setup.com makefile.vms
binutils.tar.gz: $(DIST_SUPPORT) $(BINUTILS_SUPPORT_DIRS) binutils
	$(MAKE) -f Makefile.in taz TOOL=binutils \
		SUPPORT_FILES="$(BINUTILS_SUPPORT_DIRS) makeall.bat configure.bat"

.PHONY: gas+binutils.tar.gz
GASB_SUPPORT_DIRS= $(GAS_SUPPORT_DIRS) binutils ld gprof
gas+binutils.tar.gz: $(DIST_SUPPORT) $(GASB_SUPPORT_DIRS) gas
	$(MAKE) -f Makefile.in taz TOOL=gas \
		SUPPORT_FILES="$(GASB_SUPPORT_DIRS) makeall.bat configure.bat"

.PHONY: libg++.tar.gz
LIBGXX_SUPPORT_DIRS=include libstdc++ libio librx libiberty
libg++.tar.gz: $(DIST_SUPPORT) libg++
	$(MAKE) -f Makefile.in taz TOOL=libg++ \
		SUPPORT_FILES="$(LIBGXX_SUPPORT_DIRS)"

GNATS_SUPPORT_DIRS=include libiberty send-pr
gnats.tar.gz: $(DIST_SUPPORT) $(GNATS_SUPPORT_DIRS) gnats
	$(MAKE) -f  Makefile.in taz TOOL=gnats \
		SUPPORT_FILES="$(GNATS_SUPPORT_DIRS)"

.PHONY: gdb.tar.gz
GDB_SUPPORT_DIRS= bfd include libiberty mmalloc opcodes readline sim utils
GDBTK_SUPPORT_DIRS= `if [ -d tcl -a -d tk ] ; then echo tcl tk ; fi`
gdb.tar.gz: $(DIST_SUPPORT) $(GDB_SUPPORT_DIRS) gdb
	$(MAKE) -f Makefile.in taz TOOL=gdb \
		SUPPORT_FILES="$(GDB_SUPPORT_DIRS) $(GDBTK_SUPPORT_DIRS)"

.PHONY: newlib.tar.gz
NEWLIB_SUPPORT_DIRS=libgloss
# taz configures for the sun4 target which won't configure newlib.
# We need newlib configured so that the .info files are made.
# Unfortunately, it is not enough to just configure newlib separately:
# taz will build the .info files but since SUBDIRS won't contain newlib,
# distclean won't be run (leaving Makefile, config.status, and the tmp files
# used in building the .info files, eg: *.def, *.ref).
# The problem isn't solvable however without a lot of extra work because
# target libraries are built in subdir $(target_alias) which gets nuked during
# the make distclean.  For now punt on the issue of shipping newlib info files
# with newlib net releases and wait for a day when some native target (sun4?)
# supports newlib (if only minimally).
newlib.tar.gz: $(DIST_SUPPORT) $(NEWLIB_SUPPORT_DIRS) newlib
	$(MAKE) -f Makefile.in taz TOOL=newlib \
		SUPPORT_FILES="$(NEWLIB_SUPPORT_DIRS)" \
		DEVO_SUPPORT="$(DEVO_SUPPORT) COPYING.NEWLIB" newlib

.NOEXPORT:
MAKEOVERRIDES=


# end of Makefile.in
