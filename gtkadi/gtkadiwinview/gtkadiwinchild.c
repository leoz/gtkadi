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
#define ADI_DO_TRACE
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

		type = g_type_register_static (GTK_TYPE_WINDOW, "GtkAdiWinChild", &info, (GTypeFlags)0);
	}

	return type;
}

static void 
gtk_adi_win_child_class_init (GtkAdiWinChildClass *c)
{
	parent_class = g_type_class_ref (GTK_TYPE_WINDOW);
}

static void 
gtk_adi_win_child_init (GtkAdiWinChild *self)
{
	GTK_WINDOW(self)->type = GTK_WINDOW_TOPLEVEL;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiWinChild *)g_object_new(gtk_adi_win_child_get_type(), NULL))

GtkWidget* 
gtk_adi_win_child_new (GtkWidget *widget)
{
	GtkWidget *self = GTK_WIDGET(GET_NEW);
	GTK_ADI_WIN_CHILD(self)->widget = widget;
	return self;
}
