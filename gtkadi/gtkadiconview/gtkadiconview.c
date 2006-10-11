/* GTK ADI Library
 * gtkadiconview.c: ADI Container View
 * Copyright (C) 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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
 * $Id: gtkadiconview.c 123 2006-07-13 11:03:59Z zoleo $
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef NEWHILDON_SUPPORT
#include<hildon-widgets/hildon-window.h>
#include<hildon-widgets/hildon-program.h>
#endif


#include "gtkadiconview.h"
#define ADI_DO_TRACE
#include "gtkadiutils.h"

enum {
    ADI_FOCUS_CHILD,
    ADI_CLOSE_CHILD,
    LAST_SIGNAL
};

static gint gtk_adi_con_view_signals[LAST_SIGNAL] = {0};

/* here are local prototypes */
static void gtk_adi_con_view_class_init (GtkAdiConViewClass *c);
static void gtk_adi_con_view_init (GtkAdiConView *self);
static void gtk_adi_con_view_iface_init (GtkAdiViewIface *iface);
static void gtk_adi_con_view_remove_child_notify (GtkAdiView *self,
                                      GtkWidget *child);
static void gtk_adi_con_view_get_child_data (GtkAdiChildData *data,
                                             GtkAdiContainer *c);
static GtkAdiContainer* gtk_adi_con_view_find_child (GtkAdiView *self,
                                                     GtkWidget *widget);

static gint gtk_adi_con_view_find_widget (gconstpointer a, gconstpointer b);
static gint gtk_adi_con_view_find_container (gconstpointer a, gconstpointer b);
static gint gtk_adi_con_view_find_window (gconstpointer a, gconstpointer b);
static void gtk_adi_con_view_set_current_container (GtkAdiView *self, GtkAdiContainer* c);
/* pointer to the class of our parent */
static GtkEventBoxClass *parent_class = NULL;

GType
gtk_adi_con_view_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiConViewClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_con_view_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiConView),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_con_view_init,
			NULL
		};

		static const GInterfaceInfo Gtk_Adi_View_info = {
			(GInterfaceInitFunc) gtk_adi_con_view_iface_init,
			NULL,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_EVENT_BOX, "GtkAdiConView", &info, (GTypeFlags)0);
		g_type_add_interface_static (type,
			GTK_TYPE_ADI_VIEW,
			&Gtk_Adi_View_info);
	}

	return type;
}

static void
gtk_adi_con_view_finalize(GObject *obj_self)
{
	GtkAdiConView *self = GTK_ADI_CON_VIEW (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) {
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
	}
	
	if(self->containers) {
		g_list_free(self->containers);
		self->containers = NULL;
	}
}

static void 
gtk_adi_con_view_class_init (GtkAdiConViewClass *c)
{
	GObjectClass *g_object_class = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_EVENT_BOX);
	
	g_object_class->finalize = gtk_adi_con_view_finalize;

        gtk_adi_con_view_signals[ADI_CLOSE_CHILD]
    	    = g_signal_new (ADI_CLOSE_CHILD_S,
                        G_TYPE_FROM_CLASS (c),
                        G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                        G_STRUCT_OFFSET (GtkAdiConViewClass, close_child),
                        NULL, NULL,
                        g_cclosure_marshal_VOID__OBJECT,
                        G_TYPE_NONE, 1, GTK_TYPE_WIDGET);

        gtk_adi_con_view_signals[ADI_FOCUS_CHILD]
    	    = g_signal_new (ADI_FOCUS_CHILD_S,
                        G_TYPE_FROM_CLASS (c),
                        G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                        G_STRUCT_OFFSET (GtkAdiConViewClass, focus_child),
                        NULL, NULL,
                        g_cclosure_marshal_VOID__OBJECT,
                        G_TYPE_NONE, 1, GTK_TYPE_WIDGET);

}

static void 
gtk_adi_con_view_init (GtkAdiConView *self)
{
	self->containers = NULL;
	self->current = NULL;
}


