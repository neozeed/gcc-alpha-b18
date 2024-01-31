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
host_makefile_frag = ../../host/any
#
# Makefile for newlib/libm/math
#

#  @(#)Makefile 5.1beta 93/09/24 
# 
#  ====================================================
#  Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
# 
#  Developed at SunPro, a Sun Microsystems, Inc. business.
#  Permission to use, copy, modify, and distribute this
#  software is freely granted, provided that this notice 
#  is preserved.
#  ====================================================
# 

#
# Heavily modified at Cygnus Support
#

srcdir = .

SHELL = sh

TOP = ../..
SRCTOP = ../..
TARGETDOC = ../targetdep.tex

#### Host, target, and site specific Makefile fragments come in here.
# These are set by configure.
program_transform_name = 

# Find the tools used to build newlib.
# ${rootpre} should be set to the name of the top level newlib build directory
# followed by a '/'.  Likewise with ${srcrootpre}.  If ${rootpre} is not set,
# we use program_transform_name to guess the name of the program.
# Each Makefile must define $(TOP) and $(SRCTOP); they will usually be the
# same, but they are different when building multiple versions with
# different compilation flags: $(TOP) will typically contain extra ../'s.
CC = gcc
AS = `if [ -f $${rootpre}$(TOP)/../../gas/as.new ] ; \
	then echo $${rootpre}$(TOP)/../../gas/as.new ; \
	else t='$(program_transform_name)'; echo as | sed -e '' $$t ; fi`
DLLTOOL = `if [ -f $${rootpre}$(TOP)/../../binutils/dlltool ] ; \
	then echo $${rootpre}$(TOP)/../../binutils/dlltool ; \
	else t='$(program_transform_name)'; echo dlltool | sed -e '' $$t ; fi`
AR = `if [ -f $${rootpre}$(TOP)/../../binutils/ar ] ; \
	then echo $${rootpre}$(TOP)/../../binutils/ar ; \
	else t='$(program_transform_name)'; echo ar | sed -e '' $$t ; fi`
AR_FLAGS = qc
RANLIB = `if [ -f $${rootpre}$(TOP)/../../binutils/ranlib ] ; \
	then echo $${rootpre}$(TOP)/../../binutils/ranlib ; \
	else t='$(program_transform_name)'; echo ranlib | sed -e '' $$t ; fi`

# CFLAGS is the general CFLAGS.  CROSS_CFLAGS is for special newlib
# flags.  TARGET_CFLAGS is for target specific flags, and is
# initialized by the configure script.  NEWLIB_CFLAGS is for flags we
# must always pass to gcc.
CFLAGS = -g
CROSS_CFLAGS =
TARGET_CFLAGS = -O2 -DHAVE_OPENDIR -DHAVE_RENAME -DSIGNAL_PROVIDED
NEWLIB_CFLAGS = -fno-builtin

# Get the include directories.  Note that in subdirectories, the
# string passed down from the top newlib Makefile will override this
# expression.

# If we are doing a cygwin32 build, we need to add a -I for the winsup
# header files.  We can't check whether winsup has been configured at
# this point, because newlib is normally built before winsup is
# configured.

INCLUDES = ` \
  srcrootpre=$${srcrootpre-$(srcdir)/}; \
  if [ x$(target_os) = xcygwin32 ]; then \
    echo -I$${rootpre}$(TOP)/targ-include -I$${srcrootpre}$(SRCTOP)/libc/include -I$${srcrootpre}$(SRCTOP)/../winsup/include; \
  else \
    echo -I$${rootpre}$(TOP)/targ-include -I$${srcrootpre}$(SRCTOP)/libc/include; \
  fi`

# Using CFLAGS here may be confusing if the user has given a special
# CFLAGS intended for use on the host, since we are passing it to the
# cross-compiler; I'm not sure what to do about this.  INCLUDES is
# from the top level Makefile.
.c.o:
	$(CC) $(CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) $(NEWLIB_CFLAGS) $(INCLUDES) -c $<

.s.o:
	$(AS) $(INCLUDES) -o $*.o $<

.S.o:
	$(CC) $(CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) $(NEWLIB_CFLAGS) $(INCLUDES) -c $<

# Build documentation from a .c file.
CHEW = `srcrootpre=$${srcrootpre-$(srcdir)/}; echo $${rootpre}$(TOP)/doc/makedoc -f $${srcrootpre}$(SRCTOP)/doc/doc.str`

