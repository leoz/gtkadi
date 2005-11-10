/* GTK ADI Library
 * gtkaditabview.c: ADI Tab View
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "gtkaditabview.h"
#include "gtkadititle.h"

#ifdef HILDON_SUPPORT
#include <hildon-widgets/hildon-app.h>
#endif /* HILDON_SUPPORT */

enum {
    CLOSE_CHILD,
    LAST_SIGNAL
};

static gint gtk_adi_tab_view_signals[LAST_SIGNAL] = {0};

/* here are local prototypes */
static void gtk_adi_tab_view_class_init (GtkAdiTabViewClass *c);
static void gtk_adi_tab_view_init (GtkAdiTabView *self);
static void gtk_adi_tab_view_iface_init (GtkAdiViewIface *iface);
static void gtk_adi_tab_view_get_child_data (GtkAdiView *self,
                                             GtkAdiChildData *data,
											 gint page_num);
static void gtk_adi_tab_view_remove_child_notify (GtkAdiView *self,
                                      GtkWidget *child);

/* pointer to the class of our parent */
static GtkNotebookClass *parent_class = NULL;

GType
gtk_adi_tab_view_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiTabViewClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_tab_view_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiTabView),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_tab_view_init,
			NULL
		};

		static const GInterfaceInfo Gtk_Adi_View_info = {
			(GInterfaceInitFunc) gtk_adi_tab_view_iface_init,
			NULL,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_NOTEBOOK, "GtkAdiTabView", &info, (GTypeFlags)0);
		g_type_add_interface_static (type,
			GTK_TYPE_ADI_VIEW,
			&Gtk_Adi_View_info);
	}

	return type;
}

static void 
gtk_adi_tab_view_class_init (GtkAdiTabViewClass *c)
{
	parent_class = g_type_class_ref (GTK_TYPE_NOTEBOOK);
	
        gtk_adi_tab_view_signals[CLOSE_CHILD]
    	    = g_signal_new ("close_child",
                        G_TYPE_FROM_CLASS (c),
                        G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                        G_STRUCT_OFFSET (GtkAdiTabViewClass, close_child),
                        NULL, NULL,
                        g_cclosure_marshal_VOID__OBJECT,
                        G_TYPE_NONE, 1, GTK_TYPE_WIDGET);

}
static void 
gtk_adi_tab_view_init (GtkAdiTabView *self)
{
	GTK_NOTEBOOK(self)->tab_hborder = 0;
	GTK_NOTEBOOK(self)->tab_vborder = 0;

	self->layout = GTK_ADI_HORIZONTAL;

	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (self), GTK_POS_TOP);
}


static void
gtk_adi_tab_view_iface_init (GtkAdiViewIface *iface)
{
	iface->get_layout = gtk_adi_tab_view_get_layout;
	iface->set_layout = gtk_adi_tab_view_set_layout;
	iface->add_child_with_data = gtk_adi_tab_view_add_child_with_data;
	iface->add_child_with_layout = gtk_adi_tab_view_add_child_with_layout;
	iface->set_current_child = gtk_adi_tab_view_set_current_child;
	iface->set_current_widget = gtk_adi_tab_view_set_current_widget;
	iface->remove_child = gtk_adi_tab_view_remove_child;
	iface->can_previous_child = gtk_adi_tab_view_can_previous_child;
	iface->can_next_child = gtk_adi_tab_view_can_next_child;
	iface->can_tile_h = gtk_adi_tab_view_can_tile_h;
	iface->can_tile_v = gtk_adi_tab_view_can_tile_v;
	iface->has_children = gtk_adi_tab_view_has_children;
	iface->remove_current_child = gtk_adi_tab_view_remove_current_child;
	iface->get_current_child_data = gtk_adi_tab_view_get_current_child_data;
	iface->get_first_child_data = gtk_adi_tab_view_get_first_child_data;
	iface->remove_all_children = gtk_adi_tab_view_remove_all_children;
	iface->set_previous_child = gtk_adi_tab_view_set_previous_child;
	iface->set_next_child = gtk_adi_tab_view_set_next_child;
	iface->change_mode = gtk_adi_tab_view_change_mode;
	iface->change_state = gtk_adi_tab_view_change_state;
	iface->change_color = gtk_adi_tab_view_change_color;
	iface->set_child_title_text = gtk_adi_tab_view_set_child_title_text;
	iface->set_child_close_button = gtk_adi_tab_view_set_child_close_button;
	iface->set_child_tab = gtk_adi_tab_view_set_child_tab;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiTabView *)g_object_new(gtk_adi_tab_view_get_type(), NULL))

