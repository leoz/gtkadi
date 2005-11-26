## GTK ADI Library
## Process this file with automake to produce Makefile.in
## Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
##
## This library is free software; you can redistribute it and/or
## modify it under the terms of the GNU Lesser General Public
## License as published by the Free Software Foundation; either
## version 2 of the License, or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public
## License along with this library; if not, write to the
## Free Software Foundation, Inc., 59 Temple Place - Suite 330,
## Boston, MA 02111-1307, USA.
##
## $Id$
##

libgtkadi_la_CPPFLAGS = \
	-I$(top_srcdir)/icons \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/gtkadiview \
	-I$(top_srcdir)/gtkadiboxview \
	-I$(top_srcdir)/gtkaditabview \
	$(GTK_CFLAGS) \
	$(HILDON_CFLAGS)

AM_CFLAGS = \
	-DGTK_ADI_MAJOR_VERSION=$(GTK_ADI_MAJOR_VERSION) \
	-DGTK_ADI_MINOR_VERSION=$(GTK_ADI_MINOR_VERSION) \
	-DGTK_ADI_MICRO_VERSION=$(GTK_ADI_MICRO_VERSION) \
	-Wall \
	-g

lib_LTLIBRARIES = libgtkadi.la

if WIDGETS_SUPPORT
    ADD_TOOLKITC = gtkadicmd.c gtkaditoolbar.c gtkadimenu.c
endif

libgtkadi_la_SOURCES = \
	gtkadi.c \
	$(ADD_TOOLKITC) \
	gtkadistock.c \
	gtkadiutils.c

libgtkadi_includedir = $(includedir)/gtkadi

libgtkadi_include_HEADERS = \
	$(top_srcdir)/include/gtkaditype.h \
	$(top_srcdir)/include/gtkadi.h \
	$(top_srcdir)/include/gtkadistock.h \
	$(top_srcdir)/include/gtkadiutils.h
	
libgtkadi_la_LIBADD = \
	$(top_srcdir)/gtkadiview/libgtkadiview.la \
	$(top_srcdir)/gtkadiboxview/libgtkadiboxview.la \
	$(top_srcdir)/gtkaditabview/libgtkaditabview.la

libgtkadi_la_LDFLAGS = \
	$(GTK_LIBS) \
	$(HILDON_LIBS)