.c.def:
	$(CHEW) < $< >$*.def 2>$*.ref
###

src = 	k_standard.c k_rem_pio2.c \
	k_cos.c k_sin.c k_tan.c \
	e_acos.c e_acosh.c e_asin.c e_atan2.c \
	e_atanh.c e_cosh.c e_exp.c e_fmod.c \
	er_gamma.c e_hypot.c e_j0.c \
	e_j1.c e_jn.c er_lgamma.c \
	e_log.c e_log10.c e_pow.c e_rem_pio2.c e_remainder.c \
	e_scalb.c e_sinh.c e_sqrt.c \
	w_acos.c w_acosh.c w_asin.c w_atan2.c \
	w_atanh.c w_cosh.c w_exp.c w_fmod.c \
	w_gamma.c wr_gamma.c w_hypot.c w_j0.c \
	w_j1.c w_jn.c w_lgamma.c wr_lgamma.c \
	w_log.c w_log10.c w_pow.c w_remainder.c \
	w_scalb.c w_sinh.c w_sqrt.c \
	s_asinh.c s_atan.c s_cbrt.c s_ceil.c s_copysign.c \
	s_cos.c s_erf.c s_expm1.c s_fabs.c s_finite.c s_floor.c \
	s_frexp.c s_ilogb.c s_isnan.c s_ldexp.c s_lib_ver.c \
	s_log1p.c s_logb.c s_matherr.c s_modf.c s_nextafter.c \
	s_rint.c s_scalbn.c s_signif.c s_sin.c \
	s_tan.c s_tanh.c \
	s_infinity.c s_isinf.c s_nan.c s_infconst.c \
	s_signgam.c

fsrc =	kf_rem_pio2.c \
	kf_cos.c kf_sin.c kf_tan.c \
	ef_acos.c ef_acosh.c ef_asin.c ef_atan2.c \
	ef_atanh.c ef_cosh.c ef_exp.c ef_fmod.c \
	erf_gamma.c ef_hypot.c ef_j0.c \
	ef_j1.c ef_jn.c erf_lgamma.c \
	ef_log.c ef_log10.c ef_pow.c ef_rem_pio2.c ef_remainder.c \
	ef_scalb.c ef_sinh.c ef_sqrt.c \
	wf_acos.c wf_acosh.c wf_asin.c wf_atan2.c \
	wf_atanh.c wf_cosh.c wf_exp.c wf_fmod.c \
	wf_gamma.c wrf_gamma.c wf_hypot.c wf_j0.c \
	wf_j1.c wf_jn.c wf_lgamma.c wrf_lgamma.c \
	wf_log.c wf_log10.c wf_pow.c wf_remainder.c \
	wf_scalb.c wf_sinh.c wf_sqrt.c \
	sf_asinh.c sf_atan.c sf_cbrt.c sf_ceil.c sf_copysign.c \
	sf_cos.c sf_erf.c sf_expm1.c sf_fabs.c sf_finite.c sf_floor.c \
	sf_frexp.c sf_ilogb.c sf_isnan.c sf_ldexp.c \
	sf_log1p.c sf_logb.c sf_modf.c sf_nextafter.c \
	sf_rint.c sf_scalbn.c sf_signif.c sf_sin.c \
	sf_tan.c sf_tanh.c \
	sf_infinity.c sf_isinf.c sf_nan.c

obj = 	k_standard.o k_rem_pio2.o \
	k_cos.o k_sin.o k_tan.o \
	e_acos.o e_acosh.o e_asin.o e_atan2.o \
	e_atanh.o e_cosh.o e_exp.o e_fmod.o \
	er_gamma.o e_hypot.o e_j0.o \
	e_j1.o e_jn.o er_lgamma.o \
	e_log.o e_log10.o e_pow.o e_rem_pio2.o e_remainder.o  \
	e_scalb.o e_sinh.o e_sqrt.o \
	w_acos.o w_acosh.o w_asin.o w_atan2.o \
	w_atanh.o w_cosh.o w_exp.o w_fmod.o \
	w_gamma.o wr_gamma.o w_hypot.o w_j0.o \
	w_j1.o w_jn.o w_lgamma.o wr_lgamma.o \
	w_log.o w_log10.o w_pow.o w_remainder.o \
	w_scalb.o w_sinh.o w_sqrt.o \
	w_cabs.o w_drem.o \
	s_asinh.o s_atan.o s_cbrt.o s_ceil.o s_copysign.o \
	s_cos.o s_erf.o s_expm1.o s_fabs.o s_finite.o s_floor.o \
	s_frexp.o s_ilogb.o s_isnan.o s_ldexp.o s_lib_ver.o \
	s_log1p.o s_logb.o s_matherr.o s_modf.o s_nextafter.o \
	s_rint.o s_scalbn.o s_signif.o s_sin.o \
	s_tan.o s_tanh.o \
	s_infinity.o s_isinf.o s_nan.o s_infconst.o

