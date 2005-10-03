/* GTK ADI Library
 * gtkaditoolbar.c: ADI Toolbar Widget
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

#include "gtkaditoolbar.h"

#define GETTEXT_PACKAGE "gtk20"
#include <glib/gi18n-lib.h>
#include "gtkadistock.h"
#include "gtkadicmd.h"

/* here are local prototypes */
static void gtk_adi_toolbar_class_init (GtkAdiToolbarClass * c) G_GNUC_UNUSED;
static void gtk_adi_toolbar_init (GtkAdiToolbar * self) G_GNUC_UNUSED;
static void gtk_adi_toolbar_mode_changed (GtkAdiToolbar * self, gpointer user_data) G_GNUC_UNUSED;
static void gtk_adi_toolbar_fix_toggled (GtkAdiToolbar * self, gpointer user_data) G_GNUC_UNUSED;
static void gtk_adi_toolbar_post_init (GtkAdiToolbar * self) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static GtkToolbarClass *parent_class = NULL;

/* Short form macros */
#define self_mode_changed gtk_adi_toolbar_mode_changed
#define self_mode_set gtk_adi_toolbar_mode_set
#define self_fix_toggled gtk_adi_toolbar_fix_toggled
#define self_fix_set gtk_adi_toolbar_fix_set
#define self_post_init gtk_adi_toolbar_post_init
#define self_new gtk_adi_toolbar_new
#define self_set_close_buttons gtk_adi_toolbar_set_close_buttons
#define self_set_nav_buttons gtk_adi_toolbar_set_nav_buttons
#define self_set_tile_buttons gtk_adi_toolbar_set_tile_buttons
GType
gtk_adi_toolbar_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiToolbarClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_toolbar_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiToolbar),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_toolbar_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_TOOLBAR, "GtkAdiToolbar", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiToolbar *)g_object_new(gtk_adi_toolbar_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static GtkAdiToolbar * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static GtkAdiToolbar *
GET_NEW_VARG (const char *first, ...)
{
	GtkAdiToolbar *ret;
	va_list ap;
	va_start (ap, first);
	ret = (GtkAdiToolbar *)g_object_new_valist (gtk_adi_toolbar_get_type (), first, ap);
	va_end (ap);
	return ret;
}


static void
___finalize(GObject *obj_self)
{
	GtkAdiToolbar *self G_GNUC_UNUSED = GTK_ADI_TOOLBAR (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
#define btn_new (self->btn_new)
#define VAR btn_new
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_new, 0, sizeof(btn_new));
#undef VAR
#undef btn_new
#define btn_new_h (self->btn_new_h)
#define VAR btn_new_h
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_new_h, 0, sizeof(btn_new_h));
#undef VAR
#undef btn_new_h
#define btn_new_v (self->btn_new_v)
#define VAR btn_new_v
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_new_v, 0, sizeof(btn_new_v));
#undef VAR
#undef btn_new_v
#define sep_new (self->sep_new)
#define VAR sep_new
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_new, 0, sizeof(sep_new));
#undef VAR
#undef sep_new
#define btn_cls (self->btn_cls)
#define VAR btn_cls
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_cls, 0, sizeof(btn_cls));
#undef VAR
#undef btn_cls
#define btn_cls_all (self->btn_cls_all)
#define VAR btn_cls_all
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_cls_all, 0, sizeof(btn_cls_all));
#undef VAR
#undef btn_cls_all
#define sep_cls (self->sep_cls)
#define VAR sep_cls
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_cls, 0, sizeof(sep_cls));
#undef VAR
#undef sep_cls
#define btn_next (self->btn_next)
#define VAR btn_next
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_next, 0, sizeof(btn_next));
#undef VAR
#undef btn_next
#define btn_prev (self->btn_prev)
#define VAR btn_prev
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_prev, 0, sizeof(btn_prev));
#undef VAR
#undef btn_prev
#define sep_nav (self->sep_nav)
#define VAR sep_nav
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_nav, 0, sizeof(sep_nav));
#undef VAR
#undef sep_nav
#define btn_tile_h (self->btn_tile_h)
#define VAR btn_tile_h
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_tile_h, 0, sizeof(btn_tile_h));
#undef VAR
#undef btn_tile_h
#define btn_tile_v (self->btn_tile_v)
#define VAR btn_tile_v
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&btn_tile_v, 0, sizeof(btn_tile_v));
#undef VAR
#undef btn_tile_v
#define sep_tile (self->sep_tile)
#define VAR sep_tile
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&sep_tile, 0, sizeof(sep_tile));
#undef VAR
#undef sep_tile
#define itm_mode (self->itm_mode)
#define VAR itm_mode
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&itm_mode, 0, sizeof(itm_mode));
#undef VAR
#undef itm_mode
#define cmb_mode (self->cmb_mode)
#define VAR cmb_mode
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&cmb_mode, 0, sizeof(cmb_mode));
#undef VAR
#undef cmb_mode
#define tgl_fix (self->tgl_fix)
#define VAR tgl_fix
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&tgl_fix, 0, sizeof(tgl_fix));
#undef VAR
#undef tgl_fix
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
gtk_adi_toolbar_class_init (GtkAdiToolbarClass * c G_GNUC_UNUSED)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_TOOLBAR);

	g_object_class->finalize = ___finalize;
}
static void 
gtk_adi_toolbar_init (GtkAdiToolbar * self G_GNUC_UNUSED)
{
	self->cmd = NULL;
	self->tooltips = NULL;
	self->btn_new = NULL;
	self->btn_new_h = NULL;
	self->btn_new_v = NULL;
	self->sep_new = NULL;
	self->btn_cls = NULL;
	self->btn_cls_all = NULL;
	self->sep_cls = NULL;
	self->btn_next = NULL;
	self->btn_prev = NULL;
	self->sep_nav = NULL;
	self->btn_tile_h = NULL;
	self->btn_tile_v = NULL;
	self->sep_tile = NULL;
	self->itm_mode = NULL;
	self->cmb_mode = NULL;
	self->tgl_fix = NULL;
	self->sep_mode = NULL;
 {

		self->btn_new = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_NEW));
		gtk_container_add (GTK_CONTAINER (self), self->btn_new);

		self->btn_new_h = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_NEW_HORIZONTALLY));
		gtk_container_add (GTK_CONTAINER (self), self->btn_new_h);

		self->btn_new_v = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_NEW_VERTICALLY));
		gtk_container_add (GTK_CONTAINER (self), self->btn_new_v);

		self->sep_new = (GtkWidget*) gtk_separator_tool_item_new ();
		gtk_container_add (GTK_CONTAINER (self), self->sep_new);

		self->btn_cls = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_CLOSE));
		gtk_container_add (GTK_CONTAINER (self), self->btn_cls);
		
		self->btn_cls_all = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_CLOSE_ALL));
		gtk_container_add (GTK_CONTAINER (self), self->btn_cls_all);
		
		self->sep_cls = (GtkWidget*) gtk_separator_tool_item_new ();
		gtk_container_add (GTK_CONTAINER (self), self->sep_cls);

		self->btn_next = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_NEXT));
		gtk_container_add (GTK_CONTAINER (self), self->btn_next);
		
		self->btn_prev = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_PREVIOUS));
		gtk_container_add (GTK_CONTAINER (self), self->btn_prev);
		
		self->sep_nav = (GtkWidget*) gtk_separator_tool_item_new ();
		gtk_container_add (GTK_CONTAINER (self), self->sep_nav);

		self->btn_tile_h = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_TILE_HORIZONTALLY));
		gtk_container_add (GTK_CONTAINER (self), self->btn_tile_h);

		self->btn_tile_v = GTK_WIDGET(gtk_tool_button_new_from_stock (GTK_ADI_STOCK_TILE_VERTICALLY));
		gtk_container_add (GTK_CONTAINER (self), self->btn_tile_v);

		self->sep_tile = (GtkWidget*) gtk_separator_tool_item_new ();
		gtk_container_add (GTK_CONTAINER (self), self->sep_tile);

		self->itm_mode = (GtkWidget*) gtk_tool_item_new ();
		gtk_container_add (GTK_CONTAINER (self), self->itm_mode);

		self->cmb_mode = gtk_combo_box_new_text ();
		gtk_container_add (GTK_CONTAINER (self->itm_mode), self->cmb_mode);
		gtk_combo_box_append_text (GTK_COMBO_BOX (self->cmb_mode), _("Paned"));
		gtk_combo_box_append_text (GTK_COMBO_BOX (self->cmb_mode), _("Box"));

		self->tgl_fix = GTK_WIDGET(gtk_toggle_tool_button_new_from_stock (GTK_ADI_STOCK_FIX));
		gtk_container_add (GTK_CONTAINER (self), self->tgl_fix);
		
		self->sep_mode = (GtkWidget*) gtk_separator_tool_item_new ();
		gtk_container_add (GTK_CONTAINER (self), self->sep_mode);

		gtk_combo_box_set_active (GTK_COMBO_BOX(self->cmb_mode),0);
	
 }
}