GtkWidget * 
gtk_adi_tab_view_new (void)
{	
	return GTK_WIDGET(GET_NEW);
}

GtkAdiLayout 
gtk_adi_tab_view_get_layout (GtkAdiView *self)
{
	g_return_val_if_fail (self != NULL, (GtkAdiLayout )0);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), (GtkAdiLayout )0);
	
	return GTK_ADI_TAB_VIEW(self)->layout;
}

void
gtk_adi_tab_view_set_layout (GtkAdiView *self, GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	GTK_ADI_TAB_VIEW(self)->layout = layout;

	if (layout == GTK_ADI_HORIZONTAL) {
		gtk_notebook_set_tab_pos (GTK_NOTEBOOK (self), GTK_POS_TOP);
	}
	else {
		gtk_notebook_set_tab_pos (GTK_NOTEBOOK (self), GTK_POS_LEFT);
	}
}

void
gtk_adi_tab_view_add_child_with_data (GtkAdiView *self,
                                      GtkAdiChildData *data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (data != NULL);

	gtk_adi_tab_view_add_child_with_layout(self, data->widget, data->icon, data->title, data->layout);
}

void 
gtk_adi_tab_view_add_child_with_layout (GtkAdiView * self, GtkWidget * widget, GdkPixbuf * icon, const gchar * title, GtkAdiLayout layout)
{
	gint page_num;
	GtkWidget *tab_label;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (widget != NULL);
	
	page_num = -1;
	tab_label = gtk_adi_title_new ();
	gtk_adi_title_set_layout (GTK_ADI_TITLE(tab_label), layout);
	gtk_adi_title_set_parent (GTK_ADI_TITLE(tab_label), GTK_WIDGET(self));
	gtk_adi_title_set_child  (GTK_ADI_TITLE(tab_label), widget);
	gtk_adi_title_set_text   (GTK_ADI_TITLE(tab_label), title);
	gtk_adi_title_set_icon   (GTK_ADI_TITLE(tab_label), icon);
	gtk_box_pack_start (GTK_BOX (GTK_ADI_TITLE(tab_label)->hbox),
	                    GTK_ADI_TITLE(tab_label)->label, TRUE, TRUE, 0);
	gtk_adi_title_set_text_font (GTK_ADI_TITLE(tab_label));
	gtk_widget_show_all (tab_label);
	page_num = gtk_notebook_append_page (GTK_NOTEBOOK(self),
	                                     widget, tab_label);
	gtk_widget_show_all (GTK_WIDGET(self));
	gtk_notebook_set_current_page (GTK_NOTEBOOK(self),page_num);
}

void 
gtk_adi_tab_view_set_current_child (GtkAdiView *self, GtkWidget *child)
{}

void 
gtk_adi_tab_view_set_current_widget (GtkAdiView *self, GtkWidget *widget)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (widget != NULL);

	gtk_notebook_set_current_page (GTK_NOTEBOOK(self),
	gtk_notebook_page_num (GTK_NOTEBOOK(self), widget));
}

void 
gtk_adi_tab_view_remove_child (GtkAdiView *self,
	                           GtkWidget *child,
	                           gboolean destroy)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (child != NULL);
	
	gtk_adi_tab_view_remove_child_notify(self, child);
	gtk_notebook_remove_page (GTK_NOTEBOOK(self),
	gtk_notebook_page_num (GTK_NOTEBOOK(self), child));
}

static void
gtk_adi_tab_view_get_child_data (GtkAdiView *self,
                                 GtkAdiChildData *data,
                                 gint page_num)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	g_return_if_fail (data != NULL);

	GtkWidget *tab_label = NULL;
	
	data->child = gtk_notebook_get_nth_page(GTK_NOTEBOOK(self), page_num);
	data->widget = data->child;

	if (data->widget) {
		tab_label = gtk_notebook_get_tab_label(GTK_NOTEBOOK(self), data->widget);
	
		g_return_if_fail (tab_label != NULL);
	
		data->icon = gtk_adi_title_get_icon(GTK_ADI_TITLE(tab_label));
		data->title = gtk_adi_title_get_text(GTK_ADI_TITLE(tab_label));
		data->layout = gtk_adi_title_get_layout(GTK_ADI_TITLE(tab_label));
	}
}

void gtk_adi_tab_view_get_current_child_data (GtkAdiView *self,
                                              GtkAdiChildData *data)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	gtk_adi_tab_view_get_child_data(self, data,
	                        gtk_notebook_get_current_page (GTK_NOTEBOOK(self)));
}

