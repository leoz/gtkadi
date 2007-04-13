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
gtk_adi_view_set_layout (GtkAdiView *self, GtkAdiLayout layout)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_layout (self, layout);
}

void
gtk_adi_view_set_current_child (GtkAdiView *self, GtkWidget *child)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_current_child (self, child);
}

void
gtk_adi_view_set_current_widget (GtkAdiView *self, GtkWidget *widget)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_current_widget (self, widget);
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

gboolean
gtk_adi_view_can_exit (GtkAdiView *self)
{
	return GTK_ADI_VIEW_GET_CLASS (self)->can_exit (self);
}

void
gtk_adi_view_remove_current_child (GtkAdiView *self, gboolean destroy)
{
	GTK_ADI_VIEW_GET_CLASS (self)->remove_current_child (self, destroy);
}

void
gtk_adi_view_get_current_child_data (GtkAdiView *self,
                                     GtkAdiChildData *data)
{
	GTK_ADI_VIEW_GET_CLASS (self)->get_current_child_data (self, data);
}

void
gtk_adi_view_get_first_child_data (GtkAdiView *self,
                                   GtkAdiChildData *data)
{
	GTK_ADI_VIEW_GET_CLASS (self)->get_first_child_data (self, data);
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

void
gtk_adi_view_set_child_title_text (GtkAdiView *self, GtkWidget *widget,
								   const gchar *title_text)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_child_title_text (self, widget,
	                                                     title_text);
}

void
gtk_adi_view_set_child_icon (GtkAdiView *self, GtkWidget *widget,
								   const GdkPixbuf * icon)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_child_icon (self, widget,
	                                                     icon);
}


void
gtk_adi_view_set_child_close_button (GtkAdiView *self, GtkWidget *widget,
								     gboolean enabled)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_child_close_button (self, widget,
	                                                       enabled);
}

void
gtk_adi_view_set_child_tab (GtkAdiView *self, GtkWidget *widget, gboolean enabled)
{
	GTK_ADI_VIEW_GET_CLASS (self)->set_child_tab (self, widget, enabled);
}

GtkWidget*
gtk_adi_view_get_child_container (GtkAdiView *self, GtkWidget *widget)
{
    return GTK_ADI_VIEW_GET_CLASS (self)->get_child_container (self, widget);
}

gint
gtk_adi_view_get_childs_count (GtkAdiView *self)
{
    return GTK_ADI_VIEW_GET_CLASS (self)->get_childs_count (self);
}

gboolean
gtk_adi_view_need_window (GtkAdiView *self)
{
    return GTK_ADI_VIEW_GET_CLASS (self)->need_window (self);
}
