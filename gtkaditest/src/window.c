/* GTK ADI Test
 * window.c
 * Copyright (C) 2003 - 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * $Id$
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtkadi.h>

#include "widgets.h"
#include "window.h"

#ifdef HILDON_SUPPORT
#include <hildon-widgets/hildon-app.h>
#include <hildon-widgets/hildon-appview.h>
#endif /* HILDON_SUPPORT */

/***************************************************************************/

static void destroy_main_window (GtkWidget *widget, gpointer data)
{
    if (gtk_adi_can_exit (GTK_ADI(data))) {
		gtk_main_quit ();
	}
}

/***************************************************************************/

GtkWidget* create_main_window (void)
{
	#ifdef HILDON_SUPPORT
	GtkWidget *app = NULL;
	#endif /* HILDON_SUPPORT */
	GtkWidget *main_window;
	GtkWidget *main_vbox;
	GtkWidget *main_menubar;
	GtkWidget *main_toolbar;
	GtkWidget *main_adi;
	static const gchar* style = "style \"scrolled\" {GtkScrolledWindow::scrollbar-spacing = 0} class \"GtkScrolledWindow\" style \"scrolled\"";
	gtk_rc_parse_string (style);

	#ifdef HILDON_SUPPORT
	app = hildon_app_new ();
	main_window = hildon_appview_new (NULL);
	hildon_app_set_appview (HILDON_APP(app), HILDON_APPVIEW(main_window));
	set_main_window_title (app);
	gtk_widget_show (app);
	#else
	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	set_main_window_title (main_window);
	gtk_widget_show (main_window);
	#endif /* HILDON_SUPPORT */

	main_vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (main_vbox);
	gtk_container_add (GTK_CONTAINER (main_window), main_vbox);

	main_menubar = create_menubar (main_window);
	gtk_widget_show_all (main_menubar);
	#ifndef HILDON_SUPPORT
	gtk_box_pack_start (GTK_BOX (main_vbox), main_menubar, FALSE, FALSE, 0);
	#endif /* HILDON_SUPPORT */
	GTK_WIDGET_UNSET_FLAGS (main_menubar, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS (main_menubar, GTK_CAN_DEFAULT);

	main_toolbar = create_toolbar ();
	gtk_widget_show (main_toolbar);
	
	#ifdef HILDON_SUPPORT
	gtk_widget_show (HILDON_APPVIEW(main_window)->vbox);
	gtk_box_pack_start (GTK_BOX (HILDON_APPVIEW(main_window)->vbox), main_toolbar, TRUE, TRUE, 0);
	#else
	gtk_box_pack_start (GTK_BOX (main_vbox), main_toolbar, FALSE, FALSE, 0);
	#endif /* HILDON_SUPPORT */

	GTK_WIDGET_UNSET_FLAGS (main_toolbar, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS (main_toolbar, GTK_CAN_DEFAULT);

	main_adi = create_adi ();
	gtk_adi_change_view (GTK_ADI (main_adi), GTK_ADI_VIEW_WIN);
	gtk_widget_show (main_adi);
	gtk_box_pack_start (GTK_BOX (main_vbox), main_adi, TRUE, TRUE, 0);
	gtk_widget_set_size_request (main_adi, 640, 480);
	GTK_WIDGET_UNSET_FLAGS (main_adi, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS (main_adi, GTK_CAN_DEFAULT);

	g_signal_connect (G_OBJECT (main_window), "destroy",
	                  G_CALLBACK (destroy_main_window), main_adi);

	return main_window;
}

/***************************************************************************/
