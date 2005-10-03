/* GTK ADI Library
 * gtkadiboxview.c: ADI Box View
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

#include "gtkadiboxview.h"
#include "gtkadichild.h"

/* here are local prototypes */
static void gtk_adi_box_view_class_init (GtkAdiBoxViewClass * c) G_GNUC_UNUSED;
static void gtk_adi_box_view_set_space (void) G_GNUC_UNUSED;
static void gtk_adi_box_view_init (GtkAdiBoxView * self) G_GNUC_UNUSED;
static GSList * gtk_adi_box_view_get_group (GtkAdiBoxView * self) G_GNUC_UNUSED;
static GtkWidget * gtk_adi_box_view_create_child (GtkAdiBoxView * self, GtkWidget * widget, GdkPixbuf * icon, const gchar * title) G_GNUC_UNUSED;
static GtkWidget * gtk_adi_box_view_create_container (GtkAdiBoxView * self, GtkAdiLayout layout, GtkAdiMode mode) G_GNUC_UNUSED;
static GtkWidget * gtk_adi_box_view_change_container (GtkAdiBoxView * self, GtkWidget * old_container, GtkAdiMode mode) G_GNUC_UNUSED;
static void gtk_adi_box_view_set_child (GtkWidget * container, GtkWidget * child, GtkAdiMode mode, guint n) G_GNUC_UNUSED;
static GtkWidget * gtk_adi_box_view_get_child (GtkWidget * container, guint n) G_GNUC_UNUSED;
static void gtk_adi_box_view_set_child_mode (gpointer data, gpointer user_data) G_GNUC_UNUSED;
static void gtk_adi_box_view_set_child_color (gpointer data, gpointer user_data) G_GNUC_UNUSED;
static void gtk_adi_box_view_set_child_state (gpointer data, gpointer user_data) G_GNUC_UNUSED;
static gint gtk_adi_box_view_find_widget (gconstpointer a, gconstpointer b) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static GtkEventBoxClass *parent_class = NULL;

/* Short form macros */
#define self_set_space gtk_adi_box_view_set_space
#define self_new gtk_adi_box_view_new
#define self_get_group gtk_adi_box_view_get_group
#define self_create_child gtk_adi_box_view_create_child
#define self_create_container gtk_adi_box_view_create_container
#define self_change_container gtk_adi_box_view_change_container
#define self_set_child gtk_adi_box_view_set_child
#define self_get_child gtk_adi_box_view_get_child
#define self_set_child_mode gtk_adi_box_view_set_child_mode
#define self_set_child_color gtk_adi_box_view_set_child_color
#define self_set_child_state gtk_adi_box_view_set_child_state
#define self_find_widget gtk_adi_box_view_find_widget
#define self_activate_child gtk_adi_box_view_activate_child
#define self_get_layout gtk_adi_box_view_get_layout
#define self_add_child_with_layout gtk_adi_box_view_add_child_with_layout
#define self_set_current_child gtk_adi_box_view_set_current_child
#define self_remove_child gtk_adi_box_view_remove_child
#define self_can_previous_child gtk_adi_box_view_can_previous_child
#define self_can_next_child gtk_adi_box_view_can_next_child
#define self_can_tile_h gtk_adi_box_view_can_tile_h
#define self_can_tile_v gtk_adi_box_view_can_tile_v
#define self_has_children gtk_adi_box_view_has_children
#define self_remove_current_child gtk_adi_box_view_remove_current_child
#define self_remove_all_children gtk_adi_box_view_remove_all_children
#define self_set_previous_child gtk_adi_box_view_set_previous_child
#define self_set_next_child gtk_adi_box_view_set_next_child
#define self_change_mode gtk_adi_box_view_change_mode
#define self_change_state gtk_adi_box_view_change_state
#define self_change_color gtk_adi_box_view_change_color