static void
gtk_adi_con_view_iface_init (GtkAdiViewIface *iface)
{
	iface->get_layout = gtk_adi_con_view_get_layout;
	iface->set_layout = gtk_adi_con_view_set_layout;
	iface->add_child_with_data = gtk_adi_con_view_add_child_with_data;
	iface->add_child_with_layout = gtk_adi_con_view_add_child_with_layout;
	iface->set_current_child = gtk_adi_con_view_set_current_child;
	iface->set_current_widget = gtk_adi_con_view_set_current_widget;
	iface->remove_child = gtk_adi_con_view_remove_child;
	iface->can_previous_child = gtk_adi_con_view_can_previous_child;
	iface->can_next_child = gtk_adi_con_view_can_next_child;
	iface->can_tile_h = gtk_adi_con_view_can_tile_h;
	iface->can_tile_v = gtk_adi_con_view_can_tile_v;
	iface->has_children = gtk_adi_con_view_has_children;
	iface->can_exit = gtk_adi_con_view_can_exit;
	iface->remove_current_child = gtk_adi_con_view_remove_current_child;
	iface->get_current_child_data = gtk_adi_con_view_get_current_child_data;
	iface->get_first_child_data = gtk_adi_con_view_get_first_child_data;
	iface->remove_all_children = gtk_adi_con_view_remove_all_children;
	iface->set_previous_child = gtk_adi_con_view_set_previous_child;
	iface->set_next_child = gtk_adi_con_view_set_next_child;
	iface->change_mode = gtk_adi_con_view_change_mode;
	iface->change_state = gtk_adi_con_view_change_state;
	iface->change_color = gtk_adi_con_view_change_color;
	iface->set_child_title_text = gtk_adi_con_view_set_child_title_text;
	iface->set_child_icon = gtk_adi_con_view_set_child_icon;
	iface->set_child_close_button = gtk_adi_con_view_set_child_close_button;
	iface->set_child_tab = gtk_adi_con_view_set_child_tab;
	iface->get_childs_count = gtk_adi_con_view_get_childs_count;
	iface->need_window = gtk_adi_con_view_need_window;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiConView *)g_object_new(gtk_adi_con_view_get_type(), NULL))

GtkWidget* 
gtk_adi_con_view_new (GtkAdi* adi)
{	
	GtkWidget *self = GTK_WIDGET(GET_NEW);
	GTK_ADI_CON_VIEW(self)->adi = adi;
	return self;
}

GtkAdiLayout 
gtk_adi_con_view_get_layout (GtkAdiView *self)
{
	/*TBD*/
	return 0;
}

void
gtk_adi_con_view_set_layout (GtkAdiView *self, GtkAdiLayout layout)
{
	/*TBD*/
}

void
gtk_adi_con_view_add_child_with_data (GtkAdiView *self,
                                      GtkAdiChildData *data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (data != NULL);

	gtk_adi_con_view_add_child_with_layout(self, data->widget, data->icon, data->title, data->layout);
	gtk_adi_con_view_set_child_close_button(self, data->widget, data->show_close);
}

static gboolean
gtk_adi_con_view_child_event_focus_in (GtkWidget *window,
                                       GdkEventFocus *event,
                                       GtkAdiView *self)
{
	GList* last = NULL;

	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
		
	last = g_list_find_custom (GTK_ADI_CON_VIEW(self)->containers,
							   window,
							   gtk_adi_con_view_find_window);

	if (last) {
		GTK_ADI_CON_VIEW(self)->current = (GtkAdiContainer*) last->data;
	}

	return FALSE;
}

static gboolean
gtk_adi_con_view_child_event_delete (GtkWidget *window,
                                     GdkEvent *event,
                                     GtkAdiView *self)
{
	GList* last = NULL;

	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
		
	last = g_list_find_custom (GTK_ADI_CON_VIEW(self)->containers,
							   window,
							   gtk_adi_con_view_find_window);

	if (last && last->data) {
		/* Not optimized! */
		gtk_adi_con_view_remove_child(self, ((GtkAdiContainer*)last->data)->container, TRUE);
	}

	return FALSE;
}

static void
gtk_adi_con_view_child_event_destroy (GtkWidget *widget, GtkAdiView *self)
{
	if (gtk_adi_con_view_can_exit (self)) {
			//gtk_main_quit ();
	}
}

