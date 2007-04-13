/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is GtkAdi library.
 *
 * The Initial Developer of the Original Code is
 * Leonid Zolotarev <leonid.zolotarev@gmail.com>.
 * Portions created by the Initial Developer are Copyright (C) 2003-2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s): Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

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

/* Try your own child window.
GtkWidget*
_create_window (GtkAdi *adi)
{
	GtkWidget* window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	return window;
}
*/

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
