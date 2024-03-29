dnl written by Rob Savoye <rob@cygnus.com> for Cygnus Support
dnl major rewriting for Tcl 7.5 by Don Libes <libes@nist.gov>

sinclude(../bfd/aclocal.m4)

dnl CY_AC_PATH_TCLCONFIG and CY_AC_LOAD_TCLCONFIG should be invoked
dnl (in that order) before any other TCL macros.  Similarly for TK.

dnl CYGNUS LOCAL: This gets the right posix flag for gcc
AC_DEFUN(CY_AC_TCL_LYNX_POSIX,
[AC_REQUIRE([AC_PROG_CC])AC_REQUIRE([AC_PROG_CPP])
AC_MSG_CHECKING([if running LynxOS])
AC_CACHE_VAL(ac_cv_os_lynx,
[AC_EGREP_CPP(yes,
[/*
 * The old Lynx "cc" only defines "Lynx", but the newer one uses "__Lynx__"
 */
#if defined(__Lynx__) || defined(Lynx)
yes
#endif
], ac_cv_os_lynx=yes, ac_cv_os_lynx=no)])
#
if test "$ac_cv_os_lynx" = "yes" ; then
  AC_MSG_RESULT(yes)
  AC_DEFINE(LYNX)
  AC_MSG_CHECKING([whether -mposix or -X is available])
  AC_CACHE_VAL(ac_cv_c_posix_flag,
  [AC_TRY_COMPILE(,[
  /*
   * This flag varies depending on how old the compiler is.
   * -X is for the old "cc" and "gcc" (based on 1.42).
   * -mposix is for the new gcc (at least 2.5.8).
   */
  #if defined(__GNUC__) && __GNUC__ >= 2
  choke me
  #endif
  ], ac_cv_c_posix_flag=" -mposix", ac_cv_c_posix_flag=" -X")])
  CC="$CC $ac_cv_c_posix_flag"
  AC_MSG_RESULT($ac_cv_c_posix_flag)
  else
  AC_MSG_RESULT(no)
fi
])

