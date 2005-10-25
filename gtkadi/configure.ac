dnl GTK ADI Library
dnl Process this file with automake to produce Makefile.in
dnl Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Lesser General Public
dnl License as published by the Free Software Foundation; either
dnl version 2 of the License, or (at your option) any later version.
dnl
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl Lesser General Public License for more details.
dnl
dnl You should have received a copy of the GNU Lesser General Public
dnl License along with this library; if not, write to the
dnl Free Software Foundation, Inc., 59 Temple Place - Suite 330,
dnl Boston, MA 02111-1307, USA.
dnl
dnl $Id$
dnl

AC_INIT(configure.ac)

GTK_ADI_MAJOR_VERSION=0
GTK_ADI_MINOR_VERSION=0
GTK_ADI_MICRO_VERSION=21
GTK_ADI_VERSION=$GTK_ADI_MAJOR_VERSION.$GTK_ADI_MINOR_VERSION.$GTK_ADI_MICRO_VERSION

AC_SUBST(GTK_ADI_MAJOR_VERSION)
AC_SUBST(GTK_ADI_MINOR_VERSION)
AC_SUBST(GTK_ADI_MICRO_VERSION)
AC_SUBST(GTK_ADI_VERSION)

AM_INIT_AUTOMAKE(gtkadi, $GTK_ADI_VERSION)
AM_CONFIG_HEADER(config.h)

AC_ISC_POSIX
CFLAGS=""
AC_SUBST(CFLAGS)
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC
AM_PROG_LIBTOOL

dnl Checks for libraries.

PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.0.0)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

dnl get the pixbuf source creation script
dnl This is installed from GTK+ 2.0's gdk-pixbuf
AC_PATH_PROG(GDK_PIXBUF_CSOURCE, gdk-pixbuf-csource)
test -z "$GDK_PIXBUF_CSOURCE" && AC_MSG_ERROR([
*** You need the gdk-pixbuf-csource tool which is installed
*** from GTK+ 2.0's gdk-pixbuf.
***
*** Either the location where you installed your GTK+ 2.0 is
*** not in your PATH or something is screwed up with your
*** GTK+ 2.0 installation
])

dnl Localization stuff.

GETTEXT_PACKAGE=gtkadi
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Gettext package.])

dnl Languages which your application supports

ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

AC_OUTPUT([
gtkadi.pc
Makefile
icons/Makefile
gtkadiview/Makefile
gtkadiboxview/Makefile
gtkaditabview/Makefile
src/Makefile
])