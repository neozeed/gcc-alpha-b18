# Generated automatically from Makefile.in by configure.
srcdir = .

EXECUTABLES = pthreads

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
	-rm -f *~ *.o a.out xgdb *.x *.ci *.tmp core* $(EXECUTABLES)

distclean maintainer-clean realclean: clean
	-rm -f Makefile config.status config.log config.h

Makefile : $(srcdir)/Makefile.in $(srcdir)/configure.in
	$(SHELL) ./config.status --recheck

config.h: stamp-h ; @true
stamp-h: config.in config.status
	CONFIG_HEADERS=config.h:config.in $(SHELL) config.status

config.status: configure
	$(SHELL) config.status --recheck
