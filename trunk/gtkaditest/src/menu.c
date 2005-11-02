/* GTK ADI Test
 * menu.c
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

#define GETTEXT_PACKAGE "gtk20"
#include <glib/gi18n-lib.h>
#include <gtk/gtk.h>

#include <gtkadi.h>
#include <gtkadimenu.h>

#include "toolbar.h"
#include "widgets.h"

#ifdef HILDON_SUPPORT
#include <hildon-widgets/hildon-appview.h>
#define GTK_ADI_TEST_NAME "GTK ADI Test - Maemo"
#else
#define GTK_ADI_TEST_NAME "GTK ADI Test"
#endif /* HILDON_SUPPORT */

extern GtkWidget *main_window;

static void _activate_email (GtkAboutDialog *about,
							 const gchar    *link,
							 gpointer        data)
{
	g_print ("send mail to %s\n", link);
}

static void _activate_url (GtkAboutDialog *about,
						   const gchar    *link,
						   gpointer        data)
{
	g_print ("show url %s\n", link);
}

void _about_activate (GtkWidget *window, gpointer  user_data)
{
	gchar* vers = get_gtk_adi_version_string ();

	gtk_about_dialog_set_email_hook (_activate_email, NULL, NULL);
	gtk_about_dialog_set_url_hook (_activate_url, NULL, NULL);
	gtk_show_about_dialog (GTK_WINDOW (main_window),
		"name", GTK_ADI_TEST_NAME,
		"version", vers,
		"copyright", "(C) 2003-2005 Leonid Zolotarev",
		"website", "http://gtkadi.sourceforge.net/",
		"comments", "This program is demonstrating GTK ADI functions.",
		NULL);

	g_free (vers);
}

static GtkWidget *item_gtk = NULL;
static GtkWidget *item_own = NULL;
static GtkWidget *item_native = NULL;

void _menu_color_changed (GtkAdi *adi, gpointer user_data)
{
	GtkAdiColorType color = GTK_ADI_COLOR_GTK;
	if (item_own == GTK_WIDGET(user_data)) {
		color = GTK_ADI_COLOR_OWN;
	}
	else if (item_native == GTK_WIDGET(user_data)) {
		color = GTK_ADI_COLOR_NATIVE;
	}
	gtk_adi_change_color (adi, color);
	_toolbar_color_set (color);
}

void _menu_color_set (GtkAdiColorType color)
{
	switch (color) {
	case GTK_ADI_COLOR_OWN:
		GTK_CHECK_MENU_ITEM (item_gtk   )->active = 0;
		GTK_CHECK_MENU_ITEM (item_own   )->active = 1;
		GTK_CHECK_MENU_ITEM (item_native)->active = 0;
		break;
	case GTK_ADI_COLOR_NATIVE:
		GTK_CHECK_MENU_ITEM (item_gtk   )->active = 0;
		GTK_CHECK_MENU_ITEM (item_own   )->active = 0;
		GTK_CHECK_MENU_ITEM (item_native)->active = 1;
		break;
	case GTK_ADI_COLOR_GTK:
	default:
		GTK_CHECK_MENU_ITEM (item_gtk   )->active = 1;
		GTK_CHECK_MENU_ITEM (item_own   )->active = 0;
		GTK_CHECK_MENU_ITEM (item_native)->active = 0;
		break;
	}
}

