# Generated automatically from Makefile.in by configure.
srcdir = .

all: 
	@echo "Nothing to be done for all..."

#### host, target, and site specific Makefile frags come in here.

.SUFFIXES: .ch .o .exe .exp .check

# Do 'make chillvars.check' to run just the chillvars.{ch,exp} test.

.exp.check:
	rootme=`pwd`/; export rootme; \
	cd .. ; \
	$(MAKE) just-check RUNTESTFLAGS="${RUNTESTFLAGS} $*.exp" \
	  EXPECT=${EXPECT}

clean mostlyclean:
	-rm -f *.o ${OBJS} *.exe *~ core 

distclean maintainer-clean realclean: clean
	-rm -f Makefile config.status config.log

Makefile: $(srcdir)/Makefile.in $(srcdir)/configure.in
	$(SHELL) ./config.status --recheck