fobj =	kf_rem_pio2.o \
	kf_cos.o kf_sin.o kf_tan.o \
	ef_acos.o ef_acosh.o ef_asin.o ef_atan2.o \
	ef_atanh.o ef_cosh.o ef_exp.o ef_fmod.o \
	erf_gamma.o ef_hypot.o ef_j0.o \
	ef_j1.o ef_jn.o erf_lgamma.o \
	ef_log.o ef_log10.o ef_pow.o ef_rem_pio2.o ef_remainder.o \
	ef_scalb.o ef_sinh.o ef_sqrt.o \
	wf_acos.o wf_acosh.o wf_asin.o wf_atan2.o \
	wf_atanh.o wf_cosh.o wf_exp.o wf_fmod.o \
	wf_gamma.o wrf_gamma.o wf_hypot.o wf_j0.o \
	wf_j1.o wf_jn.o wf_lgamma.o wrf_lgamma.o \
	wf_log.o wf_log10.o wf_pow.o wf_remainder.o \
	wf_scalb.o wf_sinh.o wf_sqrt.o \
	wf_cabs.o wf_drem.o \
	sf_asinh.o sf_atan.o sf_cbrt.o sf_ceil.o sf_copysign.o \
	sf_cos.o sf_erf.o sf_expm1.o sf_fabs.o sf_finite.o sf_floor.o \
	sf_frexp.o sf_ilogb.o sf_isnan.o sf_ldexp.o \
	sf_log1p.o sf_logb.o sf_modf.o sf_nextafter.o \
	sf_rint.o sf_scalbn.o sf_signif.o sf_sin.o \
	sf_tan.o sf_tanh.o \
	sf_infinity.o sf_isinf.o sf_nan.o

chobj =	wacos.def wacosh.def wasin.def sasinh.def \
	satan.def watan2.def watanh.def wj0.def \
	scopysign.def wcosh.def serf.def wexp.def \
	sfabs.def sfloor.def wfmod.def sfrexp.def \
	wgamma.def whypot.def sldexp.def wlog.def \
	wlog10.def slog1p.def smatherr.def smodf.def \
	wpow.def wremainder.def ssin.def wsinh.def \
	scbrt.def wsqrt.def stan.def stanh.def \
	sinfinity.def sisnan.def sscalbn.def snextafter.def \
	snan.def silogb.def sexpm1.def

all: lib.a

lib.a: $(obj) $(fobj) 
	rm -f $@
	$(AR) $(AR_FLAGS) $@ $(obj) $(fobj)

doc: $(chobj)
	cat $(srcdir)/math.tex >> $(TARGETDOC)

clean mostlyclean:
	$(RM) $(obj) $(fobj) $(chobj) *~ core *.ref lib.a

distclean maintainer-clean realclean: clean
	rm -f Makefile config.status

Makefile: Makefile.in $(host_makefile_frag) $(target_makefile_frag)
	$(SHELL) config.status

# Texinfo does not appear to support underscores in file names, so we
# name the .def files without underscores.

wacos.def: w_acos.c
	$(CHEW) < $(srcdir)/w_acos.c >$@ 2>/dev/null
wacosh.def: w_acosh.c
	$(CHEW) < $(srcdir)/w_acosh.c >$@ 2>/dev/null
wasin.def: w_asin.c
	$(CHEW) < $(srcdir)/w_asin.c >$@ 2>/dev/null
sasinh.def: s_asinh.c
	$(CHEW) < $(srcdir)/s_asinh.c >$@ 2>/dev/null
satan.def: s_atan.c
	$(CHEW) < $(srcdir)/s_atan.c >$@ 2>/dev/null
watan2.def: w_atan2.c
	$(CHEW) < $(srcdir)/w_atan2.c >$@ 2>/dev/null
watanh.def: w_atanh.c
	$(CHEW) < $(srcdir)/w_atanh.c >$@ 2>/dev/null
