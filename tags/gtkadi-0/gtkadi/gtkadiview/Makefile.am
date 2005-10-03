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

libgtkadiview_la_CPPFLAGS = \
	-I$(top_srcdir)/include \
	$(GTK_CFLAGS)

AM_CFLAGS = \
	-Wall \
	-g

noinst_LTLIBRARIES = libgtkadiview.la

libgtkadiview_la_SOURCES = \
	gtkadititle.c \
	gtkadicolor.c \
	gtkadiview.c

noinst_HEADERS = \
	gtkadititle.h \
	gtkadicolor.h \
	gtkadiview.h

libgtkadiview_la_LDFLAGS = \
	$(GTK_LIBS)
