/* GTK ADI Library
 * gtkadicmd.c: ADI Cmd Object
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

#include "gtkadicmd.h"

/* here are local prototypes */
static void gtk_adi_cmd_class_init (GtkAdiCmdClass * c) G_GNUC_UNUSED;
static void gtk_adi_cmd_init (GtkAdiCmd * self) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static GtkObjectClass *parent_class = NULL;

/* Short form macros */
#define self_new gtk_adi_cmd_new
#define self_get_tooltips gtk_adi_cmd_get_tooltips
#define self_create_toolbar gtk_adi_cmd_create_toolbar
#define self_create_menu gtk_adi_cmd_create_menu
#define self_set_nav_buttons gtk_adi_cmd_set_nav_buttons
#define self_set_close_buttons gtk_adi_cmd_set_close_buttons
#define self_set_tile_buttons gtk_adi_cmd_set_tile_buttons
#define self_new_clicked gtk_adi_cmd_new_clicked
#define self_new_h_clicked gtk_adi_cmd_new_h_clicked
#define self_new_v_clicked gtk_adi_cmd_new_v_clicked
#define self_close_clicked gtk_adi_cmd_close_clicked
#define self_close_all_clicked gtk_adi_cmd_close_all_clicked
#define self_next_clicked gtk_adi_cmd_next_clicked
#define self_prev_clicked gtk_adi_cmd_prev_clicked
#define self_tile_h_clicked gtk_adi_cmd_tile_h_clicked
#define self_tile_v_clicked gtk_adi_cmd_tile_v_clicked
#define self_mode_changed gtk_adi_cmd_mode_changed
#define self_fix_toggled gtk_adi_cmd_fix_toggled
GType
gtk_adi_cmd_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiCmdClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_cmd_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiCmd),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_cmd_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_OBJECT, "GtkAdiCmd", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiCmd *)g_object_new(gtk_adi_cmd_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static GtkAdiCmd * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static GtkAdiCmd *
GET_NEW_VARG (const char *first, ...)
{
	GtkAdiCmd *ret;
	va_list ap;
	va_start (ap, first);
	ret = (GtkAdiCmd *)g_object_new_valist (gtk_adi_cmd_get_type (), first, ap);
	va_end (ap);
	return ret;
}


static void
___finalize(GObject *obj_self)
{
	GtkAdiCmd *self G_GNUC_UNUSED = GTK_ADI_CMD (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
#define tooltips (self->tooltips)
#define VAR tooltips
	{
	
    	if(VAR) gtk_object_destroy(GTK_OBJECT(VAR));
    }
	memset(&tooltips, 0, sizeof(tooltips));
#undef VAR
#undef tooltips
#define toolbar (self->toolbar)
#define VAR toolbar
	{
	
    	if(VAR) gtk_widget_destroy(GTK_WIDGET(VAR));
    }
	memset(&toolbar, 0, sizeof(toolbar));
#undef VAR
#undef toolbar
#define menu (self->menu)
#define VAR menu
	{
	
    	if(VAR) gtk_widget_destroy(GTK_WIDGET(VAR));
    }
	memset(&menu, 0, sizeof(menu));
#undef VAR
#undef menu
}

static void 
gtk_adi_cmd_class_init (GtkAdiCmdClass * c G_GNUC_UNUSED)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_OBJECT);

	g_object_class->finalize = ___finalize;
}
static void 
gtk_adi_cmd_init (GtkAdiCmd * self G_GNUC_UNUSED)
{
	self->adi = NULL;
	self->tooltips = NULL;
	self->toolbar = NULL;
	self->menu = NULL;
 {

		self->tooltips = gtk_tooltips_new();
    
 }
}



GtkObject * 
gtk_adi_cmd_new (GtkAdi * adi)
{
	g_return_val_if_fail (adi != NULL, (GtkObject * )0);
	g_return_val_if_fail (GTK_IS_ADI (adi), (GtkObject * )0);
{
	
		GtkObject *object = GTK_OBJECT(GET_NEW);
		GTK_ADI_CMD(object)->adi = adi;
		return object;
	}}

GtkTooltips * 
gtk_adi_cmd_get_tooltips (GtkAdiCmd * self)
{
	g_return_val_if_fail (self != NULL, (GtkTooltips * )0);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), (GtkTooltips * )0);
{
	
		return self->tooltips;
	}}

