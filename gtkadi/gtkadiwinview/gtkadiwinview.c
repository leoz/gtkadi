/* GTK ADI Library
 * gtkadiwinview.c: ADI Window View
 * Copyright (C) 2005 - 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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

#ifdef HILDON_SUPPORT
#include <hildon-widgets/hildon-window.h>
#include <hildon-widgets/hildon-program.h>
#endif


#include "gtkadiwinview.h"
#include "gtkadiwinchild.h"
/* #define ADI_DO_TRACE */
#include "gtkadiutils.h"

/* here are local prototypes */
static void gtk_adi_win_view_class_init (GtkAdiWinViewClass *c);
static void gtk_adi_win_view_init (GtkAdiWinView *self);
static GtkWidget* gtk_adi_win_view_create_window (GtkAdi* adi, GtkWidget *widget);

static void
gtk_adi_win_view_swap_child_windows (GtkWidget *window,
				     GtkAdi *self);
									  

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

		type = g_type_register_static (GTK_TYPE_ADI_CON_VIEW, "GtkAdiWinView", &info, (GTypeFlags)0);
	}

	return type;
}

static void 
gtk_adi_win_view_class_init (GtkAdiWinViewClass *c)
{
	parent_class = g_type_class_ref (GTK_TYPE_ADI_CON_VIEW);
}

static void 
gtk_adi_win_view_init (GtkAdiWinView *self)
{}

GtkWidget* 
gtk_adi_win_view_new (GtkAdi* adi)
{	
	GtkWidget *self = gtk_adi_con_view_new(adi);
	gtk_adi_set_cont_func (GTK_ADI(adi), gtk_adi_win_view_create_window);
	return self;
}

static void
gtk_adi_win_view_swap_child_windows (GtkWidget *window,
                                     GtkAdi *self)
{
    g_return_if_fail (window != NULL);
    g_return_if_fail (self != NULL);
    g_return_if_fail (GTK_IS_ADI (self));
    
    g_signal_emit_by_name(G_OBJECT(self), ADI_FOCUS_CHILD_S, window);
}

static gboolean
gtk_adi_win_view_child_event_focus_in (GtkWidget *window,
                                       GdkEventFocus *event,
				       GtkAdi *self)
{
    g_return_val_if_fail (window != NULL, FALSE);
    g_return_val_if_fail (self != NULL, FALSE);
    g_return_val_if_fail (GTK_IS_ADI (self), FALSE);
	
    ADI_TRACE("Focus - W1: %d", (int) window);
    gtk_adi_win_view_swap_child_windows (window, self);
    gtk_widget_show (window);
																								    
    return FALSE;
}
									      

static GtkWidget*
gtk_adi_win_view_create_window (GtkAdi* adi, GtkWidget *widget)
{
	GtkWidget* window = NULL;
	g_signal_emit_by_name(G_OBJECT(adi), ADI_GET_CONT_S, &window, widget);
	if(window == NULL)
	{
	    window = hildon_window_new();
	}
	
	g_signal_connect (window, "focus-in-event",
	                  G_CALLBACK (gtk_adi_win_view_child_event_focus_in),
	                  adi);
										    
	//window = new_cont; //gtk_adi_win_child_new (adi);
	return window;
	#ifdef NEWHILDON_SUPPORT
	return window;
	#else
	return GTK_ADI_WIN_CHILD(window)->box;
	#endif
}

