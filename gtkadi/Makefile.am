SUBDIRS = \
	icons \
	gtkadiview \
	gtkadiboxview \
	gtkaditabview \
	gtkadiconview \
	gtkadiwinview \
	src
if TESTS_ENABLED
SUBDIRS += tests
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gtkadi.pc

EXTRA_DIST = \
	gtkadi.pc.in \
	autogen.sh