static void 
gtk_adi_toolbar_mode_changed (GtkAdiToolbar * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		gint value = gtk_combo_box_get_active ( GTK_COMBO_BOX (user_data) );
		GtkAdiMode mode = GTK_ADI_PANED;
		switch ( value ) {
		case 1:
			mode = GTK_ADI_BOX;
			break;
		default:
			break;
		}
		gtk_adi_cmd_mode_changed (GTK_ADI_CMD(self->cmd), mode);
	}}

void 
gtk_adi_toolbar_mode_set (GtkAdiToolbar * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		gint num = 0;
		if (mode == GTK_ADI_BOX) {
			num = 1;
		}
		gtk_combo_box_set_active (GTK_COMBO_BOX(self->cmb_mode),num);
	}}

static void 
gtk_adi_toolbar_fix_toggled (GtkAdiToolbar * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		GtkAdiState state = GTK_ADI_MOVABLE;
		if ( gtk_toggle_tool_button_get_active ( GTK_TOGGLE_TOOL_BUTTON (user_data)
												) ) {
			state = GTK_ADI_FIXED;
		}
		gtk_adi_cmd_fix_toggled (GTK_ADI_CMD(self->cmd), state);
	}}

void 
gtk_adi_toolbar_fix_set (GtkAdiToolbar * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		gtk_toggle_tool_button_set_active (
		               GTK_TOGGLE_TOOL_BUTTON (self->tgl_fix),
		               state == GTK_ADI_FIXED);
	}}

