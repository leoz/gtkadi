/* GTK ADI Test
 * window.c
 * Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * $Id$
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "widgets.h"
#include "window.h"

/***************************************************************************/

GtkWidget* create_main_window (void)
{
	GtkWidget *main_window;
	GtkWidget *main_vbox;
	GtkWidget *main_menubar;
	GtkWidget *main_toolbar;
	GtkWidget *main_adi;
	static const gchar* style = "style \"scrolled\" {GtkScrolledWindow::scrollbar-spacing = 0} class \"GtkScrolledWindow\" style \"scrolled\"";
	gtk_rc_parse_string (style);

	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	set_main_window_title (main_window);

	main_vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (main_vbox);
	gtk_container_add (GTK_CONTAINER (main_window), main_vbox);

	main_menubar = create_menubar ();
	gtk_widget_show (main_menubar);
	gtk_box_pack_start (GTK_BOX (main_vbox), main_menubar, FALSE, FALSE, 0);
	GTK_WIDGET_UNSET_FLAGS (main_menubar, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS (main_menubar, GTK_CAN_DEFAULT);

	main_toolbar = create_toolbar ();
	gtk_widget_show (main_toolbar);
	gtk_box_pack_start (GTK_BOX (main_vbox), main_toolbar, FALSE, FALSE, 0);
	GTK_WIDGET_UNSET_FLAGS (main_toolbar, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS (main_toolbar, GTK_CAN_DEFAULT);

	main_adi = create_adi ();
	gtk_widget_show (main_adi);
	gtk_box_pack_start (GTK_BOX (main_vbox), main_adi, TRUE, TRUE, 0);
	gtk_widget_set_size_request (main_adi, 640, 480);
	GTK_WIDGET_UNSET_FLAGS (main_adi, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS (main_adi, GTK_CAN_DEFAULT);

	return main_window;
}

/***************************************************************************/