void 
gtk_adi_con_view_add_child_with_layout (GtkAdiView *self,
                                        GtkWidget *widget,
                                        GdkPixbuf *icon,
                                        const gchar *title,
                                        GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	ADI_TRACE("%s", __FUNCTION__);	
	
	if (GTK_ADI_CON_VIEW(self)->adi &&
		GTK_ADI(GTK_ADI_CON_VIEW(self)->adi)->win_func) {
		/* 0. Create data element. */
		GtkAdiContainer* c = g_new0 (GtkAdiContainer, 1);
		/* 1. Get parent container. */
		c->container = (GtkWidget*)( GTK_ADI(GTK_ADI_CON_VIEW(self)->adi)->win_func (GTK_ADI_CON_VIEW(self)->adi));
		if (!c->container) {
			g_free (c);
		}
		else {
			/* 2. Get parent window. */
			c->window = gtk_widget_get_toplevel (c->container);
			if (!c->window) {
				g_free (c);
			}
			else {
				//GtkWidget *old_window = gtk_widget_get_toplevel (GTK_WIDGET(self));
				g_signal_connect (c->window, "focus-in-event",
							  G_CALLBACK (gtk_adi_con_view_child_event_focus_in),
							  self);
				g_signal_connect (c->window, "delete-event",
							  G_CALLBACK (gtk_adi_con_view_child_event_delete),
							  self);
				g_signal_connect (c->window, "destroy",
							  G_CALLBACK (gtk_adi_con_view_child_event_destroy),
							  self);
				//if (old_window) {
					/* 3. Get window size. */
				//	gint width = 0;
				//	gint height = 0;
				//	gtk_window_get_size (GTK_WINDOW (old_window), &width, &height);
					/* 4. Set window size. */
				//	gtk_widget_set_size_request (c->window, width, height);
				//}
				/* 5. Set window icon. */
				gtk_window_set_icon (GTK_WINDOW (c->window), icon);
				if (title) {
					/* 6. Set window title. */
					gtk_window_set_title (GTK_WINDOW (c->window), title);
				}
				/* 7. Add child. */
				c->widget = widget;
				c->layout = layout;
				c->show_close = TRUE; /* Need fix? */
				gtk_container_add (GTK_CONTAINER(c->container), c->widget);
				GTK_ADI_CON_VIEW(self)->current = c;
				GTK_ADI_CON_VIEW(self)->containers = g_list_append(
									GTK_ADI_CON_VIEW(self)->containers,
									c);
				gtk_widget_show_all (c->window);
			}
		}
	}
}

void 
gtk_adi_con_view_set_current_child (GtkAdiView *self, GtkWidget *child)
{
	/*TBD*/
}

void 
gtk_adi_con_view_set_current_widget (GtkAdiView *self, GtkWidget *widget)
{
	gtk_adi_con_view_set_current_container (self,
		                                    gtk_adi_con_view_find_child(self, widget));
}

void 
gtk_adi_con_view_remove_child (GtkAdiView *self,
	                           GtkWidget *child,
	                           gboolean destroy)
{
	GtkAdiContainer* c = NULL;

	GList* last = NULL;
	
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (child != NULL);
	
	last = g_list_find_custom (GTK_ADI_CON_VIEW(self)->containers,
							   child,
							   gtk_adi_con_view_find_container);

	if (last) {
		c = (GtkAdiContainer*) last->data;
	}
	
	if(!destroy) {
		// TBD gtk_adi_child_remove_widget(GTK_ADI_CHILD(child));
	}
	
	GTK_ADI_CON_VIEW(self)->containers = g_list_remove (GTK_ADI_CON_VIEW(self)->containers,
													    c);
	if ( c == GTK_ADI_CON_VIEW(self)->current ) {
		last = g_list_last (GTK_ADI_CON_VIEW(self)->containers);
		if ( last != NULL ) {
			gtk_adi_con_view_set_current_container (self, (GtkAdiContainer*) last->data);
		}
		else {
			gtk_adi_con_view_set_current_container (self, NULL);
		}
	}
	/* Close window and free data. */
	if (c) {
		if(!destroy) {
			gtk_container_remove ( GTK_CONTAINER(((GtkAdiContainer*) c)->container), ((GtkAdiContainer*) c)->widget );
		}
		gtk_widget_destroy ( ((GtkAdiContainer*) c)->window);
		g_free (c);
		c = NULL;
	}
	if ( GTK_ADI_CON_VIEW(self)->containers == NULL ) {
		GTK_ADI_CON_VIEW(self)->current = NULL;
	}
}

