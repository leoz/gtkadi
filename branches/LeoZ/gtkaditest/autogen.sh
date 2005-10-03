#!/bin/sh

set -x
glib-gettextize --copy --force
libtoolize --automake
intltoolize --copy --force --automake
aclocal-1.7
autoconf
autoheader
automake-1.7 --add-missing --foreign
