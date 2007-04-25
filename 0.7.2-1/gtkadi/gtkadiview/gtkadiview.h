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
	GtkWidget *child;
	GtkWidget *widget;
	GdkPixbuf *icon;
	const gchar *title;
	GtkAdiLayout layout;
	gboolean show_close;
};

struct _GtkAdiViewIface {
	GTypeInterface parent;

	GtkAdiLayout (*get_layout) (GtkAdiView *self);
	void (*set_layout) (GtkAdiView *self, GtkAdiLayout layout);
	void (*add_child_with_data) (GtkAdiView *self,
		                         GtkAdiChildData *data);
	void (*add_child_with_layout) (GtkAdiView *self,
		                           GtkWidget *widget,
								   GdkPixbuf *icon,
								   const gchar *title,
								   GtkAdiLayout layout);
	void (*set_current_child) (GtkAdiView *self, GtkWidget *child);
	void (*set_current_widget) (GtkAdiView *self, GtkWidget *widget);
	void (*remove_child) (GtkAdiView *self, GtkWidget *child, gboolean destroy);
	gboolean (*can_previous_child) (GtkAdiView *self);
	gboolean (*can_next_child) (GtkAdiView *self);
	gboolean (*can_tile_h) (GtkAdiView *self);
	gboolean (*can_tile_v) (GtkAdiView *self);
	gboolean (*has_children) (GtkAdiView *self);
	gboolean (*can_exit) (GtkAdiView *self);
	void (*remove_current_child) (GtkAdiView *self, gboolean destroy);
	void (*get_current_child_data) (GtkAdiView *self,
	                                GtkAdiChildData *data);
	void (*get_first_child_data) (GtkAdiView *self,
	                              GtkAdiChildData *data);
	void (*remove_all_children) (GtkAdiView *self);
	void (*set_previous_child) (GtkAdiView *self);
	void (*set_next_child) (GtkAdiView *self);
	void (*change_mode) (GtkAdiView *self, GtkAdiMode mode);
	void (*change_state) (GtkAdiView *self, GtkAdiState state);
	void (*change_color) (GtkAdiView *self, GtkAdiColorType color);
	void (*set_child_title_text) (GtkAdiView *self, GtkWidget *widget,
								  const gchar *title_text);
	void (*set_child_icon) (GtkAdiView *self, GtkWidget *widget,
								  const GdkPixbuf *icon);
	void (*set_child_close_button) (GtkAdiView *self, GtkWidget *widget,
								    gboolean enabled);
	void (*set_child_tab) (GtkAdiView *self, GtkWidget *widget,
								    gboolean enabled);
	GtkWidget* (*get_child_container) (GtkAdiView *self, GtkWidget *widget);
	gint (*get_childs_count) (GtkAdiView *self);
	gboolean (*need_window) (GtkAdiView *self);
};

GType gtk_adi_view_get_type (void);

GtkAdiLayout gtk_adi_view_get_layout (GtkAdiView *self);
void gtk_adi_view_set_layout (GtkAdiView *self, GtkAdiLayout layout);
void gtk_adi_view_add_child_with_data (GtkAdiView *self,
                                       GtkAdiChildData *data);
void gtk_adi_view_add_child_with_layout (GtkAdiView *self,
										 GtkWidget *widget,
										 GdkPixbuf *icon,
										 const gchar *title,
										 GtkAdiLayout layout);
void gtk_adi_view_set_current_child	(GtkAdiView *self,
                                     GtkWidget *child);
void gtk_adi_view_set_current_widget (GtkAdiView *self,
                                      GtkWidget *widget);
void gtk_adi_view_remove_child (GtkAdiView *self,
                                GtkWidget *child,
                                gboolean destroy);
void gtk_adi_view_get_current_child_data (GtkAdiView *self,
                                          GtkAdiChildData *data);
void gtk_adi_view_get_first_child_data (GtkAdiView *self,
                                        GtkAdiChildData *data);
gboolean gtk_adi_view_can_previous_child (GtkAdiView *self);
gboolean gtk_adi_view_can_next_child (GtkAdiView *self);
gboolean gtk_adi_view_can_tile_h (GtkAdiView *self);
gboolean gtk_adi_view_can_tile_v (GtkAdiView *self);
gboolean gtk_adi_view_has_children (GtkAdiView *self);
gboolean gtk_adi_view_can_exit (GtkAdiView *self);
void gtk_adi_view_remove_current_child (GtkAdiView *self,
                                        gboolean destroy);
void gtk_adi_view_remove_all_children (GtkAdiView *self);
void gtk_adi_view_set_previous_child (GtkAdiView *self);
void gtk_adi_view_set_next_child (GtkAdiView *self);
void gtk_adi_view_change_mode (GtkAdiView *self, GtkAdiMode mode);
void gtk_adi_view_change_state (GtkAdiView *self, GtkAdiState state);
void gtk_adi_view_change_color (GtkAdiView *self, GtkAdiColorType color);
void gtk_adi_view_set_child_title_text (GtkAdiView *self, GtkWidget *widget,
								        const gchar *title_text);
void gtk_adi_view_set_child_icon (GtkAdiView *self, GtkWidget *widget,
								        const GdkPixbuf *icon);
void gtk_adi_view_set_child_close_button (GtkAdiView *self, GtkWidget *widget,
								          gboolean enabled);
void gtk_adi_view_set_child_tab (GtkAdiView *self, GtkWidget *widget,
								          gboolean enabled);
GtkWidget * gtk_adi_view_get_child_container (GtkAdiView *self, GtkWidget *widget);
gint gtk_adi_view_get_childs_count (GtkAdiView *self);
gboolean gtk_adi_view_need_window (GtkAdiView *self);

G_END_DECLS

#endif /* __GTK_ADI_VIEW_H__ */
