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
#include "gtkadi.h"
#include "gtkadiview.h"

#ifndef __GTK_ADI_CON_VIEW_H__
#define __GTK_ADI_CON_VIEW_H__

G_BEGIN_DECLS

/*
 * Container structure
 */
#ifndef __TYPEDEF_GTK_ADI_CONTAINER__
#define __TYPEDEF_GTK_ADI_CONTAINER__
typedef struct _GtkAdiContainer GtkAdiContainer;
#endif
struct _GtkAdiContainer {
	/*< public >*/
	GtkWidget *container;
	GtkWidget *window;
	GtkWidget *widget;
	GtkAdiLayout layout;
	gboolean show_close;
};

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_CON_VIEW	(gtk_adi_con_view_get_type())
#define GTK_ADI_CON_VIEW(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_con_view_get_type(), GtkAdiConView)
#define GTK_ADI_CON_VIEW_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_con_view_get_type(), GtkAdiConView const)
#define GTK_ADI_CON_VIEW_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_con_view_get_type(), GtkAdiConViewClass)
#define GTK_IS_ADI_CON_VIEW(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_con_view_get_type ())

#define GTK_ADI_CON_VIEW_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_con_view_get_type(), GtkAdiConViewClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_CON_VIEW__
#define __TYPEDEF_GTK_ADI_CON_VIEW__
typedef struct _GtkAdiConView GtkAdiConView;
#endif
struct _GtkAdiConView {
	GtkEventBox __parent__;
	/*< public >*/
	GtkAdi *adi;
	GList *containers;
	GtkAdiContainer *current;
};

/*
 * Class definition
 */
typedef struct _GtkAdiConViewClass GtkAdiConViewClass;
struct _GtkAdiConViewClass {
	GtkEventBoxClass __parent__;
	void (* close_child) (GtkAdiConView * view);
	void (* focus_child) (GtkAdiConView * view);
};


/*
 * Public methods
 */
GType gtk_adi_con_view_get_type (void);
GtkWidget* gtk_adi_con_view_new	(GtkAdi* adi);
GtkAdiLayout gtk_adi_con_view_get_layout (GtkAdiView *self);
void gtk_adi_con_view_set_layout (GtkAdiView *self, GtkAdiLayout layout);
void gtk_adi_con_view_add_child_with_data (GtkAdiView *self,
                                           GtkAdiChildData *data);
void gtk_adi_con_view_add_child_with_layout	(GtkAdiView *self,
					GtkWidget * widget,
					GdkPixbuf * icon,
					const gchar * title,
					GtkAdiLayout layout);
void gtk_adi_con_view_set_current_child (GtkAdiView *self,
                                         GtkWidget *child);
void gtk_adi_con_view_set_current_widget (GtkAdiView *self,
                                          GtkWidget *widget);
void gtk_adi_con_view_remove_child (GtkAdiView *self,
                                    GtkWidget *child,
                                    gboolean destroy);
void gtk_adi_con_view_get_current_child_data (GtkAdiView *self,
                                              GtkAdiChildData *data);
void gtk_adi_con_view_get_first_child_data (GtkAdiView *self,
                                            GtkAdiChildData *data);
gboolean gtk_adi_con_view_can_previous_child (GtkAdiView *self);
gboolean gtk_adi_con_view_can_next_child (GtkAdiView *self);
gboolean gtk_adi_con_view_can_tile_h (GtkAdiView *self);
gboolean gtk_adi_con_view_can_tile_v (GtkAdiView *self);
gboolean gtk_adi_con_view_has_children (GtkAdiView *self);
gboolean gtk_adi_con_view_can_exit (GtkAdiView *self);

void gtk_adi_con_view_remove_current_child (GtkAdiView *self, gboolean destroy);
void 	gtk_adi_con_view_remove_all_children	(GtkAdiView * self);
void 	gtk_adi_con_view_set_previous_child	(GtkAdiView * self);
void gtk_adi_con_view_set_next_child	(GtkAdiView * self);
void gtk_adi_con_view_change_mode	(GtkAdiView * self,
					GtkAdiMode mode);
void gtk_adi_con_view_change_state	(GtkAdiView * self,
					GtkAdiState state);
void gtk_adi_con_view_change_color	(GtkAdiView * self,
					GtkAdiColorType color);
void gtk_adi_con_view_set_child_title_text (GtkAdiView *self, GtkWidget *widget,
								            const gchar *title_text);
void gtk_adi_con_view_set_child_icon (GtkAdiView *self, GtkWidget *widget, const GdkPixbuf * icon);


void gtk_adi_con_view_set_child_close_button (GtkAdiView *self, GtkWidget *widget, gboolean enabled);

void gtk_adi_con_view_set_child_tab (GtkAdiView *self, GtkWidget *widget, gboolean enabled);

GtkWidget * gtk_adi_con_view_get_child_container (GtkAdiView *self, GtkWidget *widget);

gint gtk_adi_con_view_get_childs_count (GtkAdiView *self);
gboolean gtk_adi_con_view_need_window (GtkAdiView *self);

G_END_DECLS

#endif /* __GTK_ADI_CON_VIEW_H__ */
