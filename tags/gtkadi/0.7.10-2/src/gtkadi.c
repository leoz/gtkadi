/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is GtkAdi library.
 *
 * The Initial Developer of the Original Code is
 * Leonid Zolotarev <leonid.zolotarev@gmail.com>.
 * Portions created by the Initial Developer are Copyright (C) 2003-2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s): Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

/* #define ADI_DO_TRACE */
#include "gtkadi.h"
#include "gtkadiutils.h"
#include <gtk/gtkmarshal.h>
#ifndef NO_WIDGETS
#include "gtkadicmd.h"
#endif
#include "gtkadiflex.h"
#include "gtkadistock.h"
#include "gtkadiboxview.h"
#include "gtkaditabview.h"
#include "gtkadiwinview.h"

#include <memory.h>

#ifdef HILDON_SUPPORT
#ifdef NEWHILDON_SUPPORT
#ifdef MAEMO_CHANGES
#include<hildon/hildon-window.h>
#include<hildon/hildon-program.h>
#else
#include <hildon-widgets/hildon-app.h>
#include<hildon-widgets/hildon-window.h>
#include<hildon-widgets/hildon-program.h>
#endif
#endif
#endif /* HILDON_SUPPORT */

enum {
    ADI_GET_CONT,
    ADI_FOCUS_CHILD,    
    ADI_CLOSE_CHILD,
    ADI_FREE_CONT,
    ADI_ASK_CHILD_CLOSE,
    LAST_SIGNAL
};

static gint gtk_adi_signals[LAST_SIGNAL] = {0};
	

/* here are local prototypes */
static void gtk_adi_class_init (GtkAdiClass * c);
static void gtk_adi_init (GtkAdi * self);
static void gtk_adi_add_child_notify (GtkAdi *self,
                          GtkWidget *widget,
                          GdkPixbuf *icon,
                          const gchar *title,
                          GtkAdiLayout layout);
						  
//static void gtk_adi_create_window (GtkAdi *self);
static void gtk_adi_destroy_window (GtkAdi *self);

static GtkWidget*
gtk_adi_create_window (GtkAdi* adi, GtkWidget *widget);


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
//REMOVEME			gtk_adi_cur_view_remove (self);
		}
		self->cur_view = NULL;
	}
#ifndef NO_WIDGETS
	if(self->cmd) {
		ADI_TRACE_FINALIZE("cmd");
		if (GTK_IS_WIDGET(self->cmd)) {
			gtk_object_destroy(self->cmd);
		}
		self->cmd = NULL;
	}
#endif
	if(self->flex) {
		ADI_TRACE_FINALIZE("flex");
		if (GTK_IS_WIDGET(self->flex)) {
			gtk_object_destroy(self->flex);
		}
		self->flex = NULL;
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
	
	if(self->win_view) {
		ADI_TRACE_FINALIZE("win view");
		if (GTK_IS_WIDGET(self->win_view)) {
			gtk_widget_destroy(self->win_view);
		}
		self->win_view = NULL;
	}
	
	ADI_TRACE_FINALIZE("end");
}

static void 
gtk_adi_class_init (GtkAdiClass * c)
{
	GObjectClass *g_object_class G_GNUC_UNUSED = (GObjectClass*) c;

	parent_class = g_type_class_ref (GTK_TYPE_EVENT_BOX);

	g_object_class->finalize = gtk_adi_finalize;
	
	gtk_adi_signals[ADI_GET_CONT]
		= g_signal_new (ADI_GET_CONT_S,
		        G_TYPE_FROM_CLASS (c),
			G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
			G_STRUCT_OFFSET (GtkAdiClass, get_cont),
			NULL, NULL,
			gtk_marshal_VOID__POINTER_POINTER,
			G_TYPE_NONE, 2, GTK_TYPE_POINTER, GTK_TYPE_POINTER);

        gtk_adi_signals[ADI_FOCUS_CHILD]
	        = g_signal_new (ADI_FOCUS_CHILD_S,
		        G_TYPE_FROM_CLASS (c),
			G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
			G_STRUCT_OFFSET (GtkAdiClass, focus_child),
			NULL, NULL,
			g_cclosure_marshal_VOID__POINTER,
			G_TYPE_NONE, 1, GTK_TYPE_POINTER);

        gtk_adi_signals[ADI_CLOSE_CHILD]
	        = g_signal_new (ADI_CLOSE_CHILD_S,
		        G_TYPE_FROM_CLASS (c),
			G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
			G_STRUCT_OFFSET (GtkAdiClass, remove_child),
			NULL, NULL,
			g_cclosure_marshal_VOID__POINTER,
			G_TYPE_NONE, 1, GTK_TYPE_POINTER);
        
  gtk_adi_signals[ADI_ASK_CHILD_CLOSE]
      = g_signal_new (ADI_ASK_CHILD_CLOSE_S,
              G_TYPE_FROM_CLASS (c),
              G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
              G_STRUCT_OFFSET (GtkAdiClass, ask_child_close),
              NULL, NULL,
			        gtk_marshal_VOID__POINTER_POINTER,
              G_TYPE_NONE, 2, GTK_TYPE_POINTER, GTK_TYPE_POINTER);

	gtk_adi_signals[ADI_FREE_CONT]
		= g_signal_new (ADI_FREE_CONT_S,
		        G_TYPE_FROM_CLASS (c),
			G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
			G_STRUCT_OFFSET (GtkAdiClass, get_cont),
			NULL, NULL,
			gtk_marshal_VOID__POINTER_POINTER,
			G_TYPE_NONE, 2, GTK_TYPE_POINTER, GTK_TYPE_POINTER);																								
															    
}

