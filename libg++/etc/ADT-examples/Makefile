# This file was generated automatically by configure.  Do not edit.
VPATH = .
links = 
host_alias = alpha-cygwin32
host_cpu = alpha
host_vendor = unknown
host_os = cygwin32
host_canonical = alpha-unknown-cygwin32
target_alias = alpha-cygwin32
target_cpu = alpha
target_vendor = unknown
target_os = cygwin32
target_canonical = alpha-unknown-cygwin32
build_alias = alpha-cygwin32
build_cpu = alpha
build_vendor = unknown
build_os = cygwin32
build_canonical = alpha-unknown-cygwin32
package_makefile_frag = Make.pack
target_makefile_frag = ../../target-mkfrag
# A makefile for the stuff now in libg++/etc/ADT-examples

srcdir = .

TEST_PROGS = generic-q search keyhash tsort tsortinp genkey patricia kmp

#### package, host, target, and site dependent Makefile fragments come in here.
# Start of package fragment generated by ./../../config.shared.

MULTISRCTOP =
MULTIBUILDTOP =
MULTIDIRS =
MULTISUBDIR =
MULTIDO = true
MULTICLEAN = true

# TOPDIR=$${rootme}$(MULTIBUILDTOP)../../../../ invsubdir= subdir=
srcdir = .
SUBDIRS = 
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(exec_prefix)/lib
datadir = $(prefix)/lib
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
gxx_includedir = $(includedir)/g++
docdir = $(datadir)/doc

SHELL = sh

INSTALL = $${rootme}../../../../install.sh -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL)

AR = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../../binutils/ar ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../../binutils/ar ; \
	else echo ar ; fi`
AR_FLAGS = rc
RANLIB = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../../binutils/ranlib ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../../binutils/ranlib ; \
	else echo ranlib ; fi`
NM = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../../binutils/nm.new ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../../binutils/nm.new ; \
	else echo nm ; fi`
NLMCONV = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../../binutils/nlmconv ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../../binutils/nlmconv ; \
	else echo nlmconv ; fi`
LD = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../../ld/ld.new ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../../ld/ld.new ; \
	else echo ld ; fi`

MAKEINFO = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../../texinfo/C/makeinfo ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../../texinfo/C/makeinfo ; \
	else echo makeinfo ; fi`
TEXIDIR = ../../../../texinfo
TEXI2DVI = TEXINPUTS=${TEXIDIR}:$$TEXINPUTS texi2dvi

CC = cc -D__STDC__
CXX = gcc

WRAP_C_INCLUDES =
CFLAGS = -g
CXXFLAGS = -g -O
LIBCFLAGS = $(CFLAGS)
LIBCXXFLAGS = $(CXXFLAGS) -fno-implicit-templates
PICFLAG =
PICDIR = 
TOLIBGXX = ../../
PROTODIR = $(srcdir)/../../src/gen
LIBS = -L./../../ -L./../../../libstdc++ -lg++ -lstdc++
IO_DIR = ../libio
# IO_DIR = no-stream
all: $(PICDIR) $(NOTHING) multi-all
.PHONY: all

.PHONY: multi-all
multi-all:
	@$(MULTIDO) $(FLAGS_TO_PASS) multi-do DO=all


NOSTDINC = -nostdinc++
CXXINCLUDES = $(NOSTDINC) -I. -I../../../libio -I$(srcdir) -I$(srcdir)/../../$(IO_DIR) -I$(srcdir)/../../../libstdc++ -I$(srcdir)/../../src $(WRAP_C_INCLUDES)
CINCLUDES =
XCFLAGS = $(CFLAGS)
XCXXFLAGS = $(CXXFLAGS)
.SUFFIXES: .o .C .cc .c
COMPILE.c = $(CC) -c $(XCFLAGS) $(CINCLUDES)
.c.o:
	$(COMPILE.c) $<
COMPILE.cc = $(CXX) -c $(XCXXFLAGS) $(CXXINCLUDES)
.C.o:
	$(COMPILE.cc) $<
.cc.o:
	$(COMPILE.cc) $<


.PHONY: install
install:
.PHONY: check
.PHONY: info dvi install-info clean-info
info:
dvi:
install-info:
.PHONY: do-clean-info clean-info do-clean-dvi clean-dvi
do-clean-info:
do-clean-dvi:
clean-info: do-clean-info
clean-dvi: do-clean-dvi

.PHONY: boltcc
boltcc:
	rootme=`pwd`/ ; export rootme ; $(MAKE) $(FLAGS_TO_PASS)


# clean rules
.PHONY: mostlyclean clean distclean maintainer-clean realclean
mostlyclean: clean-dvi
	rm -rf *.o \#* core input $(TEST_PROGS) 
	@$(MULTICLEAN) multi-clean DO=mostlyclean
clean: clean-dvi
	rm -rf *.o \#* core input $(TEST_PROGS)   
	@$(MULTICLEAN) multi-clean DO=clean
distclean: clean
	@$(MULTICLEAN) multi-clean DO=distclean
	rm -rf config.status Makefile *~ Make.pack multilib.out 
maintainer-clean realclean: clean clean-info
	@$(MULTICLEAN) multi-clean DO=maintainer-clean
	rm -rf config.status Makefile *~ Make.pack multilib.out  depend *.info*

.PHONY: force
force:

# with the gnu make, this is done automatically.

Makefile: $(srcdir)/Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) ./config.status