GtkWidget* _create_menu (GtkWidget *adi, GtkWidget *main_window)
{
	GtkWidget *main_menubar;
	GtkWidget *menuitem_edit;
	GtkWidget *menuitem_edit_menu;
	GtkWidget *item_exit;
	GtkWidget *tmp_image;
	GtkWidget *menuitem_windows;
	GtkWidget *menuitem_windows_menu;
	GtkWidget *item_color;
	GtkWidget *item_color_menu;
	GSList *item_gtk_group = NULL;
	GtkWidget *menuitem_about;
	GtkWidget *menuitem_about_menu;
	GtkWidget *item_about;
	GtkTooltips *tooltips;

	tooltips = gtk_tooltips_new ();

	#ifdef HILDON_SUPPORT
	main_menubar = hildon_appview_get_menu (HILDON_APPVIEW(main_window));
	#else
	main_menubar = gtk_menu_bar_new ();
	#endif /* HILDON_SUPPORT */

	menuitem_edit = gtk_menu_item_new_with_mnemonic (_("_File"));
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_edit);

	menuitem_edit_menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_edit), menuitem_edit_menu);

	item_exit = gtk_image_menu_item_new_with_mnemonic (_("_Exit"));
	gtk_container_add (GTK_CONTAINER (menuitem_edit_menu), item_exit);
	gtk_tooltips_set_tip (tooltips, item_exit, _("Exit"), NULL);

	tmp_image = gtk_image_new_from_stock ("gtk-quit", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item_exit), tmp_image);

	menuitem_windows = gtk_adi_create_menu (GTK_ADI(adi));
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_windows);

	menuitem_windows_menu = gtk_adi_menu_get_submenu (GTK_ADI_MENU(menuitem_windows));

	item_color = gtk_menu_item_new_with_mnemonic (_("_Color"));
	gtk_container_add (GTK_CONTAINER (menuitem_windows_menu), item_color);
	gtk_tooltips_set_tip (tooltips, item_color, _("Color"), NULL);

	item_color_menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (item_color), item_color_menu);

	item_gtk = gtk_radio_menu_item_new_with_mnemonic (item_gtk_group, _("_Gtk"));
	item_gtk_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (item_gtk));
	gtk_container_add (GTK_CONTAINER (item_color_menu), item_gtk);
	gtk_tooltips_set_tip (tooltips, item_gtk, _("Gtk"), NULL);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (item_gtk), TRUE);

	item_own = gtk_radio_menu_item_new_with_mnemonic (item_gtk_group, _("_Own"));
	item_gtk_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (item_own));
	gtk_container_add (GTK_CONTAINER (item_color_menu), item_own);
	gtk_tooltips_set_tip (tooltips, item_own, _("Own"), NULL);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (item_own), TRUE);

	item_native = gtk_radio_menu_item_new_with_mnemonic (item_gtk_group, _("_Native"));
	item_gtk_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (item_native));
	gtk_container_add (GTK_CONTAINER (item_color_menu), item_native);
	gtk_tooltips_set_tip (tooltips, item_native, _("Native"), NULL);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (item_native), TRUE);

	menuitem_about = gtk_menu_item_new_with_mnemonic (_("_Help"));
	gtk_container_add (GTK_CONTAINER (main_menubar), menuitem_about);

	menuitem_about_menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem_about), menuitem_about_menu);

	item_about = gtk_image_menu_item_new_with_mnemonic (_("_About"));
	gtk_container_add (GTK_CONTAINER (menuitem_about_menu), item_about);
	gtk_tooltips_set_tip (tooltips, item_about, _("About"), NULL);

	tmp_image = gtk_image_new_from_stock ("gtk-about", GTK_ICON_SIZE_MENU);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item_about), tmp_image);

	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (item_gtk), TRUE);

	g_signal_connect_swapped ((gpointer) item_exit, "activate",
					G_CALLBACK (gtk_main_quit),
					NULL);
	g_signal_connect_swapped ((gpointer) item_gtk, "activate",
					G_CALLBACK (_menu_color_changed),
					GTK_OBJECT (adi));
	g_signal_connect_swapped ((gpointer) item_own, "activate",
					G_CALLBACK (_menu_color_changed),
					GTK_OBJECT (adi));
	g_signal_connect_swapped ((gpointer) item_native, "activate",
					G_CALLBACK (_menu_color_changed),
					GTK_OBJECT (adi));
	g_signal_connect_swapped ((gpointer) item_about, "activate",
					G_CALLBACK (_about_activate),
					GTK_OBJECT (NULL));

	return main_menubar;
}
