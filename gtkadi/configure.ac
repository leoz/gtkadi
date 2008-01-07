
AC_INIT(configure.ac)

GTK_ADI_MAJOR_VERSION=0
GTK_ADI_MINOR_VERSION=7
GTK_ADI_MICRO_VERSION=8
GTK_ADI_VERSION=$GTK_ADI_MAJOR_VERSION.$GTK_ADI_MINOR_VERSION.$GTK_ADI_MICRO_VERSION

AC_SUBST(GTK_ADI_MAJOR_VERSION)
AC_SUBST(GTK_ADI_MINOR_VERSION)
AC_SUBST(GTK_ADI_MICRO_VERSION)
AC_SUBST(GTK_ADI_VERSION)

AM_INIT_AUTOMAKE(gtkadi, $GTK_ADI_VERSION)
AM_CONFIG_HEADER(config.h)

AC_ISC_POSIX
dnl CFLAGS=""
AC_SUBST(CFLAGS)
AC_PROG_CC
AM_PROG_CC_STDC
AC_HEADER_STDC
AM_PROG_LIBTOOL

dnl Checks for libraries.

PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.0.0)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

dnl Checks for Maemo libraries.

AC_ARG_ENABLE(hildon, [ --enable-hildon=[yes|no] ], [hildon_support=$enableval ])

AC_ARG_ENABLE(newhildon, [ --enable-newhildon=[yes|no] ], [newhildon_support=$enableval ])

if test "$hildon_support" != "no"; then
	
    PKG_CHECK_MODULES(HILDON, [hildon-1],
      [
          use_hildon="yes"
          newhildon_support="yes"
          AC_DEFINE(MAEMO_CHANGES, 1,"Set to 1 if enable-newhildon is yes")
      ],
      [
          PKG_CHECK_MODULES(HILDON, [hildon-libs],
            [
                newhildon_support="yes"
                hildon_support="yes"
                use_hildon="yes"
            ],
            [
                use_hildon="no"
                newhildon_support="no"
                hildon_support="no"
            ]
          )
      ]
    )

    if test "$hildon_support" = "yes"; then
        AC_SUBST(HILDON_LIBS)
        AC_SUBST(HILDON_CFLAGS)
	if test "$newhildon_support" = "yes"; then
	    AC_DEFINE(NEWHILDON_SUPPORT, [], [Support the New Hildon extensions])	
	fi

        AC_DEFINE(HILDON_SUPPORT, [], [Support the Hildon extensions])
    fi
fi

AM_CONDITIONAL(HILDON_SUPPORT, [test "${hildon_support}" = "yes"])
AM_CONDITIONAL(NEWHILDON_SUPPORT, [test "${newhildon_support}" = "yes"])


AC_ARG_ENABLE(widgets, [  --disable-widgets         Do not use widgets
  --enable-widgets(=val)    Use widgets],
 [no_widgets=$enableval ])

if test "$no_widgets" = "yes"; then
    AC_DEFINE(NO_WIDGETS, [], [Disable additional widgets Menu,Toolbar])
fi

AM_CONDITIONAL(NO_WIDGETS, [test "${no_widgets}" = "yes"])

PKG_CHECK_MODULES(OSSO, [libosso],
	[
	 	AC_DEFINE(OSSO_SUPPORT, [], [Support the libosso library])
		osso_support="yes"
	],[echo 'No libosso support.'])

AM_CONDITIONAL(OSSO_SUPPORT, [test "${osso_support}" = "yes"])

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
gtkadiconview/Makefile
gtkadiwinview/Makefile
src/Makefile
])
