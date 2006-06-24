dnl GTK ADI Library Test
dnl
dnl Copyright (C) 2003 - 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
dnl
dnl Licensed under the terms of the BSD license, see file COPYING
dnl for details.
dnl
dnl $Id$
dnl

AC_INIT(configure.ac)
AM_INIT_AUTOMAKE(gtkaditest, 0.1.2)
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

PKG_CHECK_MODULES(GTKADI, gtkadi)
AC_SUBST(GTKADI_CFLAGS)
AC_SUBST(GTKADI_LIBS)

dnl Checks for Maemo libraries.

PKG_CHECK_MODULES(HILDON, [hildon-libs],
	[
	 	AC_DEFINE(HILDON_SUPPORT, [], [Support the Hildon extensions])
		hildon_support="yes"
	],[echo 'No Hildon support.'])

AM_CONDITIONAL(HILDON_SUPPORT, [test "${hildon_support}" = "yes"])

AC_OUTPUT([
Makefile
src/Makefile
])