void gtk_adi_con_view_get_current_child_data (GtkAdiView *self,
                                              GtkAdiChildData *data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	gtk_adi_con_view_get_child_data(data, GTK_ADI_CON_VIEW(self)->current);
}

void gtk_adi_con_view_get_first_child_data (GtkAdiView *self,
                                            GtkAdiChildData *data)
{
	GList* first = NULL;
	
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	if (GTK_ADI_CON_VIEW(self)->containers != NULL) {
		first = g_list_first (GTK_ADI_CON_VIEW(self)->containers);
		if (first != NULL && first->data != NULL) {
			gtk_adi_con_view_get_child_data(data, (GtkAdiContainer*) (first->data));
		}
	}
}

gboolean 
gtk_adi_con_view_can_previous_child (GtkAdiView * self)
{
	GList *cur = NULL;

	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
	
	cur = g_list_find (GTK_ADI_CON_VIEW(self)->containers,
					   GTK_ADI_CON_VIEW(self)->current);

	return ( g_list_previous (cur) != NULL );
}

gboolean 
gtk_adi_con_view_can_next_child (GtkAdiView * self)
{
	GList *cur = NULL;

	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
	
	cur = g_list_find (GTK_ADI_CON_VIEW(self)->containers,
					   GTK_ADI_CON_VIEW(self)->current);

	return ( g_list_next (cur) != NULL );
}

gboolean 
gtk_adi_con_view_can_tile_h (GtkAdiView * self)
{
	/*TBD*/
	return FALSE;
}

gboolean 
gtk_adi_con_view_can_tile_v (GtkAdiView * self)
{
	/*TBD*/
	return FALSE;
}

gboolean 
gtk_adi_con_view_has_children (GtkAdiView *self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
	
	return ( GTK_ADI_CON_VIEW(self)->current != NULL );
}

gboolean 
gtk_adi_con_view_can_exit (GtkAdiView *self)
{
	return ( ! gtk_adi_con_view_has_children (self) );
}

void 
gtk_adi_con_view_remove_current_child (GtkAdiView *self, gboolean destroy)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	if ( GTK_ADI_CON_VIEW(self)->current != NULL ) {
		
		gtk_adi_view_remove_child (self,
								   (GtkWidget*) GTK_ADI_CON_VIEW(self)->current->container,
		                           destroy);
	}
}

void 
gtk_adi_con_view_remove_all_children (GtkAdiView *self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));

	while ( GTK_ADI_CON_VIEW(self)->current != NULL ) {
		gtk_adi_view_remove_child (self,
								   (GtkWidget*) GTK_ADI_CON_VIEW(self)->current->container, TRUE);
	}
}

void 
gtk_adi_con_view_set_previous_child (GtkAdiView * self)
{
	GList* cur  = NULL;
	GList* list = NULL;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	cur  = g_list_find (GTK_ADI_CON_VIEW(self)->containers,
						GTK_ADI_CON_VIEW(self)->current);
	list = g_list_previous (cur);

	if (list != NULL) {
		gtk_adi_con_view_set_current_container (self, (GtkAdiContainer*) list->data);
	}
}

void 
gtk_adi_con_view_set_next_child (GtkAdiView * self)
{
	GList* cur  = NULL;
	GList* list = NULL;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	cur  = g_list_find (GTK_ADI_CON_VIEW(self)->containers,
						GTK_ADI_CON_VIEW(self)->current);
	list = g_list_next (cur);

	if (list != NULL) {
		gtk_adi_con_view_set_current_container (self, (GtkAdiContainer*) list->data);
	}
}

void 
gtk_adi_con_view_change_mode (GtkAdiView * self, GtkAdiMode mode)
{
	/*TBD*/
}

void 
gtk_adi_con_view_change_state (GtkAdiView * self, GtkAdiState state)
{
	/*TBD*/
}