static void 
gtk_adi_toolbar_post_init (GtkAdiToolbar * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_new), self->tooltips, _("New Window"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_new_h), self->tooltips, _("Add New Window Horizontally"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_new_v), self->tooltips, _("Add New Window Vertically"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_cls), self->tooltips, _("Close"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_cls_all), self->tooltips, _("Close All"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_next), self->tooltips, _("Next"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_prev), self->tooltips, _("Previous"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_tile_h), self->tooltips, _("Tile Horizontally"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->btn_tile_v), self->tooltips, _("Tile Vertically"), NULL);
		gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (self->tgl_fix), self->tooltips, _("Fix"), NULL);

		g_signal_connect_swapped ((gpointer) self->btn_new, "clicked",
						G_CALLBACK (gtk_adi_cmd_new_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_new_h, "clicked",
						G_CALLBACK (gtk_adi_cmd_new_h_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_new_v, "clicked",
						G_CALLBACK (gtk_adi_cmd_new_v_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_cls, "clicked",
						G_CALLBACK (gtk_adi_cmd_close_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_cls_all, "clicked",
						G_CALLBACK (gtk_adi_cmd_close_all_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_next, "clicked",
						G_CALLBACK (gtk_adi_cmd_next_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_prev, "clicked",
						G_CALLBACK (gtk_adi_cmd_prev_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_tile_h, "clicked",
						G_CALLBACK (gtk_adi_cmd_tile_h_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->btn_tile_v, "clicked",
						G_CALLBACK (gtk_adi_cmd_tile_v_clicked),
						self->cmd);
		g_signal_connect_swapped ((gpointer) self->cmb_mode, "changed",
						G_CALLBACK (gtk_adi_toolbar_mode_changed),
						self);
		g_signal_connect_swapped ((gpointer) self->tgl_fix, "toggled",
						G_CALLBACK (gtk_adi_toolbar_fix_toggled),
						self);
	}}

GtkWidget * 
gtk_adi_toolbar_new (GtkObject * cmd)
{
	g_return_val_if_fail (cmd != NULL, (GtkWidget * )0);
{
	
		GtkWidget *widget = GTK_WIDGET(GET_NEW);
		GTK_ADI_TOOLBAR(widget)->cmd = cmd;
		GTK_ADI_TOOLBAR(widget)->tooltips = gtk_adi_cmd_get_tooltips (GTK_ADI_CMD(cmd));
		gtk_adi_toolbar_post_init (GTK_ADI_TOOLBAR(widget));
		return widget;
	}}

void 
gtk_adi_toolbar_set_close_buttons (GtkAdiToolbar * self, gboolean enable)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		gtk_widget_set_sensitive (self->btn_cls    , enable);
		gtk_widget_set_sensitive (self->btn_cls_all, enable);
	}}

void 
gtk_adi_toolbar_set_nav_buttons (GtkAdiToolbar * self, gboolean next, gboolean prev)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		gtk_widget_set_sensitive (self->btn_next, next);
		gtk_widget_set_sensitive (self->btn_prev, prev);
	}}

void 
gtk_adi_toolbar_set_tile_buttons (GtkAdiToolbar * self, gboolean tile_h, gboolean tile_v)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TOOLBAR (self));
{
	
		gtk_widget_set_sensitive (self->btn_tile_h, tile_h);
		gtk_widget_set_sensitive (self->btn_tile_v, tile_v);
	}}
