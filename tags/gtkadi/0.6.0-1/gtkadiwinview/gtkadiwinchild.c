/* GTK ADI Library
 * gtkadiwinchild.c: ADI Window Child
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

#include "gtkadiwinchild.h"
/* #define ADI_DO_TRACE */
#include "gtkadiutils.h"

/* here are local prototypes */
static void gtk_adi_win_child_class_init (GtkAdiWinChildClass *c);
static void gtk_adi_win_child_init (GtkAdiWinChild *self);

/* pointer to the class of our parent */
static GtkWindowClass *parent_class = NULL;

GType
gtk_adi_win_child_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiWinChildClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_win_child_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiWinChild),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_win_child_init,
			NULL
		};
	#ifdef NEWHILDON_SUPPORT
	type = g_type_register_static (HILDON_TYPE_WINDOW, "GtkAdiWinChild", &info, (GTypeFlags)0);
	#else
	type = g_type_register_static (GTK_TYPE_WINDOW, "GtkAdiWinChild", &info, (GTypeFlags)0);
	#endif
	}

	return type;
}

static void 
gtk_adi_win_child_class_init (GtkAdiWinChildClass *c)
{
	#ifdef NEWHILDON_SUPPORT
	parent_class = g_type_class_ref (HILDON_TYPE_WINDOW);
	#else
	parent_class = g_type_class_ref (GTK_TYPE_WINDOW);
	#endif
}

static void 
gtk_adi_win_child_init (GtkAdiWinChild *self)
{
	#ifndef NEWHILDON_SUPPORT
	self->adi = NULL;
	self->toolbar = NULL;
	self->box = gtk_vbox_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER(self->box), 10);
	gtk_container_add (GTK_CONTAINER (self), self->box);
	#endif /* NEWHILDON_SUPPORT */
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiWinChild *)g_object_new(gtk_adi_win_child_get_type(), NULL))

#ifndef NEWHILDON_SUPPORT

static gboolean
gtk_adi_win_child_event_focus_in (GtkAdiWinChild *self,
                                  GdkEventFocus *event,
                                  GtkAdi* adi)
{
	if (GTK_ADI_WIN_CHILD(self)->toolbar) {
		GtkWidget* parent = gtk_widget_get_parent (GTK_ADI_WIN_CHILD(self)->toolbar);
		if (parent && GTK_IS_CONTAINER(parent)) {
			g_object_ref (GTK_ADI_WIN_CHILD(self)->toolbar);
			gtk_container_remove (GTK_CONTAINER(parent), GTK_ADI_WIN_CHILD(self)->toolbar);
		}
		gtk_box_pack_start (GTK_BOX (GTK_ADI_WIN_CHILD(self)->box), GTK_ADI_WIN_CHILD(self)->toolbar, FALSE, FALSE, 0);
		gtk_box_reorder_child (GTK_BOX (GTK_ADI_WIN_CHILD(self)->box), GTK_ADI_WIN_CHILD(self)->toolbar, 0);
	}

	return FALSE;
}

static gboolean
gtk_adi_win_child_event_delete (GtkAdiWinChild *self,
                                GdkEvent *event,
                                GtkAdi* adi)
{
	return FALSE;
}

static void
gtk_adi_win_child_event_destroy (GtkAdiWinChild *self, GtkAdi* adi)
{
	g_object_ref (GTK_ADI_WIN_CHILD(self)->toolbar);
	gtk_container_remove (GTK_CONTAINER(GTK_ADI_WIN_CHILD(self)->box), self->toolbar);
	self->toolbar = NULL;

	if (gtk_adi_can_exit (adi)) {
//		gtk_main_quit ();
	}
}

#endif /* NEWHILDON_SUPPORT */

GtkWidget*
gtk_adi_win_child_new (GtkAdi* adi)
{
	GtkWidget *self = GTK_WIDGET(GET_NEW);

	#ifndef NEWHILDON_SUPPORT

	GTK_ADI_WIN_CHILD(self)->adi = adi;
	GTK_ADI_WIN_CHILD(self)->toolbar = gtk_adi_get_toolbar (adi);

	if (!GTK_ADI_WIN_CHILD(self)->toolbar) {
		#ifndef NO_WIDGETS
		GTK_ADI_WIN_CHILD(self)->toolbar = gtk_adi_create_toolbar (adi);
		#endif /* NO_WIDGETS */
	}

	gtk_adi_win_child_event_focus_in (GTK_ADI_WIN_CHILD(self), NULL, adi);

	g_signal_connect (self, "focus-in-event",
				  G_CALLBACK (gtk_adi_win_child_event_focus_in),
				  adi);
	g_signal_connect (self, "delete-event",
				  G_CALLBACK (gtk_adi_win_child_event_delete),
				  adi);
	g_signal_connect (self, "destroy",
				  G_CALLBACK (gtk_adi_win_child_event_destroy),
				  adi);

	#endif /* NEWHILDON_SUPPORT */

	return self;
}
