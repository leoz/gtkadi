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
