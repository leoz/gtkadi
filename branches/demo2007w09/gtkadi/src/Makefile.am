
libgtkadi_la_CPPFLAGS = \
	-I$(top_srcdir)/icons \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/gtkadiview \
	-I$(top_srcdir)/gtkadiboxview \
	-I$(top_srcdir)/gtkaditabview \
	-I$(top_srcdir)/gtkadiconview \
	-I$(top_srcdir)/gtkadiwinview \
	$(GTK_CFLAGS) \
	$(HILDON_CFLAGS)

AM_CFLAGS = \
	-DGTK_ADI_MAJOR_VERSION=$(GTK_ADI_MAJOR_VERSION) \
	-DGTK_ADI_MINOR_VERSION=$(GTK_ADI_MINOR_VERSION) \
	-DGTK_ADI_MICRO_VERSION=$(GTK_ADI_MICRO_VERSION) \
	-Wall \
	-g

lib_LTLIBRARIES = libgtkadi.la

if !NO_WIDGETS
    ADD_TOOLKIT_C = \
	gtkadicmd.c \
	gtkaditoolbar.c \
	gtkadimenu.c
    ADD_TOOLKIT_H = \
	$(top_srcdir)/include/gtkaditoolbar.h \
	$(top_srcdir)/include/gtkadimenu.h
endif

libgtkadi_la_SOURCES = \
	$(ADD_TOOLKIT_C) \
	gtkadi.c \
	gtkadistock.c \
	gtkadiflex.c \
	gtkadiutils.c

libgtkadi_includedir = $(includedir)/gtkadi

libgtkadi_include_HEADERS = \
	$(ADD_TOOLKIT_H) \
	$(top_srcdir)/include/gtkaditype.h \
	$(top_srcdir)/include/gtkadi.h \
	$(top_srcdir)/include/gtkadistock.h \
	$(top_srcdir)/include/gtkadiutils.h
	
libgtkadi_la_LIBADD = \
	$(top_srcdir)/gtkadiview/libgtkadiview.la \
	$(top_srcdir)/gtkadiboxview/libgtkadiboxview.la \
	$(top_srcdir)/gtkaditabview/libgtkaditabview.la \
	$(top_srcdir)/gtkadiconview/libgtkadiconview.la \
	$(top_srcdir)/gtkadiwinview/libgtkadiwinview.la

libgtkadi_la_LDFLAGS = \
	$(GTK_LIBS) \
	$(HILDON_LIBS)