static void 
gtk_adi_init (GtkAdi *self)
{
	self->child_func = NULL;
	self->cont_func   = NULL;
	self->def_cont_func   = NULL;
	self->icon_func  = NULL;
	self->title_func = NULL;
#ifndef NO_WIDGETS
	self->cmd = NULL;
#endif
	self->flex = NULL;
	self->box_view = NULL;
	self->tab_view = NULL;
	self->win_view = NULL;
	self->cur_view = NULL;

	gtk_adi_stock_init ();
#ifndef NO_WIDGETS
	self->cmd = gtk_adi_cmd_new (self);
#endif
	self->flex = gtk_adi_flex_new (self);
	self->def_cont_func = gtk_adi_create_window;
    gtk_adi_set_cont_func (GTK_ADI(self), gtk_adi_create_window);
	self->box_view = gtk_adi_box_view_new (self);
	self->tab_view = gtk_adi_tab_view_new (self);
	self->win_view = gtk_adi_win_view_new (self);

	gtk_widget_ref(self->box_view);
	gtk_widget_ref(self->tab_view);
	gtk_widget_ref(self->win_view);

	self->cur_view = self->box_view;
}

GtkWidget* 
gtk_adi_new (void)
{
	return GTK_WIDGET(GET_NEW);
}

void 
gtk_adi_set_child_func (GtkAdi *self, GtkAdiCreateChildFunc child_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	self->child_func = child_func;
}

void 
gtk_adi_set_cont_func (GtkAdi *self, GtkAdiCreateContFunc cont_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	self->cont_func = cont_func ? cont_func : self->def_cont_func;
}

void 
gtk_adi_set_icon_func (GtkAdi *self, GtkAdiCreateIconFunc icon_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	self->icon_func = icon_func;
}

void 
gtk_adi_set_title_func (GtkAdi *self, GtkAdiCreateTitleFunc title_func)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	self->title_func = title_func;
}

#ifndef NO_WIDGETS
GtkWidget* 
gtk_adi_create_toolbar (GtkAdi *self)
{
	GtkWidget* toolbar = NULL;

	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI (self), NULL);
	
	if ( self->cmd ) {
		toolbar = GTK_WIDGET(gtk_adi_cmd_create_toolbar (GTK_ADI_CMD(self->cmd)));
	}
	return toolbar;
}

GtkWidget* 
gtk_adi_create_menu (GtkAdi *self)
{
	GtkWidget* menu = NULL;

	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI (self), NULL);
	
	if ( self->cmd ) {
		menu = GTK_WIDGET(gtk_adi_cmd_create_menu (GTK_ADI_CMD(self->cmd)));
	}
	return menu;
}
#endif

GtkWidget*
gtk_adi_get_toolbar (GtkAdi *self)
{
	GtkWidget* toolbar = NULL;

	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI (self), NULL);
	
	#ifndef NO_WIDGETS
	if ( self->cmd ) {
		toolbar = GTK_WIDGET(gtk_adi_cmd_get_toolbar (GTK_ADI_CMD(self->cmd)));
	}
	#endif

	return toolbar;
}

GtkWidget*
gtk_adi_get_menu (GtkAdi *self)
{
	GtkWidget* menu = NULL;

	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI (self), NULL);
	
	#ifndef NO_WIDGETS
	if ( self->cmd ) {
		menu = GTK_WIDGET(gtk_adi_cmd_get_menu (GTK_ADI_CMD(self->cmd)));
	}
	#endif

	return menu;
}

