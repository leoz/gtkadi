/* GTK ADI Library
 * gtkadiview.c: ADI View
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
#include <config.h>
#endif

#include "gtkadiview.h"

static void
gtk_adi_view_base_init (gpointer g_class)
{
	static gboolean initialized = FALSE;

	if (!initialized) {
		/* create interface signals here. */
		initialized = TRUE;
	}
}

GType
gtk_adi_view_get_type (void)
{
    static GType type = 0;
    if (type == 0) {
        static const GTypeInfo info = {
            sizeof (GtkAdiViewIface),
            gtk_adi_view_base_init,   /* base_init */
            NULL,   /* base_finalize */
            NULL,   /* class_init */
            NULL,   /* class_finalize */
            NULL,   /* class_data */
            0,
            0,      /* n_preallocs */
            NULL    /* instance_init */
        };
        type = g_type_register_static (G_TYPE_INTERFACE, "GtkAdiView", &info, 0);
    }
    return type;
}

GtkAdiLayout
gtk_adi_view_get_layout (GtkAdiView *self)
{
	return GTK_ADI_VIEW_GET_CLASS (self)->get_layout (self);
}

void
gtk_adi_view_set_current_child (GtkAdiView *self, GtkWidget *child)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_current_child (self, child);
}

void
gtk_adi_view_remove_child (GtkAdiView *self, GtkWidget *child, gboolean destroy)
{
	GTK_ADI_VIEW_GET_CLASS (self)->remove_child (self, child, destroy);
}

void
gtk_adi_view_add_child_with_data (GtkAdiView *self, GtkAdiChildData *data)
{
	GTK_ADI_VIEW_GET_CLASS (self)->add_child_with_data (self, data);
}

void
gtk_adi_view_add_child_with_layout (GtkAdiView *self,
									GtkWidget *widget,
									GdkPixbuf *icon,
									const gchar *title,
									GtkAdiLayout layout)
{
	GTK_ADI_VIEW_GET_CLASS (self)->add_child_with_layout (self,
		                                                  widget,
														  icon,
														  title,
														  layout);
}

gboolean
gtk_adi_view_can_previous_child (GtkAdiView *self)
{
	return GTK_ADI_VIEW_GET_CLASS (self)->can_previous_child (self);
}

gboolean
gtk_adi_view_can_next_child (GtkAdiView *self)
{
	return GTK_ADI_VIEW_GET_CLASS (self)->can_next_child (self);
}

gboolean
gtk_adi_view_can_tile_h (GtkAdiView *self)
{
	return GTK_ADI_VIEW_GET_CLASS (self)->can_tile_h (self);
}

gboolean
gtk_adi_view_can_tile_v (GtkAdiView *self)
{
	return GTK_ADI_VIEW_GET_CLASS (self)->can_tile_v (self);
}

gboolean
gtk_adi_view_has_children (GtkAdiView *self)
{
	return GTK_ADI_VIEW_GET_CLASS (self)->has_children (self);
}

void
gtk_adi_view_remove_current_child (GtkAdiView *self, gboolean destroy)
{
	GTK_ADI_VIEW_GET_CLASS (self)->remove_current_child (self, destroy);
}

void
gtk_adi_view_remove_current_child_with_data (GtkAdiView *self,
                                             GtkAdiChildData *data)
{
	GTK_ADI_VIEW_GET_CLASS (self)->remove_current_child_with_data (self, data);
}

void
gtk_adi_view_remove_all_children (GtkAdiView *self)
{
	GTK_ADI_VIEW_GET_CLASS (self)->remove_all_children (self);
}

void
gtk_adi_view_set_previous_child (GtkAdiView *self)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_previous_child (self);
}

void
gtk_adi_view_set_next_child (GtkAdiView *self)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_next_child (self);
}

void
gtk_adi_view_change_mode (GtkAdiView *self, GtkAdiMode mode)
{
	GTK_ADI_VIEW_GET_CLASS (self)->change_mode (self, mode);
}

void
gtk_adi_view_change_state (GtkAdiView *self, GtkAdiState state)
{
	GTK_ADI_VIEW_GET_CLASS (self)->change_state (self, state);
}

void
gtk_adi_view_change_color (GtkAdiView *self, GtkAdiColorType color)
{
	GTK_ADI_VIEW_GET_CLASS (self)->change_color (self, color);
}
