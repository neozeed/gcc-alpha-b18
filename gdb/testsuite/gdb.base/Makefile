# Generated automatically from Makefile.in by configure.
srcdir = .

EXECUTABLES = bitfields interrupt mips_pro return twice-tmp break langs \
	nodebug run watchpoint callfuncs opaque scope whatis compiler \
	opaque scope coremaker printcmds setvar exprs list ptype \
	sigall funcargs recurse signals structs

# uuencoded format to avoid SCCS/RCS problems with binary files.
CROSS_EXECUTABLES = i486-elf i860-elf m68k-elf m68k-aout m68k-aout2  \
	mips-ecoff sparc-aout sparc-elf

all:
	@echo "Nothing to be done for all..."

info:
install-info:
dvi:
install:
uninstall: force
installcheck:
check:

clean mostlyclean:
	-rm -f *~ *.o a.out xgdb *.x $(CROSS_EXECUTABLES) *.ci *.tmp
	-rm -f core core.coremaker coremaker.core corefile $(EXECUTABLES)
	-rm -f twice-tmp.c

distclean maintainer-clean realclean: clean
	-rm -f *~ core
	-rm -f Makefile config.status config.log
	-rm -f *-init.exp
	-rm -fr *.log summary detail *.plog *.sum *.psum site.*

Makefile : $(srcdir)/Makefile.in $(srcdir)/configure.in
	$(SHELL) ./config.status --recheck
