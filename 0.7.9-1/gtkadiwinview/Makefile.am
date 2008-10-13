
libgtkadiwinview_la_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/gtkadiconview \
	-I$(top_srcdir)/gtkadiview \
	$(GTK_CFLAGS) \
	$(HILDON_CFLAGS)

AM_CFLAGS = \
	-Wall \
	-g

noinst_LTLIBRARIES = libgtkadiwinview.la

libgtkadiwinview_la_SOURCES = \
	gtkadiwinview.c

noinst_HEADERS = \
	gtkadiwinview.h

libgtkadiwinview_la_LDFLAGS = \
	$(GTK_LIBS) \
	$(HILDON_LIBS)
