/* GTK ADI Library
 * gtkadi.c: ADI Widget
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

#include "gtkadi.h"
#include "gtkadicmd.h"
#include "gtkadistock.h"
#include "gtkadiboxview.h"
#include "gtkaditabview.h"

/* here are local prototypes */
static void gtk_adi_class_init (GtkAdiClass * c) G_GNUC_UNUSED;
static void gtk_adi_init (GtkAdi * self) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static GtkEventBoxClass *parent_class = NULL;

/* Short form macros */
#define self_new gtk_adi_new
#define self_set_child_func gtk_adi_set_child_func
#define self_set_icon_func gtk_adi_set_icon_func
#define self_set_title_func gtk_adi_set_title_func
#define self_create_toolbar gtk_adi_create_toolbar
#define self_create_menu gtk_adi_create_menu
#define self_user_add_child gtk_adi_user_add_child
#define self_user_add_child_with_layout gtk_adi_user_add_child_with_layout
#define self_can_previous_child gtk_adi_can_previous_child
#define self_can_next_child gtk_adi_can_next_child
#define self_can_tile_h gtk_adi_can_tile_h
#define self_can_tile_v gtk_adi_can_tile_v
#define self_has_children gtk_adi_has_children
#define self_remove_current_child gtk_adi_remove_current_child
#define self_remove_all_children gtk_adi_remove_all_children
#define self_set_previous_child gtk_adi_set_previous_child
#define self_set_next_child gtk_adi_set_next_child
#define self_change_mode gtk_adi_change_mode
#define self_change_state gtk_adi_change_state
#define self_change_color gtk_adi_change_color
GType
gtk_adi_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdi),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_EVENT_BOX, "GtkAdi", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdi *)g_object_new(gtk_adi_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static GtkAdi * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static GtkAdi *
GET_NEW_VARG (const char *first, ...)
{
	GtkAdi *ret;
	va_list ap;
	va_start (ap, first);
	ret = (GtkAdi *)g_object_new_valist (gtk_adi_get_type (), first, ap);
	va_end (ap);
	return ret;
}


static void
___finalize(GObject *obj_self)
{
	GtkAdi *self G_GNUC_UNUSED = GTK_ADI (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
#define cmd (self->cmd)
#define VAR cmd
	{
	
    	if(VAR) gtk_object_destroy(VAR);
    }
	memset(&cmd, 0, sizeof(cmd));
#undef VAR
#undef cmd
#define box_view (self->box_view)
#define VAR box_view
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&box_view, 0, sizeof(box_view));
#undef VAR
#undef box_view
#define tab_view (self->tab_view)
#define VAR tab_view
	{
	
    	if(VAR) gtk_widget_destroy(VAR);
    }
	memset(&tab_view, 0, sizeof(tab_view));
#undef VAR
#undef tab_view
}

static void 
gtk_adi_class_init (GtkAdiClass * c G_GNUC_UNUSED)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_EVENT_BOX);

	g_object_class->finalize = ___finalize;
}
static void 
gtk_adi_init (GtkAdi * self G_GNUC_UNUSED)
{
	self->child_func = NULL;
	self->icon_func = NULL;
	self->title_func = NULL;
	self->cmd = NULL;
	self->box_view = NULL;
	self->tab_view = NULL;
	self->cur_view = NULL;
 {

		gtk_adi_stock_init ();
		self->cmd = gtk_adi_cmd_new (self);
		self->box_view = gtk_adi_box_view_new ();
		self->tab_view = gtk_adi_tab_view_new ();

		self->cur_view = self->tab_view;
        gtk_container_add (GTK_CONTAINER (self), self->cur_view);
	
 }
}



GtkWidget * 
gtk_adi_new (void)
{
{
	
        return GTK_WIDGET(GET_NEW);
	}}

void 
gtk_adi_set_child_func (GtkAdi * self, GtkAdiCreateChildFunc child_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		self->child_func = child_func;
	}}

void 
gtk_adi_set_icon_func (GtkAdi * self, GtkAdiCreateIconFunc icon_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		self->icon_func = icon_func;
	}}

void 
gtk_adi_set_title_func (GtkAdi * self, GtkAdiCreateTitleFunc title_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		self->title_func = title_func;
	}}

GtkWidget * 
gtk_adi_create_toolbar (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (GtkWidget * )0);
{
	
		GtkWidget* toolbar = NULL;
		if ( self->cmd ) {
			toolbar = GTK_WIDGET(gtk_adi_cmd_create_toolbar (GTK_ADI_CMD(self->cmd)));
		}
		return toolbar;
	}}

GtkWidget * 
gtk_adi_create_menu (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (GtkWidget * )0);
{
	
		GtkWidget* menu = NULL;
		if ( self->cmd ) {
			menu = GTK_WIDGET(gtk_adi_cmd_create_menu (GTK_ADI_CMD(self->cmd)));
		}
		return menu;
	}}

void 
gtk_adi_user_add_child (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_user_add_child_with_layout (self,
		gtk_adi_view_get_layout (GTK_ADI_VIEW(self->cur_view)));
	}}

void 
gtk_adi_user_add_child_with_layout (GtkAdi * self, GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		GtkWidget* widget = NULL;
		GdkPixbuf* icon = NULL;
		gchar* title = NULL;
		if (self->child_func && self->icon_func && self->title_func ) {
			widget = self->child_func ();
			icon = self->icon_func (widget);
			title = self->title_func ();
			gtk_adi_view_add_child_with_layout(GTK_ADI_VIEW(
			                                       self->cur_view),
			                                       widget, icon,
												   title, layout);
			g_free (title);
		}
	}}

gboolean 
gtk_adi_can_previous_child (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
{
	
		return gtk_adi_view_can_previous_child (GTK_ADI_VIEW(self->cur_view));
	}}

gboolean 
gtk_adi_can_next_child (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
{
	
		return gtk_adi_view_can_next_child (GTK_ADI_VIEW(self->cur_view));
	}}

gboolean 
gtk_adi_can_tile_h (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
{
	
		return gtk_adi_view_can_tile_h (GTK_ADI_VIEW(self->cur_view));
	}}

gboolean 
gtk_adi_can_tile_v (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
{
	
		return gtk_adi_view_can_tile_v (GTK_ADI_VIEW(self->cur_view));
	}}

gboolean 
gtk_adi_has_children (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
{
	
		return gtk_adi_view_has_children (GTK_ADI_VIEW(self->cur_view));
	}}

void 
gtk_adi_remove_current_child (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_view_remove_current_child (GTK_ADI_VIEW(self->cur_view));
	}}

void 
gtk_adi_remove_all_children (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_view_remove_all_children (GTK_ADI_VIEW(self->cur_view));
	}}

void 
gtk_adi_set_previous_child (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_view_set_previous_child (GTK_ADI_VIEW(self->cur_view));
	}}

void 
gtk_adi_set_next_child (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_view_set_next_child (GTK_ADI_VIEW(self->cur_view));
	}}

void 
gtk_adi_change_mode (GtkAdi * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_view_change_mode (GTK_ADI_VIEW(self->cur_view),mode);
	}}

void 
gtk_adi_change_state (GtkAdi * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_view_change_state (GTK_ADI_VIEW(self->cur_view),state);
	}}

void 
gtk_adi_change_color (GtkAdi * self, GtkAdiColorType color)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
{
	
		gtk_adi_view_change_color (GTK_ADI_VIEW(self->cur_view),color);
	}}