void gtk_adi_tab_view_get_first_child_data (GtkAdiView *self,
                                            GtkAdiChildData *data)
{
	gtk_adi_tab_view_get_child_data(self, data, 0);
}

gboolean 
gtk_adi_tab_view_can_previous_child (GtkAdiView * self)
{
	gint cur;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
	
	cur = gtk_notebook_get_current_page (GTK_NOTEBOOK(self));
	if ( cur > 0 && cur < gtk_notebook_get_n_pages (GTK_NOTEBOOK(self)) ) {
		return TRUE;
	}
	return FALSE;
}

gboolean 
gtk_adi_tab_view_can_next_child (GtkAdiView * self)
{
	gint cur;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
	
	cur = gtk_notebook_get_current_page (GTK_NOTEBOOK(self));
	if ( cur > -1 && cur < gtk_notebook_get_n_pages (GTK_NOTEBOOK(self)) - 1 ) {
		return TRUE;
	}
	return FALSE;
}

gboolean 
gtk_adi_tab_view_can_tile_h (GtkAdiView * self)
{
	return (FALSE);
}

gboolean 
gtk_adi_tab_view_can_tile_v (GtkAdiView * self)
{
	return (FALSE);
}

gboolean 
gtk_adi_tab_view_has_children (GtkAdiView * self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_VIEW (self), FALSE);
	
	return (gtk_notebook_get_n_pages (GTK_NOTEBOOK(self)) > 0);
}

void 
gtk_adi_tab_view_remove_current_child (GtkAdiView *self, gboolean destroy)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	gint page_num = gtk_notebook_get_current_page (GTK_NOTEBOOK(self));
	gtk_adi_tab_view_remove_child_notify(self,
	                   gtk_notebook_get_nth_page(GTK_NOTEBOOK(self), page_num));
	gtk_notebook_remove_page (GTK_NOTEBOOK(self), page_num);
}

void 
gtk_adi_tab_view_remove_all_children (GtkAdiView * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	gint page_num = -1;
	while (gtk_notebook_get_n_pages (GTK_NOTEBOOK(self)) > 0) {
		page_num = gtk_notebook_get_current_page (GTK_NOTEBOOK(self));
		gtk_adi_tab_view_remove_child_notify(self,
						   gtk_notebook_get_nth_page(GTK_NOTEBOOK(self), page_num));
		gtk_notebook_remove_page (GTK_NOTEBOOK(self), page_num);
	}
}

void 
gtk_adi_tab_view_set_previous_child (GtkAdiView * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	gtk_notebook_prev_page (GTK_NOTEBOOK(self));
}

void 
gtk_adi_tab_view_set_next_child (GtkAdiView * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	gtk_notebook_next_page (GTK_NOTEBOOK(self));
}

void 
gtk_adi_tab_view_change_mode (GtkAdiView * self, GtkAdiMode mode)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	/*TBD*/
}

void 
gtk_adi_tab_view_change_state (GtkAdiView * self, GtkAdiState state)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	/*TBD*/
}

void 
gtk_adi_tab_view_change_color (GtkAdiView * self, GtkAdiColorType color)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_VIEW (self));
	
	/*TBD*/
}

void
gtk_adi_tab_view_set_child_title_text (GtkAdiView *self, GtkWidget *widget,
								       const gchar *title_text)
{
	GtkWidget *tab_label;
	tab_label = gtk_notebook_get_tab_label (GTK_NOTEBOOK(self), widget);
	gtk_adi_title_set_text (GTK_ADI_TITLE(tab_label), title_text);
}

void
gtk_adi_tab_view_set_child_close_button (GtkAdiView *self, GtkWidget *widget,
								         gboolean enabled)
{
	GtkWidget *tab_label;
	tab_label = gtk_notebook_get_tab_label (GTK_NOTEBOOK(self), widget);
	gtk_adi_title_set_close_button (GTK_ADI_TITLE(tab_label), enabled);
}

void gtk_adi_tab_view_set_child_tab (GtkAdiView *self, GtkWidget *widget, gboolean enabled)
{
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(self), enabled);
}

static void 
gtk_adi_tab_view_remove_child_notify (GtkAdiView *self,
                                      GtkWidget *child)
{
	g_signal_emit(self, gtk_adi_tab_view_signals[CLOSE_CHILD], 0, child);
	#ifdef HILDON_SUPPORT
	GtkWidget *window = gtk_widget_get_ancestor (GTK_WIDGET(self),
	                                             GTK_TYPE_WINDOW);
	if (window && GTK_IS_WINDOW(window)) {
		hildon_app_unregister_view(HILDON_APP(window), child);
	}
	#endif /* HILDON_SUPPORT */
}