/* GTK ADI Library
 * gtkadimenu.c: ADI Menu Widget
 * Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * $Id$
 */


#include <string.h> /* memset() */

#include "gtkadimenu.h"

#define GETTEXT_PACKAGE "gtk20"
#include <glib/gi18n-lib.h>
#include "gtkadistock.h"
#include "gtkadicmd.h"

/* here are local prototypes */
static void gtk_adi_menu_class_init (GtkAdiMenuClass * c) G_GNUC_UNUSED;
static void gtk_adi_menu_init (GtkAdiMenu * self) G_GNUC_UNUSED;
static void gtk_adi_menu_mode_changed (GtkAdiMenu * self, gpointer user_data) G_GNUC_UNUSED;
static void gtk_adi_menu_fix_toggled (GtkAdiMenu * self, gpointer user_data) G_GNUC_UNUSED;
static void gtk_adi_menu_post_init (GtkAdiMenu * self) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static GtkMenuItemClass *parent_class = NULL;

/* Short form macros */
#define self_mode_changed gtk_adi_menu_mode_changed
#define self_mode_set gtk_adi_menu_mode_set
#define self_fix_toggled gtk_adi_menu_fix_toggled
#define self_fix_set gtk_adi_menu_fix_set
#define self_post_init gtk_adi_menu_post_init
#define self_new gtk_adi_menu_new
#define self_set_close_items gtk_adi_menu_set_close_items
#define self_set_nav_items gtk_adi_menu_set_nav_items
#define self_set_tile_items gtk_adi_menu_set_tile_items
#define self_get_submenu gtk_adi_menu_get_submenu
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

/* a function for creating a new object of our type */
#include <stdarg.h>
static GtkAdiMenu * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static GtkAdiMenu *
GET_NEW_VARG (const char *first, ...)
{
	GtkAdiMenu *ret;
	va_list ap;
	va_start (ap, first);
	ret = (GtkAdiMenu *)g_object_new_valist (gtk_adi_menu_get_type (), first, ap);
	va_end (ap);
	return ret;
}


static void
___finalize(GObject *obj_self)
{
	GtkAdiMenu *self G_GNUC_UNUSED = GTK_ADI_MENU (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
#define menu (self->menu)
#define VAR menu
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&menu, 0, sizeof(menu));
#undef VAR
#undef menu
#define item_new (self->item_new)
#define VAR item_new
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_new, 0, sizeof(item_new));
#undef VAR
#undef item_new
#define item_new_h (self->item_new_h)
#define VAR item_new_h
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_new_h, 0, sizeof(item_new_h));
#undef VAR
#undef item_new_h
#define item_new_v (self->item_new_v)
#define VAR item_new_v
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_new_v, 0, sizeof(item_new_v));
#undef VAR
#undef item_new_v
#define sep_new (self->sep_new)
#define VAR sep_new
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_new, 0, sizeof(sep_new));
#undef VAR
#undef sep_new
#define item_cls (self->item_cls)
#define VAR item_cls
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_cls, 0, sizeof(item_cls));
#undef VAR
#undef item_cls
#define item_cls_all (self->item_cls_all)
#define VAR item_cls_all
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_cls_all, 0, sizeof(item_cls_all));
#undef VAR
#undef item_cls_all
#define sep_cls (self->sep_cls)
#define VAR sep_cls
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_cls, 0, sizeof(sep_cls));
#undef VAR
#undef sep_cls
#define item_next (self->item_next)
#define VAR item_next
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_next, 0, sizeof(item_next));
#undef VAR
#undef item_next
#define item_prev (self->item_prev)
#define VAR item_prev
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_prev, 0, sizeof(item_prev));
#undef VAR
#undef item_prev
#define sep_nav (self->sep_nav)
#define VAR sep_nav
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_nav, 0, sizeof(sep_nav));
#undef VAR
#undef sep_nav
#define item_tile_h (self->item_tile_h)
#define VAR item_tile_h
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_tile_h, 0, sizeof(item_tile_h));
#undef VAR
#undef item_tile_h
#define item_tile_v (self->item_tile_v)
#define VAR item_tile_v
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_tile_v, 0, sizeof(item_tile_v));
#undef VAR
#undef item_tile_v
#define sep_tile (self->sep_tile)
#define VAR sep_tile
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_tile, 0, sizeof(sep_tile));
#undef VAR
#undef sep_tile
#define item_mode (self->item_mode)
#define VAR item_mode
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_mode, 0, sizeof(item_mode));
#undef VAR
#undef item_mode
#define menu_mode (self->menu_mode)
#define VAR menu_mode
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&menu_mode, 0, sizeof(menu_mode));
#undef VAR
#undef menu_mode
#define item_paned (self->item_paned)
#define VAR item_paned
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_paned, 0, sizeof(item_paned));
#undef VAR
#undef item_paned
#define item_box (self->item_box)
#define VAR item_box
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_box, 0, sizeof(item_box));
#undef VAR
#undef item_box
#define item_fix (self->item_fix)
#define VAR item_fix
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&item_fix, 0, sizeof(item_fix));
#undef VAR
#undef item_fix
#define sep_mode (self->sep_mode)
#define VAR sep_mode
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_mode, 0, sizeof(sep_mode));
#undef VAR
#undef sep_mode
}