static void
___Gtk_Adi_View_init (GtkAdiViewIface *iface)
{
	iface->get_layout = self_get_layout;
	iface->add_child_with_layout = self_add_child_with_layout;
	iface->set_current_child = self_set_current_child;
	iface->remove_child = self_remove_child;
	iface->can_previous_child = self_can_previous_child;
	iface->can_next_child = self_can_next_child;
	iface->can_tile_h = self_can_tile_h;
	iface->can_tile_v = self_can_tile_v;
	iface->has_children = self_has_children;
	iface->remove_current_child = self_remove_current_child;
	iface->remove_all_children = self_remove_all_children;
	iface->set_previous_child = self_set_previous_child;
	iface->set_next_child = self_set_next_child;
	iface->change_mode = self_change_mode;
	iface->change_state = self_change_state;
	iface->change_color = self_change_color;
}

GType
gtk_adi_box_view_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiBoxViewClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_box_view_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiBoxView),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_box_view_init,
			NULL
		};

		static const GInterfaceInfo Gtk_Adi_View_info = {
			(GInterfaceInitFunc) ___Gtk_Adi_View_init,
			NULL,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_EVENT_BOX, "GtkAdiBoxView", &info, (GTypeFlags)0);
		g_type_add_interface_static (type,
			GTK_TYPE_ADI_VIEW,
			&Gtk_Adi_View_info);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiBoxView *)g_object_new(gtk_adi_box_view_get_type(), NULL))

/* a function for creating a new object of our type */
#include <stdarg.h>
static GtkAdiBoxView * GET_NEW_VARG (const char *first, ...) G_GNUC_UNUSED;
static GtkAdiBoxView *
GET_NEW_VARG (const char *first, ...)
{
	GtkAdiBoxView *ret;
	va_list ap;
	va_start (ap, first);
	ret = (GtkAdiBoxView *)g_object_new_valist (gtk_adi_box_view_get_type (), first, ap);
	va_end (ap);
	return ret;
}


static void
___finalize(GObject *obj_self)
{
	GtkAdiBoxView *self G_GNUC_UNUSED = GTK_ADI_BOX_VIEW (obj_self);
	if(G_OBJECT_CLASS(parent_class)->finalize) \
		(* G_OBJECT_CLASS(parent_class)->finalize)(obj_self);
#define color (self->color)
#define VAR color
	{
	
    	if(VAR) gtk_object_destroy(VAR);
    }
	memset(&color, 0, sizeof(color));
#undef VAR
#undef color
#define children (self->children)
#define VAR children
	{
	
    	if(VAR) g_list_free(VAR);
    }
	memset(&children, 0, sizeof(children));
#undef VAR
#undef children
}

static void 
gtk_adi_box_view_class_init (GtkAdiBoxViewClass * c G_GNUC_UNUSED)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_EVENT_BOX);

	g_object_class->finalize = ___finalize;
}
static void 
gtk_adi_box_view_init (GtkAdiBoxView * self G_GNUC_UNUSED)
{
	self->color = NULL;
	self->mode = GTK_ADI_PANED;
	self->state = GTK_ADI_MOVABLE;
	self->layout = GTK_ADI_HORIZONTAL;
	self->space = 3;
	self->cur_child = NULL;
	self->children = NULL;
 {

		self->color = gtk_adi_color_new ();
		gtk_adi_box_view_set_space ();
	
 }
}


static void 
gtk_adi_box_view_set_space (void)
{
{
	
		static const gchar* style = "style \"paned\" {GtkPaned::handle_size = 3} class \"GtkPaned\" style \"paned\"";
		gtk_rc_parse_string (style);
	}}


GtkWidget * 
gtk_adi_box_view_new (void)
{
{
	
		return GTK_WIDGET(GET_NEW);
	}}

static GSList * 
gtk_adi_box_view_get_group (GtkAdiBoxView * self)
{
	g_return_val_if_fail (self != NULL, (GSList * )0);
	g_return_val_if_fail (GTK_IS_ADI_BOX_VIEW (self), (GSList * )0);
{
	
        GList* child = NULL;
        if (self->children != NULL) {
            child = g_list_last (self->children);
            if (child != NULL && child->data != NULL) {
                return gtk_adi_child_get_group(GTK_ADI_CHILD (child->data));
            }
        }
        return NULL;
	}}

