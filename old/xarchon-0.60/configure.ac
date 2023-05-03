dnl Process this file with autoconf to produce a configure script.

AC_INIT(src/actors.c)
AM_INIT_AUTOMAKE([xarchon], [0.60], [https://github.com/xtforever/xarchon/issues],[xarchon-xaw])
AM_CONFIG_HEADER(config.h)
AC_USE_SYSTEM_EXTENSIONS
dnl AM_INIT_AUTOMAKE([foreign dist-gz])

dnl ------------------
dnl Check for programs
dnl ------------------

AC_PROG_CC
if test -n "$GCC"; then
   CFLAGS="$CFLAGS -Wall"
fi
AC_PROG_CXX
if test -n "$GCC"; then
   CXXFLAGS="$CXXFLAGS -Wall"
fi
AC_PROG_RANLIB
AC_PROG_LN_S
AC_PROG_INSTALL

dnl ---------------------
dnl Check for X libraries
dnl ---------------------

AC_PATH_XTRA
FC_CHECK_X_LIB(X11, XOpenDisplay, , 
   AC_MSG_ERROR(Need X11; perhaps try/adjust --x-libraries))

dnl ---------------------
dnl Check for Xpm library
dnl ---------------------

FC_XPM_PATHS
if test "$xpm_incdir" != "no"; then
    X_CFLAGS="$X_CFLAGS -I$xpm_incdir"
fi
if test "$xpm_libdir" != "no"; then
    X_LIBS="$X_LIBS -L$xpm_libdir"
dnl Try using R values set in AC_PATH_XTRA:
    if test "$ac_R_nospace" = "yes"; then
        X_LIBS="$X_LIBS -R$xpm_libdir"
    elif test "$ac_R_space" = "yes"; then
        X_LIBS="$X_LIBS -R $xpm_libdir"
    fi
fi
fc_save_X_LIBS="$X_LIBS"
X_LIBS="$X_LIBS $X_PRE_LIBS"
FC_CHECK_X_LIB(Xpm, XpmReadFileToPixmap, , 
    AC_MSG_ERROR(Need Xpm library; perhaps try/adjust --with-xpm-lib))
X_LIBS="$X_LIBS -lXpm"

dnl ---------------------------------
dnl Check for user interface toolkits
dnl ---------------------------------

TOOLKIT_LIBS=""
TOOLKIT_LDADDS=""
fc_save_X_LIBS="$X_LIBS"
X_LIBS="$X_LIBS $X_PRE_LIBS"
FC_CHECK_X_LIB(Xaw,XawListChange , ,
	AC_MSG_ERROR(Need Xaw library; perhaps try/adjust --with-xaw-lib))
X_LIBS="$X_LIBS -lXaw"


dnl --------------------------
dnl Check for pthreads library
dnl --------------------------

have_pthreads=yes
AC_CHECK_HEADER(pthread.h, , have_pthreads=no)
AC_CHECK_LIB(pthread, pthread_create, , have_pthreads=no)

dnl -------------------------
dnl Check for sound libraries
dnl -------------------------

dnl ----------------------
dnl Check for header files
dnl ----------------------

AC_HEADER_STDC
AC_CHECK_HEADERS(limits.h sys/time.h unistd.h, ,
   AC_MSG_ERROR(Your system is missing some important stuff))

dnl ------------------------------------------------------------
dnl Check for typedefs, structures, and compiler characteristics
dnl ------------------------------------------------------------

AC_C_CONST
AC_HEADER_TIME

dnl ---------------------------
dnl Check for library functions
dnl ---------------------------

AC_FUNC_MEMCMP
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS(gettimeofday setitimer strdup , ,
   AC_MSG_ERROR(Your system is missing some important stuff))

dnl -------------------
dnl Check for nanosleep
dnl -------------------

AC_CHECK_FUNC(nanosleep)
if test $ac_cv_func_gethostbyname = no; then
   AC_CHECK_LIB(posix4, nanosleep, LIBS="-lposix4 $LIBS",
      AC_MSG_ERROR(Your system is missing some important stuff))
fi

dnl ------------------
dnl Networking support
dnl ------------------

want_networking=yes
AC_ARG_ENABLE(network, [  --disable-network       exclude networking support ],
   if test "x$enableval" = xno; then want_networking=no; fi ,)
AC_MSG_CHECKING(wheather to include networking support)
if test "x$want_networking" = xyes -a "x$have_pthreads" = xyes; then
   AC_DEFINE(NETWORKING)
   AC_MSG_RESULT(yes)
else
   AC_MSG_RESULT(no)
fi

dnl ----------------------
dnl Check for sound target
dnl ----------------------

dnl ----------------
dnl Joystick support
dnl ----------------

AC_CHECK_HEADERS(linux/joystick.h, ,)
AC_ARG_ENABLE(joystick, [  --disable-joystick      exclude joystick support ],
   if test "x$enableval" = xno; then unset HAVE_LINUX_JOYSTICK_H; fi ,)

dnl --------------
dnl Autopilot mode
dnl --------------

AC_ARG_ENABLE(autopilot, [  --enable-autopilot      a developerment option;  you *dont* wanna try this ],
   [ AC_DEFINE(AUTOPILOT) AC_MSG_RESULT(Autopilot mode selected) ] )

dnl -----------------------
dnl Get data directory path
dnl -----------------------

FC_EXPAND_DIR(DATADIR, "$datadir/xarchon")
AC_DEFINE_UNQUOTED(DATADIR, "$DATADIR")

dnl -------------------
dnl Create output files
dnl -------------------

AC_OUTPUT(
Makefile
src/Makefile
src/xaw/Makefile
data/Makefile
stamp.h)
