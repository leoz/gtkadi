/* vim:set ts=2 sw=4 sts=2 et cindent: */
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

#include "../include/gtkadimenu.h"

#define GETTEXT_PACKAGE "gtk20"
#include <glib/gi18n-lib.h>
#include "gtkadistock.h"
#include "gtkadiutils.h"
#include "gtkadicmd.h"

/* here are local prototypes */
static void gtk_adi_menu_class_init (GtkAdiMenuClass * c);
static void gtk_adi_menu_init (GtkAdiMenu * self);
static void gtk_adi_menu_mode_changed (GtkAdiMenu * self, gpointer user_data);
static void gtk_adi_menu_fix_toggled (GtkAdiMenu * self, gpointer user_data);
static void gtk_adi_menu_post_init (GtkAdiMenu * self);

/* pointer to the class of our parent */
static GtkMenuItemClass *parent_class = NULL;

GType
gtk_adi_menu_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiMenuClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_menu_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiMenu),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_menu_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_MENU_ITEM, "GtkAdiMenu", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiMenu *)g_object_new(gtk_adi_menu_get_type(), NULL))

static void
gtk_adi_menu_finalize(GObject *obj_self)
{
	GtkAdiMenu *self G_GNUC_UNUSED = GTK_ADI_MENU (obj_self);
	
	ADI_TRACE("Menu finalize: %s", "begin");

	if(G_OBJECT_CLASS(parent_class)->finalize) {
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
	}

	ADI_TRACE("Menu finalize: %s", "end");
}

static void 
gtk_adi_menu_class_init (GtkAdiMenuClass * c)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_MENU_ITEM);

	g_object_class->finalize = gtk_adi_menu_finalize;
}
static void 
gtk_adi_menu_init (GtkAdiMenu * self)
{
	GSList *group_mode = NULL;

	self->cmd = NULL;
	self->tooltips = NULL;
	self->item_new = NULL;
	self->item_new_h = NULL;
	self->item_new_v = NULL;
	self->sep_new = NULL;
	self->item_cls = NULL;
	self->item_cls_all = NULL;
	self->sep_cls = NULL;
	self->item_next = NULL;
	self->item_prev = NULL;
	self->sep_nav = NULL;
	self->item_tile_h = NULL;
	self->item_tile_v = NULL;
	self->sep_tile = NULL;
	self->item_mode = NULL;
	self->menu_mode = NULL;
	self->item_paned = NULL;
	self->item_box = NULL;
	self->item_fix = NULL;
	self->sep_mode = NULL;

	self->menu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (self), self->menu);

	self->item_new = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_NEW, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_new);

	self->item_new_h = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_NEW_HORIZONTALLY, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_new_h);

	self->item_new_v = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_NEW_VERTICALLY, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_new_v);

	self->sep_new = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (self->menu), self->sep_new);
	gtk_widget_set_sensitive (self->sep_new, FALSE);

	self->item_cls = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_CLOSE, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_cls);

	self->item_cls_all = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_CLOSE_ALL, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_cls_all);

	self->sep_cls = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (self->menu), self->sep_cls);
	gtk_widget_set_sensitive (self->sep_cls, FALSE);

	self->item_next = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_NEXT, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_next);

	self->item_prev = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_PREVIOUS, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_prev);

	self->sep_nav = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (self->menu), self->sep_nav);
	gtk_widget_set_sensitive (self->sep_nav, FALSE);

	self->item_tile_h = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_TILE_HORIZONTALLY, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_tile_h);

	self->item_tile_v = gtk_image_menu_item_new_from_stock (GTK_ADI_STOCK_TILE_VERTICALLY, NULL);
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_tile_v);

	self->sep_tile = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (self->menu), self->sep_tile);
	gtk_widget_set_sensitive (self->sep_tile, FALSE);

	self->item_mode = gtk_menu_item_new_with_mnemonic (_("_Mode"));
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_mode);

	self->menu_mode = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (self->item_mode), self->menu_mode);

	self->item_paned = gtk_radio_menu_item_new_with_mnemonic (group_mode, _("_Paned"));
	group_mode = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (self->item_paned));
	gtk_container_add (GTK_CONTAINER (self->menu_mode), self->item_paned);

	self->item_box = gtk_radio_menu_item_new_with_mnemonic (group_mode, _("_Box"));
	group_mode = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (self->item_box));
	gtk_container_add (GTK_CONTAINER (self->menu_mode), self->item_box);

	self->item_fix = gtk_check_menu_item_new_with_mnemonic (_("_Fix"));
	gtk_container_add (GTK_CONTAINER (self->menu), self->item_fix);

	self->sep_mode = gtk_separator_menu_item_new ();
	gtk_container_add (GTK_CONTAINER (self->menu), self->sep_mode);
	gtk_widget_set_sensitive (self->sep_mode, FALSE);

	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (self->item_paned), TRUE);
}



static void 
gtk_adi_menu_mode_changed (GtkAdiMenu * self, gpointer user_data)
{
	GtkAdiMode mode = GTK_ADI_PANED;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	if (self->item_box == GTK_WIDGET(user_data)) {
		mode = GTK_ADI_BOX;
	}
	gtk_adi_cmd_mode_changed (GTK_ADI_CMD(self->cmd), mode);
}

