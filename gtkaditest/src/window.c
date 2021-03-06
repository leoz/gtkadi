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

/*
#define NO_PARENT
*/
/***************************************************************************/

static GtkWidget* _create_main_adi (void);

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

	main_adi = _create_main_adi ();
	
	#ifdef NO_PARENT
	return NULL;
	#endif /* NO_PARENT */

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

	gtk_widget_show (main_adi);
	gtk_box_pack_start (GTK_BOX (main_vbox), main_adi, FALSE, FALSE, 0);
	gtk_widget_set_size_request (main_adi, 0, 0);
	GTK_WIDGET_UNSET_FLAGS (main_adi, GTK_CAN_FOCUS);
	GTK_WIDGET_UNSET_FLAGS (main_adi, GTK_CAN_DEFAULT);

	g_signal_connect (G_OBJECT (main_window), "destroy",
	                  G_CALLBACK (destroy_main_window), main_adi);

	return main_window;
}

/***************************************************************************/

static GtkWidget*
_create_main_adi (void)
{
	GtkWidget *main_adi;
	main_adi = create_adi ();
	gtk_adi_change_view (GTK_ADI (main_adi), GTK_ADI_VIEW_WIN);
	#ifdef NO_PARENT
	gtk_adi_user_add_child (GTK_ADI (main_adi));
	#endif /* NO_PARENT */
	return main_adi;
}

/***************************************************************************/