GtkAdiToolbar * 
gtk_adi_cmd_create_toolbar (GtkAdiCmd * self)
{
	g_return_val_if_fail (self != NULL, (GtkAdiToolbar * )0);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), (GtkAdiToolbar * )0);
{
	
		if ( ! self->toolbar ) {
			self->toolbar = GTK_ADI_TOOLBAR(gtk_adi_toolbar_new (GTK_OBJECT(self)));
			gtk_adi_cmd_set_close_buttons (self);
		}
		return self->toolbar;
	}}

GtkAdiMenu * 
gtk_adi_cmd_create_menu (GtkAdiCmd * self)
{
	g_return_val_if_fail (self != NULL, (GtkAdiMenu * )0);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), (GtkAdiMenu * )0);
{
	
		if ( ! self->menu ) {
			self->menu = GTK_ADI_MENU(gtk_adi_menu_new (GTK_OBJECT(self)));
			gtk_adi_cmd_set_close_buttons (self);
		}
		return self->menu;
	}}

void 
gtk_adi_cmd_set_nav_buttons (GtkAdiCmd * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gboolean next = gtk_adi_can_next_child     (self->adi);
		gboolean prev = gtk_adi_can_previous_child (self->adi);
		if ( self->toolbar ) {
			gtk_adi_toolbar_set_nav_buttons (self->toolbar, next, prev);
		}
		if ( self->menu ) {
			gtk_adi_menu_set_nav_items (self->menu, next, prev);
		}
	}}

void 
gtk_adi_cmd_set_close_buttons (GtkAdiCmd * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gboolean enable = gtk_adi_has_children (self->adi);
		if ( self->toolbar ) {
			gtk_adi_toolbar_set_close_buttons (self->toolbar, enable);
		}
		if ( self->menu ) {
			gtk_adi_menu_set_close_items (self->menu, enable);
		}
		gtk_adi_cmd_set_nav_buttons (self);
	}}

void 
gtk_adi_cmd_set_tile_buttons (GtkAdiCmd * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gboolean tile_h = gtk_adi_can_tile_h (self->adi);
		gboolean tile_v = gtk_adi_can_tile_v (self->adi);
		if ( self->toolbar ) {
			gtk_adi_toolbar_set_tile_buttons (self->toolbar, tile_h, tile_v);
		}
		if ( self->menu ) {
			gtk_adi_menu_set_tile_items (self->menu, tile_h, tile_v);
		}
	}}

void 
gtk_adi_cmd_new_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_user_add_child (self->adi);
		gtk_adi_cmd_set_close_buttons (self);
	}}

void 
gtk_adi_cmd_new_h_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_user_add_child_with_layout (self->adi,
										    GTK_ADI_VERTICAL );
		gtk_adi_cmd_set_close_buttons (self);
	}}

void 
gtk_adi_cmd_new_v_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_user_add_child_with_layout (self->adi,
										    GTK_ADI_HORIZONTAL );
		gtk_adi_cmd_set_close_buttons (self);
	}}

void 
gtk_adi_cmd_close_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_remove_current_child (self->adi);
		gtk_adi_cmd_set_close_buttons (self);
	}}

void 
gtk_adi_cmd_close_all_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_remove_all_children (self->adi);
		gtk_adi_cmd_set_close_buttons (self);
	}}

void 
gtk_adi_cmd_next_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_set_next_child (self->adi);
		gtk_adi_cmd_set_nav_buttons (self);
	}}

void 
gtk_adi_cmd_prev_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_set_previous_child (self->adi);
		gtk_adi_cmd_set_nav_buttons (self);
	}}

void 
gtk_adi_cmd_tile_h_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		g_message ( "Not implemented." );
	}}

void 
gtk_adi_cmd_tile_v_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		g_message ( "Not implemented." );
	}}

void 
gtk_adi_cmd_mode_changed (GtkAdiCmd * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_change_mode (self->adi, mode);
		if ( self->toolbar ) {
			gtk_adi_toolbar_mode_set (self->toolbar, mode);
		}
		if ( self->menu ) {
			gtk_adi_menu_mode_set (self->menu, mode);
		}
	}}

void 
gtk_adi_cmd_fix_toggled (GtkAdiCmd * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
{
	
		gtk_adi_change_state (self->adi, state);
		if ( self->toolbar ) {
			gtk_adi_toolbar_fix_set (self->toolbar, state);
		}
		if ( self->menu ) {
			gtk_adi_menu_fix_set (self->menu, state);
		}
	}}