.NOEXPORT:
MAKEOVERRIDES=
DEPEND_SOURCES = ${srcdir}/*.cc ${srcdir}/*.c
depend.new:
# The sed script below attempts to make the depend output portable.
# It cleans up the depenency information generated by cpp.
# It replaces instances of $(srcdir)/ by the string '$(srcdir)/'.
# It removes remaining absolute files names (such as /usr/include/stdio.h).
# It removes lines containing only "\\".
# It inserts '$(MULTISRCTOP)' in '$(srcdir)/..'.
# In order to support SunOS VPATH, $(srcdir)/[a-z]*.{c,cc} is replaced with
# [a-z]*.{c,cc} (the directory part is removed).
# The awk script removes a continuation marker that is followed by
# a blank line, since that may confuse make.
	echo "# AUTOMATICALLY GENERATED BY 'make depend' - DO NOT EDIT" \
	  >depend.new
	$(CXX) -M $(CXXINCLUDES) $(DEPEND_SOURCES) \
	| sed -e 's|$(srcdir)/|$$(srcdir)/|g' \
	      -e 's| /[^ ]*||g' \
	      -e '/^[ 	]*\\$$/d' -e 's/^[ 	]*$$//' \
	| sed -e 's|$$(srcdir)/[.][.]|$$(srcdir)/$$(MULTISRCTOP)..|g' \
	      -e 's|$$(srcdir)/\([^/]*[.]c\)|\1|' \
	| awk 'BEGIN   { prev = "" } \
	      /^( )*$$/ { if (prev ~ /\\$$/) \
	                    { prev = substr(prev,1,length(prev)-1); next } } \
	                { print prev; prev = $$0 } \
	      END { if (prev !~ /^( )*$$/) print prev }' \
	>> depend.new
$(srcdir)/depend:  depend.new
	mv depend.new $(srcdir)/depend


# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

Patmain.o : Patmain.cc \
  $(srcdir)/../../$(IO_DIR)/stream.h \
  $(srcdir)/../../$(IO_DIR)/iostream.h \
  $(srcdir)/../../$(IO_DIR)/streambuf.h \
  Patricia.h
Patricia.o : Patricia.cc \
  Patricia.h
genPatkey.o : genPatkey.cc \
  $(srcdir)/../../$(IO_DIR)/stream.h \
  $(srcdir)/../../$(IO_DIR)/iostream.h \
  $(srcdir)/../../$(IO_DIR)/streambuf.h 
generic-q.o : generic-q.cc \
  $(srcdir)/../../$(IO_DIR)/stream.h \
  $(srcdir)/../../$(IO_DIR)/iostream.h \
  $(srcdir)/../../$(IO_DIR)/streambuf.h 
keyhash.o : keyhash.cc \
  $(srcdir)/../../$(IO_DIR)/stream.h \
  $(srcdir)/../../$(IO_DIR)/iostream.h \
  $(srcdir)/../../$(IO_DIR)/streambuf.h 
kmp.o : kmp.cc 
search.o : search.cc \
  $(srcdir)/../../$(IO_DIR)/stream.h \
  $(srcdir)/../../$(IO_DIR)/iostream.h \
  $(srcdir)/../../$(IO_DIR)/streambuf.h 
tsort.o : tsort.cc \
  $(srcdir)/../../$(IO_DIR)/stream.h \
  $(srcdir)/../../$(IO_DIR)/iostream.h \
  $(srcdir)/../../$(IO_DIR)/streambuf.h 
tsortinp.o : tsortinp.cc \
  $(srcdir)/../../$(IO_DIR)/stream.h \
  $(srcdir)/../../$(IO_DIR)/iostream.h \
  $(srcdir)/../../$(IO_DIR)/streambuf.h 

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
# End of package fragment generated by ./../../config.shared.
# Warning this fragment is automatically generated
# RANLIB = ranlib

# If the C include files are C++-ready (with extern "C"), uncomment next line:
# WRAP_C_INCLUDES =

# Flags to pass to gen-params when building _G_config.h.
# For example: G_CONFIG_ARGS = size_t="unsigned long"
G_CONFIG_ARGS =
##

check: $(TEST_PROGS)
	-./generic-q < $(srcdir)/generic-q.cc
	-./tsortinp 20 | ./tsort
	-./keyhash < $(srcdir)/keyhash.cc
	-./search 1000
	-./genkey 1000 200 > input
	-./patricia ./input ./input | grep -v "is found"

#	-./dhrystone

run_tests: check

generic-q: generic-q.o
	$(CXX)  generic-q.o -o $@ $(LIBS)

tsort: tsortinp tsort.o
	$(CXX)  tsort.o -o $@ $(LIBS)

tsortinp: tsortinp.o
	$(CXX)  tsortinp.o -o $@ $(LIBS)

keyhash: keyhash.o
	$(CXX)  keyhash.o -o $@ $(LIBS)

search: search.o
	$(CXX)  search.o -o $@ $(LIBS)

genkey: genPatkey.o
	$(CXX)  genPatkey.o -o $@ $(LIBS)

Patricia.o: $(srcdir)/Patricia.h
Patmain.o: $(srcdir)/Patricia.h 

patricia: Patmain.o Patricia.o
	$(CXX)  Patmain.o Patricia.o -o $@ $(LIBS)

kmp: kmp.o
	$(CXX)  kmp.o -o $@ $(LIBS)