#
# Sometimes the native compiler is a bogus stub for gcc or /usr/ucb/cc. This
# makes configure think it's cross compiling. If --target wasn't used, then
# we can't configure, so something is wrong. We don't use the cache
# here cause if somebody fixes their compiler install, we want this to work.
AC_DEFUN(CY_AC_C_WORKS,
[# If we cannot compile and link a trivial program, we can't expect anything to work
AC_MSG_CHECKING(whether the compiler ($CC) actually works)
AC_TRY_COMPILE(, [/* don't need anything here */],
        c_compiles=yes, c_compiles=no)

AC_TRY_LINK(, [/* don't need anything here */],
        c_links=yes, c_links=no)

if test x"${c_compiles}" = x"no" ; then
  AC_MSG_ERROR(the native compiler is broken and won't compile.)
fi

if test x"${c_links}" = x"no" ; then
  AC_MSG_ERROR(the native compiler is broken and won't link.)
fi
AC_MSG_RESULT(yes)
])

AC_DEFUN(CY_AC_PATH_TCLH, [
#
# Ok, lets find the tcl source trees so we can use the headers
# Warning: transition of version 9 to 10 will break this algorithm
# because 10 sorts before 9. We also look for just tcl. We have to
# be careful that we don't match stuff like tclX by accident.
# the alternative search directory is involked by --with-tclinclude
#

no_tcl=true
AC_MSG_CHECKING(for Tcl private headers. dir=${configdir})
AC_ARG_WITH(tclinclude, [  --with-tclinclude       directory where tcl private headers are], with_tclinclude=${withval})
AC_CACHE_VAL(ac_cv_c_tclh,[
# first check to see if --with-tclinclude was specified
if test x"${with_tclinclude}" != x ; then
  if test -f ${with_tclinclude}/tclInt.h ; then
    ac_cv_c_tclh=`(cd ${with_tclinclude}; pwd)`
  elif test -f ${with_tclinclude}/generic/tclInt.h ; then
    ac_cv_c_tclh=`(cd ${with_tclinclude}/generic; pwd)`
  else
    AC_MSG_ERROR([${with_tclinclude} directory doesn't contain private headers])
  fi
fi

# next check if it came with Tcl configuration file
if test x"${ac_cv_c_tclconfig}" = x ; then
  if test -f $ac_cv_c_tclconfig/../generic/tclInt.h ; then
    ac_cv_c_tclh=`(cd $ac_cv_c_tclconfig/..; pwd)`
  fi
fi

# next check in private source directory
#
# since ls returns lowest version numbers first, reverse its output
if test x"${ac_cv_c_tclh}" = x ; then
  for i in \
		${srcdir}/../tcl \
		`ls -dr ${srcdir}/../tcl[[7-9]]* 2>/dev/null` \
		${srcdir}/../../tcl \
		`ls -dr ${srcdir}/../../tcl[[7-9]]* 2>/dev/null` \
		${srcdir}/../../../tcl \
		`ls -dr ${srcdir}/../../../tcl[[7-9]]* 2>/dev/null ` ; do
    if test -f $i/generic/tclInt.h ; then
      ac_cv_c_tclh=`(cd $i/generic; pwd)`
      break
    fi
  done
fi
# finally check in a few common install locations
#
# since ls returns lowest version numbers first, reverse its output
if test x"${ac_cv_c_tclh}" = x ; then
  for i in \
		`ls -dr /usr/local/src/tcl[[7-9]]* 2>/dev/null` \
		`ls -dr /usr/local/lib/tcl[[7-9]]* 2>/dev/null` \
		/usr/local/src/tcl \
		/usr/local/lib/tcl \
		${prefix}/include ; do
    if test -f $i/generic/tclInt.h ; then
      ac_cv_c_tclh=`(cd $i/generic; pwd)`
      break
    fi
  done
fi
# see if one is installed
if test x"${ac_cv_c_tclh}" = x ; then
   AC_HEADER_CHECK(tclInt.h, ac_cv_c_tclh=installed, ac_cv_c_tclh="")
fi
])
if test x"${ac_cv_c_tclh}" = x ; then
  TCLHDIR="# no Tcl private headers found"
  AC_MSG_ERROR([Can't find Tcl private headers])
fi
if test x"${ac_cv_c_tclh}" != x ; then
  no_tcl=""
  if test x"${ac_cv_c_tclh}" = x"installed" ; then
    AC_MSG_RESULT([is installed])
    TCLHDIR=""
  else
    AC_MSG_RESULT([found in ${ac_cv_c_tclh}])
    # this hack is cause the TCLHDIR won't print if there is a "-I" in it.
    TCLHDIR="-I${ac_cv_c_tclh}"
  fi
fi

AC_SUBST(TCLHDIR)
])


AC_DEFUN(CY_AC_PATH_TCLCONFIG, [
#
# Ok, lets find the tcl configuration
# First, look for one uninstalled.  
# the alternative search directory is invoked by --with-tclconfig
#

if test x"${no_tcl}" = x ; then
  # we reset no_tcl in case something fails here
  no_tcl=true
  AC_ARG_WITH(tclconfig, [  --with-tclconfig           directory containing tcl configuration (tclConfig.sh)],
         with_tclconfig=${withval})
  AC_MSG_CHECKING([for Tcl configuration])
  AC_CACHE_VAL(ac_cv_c_tclconfig,[

  # First check to see if --with-tclconfig was specified.
  if test x"${with_tclconfig}" != x ; then
    if test -f "${with_tclconfig}/tclConfig.sh" ; then
      ac_cv_c_tclconfig=`(cd ${with_tclconfig}; pwd)`
    else
      AC_MSG_ERROR([${with_tclconfig} directory doesn't contain tclConfig.sh])
    fi
  fi

  # then check for a private Tcl installation
  if test x"${ac_cv_c_tclconfig}" = x ; then
    for i in \
		../tcl \
		`ls -dr ../tcl[[7-9]]* 2>/dev/null` \
		../../tcl \
		`ls -dr ../../tcl[[7-9]]* 2>/dev/null` \
		../../../tcl \
		`ls -dr ../../../tcl[[7-9]]* 2>/dev/null` ; do
      if test -f "$i/${configdir}/tclConfig.sh" ; then
        ac_cv_c_tclconfig=`(cd $i/${configdir}; pwd)`
	break
      fi
    done
  fi
  # check in a few common install locations
  if test x"${ac_cv_c_tclconfig}" = x ; then
    for i in `ls -d ${prefix}/lib /usr/local/lib 2>/dev/null` ; do
      if test -f "$i/tclConfig.sh" ; then
        ac_cv_c_tclconfig=`(cd $i; pwd)`
	break
      fi
    done
  fi
  # check in a few other private locations
  if test x"${ac_cv_c_tclconfig}" = x ; then
    for i in \
		${srcdir}/../tcl \
		`ls -dr ${srcdir}/../tcl[[7-9]]* 2>/dev/null` ; do
      if test -f "$i/${configdir}/tclConfig.sh" ; then
        ac_cv_c_tclconfig=`(cd $i/${configdir}; pwd)`
	break
      fi
    done
  fi
  ])
  if test x"${ac_cv_c_tclconfig}" = x ; then
    TCLCONFIG="# no Tcl configs found"
    AC_MSG_WARN(Can't find Tcl configuration definitions)
  else
    no_tcl=
    TCLCONFIG=${ac_cv_c_tclconfig}/tclConfig.sh
    AC_MSG_RESULT(found $TCLCONFIG)
  fi
fi
])

# Defined as a separate macro so we don't have to cache the values
# from PATH_TCLCONFIG (because this can also be cached).
AC_DEFUN(CY_AC_LOAD_TCLCONFIG, [
    . $TCLCONFIG

    AC_SUBST(TCL_VERSION)
    AC_SUBST(TCL_MAJOR_VERSION)
    AC_SUBST(TCL_MINOR_VERSION)
    AC_SUBST(TCL_CC)
    AC_SUBST(TCL_DEFS)

dnl not used, don't export to save symbols
dnl    AC_SUBST(TCL_LIB_FILE)

dnl don't export, not used outside of configure
dnl     AC_SUBST(TCL_LIBS)
dnl not used, don't export to save symbols
dnl    AC_SUBST(TCL_PREFIX)

dnl not used, don't export to save symbols
dnl    AC_SUBST(TCL_EXEC_PREFIX)

    AC_SUBST(TCL_SHLIB_CFLAGS)
    AC_SUBST(TCL_SHLIB_LD)
dnl don't export, not used outside of configure
    AC_SUBST(TCL_SHLIB_LD_LIBS)
    AC_SUBST(TCL_SHLIB_SUFFIX)
dnl not used, don't export to save symbols
    AC_SUBST(TCL_DL_LIBS)
    AC_SUBST(TCL_LD_FLAGS)
dnl don't export, not used outside of configure
    AC_SUBST(TCL_LD_SEARCH_FLAGS)
    AC_SUBST(TCL_COMPAT_OBJS)
    AC_SUBST(TCL_RANLIB)
    AC_SUBST(TCL_BUILD_LIB_SPEC)
    AC_SUBST(TCL_LIB_SPEC)
    AC_SUBST(TCL_LIB_VERSIONS_OK)

dnl not used, don't export to save symbols
dnl    AC_SUBST(TCL_SHARED_LIB_SUFFIX)

dnl not used, don't export to save symbols
dnl    AC_SUBST(TCL_UNSHARED_LIB_SUFFIX)
])

# Warning: Tk definitions are very similar to Tcl definitions but
# are not precisely the same.  There are a couple of differences,
# so don't do changes to Tcl thinking you can cut and paste it do 
# the Tk differences and later simply substitute "Tk" for "Tcl".
# Known differences:
#  - Acceptable Tcl major version #s is 7-9 while Tk is 4-9
#  - Searching for Tcl includes looking for tclInt.h, Tk looks for tk.h
#  - Computing major/minor versions is different because Tk depends on
#    headers to Tcl, Tk, and X.
#  - Symbols in tkConfig.sh are different than tclConfig.sh
#  - Acceptable for Tk to be missing but not Tcl.

AC_DEFUN(CY_AC_PATH_TKH, [
#
# Ok, lets find the tk source trees so we can use the headers
# If the directory (presumably symlink) named "tk" exists, use that one
# in preference to any others.  Same logic is used when choosing library
# and again with Tcl. The search order is the best place to look first, then in
# decreasing significance. The loop breaks if the trigger file is found.
# Note the gross little conversion here of srcdir by cd'ing to the found
# directory. This converts the path from a relative to an absolute, so
# recursive cache variables for the path will work right. We check all
# the possible paths in one loop rather than many seperate loops to speed
# things up.
# the alternative search directory is involked by --with-tkinclude
#
no_tk=true
AC_MSG_CHECKING(for Tk private headers)
AC_ARG_WITH(tkinclude, [  --with-tkinclude       directory where tk private headers are], with_tkinclude=${withval})
AC_CACHE_VAL(ac_cv_c_tkh,[
# first check to see if --with-tkinclude was specified
if test x"${with_tkinclude}" != x ; then
  if test -f ${with_tkinclude}/tk.h ; then
    ac_cv_c_tkh=`(cd ${with_tkinclude}; pwd)`
  elif test -f ${with_tkinclude}/generic/tk.h ; then
    ac_cv_c_tkh=`(cd ${with_tkinclude}/generic; pwd)`
  else
    AC_MSG_ERROR([${with_tkinclude} directory doesn't contain private headers])
  fi
fi

# next check if it came with Tk configuration file
if test x"${ac_cv_c_tkconfig}" = x ; then
  if test -f $ac_cv_c_tkconfig/../generic/tk.h ; then
    ac_cv_c_tkh=`(cd $ac_cv_c_tkconfig/..; pwd)`
  fi
fi

# next check in private source directory
#
# since ls returns lowest version numbers first, reverse its output
if test x"${ac_cv_c_tkh}" = x ; then
  for i in \
		${srcdir}/../tk \
		`ls -dr ${srcdir}/../tk[[4-9]]* 2>/dev/null` \
		${srcdir}/../../tk \
		`ls -dr ${srcdir}/../../tk[[4-9]]* 2>/dev/null` \
		${srcdir}/../../../tk \
		`ls -dr ${srcdir}/../../../tk[[4-9]]* 2>/dev/null ` ; do
    if test -f $i/generic/tk.h ; then
      ac_cv_c_tkh=`(cd $i/generic; pwd)`
      break
    fi
  done
fi
# finally check in a few common install locations
#
# since ls returns lowest version numbers first, reverse its output
if test x"${ac_cv_c_tkh}" = x ; then
  for i in \
		`ls -dr /usr/local/src/tk[[4-9]]* 2>/dev/null` \
		`ls -dr /usr/local/lib/tk[[4-9]]* 2>/dev/null` \
		/usr/local/src/tk \
		/usr/local/lib/tk \
		${prefix}/include ; do
    if test -f $i/generic/tk.h ; then
      ac_cv_c_tkh=`(cd $i/generic; pwd)`
      break
    fi
  done
fi
# see if one is installed
if test x"${ac_cv_c_tkh}" = x ; then
   AC_HEADER_CHECK(tk.h, ac_cv_c_tkh=installed, ac_cv_c_tkh="")
fi
])
if test x"${ac_cv_c_tkh}" != x ; then
  no_tk=""
  if test x"${ac_cv_c_tkh}" = x"installed" ; then
    AC_MSG_RESULT([is installed])
    TKHDIR=""
  else
    AC_MSG_RESULT([found in ${ac_cv_c_tkh}])
    # this hack is cause the TKHDIR won't print if there is a "-I" in it.
    TKHDIR="-I${ac_cv_c_tkh}"
  fi
else
  TKHDIR="# no Tk directory found"
  AC_MSG_WARN([Can't find Tk private headers])
  no_tk=true
fi

AC_SUBST(TKHDIR)
])


AC_DEFUN(CY_AC_PATH_TKCONFIG, [
#
# Ok, lets find the tk configuration
# First, look for one uninstalled.  
# the alternative search directory is invoked by --with-tkconfig
#

if test x"${no_tk}" = x ; then
  # we reset no_tk in case something fails here
  no_tk=true
  AC_ARG_WITH(tkconfig, [  --with-tkconfig           directory containing tk configuration (tkConfig.sh)],
         with_tkconfig=${withval})
  AC_MSG_CHECKING([for Tk configuration])
  AC_CACHE_VAL(ac_cv_c_tkconfig,[

  # First check to see if --with-tkconfig was specified.
  if test x"${with_tkconfig}" != x ; then
    if test -f "${with_tkconfig}/tkConfig.sh" ; then
      ac_cv_c_tkconfig=`(cd ${with_tkconfig}; pwd)`
    else
      AC_MSG_ERROR([${with_tkconfig} directory doesn't contain tkConfig.sh])
    fi
  fi

  # then check for a private Tk library
  if test x"${ac_cv_c_tkconfig}" = x ; then
    for i in \
		../tk \
		`ls -dr ../tk[[4-9]]* 2>/dev/null` \
		../../tk \
		`ls -dr ../../tk[[4-9]]* 2>/dev/null` \
		../../../tk \
		`ls -dr ../../../tk[[4-9]]* 2>/dev/null` ; do
      if test -f "$i/${configdir}/tkConfig.sh" ; then
        ac_cv_c_tkconfig=`(cd $i/${configdir}; pwd)`
	break
      fi
    done
  fi
  # check in a few common install locations
  if test x"${ac_cv_c_tkconfig}" = x ; then
    for i in `ls -d ${prefix}/lib /usr/local/lib 2>/dev/null` ; do
      if test -f "$i/tkConfig.sh" ; then
        ac_cv_c_tkconfig=`(cd $i; pwd)`
	break
      fi
    done
  fi
  # check in a few other private locations
  if test x"${ac_cv_c_tkconfig}" = x ; then
    for i in \
		${srcdir}/../tk \
		`ls -dr ${srcdir}/../tk[[4-9]]* 2>/dev/null` ; do
      if test -f "$i/${configdir}/tkConfig.sh" ; then
        ac_cv_c_tkconfig=`(cd $i/${configdir}; pwd)`
	break
      fi
    done
  fi
  ])
  if test x"${ac_cv_c_tkconfig}" = x ; then
    TKCONFIG="# no Tk configs found"
    AC_MSG_WARN(Can't find Tk configuration definitions)
  else
    no_tk=
    TKCONFIG=${ac_cv_c_tkconfig}/tkConfig.sh
    AC_MSG_RESULT(found $TKCONFIG)
  fi
fi

])

# Defined as a separate macro so we don't have to cache the values
# from PATH_TKCONFIG (because this can also be cached).
AC_DEFUN(CY_AC_LOAD_TKCONFIG, [
    if test -f "$TKCONFIG" ; then
      . $TKCONFIG
    fi

    AC_SUBST(TK_VERSION)
dnl not actually used, don't export to save symbols
dnl    AC_SUBST(TK_MAJOR_VERSION)
dnl    AC_SUBST(TK_MINOR_VERSION)
    AC_SUBST(TK_DEFS)

dnl not used, don't export to save symbols
    dnl AC_SUBST(TK_LIB_FILE)

dnl not used outside of configure
dnl    AC_SUBST(TK_LIBS)
dnl not used, don't export to save symbols
dnl    AC_SUBST(TK_PREFIX)

dnl not used, don't export to save symbols
dnl    AC_SUBST(TK_EXEC_PREFIX)

    AC_SUBST(TK_XINCLUDES)
    AC_SUBST(TK_XLIBSW)
    AC_SUBST(TK_BUILD_LIB_SPEC)
    AC_SUBST(TK_LIB_SPEC)
])

