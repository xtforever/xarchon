#ifndef __MY_CONFIG_H
#define __MY_CONFIG_H

/* Define to empty if the keyword does not work.  */
#define const

/* Define if you don't have vprintf but do have _doprnt.  */
#undef HAVE_DOPRNT

/* Define if you have the vprintf function.  */
#define HAVE_VPRINTF

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE int

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
#define TIME_WITH_SYS_TIME

/* Define if the X Window System is missing or not being used.  */
#undef X_DISPLAY_MISSING

#define DATADIR "."
#undef AUTOPILOT
#undef NETWORKING
#undef HAVE_GTK
#undef HAVE_QT
#undef HAVE_XAW

/* Define if you have the gettimeofday function.  */
#define HAVE_GETTIMEOFDAY

/* Define if you have the setitimer function.  */
#define HAVE_SETITIMER

/* Define if you have the strdup function.  */
#define HAVE_STRDUP

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H

/* Define if you have the <linux/joystick.h> header file.  */
#define HAVE_LINUX_JOYSTICK_H

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H

/* Define if you have the pthread library (-lpthread).  */
#define HAVE_LIBPTHREAD

/* Name of package */
#define PACKAGE "xarchon"

/* Version number of package */
#define VERSION "0.6.1"

#endif