static GtkWidget * 
gtk_adi_box_view_create_child (GtkAdiBoxView * self, GtkWidget * widget, GdkPixbuf * icon, const gchar * title)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI_BOX_VIEW (self), (GtkWidget * )0);
{
	
	    GtkWidget* adi_child = gtk_adi_child_new ();
	    gtk_adi_child_set_parent (GTK_ADI_CHILD(adi_child), GTK_WIDGET(self));
	    gtk_adi_child_set_group  (GTK_ADI_CHILD(adi_child), gtk_adi_box_view_get_group(self));
	    gtk_adi_child_set_color  (GTK_ADI_CHILD(adi_child), self->color);
	    gtk_adi_child_set_widget (GTK_ADI_CHILD(adi_child), widget);
	    gtk_adi_child_set_text   (GTK_ADI_CHILD(adi_child), title);
	    gtk_adi_child_set_icon   (GTK_ADI_CHILD(adi_child), icon);
		g_signal_connect_swapped ((gpointer) adi_child, "set_focus_child",
		G_CALLBACK (gtk_adi_box_view_activate_child),
		GTK_OBJECT (self));
	    return adi_child;
	}}

static GtkWidget * 
gtk_adi_box_view_create_container (GtkAdiBoxView * self, GtkAdiLayout layout, GtkAdiMode mode)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI_BOX_VIEW (self), (GtkWidget * )0);
{
	
		GtkWidget* container = NULL;
		if ( layout == GTK_ADI_VERTICAL ) {
			if ( mode == GTK_ADI_PANED ) {
				container = gtk_vpaned_new ();
			}
			else {
				container = gtk_vbox_new   ( FALSE, self->space );
			}
		}
		else {
			if ( mode == GTK_ADI_PANED ) {
				container = gtk_hpaned_new ();
			}
			else {
				container = gtk_hbox_new   ( FALSE, self->space );
			}
		}
		return container;
	}}

static GtkWidget * 
gtk_adi_box_view_change_container (GtkAdiBoxView * self, GtkWidget * old_container, GtkAdiMode mode)
{
	g_return_val_if_fail (self != NULL, (GtkWidget * )0);
	g_return_val_if_fail (GTK_IS_ADI_BOX_VIEW (self), (GtkWidget * )0);
	g_return_val_if_fail (old_container != NULL, (GtkWidget * )0);
{
	
		GtkWidget* container = NULL;
		GtkAdiLayout layout = GTK_ADI_HORIZONTAL;
		if ( mode == GTK_ADI_PANED ) {
			if ( GTK_IS_VBOX (old_container) ) {
				layout = GTK_ADI_VERTICAL;
			}
			else if ( GTK_IS_HBOX (old_container) ) {
				layout = GTK_ADI_HORIZONTAL;
			}
			else {
				container = old_container;
			}
		}
		else {
			if ( GTK_IS_VPANED (old_container) ) {
				layout = GTK_ADI_VERTICAL;
			}
			else if ( GTK_IS_HPANED (old_container) ) {
				layout = GTK_ADI_HORIZONTAL;
			}
			else {
				container = old_container;
			}
		}
		if ( container == NULL ) {
			container = gtk_adi_box_view_create_container ( self, layout, mode );
		}
		return container;
	}}

static void 
gtk_adi_box_view_set_child (GtkWidget * container, GtkWidget * child, GtkAdiMode mode, guint n)
{
	g_return_if_fail (container != NULL);
	g_return_if_fail (child != NULL);
{
	
		if ( mode == GTK_ADI_PANED && GTK_IS_PANED (container) ) {
			if ( n == 1 ) {
				gtk_paned_add1 ( GTK_PANED (container), child );
			}
			else {
				gtk_paned_add2 ( GTK_PANED (container), child );
			}
		}
		else {
			gtk_container_add ( GTK_CONTAINER (container), child );
		}
	}}

static GtkWidget * 
gtk_adi_box_view_get_child (GtkWidget * container, guint n)
{
	g_return_val_if_fail (container != NULL, (GtkWidget * )0);
{
	
		GtkWidget* child = NULL;
		GList* list  = g_list_nth ( gtk_container_get_children (
		                            GTK_CONTAINER (container) ), n - 1 );
		if ( list != NULL && list->data != NULL ) {
			child = GTK_WIDGET ( list->data );
		}
		return child;
	}}

