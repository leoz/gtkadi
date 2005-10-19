/* GTK ADI Library
 * gtkadiview.h: ADI View
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

#include <gtk/gtk.h>
#include "gtkaditype.h"

#ifndef __GTK_ADI_VIEW_H__
#define __GTK_ADI_VIEW_H__

G_BEGIN_DECLS

#define GTK_TYPE_ADI_VIEW             (gtk_adi_view_get_type ())
#define GTK_ADI_VIEW(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ADI_VIEW, GtkAdiView))
#define GTK_ADI_VIEW_CLASS(vtable)    (G_TYPE_CHECK_CLASS_CAST ((vtable), GTK_TYPE_ADI_VIEW, GtkAdiViewIface))
#define GTK_IS_ADI_VIEW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ADI_VIEW))
#define GTK_IS_ADI_VIEW_CLASS(vtable) (G_TYPE_CHECK_CLASS_TYPE ((vtable), GTK_TYPE_ADI_VIEW))
#define GTK_ADI_VIEW_GET_CLASS(inst)  (G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_ADI_VIEW, GtkAdiViewIface))


typedef struct _GtkAdiView GtkAdiView; /* dummy object */
typedef struct _GtkAdiChildData GtkAdiChildData;
typedef struct _GtkAdiViewIface GtkAdiViewIface;

struct _GtkAdiChildData {
	GtkWidget *widget;
	GdkPixbuf *icon;
	const gchar *title;
	GtkAdiLayout layout;
};

struct _GtkAdiViewIface {
	GTypeInterface parent;

	GtkAdiLayout (*get_layout) (GtkAdiView *self);
	void (*add_child_with_data) (GtkAdiView *self,
		                         GtkAdiChildData *data);
	void (*add_child_with_layout) (GtkAdiView *self,
		                           GtkWidget *widget,
								   GdkPixbuf *icon,
								   const gchar *title,
								   GtkAdiLayout layout);
	void (*set_current_child) (GtkAdiView *self, GtkWidget *child);
	void (*remove_child) (GtkAdiView *self, GtkWidget *child);
	gboolean (*can_previous_child) (GtkAdiView *self);
	gboolean (*can_next_child) (GtkAdiView *self);
	gboolean (*can_tile_h) (GtkAdiView *self);
	gboolean (*can_tile_v) (GtkAdiView *self);
	gboolean (*has_children) (GtkAdiView *self);
	void (*remove_current_child) (GtkAdiView *self);
	void (*remove_current_child_with_data) (GtkAdiView *self,
	                                        GtkAdiChildData *data);
	void (*remove_all_children) (GtkAdiView *self);
	void (*set_previous_child) (GtkAdiView *self);
	void (*set_next_child) (GtkAdiView *self);
	void (*change_mode) (GtkAdiView *self, GtkAdiMode mode);
	void (*change_state) (GtkAdiView *self, GtkAdiState state);
	void (*change_color) (GtkAdiView *self, GtkAdiColorType color);
};

GType gtk_adi_view_get_type (void);

GtkAdiLayout gtk_adi_view_get_layout (GtkAdiView *self);
void gtk_adi_view_add_child_with_data (GtkAdiView *self,
                                       GtkAdiChildData *data);
void gtk_adi_view_add_child_with_layout (GtkAdiView *self,
										 GtkWidget *widget,
										 GdkPixbuf *icon,
										 const gchar *title,
										 GtkAdiLayout layout);
void gtk_adi_view_set_current_child	(GtkAdiView *self, GtkWidget *child);
void gtk_adi_view_remove_child (GtkAdiView *self, GtkWidget *child);
void gtk_adi_view_remove_current_child_with_data (GtkAdiView *self,
                                                  GtkAdiChildData *data);
gboolean gtk_adi_view_can_previous_child (GtkAdiView *self);
gboolean gtk_adi_view_can_next_child (GtkAdiView *self);
gboolean gtk_adi_view_can_tile_h (GtkAdiView *self);
gboolean gtk_adi_view_can_tile_v (GtkAdiView *self);
gboolean gtk_adi_view_has_children (GtkAdiView *self);
void gtk_adi_view_remove_current_child (GtkAdiView *self);
void gtk_adi_view_remove_all_children (GtkAdiView *self);
void gtk_adi_view_set_previous_child (GtkAdiView *self);
void gtk_adi_view_set_next_child (GtkAdiView *self);
void gtk_adi_view_change_mode (GtkAdiView *self, GtkAdiMode mode);
void gtk_adi_view_change_state (GtkAdiView *self, GtkAdiState state);
void gtk_adi_view_change_color (GtkAdiView *self, GtkAdiColorType color);

G_END_DECLS

#endif /* __GTK_ADI_VIEW_H__ */