void 
gtk_adi_con_view_change_color (GtkAdiView * self, GtkAdiColorType color)
{
	/*TBD*/
}

void
gtk_adi_con_view_set_child_title_text (GtkAdiView *self, GtkWidget *widget,
								       const gchar *title_text)
{
	GtkAdiContainer* child = gtk_adi_con_view_find_child(self, widget);
	if (child && child->window) {
		gtk_window_set_title(GTK_WINDOW(child->window), title_text);
	}
}

void
gtk_adi_con_view_set_child_icon (GtkAdiView *self, GtkWidget *widget,
								       const GdkPixbuf * icon)
{
	GtkAdiContainer* child = gtk_adi_con_view_find_child(self, widget);
	if (child && child->window) {
		gtk_window_set_icon(GTK_WINDOW(child->window), (GdkPixbuf *) icon);
	}
}

void
gtk_adi_con_view_set_child_close_button (GtkAdiView *self, GtkWidget *widget,
								         gboolean enabled)
{
	/*TBD*/
}

void gtk_adi_con_view_set_child_tab (GtkAdiView *self,
                                     GtkWidget *widget,
                                     gboolean enabled)
{
	/*TBD*/
}

static void 
gtk_adi_con_view_remove_child_notify (GtkAdiView *self,
                                      GtkWidget *child)
{
	/*TBD*/
}

static void
gtk_adi_con_view_get_child_data (GtkAdiChildData *data,
                                 GtkAdiContainer *c)
{
	g_return_if_fail (data != NULL);
	if (c) {
		/* Set data. */
		data->child = c->container;
		data->widget = c->widget;
		data->icon = gtk_window_get_icon(GTK_WINDOW(c->window));
		data->title = gtk_window_get_title(GTK_WINDOW(c->window));
		data->layout = c->layout;
		data->show_close = c->show_close;
	}
}

gint
gtk_adi_con_view_get_childs_count (GtkAdiView *self)
{
    g_return_val_if_fail (self != NULL, 0);
    g_return_val_if_fail (GTK_IS_ADI_VIEW (self), 0);
    
    return g_list_length(GTK_ADI_CON_VIEW(self)->containers);
}

static GtkAdiContainer*
gtk_adi_con_view_find_child (GtkAdiView *self, GtkWidget *widget)
{
	GtkAdiContainer* child = NULL;
	
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_CON_VIEW (self), NULL);
	
	if (widget) {
		if (GTK_ADI_CON_VIEW(self)->current &&
			(GTK_ADI_CON_VIEW(self)->current)->widget == widget)
			{
				child = GTK_ADI_CON_VIEW(self)->current;
			}
			else
			{
				GList* list = NULL;
				list = g_list_find_custom (GTK_ADI_CON_VIEW(self)->containers,
				                           widget,
										   gtk_adi_con_view_find_widget);
				if (list != NULL) {
					child = (GtkAdiContainer*) (list->data);
				}
			}
	}
	
	return child;
}

static gint 
gtk_adi_con_view_find_widget (gconstpointer a, gconstpointer b)
{
	if (a && b && ((GtkAdiContainer*)(a))->widget == GTK_WIDGET(b)) {
		return 0;
	}
	return 1;
}

static gint 
gtk_adi_con_view_find_container (gconstpointer a, gconstpointer b)
{
	if (a && b && ((GtkAdiContainer*)(a))->container == GTK_WIDGET(b)) {
		return 0;
	}
	return 1;
}

static gint 
gtk_adi_con_view_find_window (gconstpointer a, gconstpointer b)
{
	if (a && b && ((GtkAdiContainer*)(a))->window == GTK_WIDGET(b)) {
		return 0;
	}
	return 1;
}

static void 
gtk_adi_con_view_set_current_container (GtkAdiView *self, GtkAdiContainer* c)
{
	g_return_if_fail (self != NULL);

	GTK_ADI_CON_VIEW(self)->current = c;
	
	if (c && c->window) {
		gtk_window_present(GTK_WINDOW(c->window));
	}
}

gboolean
gtk_adi_con_view_need_window (GtkAdiView *self)
{
    return FALSE;
}