void
gtk_adi_add (GtkAdi *self, GtkWidget *widget)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	g_return_if_fail (widget != NULL);
	
	gtk_adi_add_child_notify (self, widget, NULL, NULL,
	gtk_adi_flex_add_layout (GTK_ADI_FLEX(self->flex)));
}

void 
gtk_adi_user_add_child (GtkAdi *self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_user_add_child_with_layout (self,
	gtk_adi_flex_add_layout (GTK_ADI_FLEX(self->flex)));
}

void 
gtk_adi_user_add_child_with_layout (GtkAdi *self, GtkAdiLayout layout)
{
	GtkWidget* widget = NULL;
	GdkPixbuf* icon = NULL;
	gchar* title = NULL;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	if (self->child_func && self->icon_func && self->title_func ) {
		widget = self->child_func ();
		icon = self->icon_func (widget);
		title = self->title_func ();
		gtk_adi_add_child_notify (self, widget, icon, title, layout);
		g_free (title);
	}
}

gboolean 
gtk_adi_can_previous_child (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI (self), FALSE);
	
	return gtk_adi_view_can_previous_child (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_can_next_child (GtkAdi * self)

{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI (self), FALSE);
	
	return gtk_adi_view_can_next_child (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_can_tile_h (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI (self), FALSE);
	
	return gtk_adi_view_can_tile_h (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_can_tile_v (GtkAdi * self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI (self), FALSE);
	
	return gtk_adi_view_can_tile_v (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_has_children (GtkAdi *self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI (self), FALSE);
	
	return gtk_adi_view_has_children (GTK_ADI_VIEW(self->cur_view));
}

gboolean 
gtk_adi_can_exit (GtkAdi *self)
{
	g_return_val_if_fail (self != NULL, TRUE);
	g_return_val_if_fail (GTK_IS_ADI (self), TRUE);
	
	return gtk_adi_view_can_exit (GTK_ADI_VIEW(self->cur_view));
}

void
gtk_adi_set_current_child (GtkAdi *self, GtkWidget *child)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	gtk_adi_view_set_current_child (GTK_ADI_VIEW(self->cur_view), child);
}

void
gtk_adi_set_current_widget (GtkAdi *self, GtkWidget *widget)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));

	gtk_adi_view_set_current_widget (GTK_ADI_VIEW(self->cur_view), widget);
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
gtk_adi_change_view (GtkAdi *self, GtkAdiViewType view)
{
	GtkWidget* old_view = NULL;
	GtkWidget* current = NULL;
	GtkAdiChildData data;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	#ifndef NO_WIDGETS
	gtk_adi_cmd_set_view(GTK_ADI_CMD(self->cmd), view);
	#endif

	/* 0. Check if the change is needed */
	if (gtk_adi_get_view(self) == view) {
		return;
	}
	
	/* 1. Hide current view */
	if (self->cur_view) {
		gtk_widget_hide(self->cur_view);
		gtk_widget_ref(self->cur_view);
	//	gtk_adi_cur_view_remove (self);
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
	case GTK_ADI_VIEW_WIN:
		self->cur_view = self->win_view;
		break;
	default:
		self->cur_view = NULL;
		break;
	}
	
	/* 3. Add current view */
	if (self->cur_view) {
//		gtk_adi_cur_view_add (self);
//		gtk_widget_unref(self->cur_view);
	}

	/* 4. Move child windows */	
	if (self->cur_view && old_view) {
		ADI_TRACE_MSG("Entering change view.")
		
		memset(&data, 0, sizeof(data));
		gtk_adi_view_get_current_child_data(GTK_ADI_VIEW(old_view), &data);
		
		current = data.widget;
		
		memset(&data, 0, sizeof(data));
		gtk_adi_view_get_first_child_data(GTK_ADI_VIEW(old_view), &data);
		
		while (data.widget) {
			ADI_TRACE_MSG("Change view - iteration.\n------------\n")
			gtk_widget_ref (data.widget);
			data.title = g_strdup(data.title);
			if (data.icon)
			    data.icon = gdk_pixbuf_copy(data.icon);
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
	
}

GtkAdiViewType
gtk_adi_get_view (GtkAdi *self)
{
	g_return_val_if_fail (self != NULL, GTK_ADI_VIEW_BOX);
	g_return_val_if_fail (GTK_IS_ADI (self), GTK_ADI_VIEW_BOX);
	
	if (self->cur_view && self->cur_view == self->tab_view) {
		return GTK_ADI_VIEW_TAB;
	}
	if (self->cur_view && self->cur_view == self->win_view) {
		return GTK_ADI_VIEW_WIN;
	}
	return GTK_ADI_VIEW_BOX;
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

void gtk_adi_set_child_icon (GtkAdi *self, GtkWidget *widget,
								   const GdkPixbuf * icon)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_set_child_icon (GTK_ADI_VIEW(self->cur_view),
	                                   widget,
	                                   icon);
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

void gtk_adi_set_child_tab (GtkAdi *self, GtkWidget *widget,
								     gboolean enabled)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	gtk_adi_view_set_child_tab (GTK_ADI_VIEW(self->cur_view),
	                                     widget,
	                                     enabled);
}


void
gtk_adi_set_layout (GtkAdi *self, GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI (self));
	
	gtk_adi_view_set_layout (GTK_ADI_VIEW(self->box_view), layout);
	gtk_adi_view_set_layout (GTK_ADI_VIEW(self->tab_view), layout);
	gtk_adi_view_set_layout (GTK_ADI_VIEW(self->win_view), layout);
	gtk_adi_view_set_layout (GTK_ADI_VIEW(self->cur_view), layout);
}

GtkWidget*
gtk_adi_get_child_container (GtkAdi *self, GtkWidget *widget)
{
    g_return_val_if_fail (self != NULL, 0);
    g_return_val_if_fail (GTK_IS_ADI (self), 0);
    g_return_val_if_fail (widget != NULL, 0);

    return gtk_adi_view_get_child_container (GTK_ADI_VIEW(self->cur_view), widget);
}

gint
gtk_adi_get_childs_count (GtkAdi *self)
{
    g_return_val_if_fail (self != NULL, 0);
    g_return_val_if_fail (GTK_IS_ADI (self), 0);

    return gtk_adi_view_get_childs_count (GTK_ADI_VIEW(self->cur_view));
}

static void
gtk_adi_add_child_notify (GtkAdi *self,
                          GtkWidget *widget,
                          GdkPixbuf *icon,
                          const gchar *title,
                          GtkAdiLayout layout)
{	
    gtk_adi_view_add_child_with_layout(GTK_ADI_VIEW(self->cur_view),
                                       widget, icon, title, layout);
}

static GtkAdi * glob_signal_adi = NULL;
static gboolean
gtk_adi_cont_event_focus_in (GtkWidget *window,
#ifdef NEWHILDON_SUPPORT
                             GParamSpec *event,
#else
                             GdkEventFocus *event,
#endif
                             GtkWidget *data)
{
    g_return_val_if_fail (window, FALSE);
    g_return_val_if_fail (data, FALSE);
    ADI_TRACE("Focus - W1: %p", window);
    if (!GTK_IS_WIDGET(data))
	return FALSE;
#ifdef NEWHILDON_SUPPORT
    if(hildon_window_get_is_topmost(window))
#endif
	if (GTK_IS_WIDGET(data))
	    gtk_adi_internal_send_signal(G_OBJECT(glob_signal_adi), ADI_FOCUS_CHILD_S,  data);
    return FALSE;
}

static GtkWidget*
gtk_adi_create_window (GtkAdi* adi, GtkWidget *widget)
{
    GtkWidget* container = NULL;
    GtkWidget* window = NULL;
    g_signal_emit_by_name(G_OBJECT(adi), ADI_GET_CONT_S, &container, widget);
    if(container == NULL)
    {
#ifdef NEWHILDON_SUPPORT
        window = GTK_WIDGET(hildon_window_new());
#else
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
#endif
        container = window;
    }

    glob_signal_adi = adi;
    if (glob_signal_adi && glob_signal_adi->cur_view != glob_signal_adi->win_view)
        return container;

#ifdef NEWHILDON_SUPPORT
    window = GTK_WIDGET(HILDON_WINDOW(gtk_widget_get_toplevel(container)));
    g_signal_connect (window, "notify::is-topmost",
                      G_CALLBACK (gtk_adi_cont_event_focus_in),
                      widget);
#else
    window = GTK_WIDGET(GTK_WINDOW(gtk_widget_get_toplevel(container)));
    g_signal_connect (window, "focus-in-event",
                      G_CALLBACK (gtk_adi_cont_event_focus_in),
                      widget);
#endif
    return container;
}