static void 
gtk_adi_box_view_set_child_mode (gpointer data, gpointer user_data)
{
	g_return_if_fail (data != NULL);
	g_return_if_fail (user_data != NULL);
{
	
		GtkWidget     *child = GTK_WIDGET       (data);
		GtkAdiBoxView *self  = GTK_ADI_BOX_VIEW (user_data);
	
		GtkWidget* widget1       = NULL;
		GtkWidget* widget2       = NULL;
		GtkWidget *new_container = NULL;
		GtkWidget *old_container = gtk_widget_get_parent (child);
		GtkWidget *parent        = gtk_widget_get_parent (old_container);
		guint     n              = 2;
	
		gint w1 = -1, w2 = -1;
		gint h1 = -1, h2 = -1;
	
		gint pos = -1;
	
		if ( gtk_adi_box_view_get_child ( parent, n ) != old_container ) {
			n = 1;
		}
		new_container = gtk_adi_box_view_change_container ( self, old_container, self->mode );
		if ( new_container != old_container ) {
			widget1 = gtk_adi_box_view_get_child ( old_container, 1 );
			widget2 = gtk_adi_box_view_get_child ( old_container, 2 );
					
			if ( self->mode == GTK_ADI_PANED ) {
				if ( GTK_IS_VPANED (new_container) ) {
					pos = widget1->allocation.height;
				}
				else {
					pos = widget1->allocation.width;
				}
				gtk_paned_set_position ( GTK_PANED (new_container), pos );
			}
			else if ( self->state == GTK_ADI_FIXED ) {
				w1 = widget1->allocation.width;
				h1 = widget1->allocation.height;
				w2 = widget2->allocation.width;
				h2 = widget2->allocation.height;
			}
	
			gtk_widget_ref ( widget1 );
			gtk_widget_ref ( widget2 );
	
			gtk_container_remove ( GTK_CONTAINER (old_container), widget1 );
			gtk_container_remove ( GTK_CONTAINER (old_container), widget2 );
			
			gtk_adi_box_view_set_child ( new_container, widget1, self->mode, 1 );
			gtk_adi_box_view_set_child ( new_container, widget2, self->mode, 2 );
				
			gtk_widget_destroy ( old_container );
	
			gtk_widget_unref ( widget1 );
			gtk_widget_unref ( widget2 );
	
			if ( n == 1 ) {
				gtk_adi_box_view_set_child ( parent, new_container, self->mode, 1 );
			}
			else {
				gtk_adi_box_view_set_child ( parent, new_container, self->mode, 2 );
			}
	
			if ( GTK_IS_ADI_CHILD ( widget1 ) ) {
				gtk_widget_set_size_request ( widget1, w1, h1 );
			}
			if ( GTK_IS_ADI_CHILD ( widget2 ) ) {
				gtk_widget_set_size_request ( widget2, w2, h2 );
			}
		}
	}}

static void 
gtk_adi_box_view_set_child_color (gpointer data, gpointer user_data)
{
	g_return_if_fail (data != NULL);
	g_return_if_fail (user_data != NULL);
{
	
	    gtk_adi_child_set_color (GTK_ADI_CHILD(data), GTK_OBJECT(user_data));
	}}

static void 
gtk_adi_box_view_set_child_state (gpointer data, gpointer user_data)
{
	g_return_if_fail (data != NULL);
	g_return_if_fail (user_data != NULL);
{
	
		GtkWidget     *child = GTK_WIDGET       (data);
		GtkAdiBoxView *self  = GTK_ADI_BOX_VIEW (user_data);

		gint w = -1, h = -1;

		if ( self->state == GTK_ADI_FIXED ) {
			w = child->allocation.width;
			h = child->allocation.height;
		}

		gtk_widget_set_size_request ( child, w, h );
	}}

static gint 
gtk_adi_box_view_find_widget (gconstpointer a, gconstpointer b)
{
{
	
		if (a && b && GTK_ADI_CHILD(a)->box == GTK_WIDGET(b)) {
			return 0;
		}
		return 1;
	}}

void 
gtk_adi_box_view_activate_child (GtkAdiBoxView * self, GtkWidget * widget)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_VIEW (self));
	g_return_if_fail (widget != NULL);
{
	
		GList* list = NULL;
		GtkWidget* cur = GTK_ADI_CHILD(self->cur_child)->widget;
		if (cur != widget) {
			list = g_list_find_custom (self->children, widget,
                                       gtk_adi_box_view_find_widget);
			if (list != NULL) {
				gtk_adi_child_set_active(GTK_ADI_CHILD (list->data));
			}
		}
	}}

