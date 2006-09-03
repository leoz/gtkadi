/* GTK ADI Test
 * toolbar.c
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
#include <gtkaditoolbar.h>

#include "menu.h"

void _toolbar_color_changed (GtkAdi *adi, gpointer user_data)
{
	gint value = gtk_combo_box_get_active ( GTK_COMBO_BOX (user_data) );
	GtkAdiColorType color = GTK_ADI_COLOR_GTK;
	switch ( value ) {
	case 1:
		color = GTK_ADI_COLOR_OWN;
		break;
	case 2:
		color = GTK_ADI_COLOR_NATIVE;
		break;
	default:
		break;
	}
	gtk_adi_change_color (adi, color);
	_menu_color_set (color);
}

static 	GtkWidget *combobox_color = NULL;

void _toolbar_color_set (GtkAdiColorType color)
{
	switch (color) {
	case GTK_ADI_COLOR_OWN:
		gtk_combo_box_set_active (GTK_COMBO_BOX(combobox_color),1);
		break;
	case GTK_ADI_COLOR_NATIVE:
		gtk_combo_box_set_active (GTK_COMBO_BOX(combobox_color),2);
		break;
	case GTK_ADI_COLOR_GTK:
	default:
		gtk_combo_box_set_active (GTK_COMBO_BOX(combobox_color),0);
		break;
	}
}

void _create_toolbar (GtkWidget *adi, GtkWidget *toolbar)
{
	GtkWidget *toolitem_color = NULL;
		
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_ICONS);
	
	toolitem_color = (GtkWidget*) gtk_tool_item_new ();
	gtk_container_add (GTK_CONTAINER (toolbar), toolitem_color);
	
	combobox_color = gtk_combo_box_new_text ();
	gtk_container_add (GTK_CONTAINER (toolitem_color), combobox_color);
	gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_color), _("Gtk"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_color), _("Own"));
	gtk_combo_box_append_text (GTK_COMBO_BOX (combobox_color), _("Native"));
	
	g_signal_connect_swapped ((gpointer) combobox_color, "changed",
					G_CALLBACK (_toolbar_color_changed),
					GTK_OBJECT (adi));
	
	gtk_combo_box_set_active (GTK_COMBO_BOX(combobox_color),0);
}