wj0.def: w_j0.c
	$(CHEW) < $(srcdir)/w_j0.c >$@ 2>/dev/null
scopysign.def: s_copysign.c
	$(CHEW) < $(srcdir)/s_copysign.c >$@ 2>/dev/null
wcosh.def: w_cosh.c
	$(CHEW) < $(srcdir)/w_cosh.c >$@ 2>/dev/null
serf.def: s_erf.c
	$(CHEW) < $(srcdir)/s_erf.c >$@ 2>/dev/null
wexp.def: w_exp.c
	$(CHEW) < $(srcdir)/w_exp.c >$@ 2>/dev/null
sfabs.def: s_fabs.c
	$(CHEW) < $(srcdir)/s_fabs.c >$@ 2>/dev/null
sfloor.def: s_floor.c
	$(CHEW) < $(srcdir)/s_floor.c >$@ 2>/dev/null
wfmod.def: w_fmod.c
	$(CHEW) < $(srcdir)/w_fmod.c >$@ 2>/dev/null
sfrexp.def: s_frexp.c
	$(CHEW) < $(srcdir)/s_frexp.c >$@ 2>/dev/null
wgamma.def: w_gamma.c
	$(CHEW) < $(srcdir)/w_gamma.c >$@ 2>/dev/null
whypot.def: w_hypot.c
	$(CHEW) < $(srcdir)/w_hypot.c >$@ 2>/dev/null
sldexp.def: s_ldexp.c
	$(CHEW) < $(srcdir)/s_ldexp.c >$@ 2>/dev/null
wlog.def: w_log.c
	$(CHEW) < $(srcdir)/w_log.c >$@ 2>/dev/null
wlog10.def: w_log10.c
	$(CHEW) < $(srcdir)/w_log10.c >$@ 2>/dev/null
slog1p.def: s_log1p.c
	$(CHEW) < $(srcdir)/s_log1p.c >$@ 2>/dev/null
smatherr.def: s_matherr.c
	$(CHEW) < $(srcdir)/s_matherr.c >$@ 2>/dev/null
smodf.def: s_modf.c
	$(CHEW) < $(srcdir)/s_modf.c >$@ 2>/dev/null
wpow.def: w_pow.c
	$(CHEW) < $(srcdir)/w_pow.c >$@ 2>/dev/null
wremainder.def: w_remainder.c
	$(CHEW) < $(srcdir)/w_remainder.c >$@ 2>/dev/null
ssin.def: s_sin.c
	$(CHEW) < $(srcdir)/s_sin.c >$@ 2>/dev/null
wsinh.def: w_sinh.c
	$(CHEW) < $(srcdir)/w_sinh.c >$@ 2>/dev/null
scbrt.def: s_cbrt.c
	$(CHEW) < $(srcdir)/s_cbrt.c >$@ 2>/dev/null
wsqrt.def: w_sqrt.c
	$(CHEW) < $(srcdir)/w_sqrt.c >$@ 2>/dev/null
stan.def: s_tan.c
	$(CHEW) < $(srcdir)/s_tan.c >$@ 2>/dev/null
stanh.def: s_tanh.c
	$(CHEW) < $(srcdir)/s_tanh.c >$@ 2>/dev/null
sinfinity.def: s_infinity.c
	$(CHEW) < $(srcdir)/s_infinity.c >$@ 2>/dev/null
sisnan.def: s_isnan.c
	$(CHEW) < $(srcdir)/s_isnan.c >$@ 2>/dev/null
sscalbn.def: s_scalbn.c
	$(CHEW) < $(srcdir)/s_scalbn.c >$@ 2>/dev/null
snextafter.def: s_nextafter.c
	$(CHEW) < $(srcdir)/s_nextafter.c >$@ 2>/dev/null
snan.def: s_nan.c
	$(CHEW) < $(srcdir)/s_nan.c >$@ 2>/dev/null
silogb.def: s_ilogb.c
	$(CHEW) < $(srcdir)/s_ilogb.c >$@ 2>/dev/null
sexpm1.def: s_expm1.c
	$(CHEW) < $(srcdir)/s_expm1.c >$@ 2>/dev/null

# A partial dependency list.

$(obj) $(fobj): $(srcdir)/$(SRCTOP)/libc/include/math.h fdlibm.h

