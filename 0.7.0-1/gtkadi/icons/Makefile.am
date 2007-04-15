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

stockimages = \
	stock_adi_close_16.png				\
	stock_adi_close_24.png				\
	stock_adi_close_all_16.png			\
	stock_adi_close_all_24.png			\
	stock_adi_close_window_10.png		\
	stock_adi_fix_16.png				\
	stock_adi_fix_24.png				\
	stock_adi_new_16.png				\
	stock_adi_new_24.png				\
	stock_adi_new_horizontally_16.png	\
	stock_adi_new_horizontally_24.png	\
	stock_adi_new_vertically_16.png		\
	stock_adi_new_vertically_24.png		\
	stock_adi_next_16.png				\
	stock_adi_next_24.png				\
	stock_adi_previous_16.png			\
	stock_adi_previous_24.png			\
	stock_adi_tile_horizontally_16.png	\
	stock_adi_tile_horizontally_24.png	\
	stock_adi_tile_vertically_16.png	\
	stock_adi_tile_vertically_24.png	\
	stock_adi_windows_16.png			\
	stock_adi_windows_24.png			\
	stock_adi_window_14.png

dist_noinst_DATA = $(stockimages)

noinst_HEADERS = gtkadiicons.h
BUILT_SOURCES = gtkadiicons.h

CLEANFILES = $(BUILT_SOURCES)
DISTCLEANFILES = $(BUILT_SOURCES)

# use --extern here and include gtkadiicons.h within an anonymous namespace
gdk_pixbuf_csource_command = $(GDK_PIXBUF_CSOURCE) --extern --raw

gtkadiicons.h: $(stockimages)
	@build_list='--build-list'; \
	list='$(stockimages)'; for file in $$list; do \
	  name=`echo "$$file" | sed 's|^.*/||;s|\..*$$||;s|-|_|g'`; \
	  dir=; test -f "$$file" || dir='$(srcdir)/'; \
	  build_list="$$build_list $$name $$dir$$file"; \
	done; \
	echo " $(gdk_pixbuf_csource_command) $$build_list >$@"; \
	$(gdk_pixbuf_csource_command) $$build_list >$@