GtkAdiLayout 
gtk_adi_box_view_get_layout (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, (GtkAdiLayout )0);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), (GtkAdiLayout )0);
{
	
		return GTK_ADI_BOX_VIEW(self)->layout;
	}}

void 
gtk_adi_box_view_add_child_with_layout (GtkAdiView * self, GtkWidget * widget, GdkPixbuf * icon, const gchar * title, GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (widget != NULL);
{
	
	    GtkWidget* child         = NULL;
		GtkWidget* container     = NULL;
		GtkWidget* old_child     = GTK_ADI_BOX_VIEW(self)->cur_child;
		GtkWidget* old_container = NULL;
	
		child = gtk_adi_box_view_create_child (GTK_ADI_BOX_VIEW(self), widget, icon, title);

		if ( old_child == NULL ) {
			gtk_container_add ( GTK_CONTAINER (self), child );
		}
		else {
			old_container = gtk_widget_get_parent ( old_child );
			
			gtk_widget_ref ( old_child );
	
			gtk_container_remove ( GTK_CONTAINER (old_container), old_child );
			container = gtk_adi_box_view_create_container ( GTK_ADI_BOX_VIEW(self),
			                             layout,
			                             GTK_ADI_BOX_VIEW(self)->mode );
			gtk_container_add ( GTK_CONTAINER (old_container), container );
	
			gtk_adi_box_view_set_child ( container, old_child,
			                             GTK_ADI_BOX_VIEW(self)->mode, 1 );
			gtk_adi_box_view_set_child ( container, child    ,
			                             GTK_ADI_BOX_VIEW(self)->mode, 2 );
	
			gtk_widget_unref ( old_child );
		}
		GTK_ADI_BOX_VIEW(self)->cur_child = child;
		GTK_ADI_BOX_VIEW(self)->children = g_list_append(
		                               GTK_ADI_BOX_VIEW(self)->children,
		                               GTK_ADI_BOX_VIEW(self)->cur_child);
		gtk_widget_show_all ( GTK_WIDGET(self) );
	}}

void 
gtk_adi_box_view_set_current_child (GtkAdiView * self, GtkWidget * child)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		GTK_ADI_BOX_VIEW(self)->cur_child = child;
	}}

void 
gtk_adi_box_view_remove_child (GtkAdiView * self, GtkWidget * child)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (child != NULL);
{
	
		GtkWidget* container     = NULL;
		GtkWidget* old_child     = NULL;
		GtkWidget* old_container = NULL;
		GList* last = NULL;
		guint n = 2;
		GTK_ADI_BOX_VIEW(self)->children = g_list_remove (GTK_ADI_BOX_VIEW(self)->children,
		                                                  child);
		if ( child == GTK_ADI_BOX_VIEW(self)->cur_child ) {
			last = g_list_last (GTK_ADI_BOX_VIEW(self)->children);
			if ( last != NULL ) {
				GTK_ADI_BOX_VIEW(self)->cur_child = ((GtkWidget*) last->data);
				gtk_adi_child_set_active(GTK_ADI_CHILD (GTK_ADI_BOX_VIEW(self)->cur_child));
			}
			else {
				GTK_ADI_BOX_VIEW(self)->cur_child = NULL;
			}
		}
		container = gtk_widget_get_parent ( child );
		if ( container == GTK_WIDGET(self) ) {
			gtk_widget_destroy (child);
		}
		else {
			old_container = gtk_widget_get_parent (container);
			
			if ( gtk_adi_box_view_get_child (old_container, n) != container ) {
				n = 1;
			}
			
			old_child = gtk_adi_box_view_get_child (container, 1);
			if ( old_child == child ) {
				old_child = gtk_adi_box_view_get_child (container, 2);
			}
			
			gtk_widget_ref (old_child);
	
			gtk_container_remove (GTK_CONTAINER (container), old_child);
			
			gtk_widget_destroy (container);
	
			gtk_adi_box_view_set_child (old_container, old_child,
			                            GTK_ADI_BOX_VIEW(self)->mode, n);
	
			gtk_widget_unref (old_child);	
		}
		if ( GTK_ADI_BOX_VIEW(self)->children == NULL ) {
			GTK_ADI_BOX_VIEW(self)->cur_child = NULL;
		}
	}}