# To support SunOS VPATH
e_acos.o: e_acos.c
e_acosh.o: e_acosh.c
e_asin.o: e_asin.c
e_atan2.o: e_atan2.c
e_atanh.o: e_atanh.c
e_cosh.o: e_cosh.c
e_exp.o: e_exp.c
e_fmod.o: e_fmod.c
e_hypot.o: e_hypot.c
e_j0.o: e_j0.c
e_j1.o: e_j1.c
e_jn.o: e_jn.c
e_log.o: e_log.c
e_log10.o: e_log10.c
e_pow.o: e_pow.c
e_rem_pio2.o: e_rem_pio2.c
e_remainder.o: e_remainder.c
e_scalb.o: e_scalb.c
e_sinh.o: e_sinh.c
e_sqrt.o: e_sqrt.c
ef_acos.o: ef_acos.c
ef_acosh.o: ef_acosh.c
ef_asin.o: ef_asin.c
ef_atan2.o: ef_atan2.c
ef_atanh.o: ef_atanh.c
ef_cosh.o: ef_cosh.c
ef_exp.o: ef_exp.c
ef_fmod.o: ef_fmod.c
ef_hypot.o: ef_hypot.c
ef_j0.o: ef_j0.c
ef_j1.o: ef_j1.c
ef_jn.o: ef_jn.c
ef_log.o: ef_log.c
ef_log10.o: ef_log10.c
ef_pow.o: ef_pow.c
ef_rem_pio2.o: ef_rem_pio2.c
ef_remainder.o: ef_remainder.c
ef_scalb.o: ef_scalb.c
ef_sinh.o: ef_sinh.c
ef_sqrt.o: ef_sqrt.c
er_gamma.o: er_gamma.c
er_lgamma.o: er_lgamma.c
erf_gamma.o: erf_gamma.c
erf_lgamma.o: erf_lgamma.c
k_cos.o: k_cos.c
k_rem_pio2.o: k_rem_pio2.c
k_sin.o: k_sin.c
k_standard.o: k_standard.c
k_tan.o: k_tan.c
kf_cos.o: kf_cos.c
kf_rem_pio2.o: kf_rem_pio2.c
kf_sin.o: kf_sin.c
kf_tan.o: kf_tan.c
s_asinh.o: s_asinh.c
s_atan.o: s_atan.c
s_cbrt.o: s_cbrt.c
s_ceil.o: s_ceil.c
s_copysign.o: s_copysign.c
s_cos.o: s_cos.c
s_erf.o: s_erf.c
s_expm1.o: s_expm1.c
s_fabs.o: s_fabs.c
s_finite.o: s_finite.c
s_floor.o: s_floor.c
s_frexp.o: s_frexp.c
s_ilogb.o: s_ilogb.c
s_infconst.o: s_infconst.c
s_infinity.o: s_infinity.c
s_isinf.o: s_isinf.c
s_isnan.o: s_isnan.c
s_ldexp.o: s_ldexp.c
s_lib_ver.o: s_lib_ver.c
s_log1p.o: s_log1p.c
s_logb.o: s_logb.c
s_matherr.o: s_matherr.c
s_modf.o: s_modf.c
s_nan.o: s_nan.c
s_nextafter.o: s_nextafter.c
s_rint.o: s_rint.c
s_scalbn.o: s_scalbn.c
s_signif.o: s_signif.c
s_sin.o: s_sin.c
s_tan.o: s_tan.c
s_tanh.o: s_tanh.c
sf_asinh.o: sf_asinh.c
sf_atan.o: sf_atan.c
sf_cbrt.o: sf_cbrt.c
sf_ceil.o: sf_ceil.c
sf_copysign.o: sf_copysign.c
sf_cos.o: sf_cos.c
sf_erf.o: sf_erf.c
sf_expm1.o: sf_expm1.c
sf_fabs.o: sf_fabs.c
sf_finite.o: sf_finite.c
sf_floor.o: sf_floor.c
sf_frexp.o: sf_frexp.c
sf_ilogb.o: sf_ilogb.c
sf_infinity.o: sf_infinity.c
sf_isinf.o: sf_isinf.c
sf_isnan.o: sf_isnan.c
sf_ldexp.o: sf_ldexp.c
sf_log1p.o: sf_log1p.c
sf_logb.o: sf_logb.c
sf_modf.o: sf_modf.c
sf_nan.o: sf_nan.c
sf_nextafter.o: sf_nextafter.c
sf_rint.o: sf_rint.c
sf_scalbn.o: sf_scalbn.c
sf_signif.o: sf_signif.c
sf_sin.o: sf_sin.c
sf_tan.o: sf_tan.c
sf_tanh.o: sf_tanh.c
w_acos.o: w_acos.c
w_acosh.o: w_acosh.c
w_asin.o: w_asin.c
w_atan2.o: w_atan2.c
w_atanh.o: w_atanh.c
w_cabs.o: w_cabs.c
w_cosh.o: w_cosh.c
w_drem.o: w_drem.c
w_exp.o: w_exp.c
w_fmod.o: w_fmod.c
w_gamma.o: w_gamma.c
w_hypot.o: w_hypot.c
w_j0.o: w_j0.c
w_j1.o: w_j1.c
w_jn.o: w_jn.c
w_lgamma.o: w_lgamma.c
w_log.o: w_log.c
w_log10.o: w_log10.c
w_pow.o: w_pow.c
w_remainder.o: w_remainder.c
w_scalb.o: w_scalb.c
w_sinh.o: w_sinh.c
w_sqrt.o: w_sqrt.c
wf_acos.o: wf_acos.c
wf_acosh.o: wf_acosh.c
wf_asin.o: wf_asin.c
wf_atan2.o: wf_atan2.c
wf_atanh.o: wf_atanh.c
wf_cabs.o: wf_cabs.c
wf_cosh.o: wf_cosh.c
wf_drem.o: wf_drem.c
wf_exp.o: wf_exp.c
wf_fmod.o: wf_fmod.c
wf_gamma.o: wf_gamma.c
wf_hypot.o: wf_hypot.c
wf_j0.o: wf_j0.c
wf_j1.o: wf_j1.c
wf_jn.o: wf_jn.c
wf_lgamma.o: wf_lgamma.c
wf_log.o: wf_log.c
wf_log10.o: wf_log10.c
wf_pow.o: wf_pow.c
wf_remainder.o: wf_remainder.c
wf_scalb.o: wf_scalb.c
wf_sinh.o: wf_sinh.c
wf_sqrt.o: wf_sqrt.c
wr_gamma.o: wr_gamma.c
wr_lgamma.o: wr_lgamma.c
wrf_gamma.o: wrf_gamma.c
wrf_lgamma.o: wrf_lgamma.c

