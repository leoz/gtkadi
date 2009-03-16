
libgtkadiboxview_la_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/gtkadiview \
	$(GTK_CFLAGS) \
	$(COVERAGE_CFLAGS)

AM_CFLAGS = \
	-Wall \
	-g

noinst_LTLIBRARIES = libgtkadiboxview.la

libgtkadiboxview_la_SOURCES = \
	gtkadiboxtitle.c \
	gtkadiboxview.c \
	gtkadichild.c

noinst_HEADERS = \
	gtkadiboxtitle.h \
	gtkadiboxview.h \
	gtkadichild.h

libgtkadiboxview_la_LDFLAGS = \
	$(GTK_LIBS) \
	$(COVERAGE_LIBS)
