## GTK ADI Library
## Process this file with automake to produce Makefile.in
## Copyright (C) 2003 - 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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
	gtkadiwinchild.c \
	gtkadiwinview.c

noinst_HEADERS = \
	gtkadiwinchild.c \
	gtkadiwinview.h

libgtkadiwinview_la_LDFLAGS = \
	$(GTK_LIBS) \
	$(HILDON_LIBS)