gboolean 
gtk_adi_box_view_can_previous_child (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), (gboolean )0);
{
	
		GList* cur = g_list_find (GTK_ADI_BOX_VIEW(self)->children,
		                          GTK_ADI_BOX_VIEW(self)->cur_child);
		return ( g_list_previous (cur) != NULL );
	}}

gboolean 
gtk_adi_box_view_can_next_child (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), (gboolean )0);
{
	
		GList* cur = g_list_find (GTK_ADI_BOX_VIEW(self)->children,
		                          GTK_ADI_BOX_VIEW(self)->cur_child);
		return ( g_list_next (cur) != NULL );
	}}

gboolean 
gtk_adi_box_view_can_tile_h (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), (gboolean )0);
{
	
		return ( FALSE );
	}}

gboolean 
gtk_adi_box_view_can_tile_v (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), (gboolean )0);
{
	
		return ( FALSE );
	}}

gboolean 
gtk_adi_box_view_has_children (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, (gboolean )0);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), (gboolean )0);
{
	
		return ( GTK_ADI_BOX_VIEW(self)->cur_child != NULL );
	}}

void 
gtk_adi_box_view_remove_current_child (GtkAdiView * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		if ( GTK_ADI_BOX_VIEW(self)->cur_child != NULL ) {
			gtk_adi_view_remove_child (self,
			                           GTK_ADI_BOX_VIEW(self)->cur_child);
		}
	}}

void 
gtk_adi_box_view_remove_all_children (GtkAdiView * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		while ( GTK_ADI_BOX_VIEW(self)->cur_child != NULL ) {
			gtk_adi_view_remove_child (self,
			                           GTK_ADI_BOX_VIEW(self)->cur_child);
		}
	}}

void 
gtk_adi_box_view_set_previous_child (GtkAdiView * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		GList* cur  = g_list_find (GTK_ADI_BOX_VIEW(self)->children,
		                           GTK_ADI_BOX_VIEW(self)->cur_child);
		GList* list = g_list_previous (cur);
		if (list != NULL) {
			gtk_adi_child_set_active(GTK_ADI_CHILD (list->data));
		}
	}}

void 
gtk_adi_box_view_set_next_child (GtkAdiView * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		GList* cur  = g_list_find (GTK_ADI_BOX_VIEW(self)->children,
		                           GTK_ADI_BOX_VIEW(self)->cur_child);
		GList* list = g_list_next (cur);
		if (list != NULL) {
			gtk_adi_child_set_active(GTK_ADI_CHILD (list->data));
		}
	}}

void 
gtk_adi_box_view_change_mode (GtkAdiView * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		if ( GTK_ADI_BOX_VIEW(self)->mode != mode ) {
			GTK_ADI_BOX_VIEW(self)->mode = mode;
			g_list_foreach (GTK_ADI_BOX_VIEW(self)->children,
			                gtk_adi_box_view_set_child_mode,
							self);
			gtk_widget_show_all (GTK_WIDGET(self));
		}
	}}

void 
gtk_adi_box_view_change_state (GtkAdiView * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		if ( GTK_ADI_BOX_VIEW(self)->state != state ) {
			GTK_ADI_BOX_VIEW(self)->state = state;
			g_list_foreach (GTK_ADI_BOX_VIEW(self)->children,
			                gtk_adi_box_view_set_child_state,
							self);
		}
	}}

void 
gtk_adi_box_view_change_color (GtkAdiView * self, GtkAdiColorType color)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
{
	
		if ( GTK_ADI_BOX_VIEW(self)->color != NULL &&
             GTK_ADI_COLOR(GTK_ADI_BOX_VIEW(self)->color)->type != color ) {
			gtk_adi_color_set (GTK_ADI_COLOR(GTK_ADI_BOX_VIEW(self)->color), color);
			g_list_foreach (GTK_ADI_BOX_VIEW(self)->children,
			                gtk_adi_box_view_set_child_color,
							GTK_ADI_BOX_VIEW(self)->color);
		}
	}}
