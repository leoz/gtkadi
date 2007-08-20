/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* GTK ADI Library
 * gtkadiboxview.h: ADI Box View
 * Copyright (C) 2003 - 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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
#include "gtkadi.h"
#include "gtkadiview.h"
#include "gtkadicolor.h"

#ifndef __GTK_ADI_BOX_VIEW_H__
#define __GTK_ADI_BOX_VIEW_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_BOX_VIEW	(gtk_adi_box_view_get_type())
#define GTK_ADI_BOX_VIEW(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_box_view_get_type(), GtkAdiBoxView)
#define GTK_ADI_BOX_VIEW_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_box_view_get_type(), GtkAdiBoxView const)
#define GTK_ADI_BOX_VIEW_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_box_view_get_type(), GtkAdiBoxViewClass)
#define GTK_IS_ADI_BOX_VIEW(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_box_view_get_type ())

#define GTK_ADI_BOX_VIEW_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_box_view_get_type(), GtkAdiBoxViewClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_BOX_VIEW__
#define __TYPEDEF_GTK_ADI_BOX_VIEW__
typedef struct _GtkAdiBoxView GtkAdiBoxView;
#endif
struct _GtkAdiBoxView {
	GtkEventBox __parent__;
	/*< public >*/
	GtkObject * color;
	GtkAdiMode mode;
	GtkAdiState state;
	GtkAdiLayout layout;
	gint space;
	GtkWidget * cur_child;
	GList * children;
    GtkAdi *adi;
};

/*
 * Class definition
 */
typedef struct _GtkAdiBoxViewClass GtkAdiBoxViewClass;
struct _GtkAdiBoxViewClass {
	GtkEventBoxClass __parent__;
	void (* close_child) (GtkAdiBoxView * view);
	void (* focus_child) (GtkAdiBoxView * view);
};


/*
 * Public methods
 */
GType	gtk_adi_box_view_get_type	(void);
GtkWidget * 	gtk_adi_box_view_new	(GtkAdi *self);
GtkAdiLayout 	gtk_adi_box_view_get_layout	(GtkAdiView * self);
void gtk_adi_box_view_set_layout (GtkAdiView *self, GtkAdiLayout layout);
void gtk_adi_box_view_add_child_with_data (GtkAdiView *self,
                                           GtkAdiChildData *data);
void 	gtk_adi_box_view_add_child_with_layout	(GtkAdiView * self,
					GtkWidget * widget,
					GdkPixbuf * icon,
					const gchar * title,
					GtkAdiLayout layout);
void gtk_adi_box_view_set_current_child	(GtkAdiView *self,
                                         GtkWidget *child);
void gtk_adi_box_view_set_current_child_widget (GtkAdiView *self,
                                                GtkWidget *widget);
void gtk_adi_box_view_set_current_widget (GtkAdiView *self,
                                          GtkWidget *widget);
void gtk_adi_box_view_remove_child (GtkAdiView *self,
                                    GtkWidget *child,
									gboolean destroy);
void gtk_adi_box_view_get_current_child_data (GtkAdiView *self,
                                              GtkAdiChildData *data);
void gtk_adi_box_view_get_first_child_data (GtkAdiView *self,
                                            GtkAdiChildData *data);
gboolean gtk_adi_box_view_can_previous_child (GtkAdiView *self);
gboolean gtk_adi_box_view_can_next_child (GtkAdiView *self);
gboolean gtk_adi_box_view_can_tile_h (GtkAdiView *self);
gboolean gtk_adi_box_view_can_tile_v (GtkAdiView *self);
gboolean gtk_adi_box_view_has_children (GtkAdiView *self);
gboolean gtk_adi_box_view_can_exit (GtkAdiView *self);
void gtk_adi_box_view_remove_current_child (GtkAdiView *self,
                                            gboolean destroy);
void 	gtk_adi_box_view_remove_all_children	(GtkAdiView * self);
void 	gtk_adi_box_view_set_previous_child	(GtkAdiView * self);
void 	gtk_adi_box_view_set_next_child	(GtkAdiView * self);
void 	gtk_adi_box_view_change_mode	(GtkAdiView * self,
					GtkAdiMode mode);
void 	gtk_adi_box_view_change_state	(GtkAdiView * self,
					GtkAdiState state);
void 	gtk_adi_box_view_change_color	(GtkAdiView * self,
					GtkAdiColorType color);
void gtk_adi_box_view_set_child_title_text (GtkAdiView *self, GtkWidget *widget,
								            const gchar *title_text);
void gtk_adi_box_view_set_child_icon (GtkAdiView *self, GtkWidget *widget,
                                                                            const GdkPixbuf * icon);

void gtk_adi_box_view_set_child_close_button (GtkAdiView *self,
                                              GtkWidget *widget,
								              gboolean enabled);
void gtk_adi_box_view_set_child_tab (GtkAdiView *self,
                                              GtkWidget *widget,
								              gboolean enabled);
gint gtk_adi_box_view_get_childs_count (GtkAdiView *self);
gboolean gtk_adi_box_view_need_window (GtkAdiView *self);

G_END_DECLS

#endif