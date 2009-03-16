
libgtkaditabview_la_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/gtkadiview \
	$(GTK_CFLAGS) \
	$(HILDON_CFLAGS) \
	$(COVERAGE_CFLAGS)

AM_CFLAGS = \
	-Wall \
	-g

noinst_LTLIBRARIES = libgtkaditabview.la

libgtkaditabview_la_SOURCES = \
	gtkaditabview.c

noinst_HEADERS = \
	gtkaditabview.h

libgtkaditabview_la_LDFLAGS = \
	$(GTK_LIBS) \
	$(HILDON_LIBS) \
	$(COVERAGE_LIBS)
