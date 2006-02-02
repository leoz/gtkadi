/* GTK ADI Library
 * gtkadicmd.c: ADI Cmd Object
 * Copyright (C) 2003 - 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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

#include "gtkadiutils.h"
#include "gtkadicmd.h"

/* here are local prototypes */
static void gtk_adi_cmd_class_init (GtkAdiCmdClass * c);
static void gtk_adi_cmd_init (GtkAdiCmd * self);

/* pointer to the class of our parent */
static GtkObjectClass *parent_class = NULL;

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

static void
gtk_adi_cmd_finalize(GObject *obj_self)
{
	GtkAdiCmd *self = GTK_ADI_CMD (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) {
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
	}
	
	ADI_TRACE("Cmd finalize: %s", "begin");
	
	if(self->tooltips) {
		gtk_object_destroy(GTK_OBJECT(self->tooltips));
		self->tooltips = NULL;
	}
	if(self->toolbar) {
		gtk_widget_destroy(GTK_WIDGET(self->toolbar));
		self->toolbar = NULL;
	}
	if(self->menu) {
		gtk_widget_destroy(GTK_WIDGET(self->menu));
		self->menu = NULL;
	}
	
	ADI_TRACE("Cmd finalize: %s", "end");
}

static void 
gtk_adi_cmd_class_init (GtkAdiCmdClass * c)
{
	GObjectClass *g_object_class = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_OBJECT);

	g_object_class->finalize = gtk_adi_cmd_finalize;
}

static void 
gtk_adi_cmd_init (GtkAdiCmd * self)
{
	self->adi = NULL;
	self->tooltips = NULL;
	self->toolbar = NULL;
	self->menu = NULL;

	self->tooltips = gtk_tooltips_new();
}



GtkObject * 
gtk_adi_cmd_new (GtkAdi * adi)
{
	g_return_val_if_fail (adi != NULL, (GtkObject * )0);
	g_return_val_if_fail (GTK_IS_ADI (adi), (GtkObject * )0);
	
	GtkObject *object = GTK_OBJECT(GET_NEW);
	GTK_ADI_CMD(object)->adi = adi;
	return object;
}

GtkTooltips * 
gtk_adi_cmd_get_tooltips (GtkAdiCmd * self)
{
	g_return_val_if_fail (self != NULL, (GtkTooltips * )0);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), (GtkTooltips * )0);
	
	return self->tooltips;
}

GtkAdiToolbar* 
gtk_adi_cmd_create_toolbar (GtkAdiCmd * self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), NULL);
	
	if ( ! self->toolbar ) {
		self->toolbar = GTK_ADI_TOOLBAR(gtk_adi_toolbar_new (GTK_OBJECT(self)));
		gtk_adi_cmd_set_close_buttons (self);
	}
	return self->toolbar;
}

GtkAdiMenu* 
gtk_adi_cmd_create_menu (GtkAdiCmd * self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), NULL);
	
	if ( ! self->menu ) {
		self->menu = GTK_ADI_MENU(gtk_adi_menu_new (GTK_OBJECT(self)));
		gtk_adi_cmd_set_close_buttons (self);
	}
	return self->menu;
}

GtkWidget*
gtk_adi_cmd_get_toolbar (GtkAdiCmd *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), NULL);
	
	return GTK_WIDGET(self->toolbar); // FIX ME
}

GtkWidget*
gtk_adi_cmd_get_menu (GtkAdiCmd *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_CMD (self), NULL);
	
	return GTK_WIDGET(self->menu); // FIX ME
}

void 
gtk_adi_cmd_set_nav_buttons (GtkAdiCmd * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gboolean next = gtk_adi_can_next_child     (self->adi);
	gboolean prev = gtk_adi_can_previous_child (self->adi);
	if ( self->toolbar ) {
		gtk_adi_toolbar_set_nav_buttons (self->toolbar, next, prev);
	}
	if ( self->menu ) {
		gtk_adi_menu_set_nav_items (self->menu, next, prev);
	}
}

void 
gtk_adi_cmd_set_close_buttons (GtkAdiCmd * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gboolean enable = gtk_adi_has_children (self->adi);
	if ( self->toolbar ) {
		gtk_adi_toolbar_set_close_buttons (self->toolbar, enable);
	}
	if ( self->menu ) {
		gtk_adi_menu_set_close_items (self->menu, enable);
	}
	gtk_adi_cmd_set_nav_buttons (self);
}

void 
gtk_adi_cmd_set_tile_buttons (GtkAdiCmd * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gboolean tile_h = gtk_adi_can_tile_h (self->adi);
	gboolean tile_v = gtk_adi_can_tile_v (self->adi);
	if ( self->toolbar ) {
		gtk_adi_toolbar_set_tile_buttons (self->toolbar, tile_h, tile_v);
	}
	if ( self->menu ) {
		gtk_adi_menu_set_tile_items (self->menu, tile_h, tile_v);
	}
}

void 
gtk_adi_cmd_new_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_user_add_child (self->adi);
	gtk_adi_cmd_set_close_buttons (self);
}

void 
gtk_adi_cmd_new_h_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_user_add_child_with_layout (self->adi,
										GTK_ADI_VERTICAL );
	gtk_adi_cmd_set_close_buttons (self);
}

void 
gtk_adi_cmd_new_v_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_user_add_child_with_layout (self->adi,
										GTK_ADI_HORIZONTAL );
	gtk_adi_cmd_set_close_buttons (self);
}

void 
gtk_adi_cmd_close_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_remove_current_child (self->adi);
	gtk_adi_cmd_set_close_buttons (self);
}

void 
gtk_adi_cmd_close_all_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_remove_all_children (self->adi);
	gtk_adi_cmd_set_close_buttons (self);
}

void 
gtk_adi_cmd_next_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_set_next_child (self->adi);
	gtk_adi_cmd_set_nav_buttons (self);
}

void 
gtk_adi_cmd_prev_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_set_previous_child (self->adi);
	gtk_adi_cmd_set_nav_buttons (self);
}

void 
gtk_adi_cmd_tile_h_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));

	g_message ( "Not implemented." );
}

void 
gtk_adi_cmd_tile_v_clicked (GtkAdiCmd * self, gpointer user_data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));

	g_message ( "Not implemented." );
}

void 
gtk_adi_cmd_mode_changed (GtkAdiCmd * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_change_mode (self->adi, mode);
	if ( self->toolbar ) {
		gtk_adi_toolbar_mode_set (self->toolbar, mode);
	}
	if ( self->menu ) {
		gtk_adi_menu_mode_set (self->menu, mode);
	}
}

void 
gtk_adi_cmd_view_changed (GtkAdiCmd *self, GtkAdiViewType view)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_change_view (self->adi, view);
	gtk_adi_cmd_set_view (self, view);
}

void
gtk_adi_cmd_set_view (GtkAdiCmd *self, GtkAdiViewType view)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));

	if ( self->toolbar ) {
		gtk_adi_toolbar_view_set (self->toolbar, view);
	}
	if ( self->menu ) {
//		gtk_adi_menu_view_set (self->menu, view);
	}
}

void 
gtk_adi_cmd_fix_toggled (GtkAdiCmd * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_CMD (self));
	
	gtk_adi_change_state (self->adi, state);
	if ( self->toolbar ) {
		gtk_adi_toolbar_fix_set (self->toolbar, state);
	}
	if ( self->menu ) {
		gtk_adi_menu_fix_set (self->menu, state);
	}
}
