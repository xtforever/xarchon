## Process this file with automake to produce Makefile.in

SUBDIRS = @GTK_SUBDIR@ @QT_SUBDIR@

INCLUDES = @X_CFLAGS@ @ESD_CFLAGS@

SOUND_DRIVER_C = sample-driver-@SOUND_DRIVER@.c

COMMON_sources = \

bin_PROGRAMS = xarchon

# noinst_PROGRAMS = genetics

xarchon_SOURCES = $(COMMON_sources) main.c main.h

xarchon_DEPENDENCIES = @TOOLKIT_LIBS@

# genetics_SOURCES = $(COMMON_sources) genetics_main.c main.h

xarchon_LDADD = @X_LIBS@ @TOOLKIT_LIBS@ @TOOLKIT_LDADDS@ @ESD_LIBS@

# genetics_LDADD = @X_LIBS@ @ESD_LIBS@

man_MANS = xarchon.6

EXTRA_DIST = box xarchon.6

CLEANFILES = genetics
