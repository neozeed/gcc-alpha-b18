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
target_makefile_frag = ../target-mkfrag
srcdir = .

#### package, host, target, and site dependent Makefile fragments come in here.
# Start of package fragment generated by ./../config.shared.

MULTISRCTOP =
MULTIBUILDTOP =
MULTIDIRS =
MULTISUBDIR =
MULTIDO = true
MULTICLEAN = true

# TOPDIR=$${rootme}$(MULTIBUILDTOP)../../../ invsubdir= subdir=
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

INSTALL = $${rootme}../../../install.sh -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL)

AR = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../binutils/ar ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../binutils/ar ; \
	else echo ar ; fi`
AR_FLAGS = rc
RANLIB = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../binutils/ranlib ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../binutils/ranlib ; \
	else echo ranlib ; fi`
NM = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../binutils/nm.new ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../binutils/nm.new ; \
	else echo nm ; fi`
NLMCONV = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../binutils/nlmconv ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../binutils/nlmconv ; \
	else echo nlmconv ; fi`
LD = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../ld/ld.new ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../ld/ld.new ; \
	else echo ld ; fi`

MAKEINFO = `if [ -f $${rootme}$(MULTIBUILDTOP)../../../texinfo/C/makeinfo ] ; \
	then echo $${rootme}$(MULTIBUILDTOP)../../../texinfo/C/makeinfo ; \
	else echo makeinfo ; fi`
TEXIDIR = ../../../texinfo
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
TOLIBGXX = ../
PROTODIR = $(srcdir)/../src/gen
LIBS = -L./../ -L./../../libstdc++ -lg++ -lstdc++
IO_DIR = ../libio
# IO_DIR = no-stream
all: $(PICDIR) force multi-all
.PHONY: all

.PHONY: multi-all
multi-all:
	@$(MULTIDO) $(FLAGS_TO_PASS) multi-do DO=all


#NOSTDINC = -nostdinc++
NOSTDINC =
CXXINCLUDES = $(NOSTDINC) -I. -I../../libio -I$(srcdir) -I$(srcdir)/../$(IO_DIR) -I$(srcdir)/../../libstdc++ -I$(srcdir)/../src $(WRAP_C_INCLUDES)
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
check: $(PICDIR) force 
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
	rm -rf *.out *.o \#* core trie-gen ffile streamfile i*.cc i*.h CXX.hack* test.bye test.bye2 test.shell $(LIBTEST) $(TOUTS) 
	@$(MULTICLEAN) multi-clean DO=mostlyclean
clean: clean-dvi
	rm -rf *.out *.o \#* core trie-gen ffile streamfile i*.cc i*.h CXX.hack* test.bye test.bye2 test.shell $(LIBTEST) $(TOUTS)  
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

tBag.o : tBag.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iBag.h \
  iXPBag.h \
  iSLBag.h \
  iVHBag.h \
  iCHBag.h \
  iOXPBag.h \
  iOSLBag.h \
  iSplayBag.h
tBitSet.o : tBitSet.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tBitString.o : tBitString.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tComplex.o : tComplex.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tCurses.o : tCurses.cc 
tDeque.o : tDeque.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iDeque.h \
  iXPDeque.h \
  iDLDeque.h
tFile.o : tFile.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  $(srcdir)/../$(IO_DIR)/strstream.h \
  $(srcdir)/../$(IO_DIR)/SFile.h \
  $(srcdir)/../$(IO_DIR)/fstream.h \
  $(srcdir)/../$(IO_DIR)/PlotFile.h 
tFix.o : tFix.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tFix16.o : tFix16.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tFix24.o : tFix24.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tGetOpt.o : tGetOpt.cc 
tInteger.o : tInteger.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tLList.o : tLList.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iSLList.h \
  iDLList.h
tList.o : tList.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iList.h 
tMap.o : tMap.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iMap.h \
  iSplayMap.h \
  iVHMap.h \
  iCHMap.h \
  iAVLMap.h \
  iRAVLMap.h
tObstack.o : tObstack.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tPQ.o : tPQ.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iPQ.h \
  iXPPQ.h \
  iPHPQ.h \
  iSplayPQ.h
tPlex.o : tPlex.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iPlex.h \
  iFPlex.h \
  iXPlex.h \
  iMPlex.h \
  iRPlex.h
tQueue.o : tQueue.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iQueue.h \
  iXPQueue.h \
  iVQueue.h \
  iSLQueue.h
tRandom.o : tRandom.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tRational.o : tRational.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tSet.o : tSet.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iSet.h \
  iXPSet.h \
  iSLSet.h \
  iVHSet.h \
  iVOHSet.h \
  iCHSet.h \
  iOXPSet.h \
  iOSLSet.h \
  iBSTSet.h \
  iAVLSet.h \
  iSplaySet.h
tStack.o : tStack.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iStack.h \
  iXPStack.h \
  iVStack.h \
  iSLStack.h
tString.o : tString.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h 
tVec.o : tVec.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  iVec.h \
  iAVec.h 
test_h.o : test_h.cc \
  $(srcdir)/../$(IO_DIR)/stream.h \
  $(srcdir)/../$(IO_DIR)/iostream.h \
  $(srcdir)/../$(IO_DIR)/streambuf.h \
  $(srcdir)/../$(IO_DIR)/istream.h \
  $(srcdir)/../$(IO_DIR)/ostream.h 

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
# End of package fragment generated by ./../config.shared.
# Warning this fragment is automatically generated
# RANLIB = ranlib

# If the C include files are C++-ready (with extern "C"), uncomment next line:
# WRAP_C_INCLUDES =

# Flags to pass to gen-params when building _G_config.h.
# For example: G_CONFIG_ARGS = size_t="unsigned long"
G_CONFIG_ARGS =
##

GENCLASS = ../genclass/genclass
PROTODIR = $(srcdir)/../src/gen

# compilation notes:
# The following g++ warnings are expected to appear:
#
# 2. Several warnings from genclass about classes with only .h, no .cc files
#
# 3. A few harmless reminder warnings that some classes have no data members.
#
# 4. Many harmless warnings that arguments to vector-delete are unnecessary
#    when deleting arrays of builtin types.

#--- NOTE: Lots of stuff gets added by ${srcdir}/Makefile.sh

Makefile: $(srcdir)/Makefile.sh

# test files
TSRCS =  tObstack.cc tString.cc tInteger.cc tRational.cc \
 tBitSet.cc tBitString.cc tRandom.cc tList.cc tPlex.cc \
 tLList.cc tVec.cc tStack.cc tQueue.cc tDeque.cc tPQ.cc tSet.cc  tBag.cc \
 tMap.cc tFix.cc tFix16.cc tFix24.cc \
 tGetOpt.cc \
 tiLList.cc
# executables
TOUTS =  test_h tObstack tString tInteger tRational tBitSet tBitString tFix tFix16 tFix24 tRandom tStack tQueue tDeque tPQ tSet tBag tMap tList tPlex tLList tVec tiLList tGetOpt

# files for archived prototype classes
LOBJS = \
 iList.o iSLList.o iDLList.o iVec.o iAVec.o \
 iPlex.o  iFPlex.o  iXPlex.o iRPlex.o iMPlex.o \
 iSet.o iBag.o iMap.o iPQ.o \
 iXPSet.o  iOXPSet.o  iSLSet.o  iOSLSet.o  iBSTSet.o iCHNode.o \
 iAVLSet.o  iSplayNode.o iSplaySet.o  iVHSet.o  iVOHSet.o  iCHSet.o \
 iXPBag.o  iOXPBag.o  iSLBag.o  iOSLBag.o  iSplayBag.o iVHBag.o  iCHBag.o \
 iVHMap.o  iCHMap.o  iSplayMap.o  iAVLMap.o iRAVLMap.o \
 iSplayPQ.o  iPHPQ.o  iXPPQ.o \
 iVStack.o iVQueue.o iStack.o iQueue.o iDeque.o \
 iXPStack.o iSLStack.o iXPQueue.o  iSLQueue.o iXPDeque.o iDLDeque.o

LSRCS = \
 iList.cc iSLList.cc iDLList.cc iVec.cc iAVec.cc \
 iPlex.cc  iFPlex.cc  iXPlex.cc iRPlex.cc iMPlex.cc \
 iSet.cc iBag.cc iMap.cc iPQ.cc \
 iXPSet.cc  iOXPSet.cc  iSLSet.cc  iOSLSet.cc  iBSTSet.cc iCHNode.cc \
 iAVLSet.cc  iSplayNode.cc iSplaySet.cc  iVHSet.cc  iVOHSet.cc  iCHSet.cc \
 iXPBag.cc iOXPBag.cc iSLBag.cc iOSLBag.cc  iSplayBag.cc iVHBag.cc iCHBag.cc \
 iVHMap.cc  iCHMap.cc  iSplayMap.cc  iAVLMap.cc iRAVLMap.cc \
 iSplayPQ.cc  iPHPQ.cc  iXPPQ.cc \
 iVStack.cc iVQueue.cc iStack.cc iQueue.cc iDeque.cc \
 iXPStack.cc iSLStack.cc iXPQueue.cc  iSLQueue.cc iXPDeque.cc iDLDeque.cc

DEPEND_SOURCES = $(srcdir)/*.cc $(LSRCS)

LHDRS =  idefs.h 

.PHONY: all
all:

.PHONY: info
info:
.PHONY: install-info
install-info:
.PHONY: clean-info
clean-info:

.PHONY: check
check: tests

.PHONY: check-tGetOpt
.PHONY: check-tObstack
check-tObstack: tObstack $(srcdir)/tObstack.inp
	./tObstack < $(srcdir)/tObstack.inp > tObstack.out 2>&1
	diff -b $(srcdir)/tObstack.exp tObstack.out
.PHONY: check-tString
check-tString: tString $(srcdir)/tString.inp
	./tString < $(srcdir)/tString.inp > tString.out 2>&1
	diff -b $(srcdir)/tString.exp tString.out
.PHONY: check-tInteger
check-tInteger: tInteger $(srcdir)/tInteger.inp
	./tInteger < $(srcdir)/tInteger.inp > tInteger.out 2>&1
	diff -b $(srcdir)/tInteger.exp tInteger.out
.PHONY: check-tRational
check-tRational: tRational $(srcdir)/tRational.inp
	./tRational < $(srcdir)/tRational.inp > tRational.out 2>&1
	diff -b $(srcdir)/tRational.exp tRational.out
.PHONY: check-tBitSet
check-tBitSet: tBitSet
	./tBitSet > tBitSet.out 2>&1
	diff -b $(srcdir)/tBitSet.exp tBitSet.out
.PHONY: check-tBitString
check-tBitString: tBitString
	./tBitString > tBitString.out 2>&1
	diff -b $(srcdir)/tBitString.exp tBitString.out
.PHONY: check-tFix
check-tFix: tFix
	./tFix > tFix.out 2>&1
	diff -b $(srcdir)/tFix.exp tFix.out
.PHONY: check-tFix16
check-tFix16: tFix16
	./tFix16 > tFix16.out 2>&1
	diff -b $(srcdir)/tFix16.exp tFix16.out
.PHONY: check-tFix24
check-tFix24: tFix24
	./tFix24 > tFix24.out 2>&1
	diff -b $(srcdir)/tFix24.exp tFix24.out
.PHONY: check-tRandom
check-tRandom: tRandom
	./tRandom > tRandom.out 2>&1
	diff -b $(srcdir)/tRandom.exp tRandom.out
.PHONY: check-tStack
check-tStack: tStack
	./tStack > tStack.out 2>&1
	diff -b $(srcdir)/tStack.exp tStack.out
.PHONY: check-tQueue
check-tQueue: tQueue
	./tQueue > tQueue.out 2>&1
	diff -b $(srcdir)/tQueue.exp tQueue.out
.PHONY: check-tDeque
check-tDeque: tDeque
	./tDeque > tDeque.out 2>&1
	diff -b $(srcdir)/tDeque.exp tDeque.out
.PHONY: check-tPQ
check-tPQ: tPQ
	./tPQ > tPQ.out 2>&1
	diff -b $(srcdir)/tPQ.exp tPQ.out
.PHONY: check-tSet
check-tSet: tSet
	./tSet > tSet.out 2>&1
	diff -b $(srcdir)/tSet.exp tSet.out
.PHONY: check-tBag
check-tBag: tBag
	./tBag > tBag.out 2>&1
	diff -b $(srcdir)/tBag.exp tBag.out
.PHONY: check-tMap
check-tMap: tMap
	./tMap > tMap.out 2>&1
	diff -b $(srcdir)/tMap.exp tMap.out
.PHONY: check-tList
check-tList: tList
	./tList > tList.out 2>&1
	diff -b $(srcdir)/tList.exp tList.out
.PHONY: check-tPlex
check-tPlex: tPlex
	./tPlex > tPlex.out 2>&1
	diff -b $(srcdir)/tPlex.exp tPlex.out
.PHONY: check-tLList
check-tLList: tLList
	./tLList > tLList.out 2>&1
	diff -b $(srcdir)/tLList.exp tLList.out
.PHONY: check-tVec
check-tVec: tVec
	./tVec > tVec.out 2>&1
	diff -b $(srcdir)/tVec.exp tVec.out
.PHONY: check-tiLList
check-tiLList: tiLList
	./tiLList > tiLList.out 2>&1
	diff -b $(srcdir)/tiLList.exp tiLList.out

check-tGetOpt: tGetOpt $(srcdir)/tGetOpt.inp
	./tGetOpt -abc -de10 -2000 -h3i \
	  <$(srcdir)/tGetOpt.inp >tGetOpt.out 2>&1
	diff -b $(srcdir)/tGetOpt.exp tGetOpt.out

$(TOUTS): $(LIBGXX)

LIBTEST=libtest.a

# We don't do check-tRandom, because it is not portable.

# Comment this out if your compiler doesn't handle templates:
CHECK_TEMPLATES=check-templates

tests checktests: clean_tests test_h \
  check-tObstack check-tString check-tInteger \
  check-tRational check-tBitSet check-tBitString \
  check-tFix check-tFix16 check-tFix24 check-tGetOpt \
  check-tList check-tPlex check-tLList check-tVec \
  check-tStack check-tQueue check-tDeque check-tPQ \
  check-tSet check-tBag check-tMap $(CHECK_TEMPLATES)
	./test_h

check-templates: check-tiLList

# Build all the tests, but don't run them. (Useful when cross-compiling.)

make-tests: $(TOUTS)

test_h: test_h.o
	$(CXX) $(LDFLAGS) test_h.o -o $@ $(LIBS) -lm

$(LIBTEST): $(LHDRS) $(LOBJS)
	rm -f $(LIBTEST)
	$(AR) r $(LIBTEST) $(LOBJS)
	$(RANLIB) $(LIBTEST)

#
# other tests
#
tObstack: tObstack.o
	$(CXX) $(LDFLAGS) tObstack.o -o $@ $(LIBS)

tString: tString.o
	$(CXX) $(LDFLAGS) tString.o -o $@ $(LIBS)

tInteger: tInteger.o
	$(CXX) $(LDFLAGS) tInteger.o -o $@ $(LIBS) -lm

tRational: tRational.o
	$(CXX) $(LDFLAGS) tRational.o -o $@ $(LIBS) -lm

tBitSet: tBitSet.o
	$(CXX) $(LDFLAGS) tBitSet.o -o $@ $(LIBS)

tBitString: tBitString.o
	$(CXX) $(LDFLAGS) tBitString.o -o $@ $(LIBS)

tFix: tFix.o
	$(CXX) $(LDFLAGS) tFix.o -o $@ $(LIBS) -lm

tFix16: tFix16.o
	$(CXX) $(LDFLAGS) tFix16.o -o $@ $(LIBS) -lm

tFix24: tFix24.o
	$(CXX) $(LDFLAGS) tFix24.o -o $@ $(LIBS) -lm

tRandom: tRandom.o
	$(CXX) $(LDFLAGS) tRandom.o -o $@ $(LIBS) -lm

tiLList: tiLList.o
	$(CXX) $(LDFLAGS) tiLList.o -o $@ $(LIBS)

tGetOpt: tGetOpt.o
	$(CXX) $(LDFLAGS) tGetOpt.o -o $@ $(LIBS)

twrapper:  $(LIBTEST)  twrapper.o
	$(CXX) $(LDFLAGS) twrapper.o -o $@ $(LIBTEST) $(LIBS)

tgwrapper:  $(LIBTEST)  tgwrapper.o
	$(CXX) $(LDFLAGS) tgwrapper.o -o $@ $(LIBTEST) $(LIBS)

tStack:  $(LIBTEST)  tStack.o
	$(CXX) $(LDFLAGS) tStack.o -o $@ $(LIBTEST) $(LIBS)

tQueue:  $(LIBTEST)  tQueue.o
	$(CXX) $(LDFLAGS) tQueue.o -o $@ $(LIBTEST) $(LIBS)

tDeque:  $(LIBTEST)  tDeque.o
	$(CXX) $(LDFLAGS) tDeque.o -o $@ $(LIBTEST) $(LIBS)

tPQ:  $(LIBTEST)  tPQ.o
	$(CXX) $(LDFLAGS) tPQ.o -o $@ $(LIBTEST) $(LIBS)

tSet:  $(LIBTEST)  tSet.o
	$(CXX) $(LDFLAGS) tSet.o -o $@ $(LIBTEST) $(LIBS)

tBag:  $(LIBTEST)  tBag.o
	$(CXX) $(LDFLAGS) tBag.o -o $@ $(LIBTEST) $(LIBS)

tMap:  $(LIBTEST)  tMap.o
	$(CXX) $(LDFLAGS) tMap.o -o $@ $(LIBTEST) $(LIBS)

tList:  $(LIBTEST)  tList.o
	$(CXX) $(LDFLAGS) tList.o -o $@ $(LIBTEST) $(LIBS)

tPlex:  $(LIBTEST)  tPlex.o
	$(CXX) $(LDFLAGS) tPlex.o -o $@ $(LIBTEST) $(LIBS)

tLList:  $(LIBTEST)  tLList.o
	$(CXX) $(LDFLAGS) tLList.o -o $@ $(LIBTEST) $(LIBS)

tVec:  $(LIBTEST)  tVec.o
	$(CXX) $(LDFLAGS) tVec.o -o $@ $(LIBTEST) $(LIBS)

idefs.h:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val defs i
iSet.h iSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val Set i
iXPSet.h iXPSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val XPSet i
iOXPSet.h iOXPSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val OXPSet i
iSLSet.h iSLSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SLSet i
iOSLSet.h iOSLSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val OSLSet i
iBSTSet.h iBSTSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val BSTSet i
iAVLSet.h iAVLSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val AVLSet i
iSplayNode.h iSplayNode.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SplayNode i
iSplaySet.h iSplaySet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SplaySet i
iVHSet.h iVHSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val VHSet i
iVOHSet.h iVOHSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val VOHSet i
iCHSet.h iCHSet.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val CHSet i
iCHNode.h iCHNode.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val CHNode i
iBag.h iBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val Bag i
iXPBag.h iXPBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val XPBag i
iOXPBag.h iOXPBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val OXPBag i
iSLBag.h iSLBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SLBag i
iOSLBag.h iOSLBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val OSLBag i
iSplayBag.h iSplayBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SplayBag i
iVHBag.h iVHBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val VHBag i
iCHBag.h iCHBag.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val CHBag i
iPQ.h iPQ.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val PQ i
iPHPQ.h iPHPQ.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val PHPQ i
iSplayPQ.h iSplayPQ.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SplayPQ i
iXPPQ.h iXPPQ.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val XPPQ i
iStack.h iStack.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val Stack i
iQueue.h iQueue.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val Queue i
iDeque.h iDeque.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val Deque i
iSLStack.h iSLStack.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SLStack i
iSLQueue.h iSLQueue.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SLQueue i
iDLDeque.h iDLDeque.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val DLDeque i
iList.h iList.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val List i
iPlex.h iPlex.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val Plex i
iFPlex.h iFPlex.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val FPlex i
iXPlex.h iXPlex.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val XPlex i
iMPlex.h iMPlex.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val MPlex i
iRPlex.h iRPlex.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val RPlex i
iFPStack.h iFPStack.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val FPStack i
iXPStack.h iXPStack.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val XPStack i
iFPQueue.h iFPQueue.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val FPQueue i
iXPQueue.h iXPQueue.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val XPQueue i
iXPDeque.h iXPDeque.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val XPDeque i
iSLList.h iSLList.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val SLList i
iDLList.h iDLList.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val DLList i
iVec.h iVec.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val Vec i
iAVec.h iAVec.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val AVec i
iMap.h iMap.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) -2 int val int val Map i
iVHMap.h iVHMap.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) -2 int val int val VHMap i
iCHMap.h iCHMap.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) -2 int val int val CHMap i
iSplayMap.h iSplayMap.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) -2 int val int val SplayMap i
iAVLMap.h iAVLMap.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) -2 int val int val AVLMap i
iRAVLMap.h iRAVLMap.cc:
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) -2 int val int val RAVLMap i
iVStack.h iVStack.cc: iStack.h
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val VStack i
iVQueue.h iVQueue.cc: iQueue.h
	PROTODIR=$(PROTODIR); export PROTODIR; $(GENCLASS) int val VQueue i

relink: force
	rm -f $(TOUTS)

.PHONY: clean_tests
clean_tests: force
	rm -f *.out

force:
