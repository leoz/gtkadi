/* GTK ADI Library
 * gtkadiwinview.c: ADI Window View
 * Copyright (C) 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "gtkadiwinview.h"
#include "gtkadiwinchild.h"
#define ADI_DO_TRACE
#include "gtkadiutils.h"

enum {
    FOCUS_CHILD,
    CLOSE_CHILD,
    LAST_SIGNAL
};

static gint gtk_adi_win_view_signals[LAST_SIGNAL] = {0};

/* here are local prototypes */
static void gtk_adi_win_view_class_init (GtkAdiWinViewClass *c);
static void gtk_adi_win_view_init (GtkAdiWinView *self);
static void gtk_adi_win_view_iface_init (GtkAdiViewIface *iface);
static void gtk_adi_win_view_get_child_data (GtkAdiView *self,
                                             GtkAdiChildData *data,
											 gint page_num);
static void gtk_adi_win_view_remove_child_notify (GtkAdiView *self,
                                      GtkWidget *child);

/* pointer to the class of our parent */
static GtkEventBoxClass *parent_class = NULL;

GType
gtk_adi_win_view_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiWinViewClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_win_view_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiWinView),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_win_view_init,
			NULL
		};

		static const GInterfaceInfo Gtk_Adi_View_info = {
			(GInterfaceInitFunc) gtk_adi_win_view_iface_init,
			NULL,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_EVENT_BOX, "GtkAdiWinView", &info, (GTypeFlags)0);
		g_type_add_interface_static (type,
			GTK_TYPE_ADI_VIEW,
			&Gtk_Adi_View_info);
	}

	return type;
}

static void 
gtk_adi_win_view_class_init (GtkAdiWinViewClass *c)
{
	parent_class = g_type_class_ref (GTK_TYPE_EVENT_BOX);
	
        gtk_adi_win_view_signals[CLOSE_CHILD]
    	    = g_signal_new ("close_child",
                        G_TYPE_FROM_CLASS (c),
                        G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                        G_STRUCT_OFFSET (GtkAdiWinViewClass, close_child),
                        NULL, NULL,
                        g_cclosure_marshal_VOID__OBJECT,
                        G_TYPE_NONE, 1, GTK_TYPE_WIDGET);

        gtk_adi_win_view_signals[FOCUS_CHILD]
    	    = g_signal_new ("focus_child",
                        G_TYPE_FROM_CLASS (c),
                        G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                        G_STRUCT_OFFSET (GtkAdiWinViewClass, focus_child),
                        NULL, NULL,
                        g_cclosure_marshal_VOID__OBJECT,
                        G_TYPE_NONE, 1, GTK_TYPE_WIDGET);

}

static void 
gtk_adi_win_view_init (GtkAdiWinView *self)
{
	self->own_widget = NULL;
}


static void
gtk_adi_win_view_iface_init (GtkAdiViewIface *iface)
{
	iface->get_layout = gtk_adi_win_view_get_layout;
	iface->set_layout = gtk_adi_win_view_set_layout;
	iface->add_child_with_data = gtk_adi_win_view_add_child_with_data;
	iface->add_child_with_layout = gtk_adi_win_view_add_child_with_layout;
	iface->set_current_child = gtk_adi_win_view_set_current_child;
	iface->set_current_widget = gtk_adi_win_view_set_current_widget;
	iface->remove_child = gtk_adi_win_view_remove_child;
	iface->can_previous_child = gtk_adi_win_view_can_previous_child;
	iface->can_next_child = gtk_adi_win_view_can_next_child;
	iface->can_tile_h = gtk_adi_win_view_can_tile_h;
	iface->can_tile_v = gtk_adi_win_view_can_tile_v;
	iface->has_children = gtk_adi_win_view_has_children;
	iface->remove_current_child = gtk_adi_win_view_remove_current_child;
	iface->get_current_child_data = gtk_adi_win_view_get_current_child_data;
	iface->get_first_child_data = gtk_adi_win_view_get_first_child_data;
	iface->remove_all_children = gtk_adi_win_view_remove_all_children;
	iface->set_previous_child = gtk_adi_win_view_set_previous_child;
	iface->set_next_child = gtk_adi_win_view_set_next_child;
	iface->change_mode = gtk_adi_win_view_change_mode;
	iface->change_state = gtk_adi_win_view_change_state;
	iface->change_color = gtk_adi_win_view_change_color;
	iface->set_child_title_text = gtk_adi_win_view_set_child_title_text;
	iface->set_child_close_button = gtk_adi_win_view_set_child_close_button;
	iface->set_child_tab = gtk_adi_win_view_set_child_tab;
	iface->get_childs_count = gtk_adi_win_view_get_childs_count;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiWinView *)g_object_new(gtk_adi_win_view_get_type(), NULL))

GtkWidget * 
gtk_adi_win_view_new (void)
{	
	return GTK_WIDGET(GET_NEW);
}

GtkAdiLayout 
gtk_adi_win_view_get_layout (GtkAdiView *self)
{
	/*TBD*/
	return 0;
}

void
gtk_adi_win_view_set_layout (GtkAdiView *self, GtkAdiLayout layout)
{
	/*TBD*/
}

void
gtk_adi_win_view_add_child_with_data (GtkAdiView *self,
                                      GtkAdiChildData *data)
{
	/*TBD*/
}

void 
gtk_adi_win_view_add_child_with_layout (GtkAdiView *self,
                                        GtkWidget *widget,
                                        GdkPixbuf *icon,
                                        const gchar *title,
                                        GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	ADI_TRACE("%s", __FUNCTION__);

	if ( !GTK_ADI_WIN_VIEW(self)->own_widget ) {
		GTK_ADI_WIN_VIEW(self)->own_widget = widget;
		gtk_container_add (GTK_CONTAINER (self),
		                   GTK_ADI_WIN_VIEW(self)->own_widget);
		gtk_widget_show_all (GTK_WIDGET(self));
	}
	else {
		GtkWidget *window;
		window = gtk_adi_win_child_new ();
		gtk_container_add (GTK_CONTAINER(window), widget);
		gtk_window_set_icon (GTK_WINDOW (window), icon);
		gtk_window_set_title (GTK_WINDOW (window), title);
		gtk_widget_show_all (window);
	}
}

void 
gtk_adi_win_view_set_current_child (GtkAdiView *self, GtkWidget *child)
{
	/*TBD*/
}

void 
gtk_adi_win_view_set_current_widget (GtkAdiView *self, GtkWidget *widget)
{
	/*TBD*/
}

void 
gtk_adi_win_view_remove_child (GtkAdiView *self,
	                           GtkWidget *child,
	                           gboolean destroy)
{
	/*TBD*/
}

static void
gtk_adi_win_view_get_child_data (GtkAdiView *self,
                                 GtkAdiChildData *data,
                                 gint page_num)
{
	/*TBD*/
}

void gtk_adi_win_view_get_current_child_data (GtkAdiView *self,
                                              GtkAdiChildData *data)
{
	/*TBD*/
}

void gtk_adi_win_view_get_first_child_data (GtkAdiView *self,
                                            GtkAdiChildData *data)
{
	/*TBD*/
}

gboolean 
gtk_adi_win_view_can_previous_child (GtkAdiView * self)
{
	/*TBD*/
	return FALSE;
}

gboolean 
gtk_adi_win_view_can_next_child (GtkAdiView * self)
{
	/*TBD*/
	return FALSE;
}

gboolean 
gtk_adi_win_view_can_tile_h (GtkAdiView * self)
{
	/*TBD*/
	return FALSE;
}

gboolean 
gtk_adi_win_view_can_tile_v (GtkAdiView * self)
{
	/*TBD*/
	return FALSE;
}

gboolean 
gtk_adi_win_view_has_children (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
	
	return (GTK_ADI_WIN_VIEW(self)->own_widget != NULL);
}

void 
gtk_adi_win_view_remove_current_child (GtkAdiView *self, gboolean destroy)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	ADI_TRACE("%s", __FUNCTION__);

	GList* list;
	GtkWidget* window = NULL;
	
	list = gtk_window_list_toplevels ();
	g_list_foreach(list, (GFunc)g_object_ref, NULL);
	list = g_list_first(list);
	while (list) {
		if (GTK_IS_ADI_WIN_CHILD(list->data)) {
			if (gtk_window_has_toplevel_focus(GTK_WINDOW(list->data))) {
				/* This case will never be executed if the function called
				   from some other window.*/
				ADI_TRACE("Delete child: %s",
						  gtk_window_get_title(GTK_WINDOW(list->data)));
				gtk_widget_destroy(GTK_WIDGET(list->data));
				window = NULL;
				break;
			}
			else {
				window = GTK_WIDGET(list->data);
			}
		}
		list = g_list_next(list);
	}
	g_list_foreach (list, (GFunc)g_object_unref, NULL);
	g_list_free (list);
	
	if (window) {
		gtk_widget_destroy(window);
		window = NULL;
	}
	else {
		if ( GTK_ADI_WIN_VIEW(self)->own_widget ) {
			gtk_container_remove (GTK_CONTAINER (self),
								  GTK_ADI_WIN_VIEW(self)->own_widget);
			GTK_ADI_WIN_VIEW(self)->own_widget = NULL;
		}
	}
}

void 
gtk_adi_win_view_remove_all_children (GtkAdiView *self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	ADI_TRACE("%s", __FUNCTION__);

	GList* list;
	
	list = gtk_window_list_toplevels ();
	g_list_foreach(list, (GFunc)g_object_ref, NULL);
	list = g_list_first(list);
	while (list) {
		if (GTK_IS_ADI_WIN_CHILD(list->data)) {
			ADI_TRACE("Delete child: %s",
			          gtk_window_get_title(GTK_WINDOW(list->data)));
			gtk_widget_destroy(GTK_WIDGET(list->data));
		}
		list = g_list_next(list);
	}
	g_list_foreach (list, (GFunc)g_object_unref, NULL);
	g_list_free (list);
	
	if ( GTK_ADI_WIN_VIEW(self)->own_widget ) {
		gtk_container_remove (GTK_CONTAINER (self),
		                      GTK_ADI_WIN_VIEW(self)->own_widget);
		GTK_ADI_WIN_VIEW(self)->own_widget = NULL;
	}
}

void 
gtk_adi_win_view_set_previous_child (GtkAdiView * self)
{
	/*TBD*/
}

void 
gtk_adi_win_view_set_next_child (GtkAdiView * self)
{
	/*TBD*/
}

void 
gtk_adi_win_view_change_mode (GtkAdiView * self, GtkAdiMode mode)
{
	/*TBD*/
}

void 
gtk_adi_win_view_change_state (GtkAdiView * self, GtkAdiState state)
{
	/*TBD*/
}

void 
gtk_adi_win_view_change_color (GtkAdiView * self, GtkAdiColorType color)
{
	/*TBD*/
}

void
gtk_adi_win_view_set_child_title_text (GtkAdiView *self, GtkWidget *widget,
								       const gchar *title_text)
{
	/*TBD*/
}

void
gtk_adi_win_view_set_child_close_button (GtkAdiView *self, GtkWidget *widget,
								         gboolean enabled)
{
	/*TBD*/
}

void gtk_adi_win_view_set_child_tab (GtkAdiView *self,
                                     GtkWidget *widget,
                                     gboolean enabled)
{
	/*TBD*/
}

static void 
gtk_adi_win_view_remove_child_notify (GtkAdiView *self,
                                      GtkWidget *child)
{
	/*TBD*/
}

gint
gtk_adi_win_view_get_childs_count (GtkAdiView *self)
{
	gint count = 0;
	
	GList* list;

	if ( GTK_ADI_WIN_VIEW(self)->own_widget ) {
		count++;
	}

	list = gtk_window_list_toplevels ();
	list = g_list_first(list);
	while (list) {
		if (GTK_IS_ADI_WIN_CHILD(list->data)) {
			count++;
		}
		list = g_list_next(list);
	}
	g_list_free (list);
	
	return count;
}