static void 
gtk_adi_menu_class_init (GtkAdiMenuClass * c G_GNUC_UNUSED)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_MENU_ITEM);

	g_object_class->finalize = ___finalize;
}
static void 
gtk_adi_menu_init (GtkAdiMenu * self G_GNUC_UNUSED)
{
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
 {

		GSList *group_mode = NULL;

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
}



static void 
gtk_adi_menu_mode_changed (GtkAdiMenu * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
		GtkAdiMode mode = GTK_ADI_PANED;
		if (self->item_box == GTK_WIDGET(user_data)) {
			mode = GTK_ADI_BOX;
		}
		gtk_adi_cmd_mode_changed (GTK_ADI_CMD(self->cmd), mode);
	}}

void 
gtk_adi_menu_mode_set (GtkAdiMenu * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
		if (mode == GTK_ADI_BOX) {
			GTK_CHECK_MENU_ITEM (self->item_paned)->active = 0;
			GTK_CHECK_MENU_ITEM (self->item_box  )->active = 1;
		}
		else {
			GTK_CHECK_MENU_ITEM (self->item_paned)->active = 1;
			GTK_CHECK_MENU_ITEM (self->item_box  )->active = 0;
		}
	}}

static void 
gtk_adi_menu_fix_toggled (GtkAdiMenu * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
		GtkAdiState state = GTK_ADI_MOVABLE;
		if ( gtk_check_menu_item_get_active (GTK_CHECK_MENU_ITEM (user_data)
												) ) {
			state = GTK_ADI_FIXED;
		}
		gtk_adi_cmd_fix_toggled (GTK_ADI_CMD(self->cmd), state);
	}}

void 
gtk_adi_menu_fix_set (GtkAdiMenu * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
		gtk_check_menu_item_set_active (
		              GTK_CHECK_MENU_ITEM (self->item_fix),
					  state == GTK_ADI_FIXED);
	}}

static void 
gtk_adi_menu_post_init (GtkAdiMenu * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
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
	}}

GtkWidget * 
gtk_adi_menu_new (GtkObject * cmd)
{
	g_return_val_if_fail (cmd != NULL, (GtkWidget * )0);
{
	
		GtkWidget *widget = GTK_WIDGET(GET_NEW);
		GtkWidget *label_widget = gtk_label_new_with_mnemonic (_("_Window"));
		gtk_container_add (GTK_CONTAINER (widget), label_widget);
		GTK_ADI_MENU(widget)->cmd = cmd;
		GTK_ADI_MENU(widget)->tooltips = gtk_adi_cmd_get_tooltips (GTK_ADI_CMD(cmd));
		gtk_adi_menu_post_init (GTK_ADI_MENU(widget));
		return widget;
	}}

void 
gtk_adi_menu_set_close_items (GtkAdiMenu * self, gboolean enable)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
		gtk_widget_set_sensitive (self->item_cls    , enable);
		gtk_widget_set_sensitive (self->item_cls_all, enable);
	}}

void 
gtk_adi_menu_set_nav_items (GtkAdiMenu * self, gboolean next, gboolean prev)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
		gtk_widget_set_sensitive (self->item_next, next);
		gtk_widget_set_sensitive (self->item_prev, prev);
	}}

void 
gtk_adi_menu_set_tile_items (GtkAdiMenu * self, gboolean tile_h, gboolean tile_v)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_MENU (self));
{
	
		gtk_widget_set_sensitive (self->item_tile_h, tile_h);
		gtk_widget_set_sensitive (self->item_tile_v, tile_v);
	}}

GtkWidget * 
gtk_adi_menu_get_submenu (GtkAdiMenu * self)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI_MENU (self), (GtkWidget * )0);
{
	
		return self->menu;
	}}
