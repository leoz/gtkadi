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
#include "gtkadiutils.h"
#include "gtkadicmd.h"
#include "gtkadistock.h"
#include "gtkadiboxview.h"
#include "gtkaditabview.h"

#include <memory.h>

/* here are local prototypes */
static void gtk_adi_class_init (GtkAdiClass * c);
static void gtk_adi_init (GtkAdi * self);

/* pointer to the class of our parent */
static GtkEventBoxClass *parent_class = NULL;

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

#define ADI_TRACE_FINALIZE(msg) ADI_TRACE("ADI finalize: %s", msg)

static void
gtk_adi_finalize(GObject *obj_self)
{
	GtkAdi *self G_GNUC_UNUSED = GTK_ADI (obj_self);
	
	ADI_TRACE_FINALIZE("begin");
	
	if(G_OBJECT_CLASS(parent_class)->finalize) {
		ADI_TRACE_FINALIZE("parent");
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
	}

	if (self->cur_view) {
		ADI_TRACE_FINALIZE("current");
		if (GTK_IS_WIDGET(self->cur_view)) {
			gtk_container_remove (GTK_CONTAINER (self), self->cur_view);
		}
		self->cur_view = NULL;
	}

	if(self->cmd) {
		ADI_TRACE_FINALIZE("cmd");
		if (GTK_IS_WIDGET(self->cmd)) {
			gtk_object_destroy(self->cmd);
		}
		self->cmd = NULL;
	}
	
	if(self->box_view) {
		ADI_TRACE_FINALIZE("box view");
		if (GTK_IS_WIDGET(self->box_view)) {
			gtk_widget_destroy(self->box_view);
		}
		self->box_view = NULL;
	}
	
	if(self->tab_view) {
		ADI_TRACE_FINALIZE("tab view");
		if (GTK_IS_WIDGET(self->tab_view)) {
			gtk_widget_destroy(self->tab_view);
		}
		self->tab_view = NULL;
	}
	
	ADI_TRACE_FINALIZE("end");
}

static void 
gtk_adi_class_init (GtkAdiClass * c)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_EVENT_BOX);

	g_object_class->finalize = gtk_adi_finalize;
}

static void 
gtk_adi_init (GtkAdi * self)
{
	self->child_func = NULL;
	self->icon_func = NULL;
	self->title_func = NULL;
	self->cmd = NULL;
	self->box_view = NULL;
	self->tab_view = NULL;
	self->cur_view = NULL;

	gtk_adi_stock_init ();
	self->cmd = gtk_adi_cmd_new (self);
	self->box_view = gtk_adi_box_view_new ();
	self->tab_view = gtk_adi_tab_view_new ();

	gtk_widget_ref(self->box_view);
	gtk_widget_ref(self->tab_view);

	self->cur_view = self->box_view;
	gtk_container_add (GTK_CONTAINER (self), self->cur_view);
	gtk_widget_unref(self->cur_view);
}

GtkWidget * 
gtk_adi_new (void)
{
	return GTK_WIDGET(GET_NEW);
}

void 
gtk_adi_set_child_func (GtkAdi * self, GtkAdiCreateChildFunc child_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	self->child_func = child_func;
}

void 
gtk_adi_set_icon_func (GtkAdi * self, GtkAdiCreateIconFunc icon_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	self->icon_func = icon_func;
}

void 
gtk_adi_set_title_func (GtkAdi * self, GtkAdiCreateTitleFunc title_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	self->title_func = title_func;
}

GtkWidget * 
gtk_adi_create_toolbar (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (GtkWidget * )0);
	
	GtkWidget* toolbar = NULL;
	if ( self->cmd ) {
		toolbar = GTK_WIDGET(gtk_adi_cmd_create_toolbar (GTK_ADI_CMD(self->cmd)));
	}
	return toolbar;
}

GtkWidget * 
gtk_adi_create_menu (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (GtkWidget * )0);
	
	GtkWidget* menu = NULL;
	if ( self->cmd ) {
		menu = GTK_WIDGET(gtk_adi_cmd_create_menu (GTK_ADI_CMD(self->cmd)));
	}
	return menu;
}

void
gtk_adi_add (GtkAdi *self, GtkWidget *widget)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	g_return_if_fail (widget != NULL);
	
	gtk_adi_view_add_child_with_layout(GTK_ADI_VIEW(
										   self->cur_view),
										   widget,
	                                       NULL,
										   NULL,
	          gtk_adi_view_get_layout (GTK_ADI_VIEW(GTK_ADI(self)->cur_view)));
}

