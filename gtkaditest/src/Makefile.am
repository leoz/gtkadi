
INCLUDES = \
	-I../include \
	$(GTK_CFLAGS) \
	$(GTKADI_CFLAGS) \
	$(HILDON_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gtkaditest

noinst_HEADERS = \
	../include/child.h   \
	../include/menu.h    \
	../include/toolbar.h \
	../include/widgets.h \
	../include/window.h

gtkaditest_SOURCES = \
	child.c   \
	main.c    \
	menu.c    \
	toolbar.c \
	widgets.c \
	window.c

gtkaditest_LDADD = \
	$(GTK_LIBS) \
	$(GTKADI_LIBS) \
	$(HILDON_LIBS)