# FIXME: There should be an @-sign in front of the `if'.
# Leave out until this is tested a bit more.
multi-do:
	if [ -z "$(MULTIDIRS)" ]; then \
	  true; \
	else \
	  rootpre=`pwd`/; export rootpre; \
	  srcrootpre=`cd $(srcdir); pwd`/; export srcrootpre; \
	  lib=`echo $${rootpre} | sed -e 's,^.*/\([^/][^/]*\)/$$,\1,'`; \
	  compiler="$(CC)"; \
	  for i in `$${compiler} --print-multi-lib 2>/dev/null`; do \
	    dir=`echo $$i | sed -e 's/;.*$$//'`; \
	    if [ "$${dir}" = "." ]; then \
	      true; \
	    else \
	      if [ -d ../$${dir}/$${lib} ]; then \
		flags=`echo $$i | sed -e 's/^[^;]*;//' -e 's/@/ -/g'`; \
		if (cd ../$${dir}/$${lib}; $(MAKE) $(FLAGS_TO_PASS) \
				CFLAGS="$(CFLAGS) $${flags}" \
				CXXFLAGS="$(CXXFLAGS) $${flags}" \
				LIBCFLAGS="$(LIBCFLAGS) $${flags}" \
				LIBCXXFLAGS="$(LIBCXXFLAGS) $${flags}" \
				$(DO)); then \
		  true; \
		else \
		  exit 1; \
		fi; \
	      else true; \
	      fi; \
	    fi; \
	  done; \
	fi

# FIXME: There should be an @-sign in front of the `if'.
# Leave out until this is tested a bit more.
multi-clean:
	if [ -z "$(MULTIDIRS)" ]; then \
	  true; \
	else \
	  lib=`pwd | sed -e 's,^.*/\([^/][^/]*\)$$,\1,'`; \
	  for dir in Makefile $(MULTIDIRS); do \
	    if [ -f ../$${dir}/$${lib}/Makefile ]; then \
	      if (cd ../$${dir}/$${lib}; $(MAKE) $(FLAGS_TO_PASS) $(DO)); \
	      then true; \
	      else exit 1; \
	      fi; \
	    else true; \
	    fi; \
	  done; \
	fi