void 
gtk_adi_user_add_child (GtkAdi *self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_user_add_child_with_layout (self,
	gtk_adi_view_get_layout (GTK_ADI_VIEW(self->cur_view)));
}

void 
gtk_adi_user_add_child_with_layout (GtkAdi *self, GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
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
}

gboolean 
gtk_adi_can_previous_child (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
	
	return gtk_adi_view_can_previous_child (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_can_next_child (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
	
	return gtk_adi_view_can_next_child (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_can_tile_h (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
	
	return gtk_adi_view_can_tile_h (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_can_tile_v (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
	
	return gtk_adi_view_can_tile_v (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_has_children (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI (self), (gboolean )0);
	
	return gtk_adi_view_has_children (GTK_ADI_VIEW(self->cur_view));
}

void 
gtk_adi_remove_current_child (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_remove_current_child (GTK_ADI_VIEW(self->cur_view), TRUE);
}

void 
gtk_adi_remove_all_children (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_remove_all_children (GTK_ADI_VIEW(self->cur_view));
}

void 
gtk_adi_set_previous_child (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_set_previous_child (GTK_ADI_VIEW(self->cur_view));
}

void 
gtk_adi_set_next_child (GtkAdi * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_set_next_child (GTK_ADI_VIEW(self->cur_view));
}

void 
gtk_adi_change_mode (GtkAdi * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_change_mode (GTK_ADI_VIEW(self->cur_view),mode);
}

void 
gtk_adi_change_view (GtkAdi * self, GtkAdiViewType view)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	GtkWidget* old_view = NULL;
	GtkWidget* current = NULL;
	
	/* 1. Hide current view */
	if (self->cur_view) {
		gtk_widget_hide(self->cur_view);
		gtk_widget_ref(self->cur_view);
		gtk_container_remove(GTK_CONTAINER (self), self->cur_view);
		old_view = self->cur_view;
		self->cur_view = NULL;
	}
	
	/* 2. Swap views */
	switch ( view ) {
	case GTK_ADI_VIEW_BOX:
		self->cur_view = self->box_view;
		break;
	case GTK_ADI_VIEW_TAB:
		self->cur_view = self->tab_view;
		break;
	default:
		self->cur_view = NULL;
		break;
	}
	
	/* 3. Move child windows */
	GtkAdiChildData data;
	
	if (self->cur_view && old_view) {
		ADI_TRACE_MSG("Entering change view.")
		
		memset(&data, 0, sizeof(data));
		gtk_adi_view_get_current_child_data(GTK_ADI_VIEW(old_view), &data);
		
		current = data.widget;
		
		memset(&data, 0, sizeof(data));
		gtk_adi_view_get_first_child_data(GTK_ADI_VIEW(old_view), &data);
		
		while (data.widget) {
			ADI_TRACE_MSG("Change view - iteration.")
			gtk_widget_ref (data.widget);
			data.title = g_strdup(data.title);
			gtk_adi_view_remove_child(GTK_ADI_VIEW(old_view), data.child, FALSE);
			gtk_adi_view_add_child_with_data(GTK_ADI_VIEW(self->cur_view),
			                                              &data);
			gtk_widget_unref (data.widget);
			memset(&data, 0, sizeof(data));
			gtk_adi_view_get_first_child_data(GTK_ADI_VIEW(old_view), &data);
		}
		
		if (current) {
			gtk_adi_view_set_current_widget(GTK_ADI_VIEW(self->cur_view),
			                                current);
		}
	}

	ADI_TRACE_MSG("Exit change view.")
	
	/* 4. Show current view */
	if (self->cur_view) {
		gtk_container_add(GTK_CONTAINER (self), self->cur_view);
		gtk_widget_unref(self->cur_view);
		gtk_widget_show(self->cur_view);
	}
}

void 
gtk_adi_change_state (GtkAdi *self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_change_state (GTK_ADI_VIEW(self->cur_view),state);
}

void 
gtk_adi_change_color (GtkAdi *self, GtkAdiColorType color)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_change_color (GTK_ADI_VIEW(self->cur_view),color);
}

void gtk_adi_set_child_title_text (GtkAdi *self, GtkWidget *widget,
								   const gchar *title_text)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_set_child_title_text (GTK_ADI_VIEW(self->cur_view),
	                                   widget,
	                                   title_text);
}

void gtk_adi_set_child_close_button (GtkAdi *self, GtkWidget *widget,
								     gboolean enabled)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_set_child_close_button (GTK_ADI_VIEW(self->cur_view),
	                                     widget,
	                                     enabled);
}