void 
gtk_adi_menu_mode_set (GtkAdiMenu * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	if (mode == GTK_ADI_BOX) {
		GTK_CHECK_MENU_ITEM (self->item_paned)->active = 0;
		GTK_CHECK_MENU_ITEM (self->item_box  )->active = 1;
	}
	else {
		GTK_CHECK_MENU_ITEM (self->item_paned)->active = 1;
		GTK_CHECK_MENU_ITEM (self->item_box  )->active = 0;
	}
}

static void 
gtk_adi_menu_fix_toggled (GtkAdiMenu * self, gpointer user_data)
{
	GtkAdiState state = GTK_ADI_MOVABLE;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	if ( gtk_check_menu_item_get_active (GTK_CHECK_MENU_ITEM (user_data)
											) ) {
		state = GTK_ADI_FIXED;
	}
	gtk_adi_cmd_fix_toggled (GTK_ADI_CMD(self->cmd), state);
}

void 
gtk_adi_menu_fix_set (GtkAdiMenu * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	gtk_check_menu_item_set_active (
				  GTK_CHECK_MENU_ITEM (self->item_fix),
				  state == GTK_ADI_FIXED);
}

static void 
gtk_adi_menu_post_init (GtkAdiMenu * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	gtk_tooltips_set_tip (self->tooltips, GTK_WIDGET(self), _("Window"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_new, _("New"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_new_h, _("New Hor."), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_new_v, _("New Vert."), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_cls, _("Close"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_cls_all, _("Close All"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_next, _("Next"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_prev, _("Prev."), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_tile_h, _("Tile Hor."), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_tile_v, _("Tile Vert."), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_mode, _("Mode"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_paned, _("Paned"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_box, _("Box"), NULL);
	gtk_tooltips_set_tip (self->tooltips, self->item_fix, _("Fix"), NULL);

	g_signal_connect_swapped ((gpointer) self->item_new, "activate",
					G_CALLBACK (gtk_adi_cmd_new_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_new_h, "activate",
					G_CALLBACK (gtk_adi_cmd_new_h_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_new_v, "activate",
					G_CALLBACK (gtk_adi_cmd_new_v_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_cls, "activate",
					G_CALLBACK (gtk_adi_cmd_close_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_cls_all, "activate",
					G_CALLBACK (gtk_adi_cmd_close_all_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_next, "activate",
					G_CALLBACK (gtk_adi_cmd_next_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_prev, "activate",
					G_CALLBACK (gtk_adi_cmd_prev_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_tile_h, "activate",
					G_CALLBACK (gtk_adi_cmd_tile_h_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_tile_v, "activate",
					G_CALLBACK (gtk_adi_cmd_tile_v_clicked),
					self->cmd);
	g_signal_connect_swapped ((gpointer) self->item_paned, "activate",
					G_CALLBACK (gtk_adi_menu_mode_changed),
					self);
	g_signal_connect_swapped ((gpointer) self->item_box, "activate",
					G_CALLBACK (gtk_adi_menu_mode_changed),
					self);
	g_signal_connect_swapped ((gpointer) self->item_fix, "activate",
					G_CALLBACK (gtk_adi_menu_fix_toggled),
					self);
}

GtkWidget* 
gtk_adi_menu_new (GtkObject * cmd)
{
	GtkWidget *widget = NULL;
	GtkWidget *label_widget = NULL;

	g_return_val_if_fail (cmd != NULL, (GtkWidget * )0);
	
	widget = GTK_WIDGET(GET_NEW);
	label_widget = gtk_label_new_with_mnemonic (_("_Window"));

	gtk_container_add (GTK_CONTAINER (widget), label_widget);
	GTK_ADI_MENU(widget)->cmd = cmd;
	GTK_ADI_MENU(widget)->tooltips = gtk_adi_cmd_get_tooltips (GTK_ADI_CMD(cmd));
	gtk_adi_menu_post_init (GTK_ADI_MENU(widget));
	return widget;
}

void 
gtk_adi_menu_set_close_items (GtkAdiMenu * self, gboolean enable)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	gtk_widget_set_sensitive (self->item_cls    , enable);
	gtk_widget_set_sensitive (self->item_cls_all, enable);
}

void 
gtk_adi_menu_set_nav_items (GtkAdiMenu * self, gboolean next, gboolean prev)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	gtk_widget_set_sensitive (self->item_next, next);
	gtk_widget_set_sensitive (self->item_prev, prev);
}

void 
gtk_adi_menu_set_tile_items (GtkAdiMenu * self, gboolean tile_h, gboolean tile_v)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
	
	gtk_widget_set_sensitive (self->item_tile_h, tile_h);
	gtk_widget_set_sensitive (self->item_tile_v, tile_v);
}

GtkWidget * 
gtk_adi_menu_get_submenu (GtkAdiMenu * self)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI_MENU (self), (GtkWidget * )0);
	
	return self->menu;
}
