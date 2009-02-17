
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
