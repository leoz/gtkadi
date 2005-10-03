/* GTK ADI Test
 * child.c
 * Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * $Id$
 */

#include <gtkadistock.h>
#include "child.h"

gint _count = 0;

static void
_create_tags (GtkTextBuffer *buffer)
{
	gtk_text_buffer_create_tag (buffer, "big", 
		                        "size", 20 * PANGO_SCALE, NULL);
	gtk_text_buffer_create_tag (buffer, "navy_foreground",
		                        "foreground", "navy", NULL);  
}

static void
_insert_text (GtkTextBuffer *buffer)
{
	gchar* text;
	GtkTextIter iter;
	
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);

	gtk_text_buffer_insert (buffer, &iter, "This is a test example number\n\n", -1);

	text = g_strdup_printf ( "   %d", _count );
	_count++;

	gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
		                                      text, -1,
											  "big", NULL);
	g_free ( text );

	gtk_text_buffer_insert_with_tags_by_name (buffer, &iter, 
		                                      "\n\nGTK ADI is used here.\n\n", -1,
											  "navy_foreground", NULL);
}

GtkWidget*
_create_child (void)
{
	GtkWidget *main_scrolledwindow;
	GtkWidget *main_textview;
	GtkTextBuffer *buffer;

	main_scrolledwindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (main_scrolledwindow), GTK_SHADOW_IN);

	main_textview = gtk_text_view_new ();
	gtk_container_add (GTK_CONTAINER (main_scrolledwindow), main_textview);

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (main_textview));
	_create_tags (buffer);
	_insert_text (buffer);

	return main_scrolledwindow;
}

GdkPixbuf*
_create_icon (GtkWidget* widget)
{
	GdkPixbuf *icon = NULL;
	/* Default window icon could be used also. */
	/*
	icon = gtk_widget_render_icon (widget,GTK_ADI_STOCK_WINDOW, GTK_ICON_SIZE_MENU,NULL);
	*/
	icon = gtk_widget_render_icon (widget,"gtk-file", GTK_ICON_SIZE_MENU,NULL);
	return icon;
}


gchar*
_create_title (void)
{
	gchar* title = NULL;
	title  = g_strdup_printf ( "Title: %d.", _count );
	return title;
}
