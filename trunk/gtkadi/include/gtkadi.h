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
#include <glib.h>
#include <glib-object.h> 
#ifndef __GTK_ADI_H__
#define __GTK_ADI_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI	(gtk_adi_get_type())
#define GTK_ADI(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_get_type(), GtkAdi)
#define GTK_ADI_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_get_type(), GtkAdi const)
#define GTK_ADI_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_get_type(), GtkAdiClass)
#define GTK_IS_ADI(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_get_type ())

#define GTK_ADI_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_get_type(), GtkAdiClass)

#define ADI_CLOSE_CHILD_S "adi-close-child"
#define ADI_FOCUS_CHILD_S "adi-focus-child"
#define ADI_GET_CONT_S "adi-get-cont"
#define ADI_FREE_CONT_S "adi-free-cont"
/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI__
#define __TYPEDEF_GTK_ADI__
typedef struct _GtkAdi GtkAdi;
#endif

typedef GtkWidget* (*GtkAdiCreateChildFunc) (void);
typedef GtkWidget* (*GtkAdiCreateContFunc)  (GtkAdi *adi, GtkWidget *widget);
typedef GdkPixbuf* (*GtkAdiCreateIconFunc)  (GtkWidget *widget);
typedef gchar*     (*GtkAdiCreateTitleFunc) (void);

struct _GtkAdi {
	GtkEventBox __parent__;
	/*< public >*/
	GtkAdiCreateChildFunc child_func;
	GtkAdiCreateContFunc  cont_func;
	GtkAdiCreateContFunc  def_cont_func;
	GtkAdiCreateIconFunc  icon_func;
	GtkAdiCreateTitleFunc title_func;
#ifndef NO_WIDGETS
	GtkObject *cmd;
#endif
	GtkObject *flex;
	GtkWidget *box_view;
	GtkWidget *tab_view;
	GtkWidget *win_view;
	GtkWidget *cur_view;
};

/*
 * Class definition
 */
typedef struct _GtkAdiClass GtkAdiClass;
struct _GtkAdiClass {
	GtkEventBoxClass __parent__;
	void (* get_cont) (GtkAdi * adi);
	void (* focus_child) (GtkAdi * adi);
	void (* remove_child) (GtkAdi * adi);
};


/*
 * Public methods
 */
GType	gtk_adi_get_type	(void);
GtkWidget * 	gtk_adi_new	(void);
void gtk_adi_set_child_func	(GtkAdi *self,
							 GtkAdiCreateChildFunc child_func);
void gtk_adi_set_cont_func(GtkAdi *self,
              GtkAdiCreateContFunc cont_func);
void gtk_adi_set_icon_func	(GtkAdi *self,
							 GtkAdiCreateIconFunc icon_func);
void gtk_adi_set_title_func	(GtkAdi *self,
							 GtkAdiCreateTitleFunc title_func);
#ifndef NO_WIDGETS
GtkWidget* gtk_adi_create_toolbar (GtkAdi *self);
GtkWidget* gtk_adi_create_menu (GtkAdi *self);
#endif
GtkWidget* gtk_adi_get_toolbar (GtkAdi *self);
GtkWidget* gtk_adi_get_menu (GtkAdi *self);
void gtk_adi_add (GtkAdi *self, GtkWidget *widget);
void 	gtk_adi_user_add_child	(GtkAdi *self);
void 	gtk_adi_user_add_child_with_layout	(GtkAdi * self,
					GtkAdiLayout layout);
gboolean gtk_adi_can_previous_child (GtkAdi *self);
gboolean gtk_adi_can_next_child (GtkAdi *self);
gboolean gtk_adi_can_tile_h (GtkAdi *self);
gboolean gtk_adi_can_tile_v (GtkAdi *self);
gboolean gtk_adi_has_children (GtkAdi *self);
gboolean gtk_adi_can_exit (GtkAdi *self);
void gtk_adi_set_current_child (GtkAdi *self, GtkWidget *child);
void gtk_adi_set_current_widget (GtkAdi *self, GtkWidget *widget);
void gtk_adi_remove_current_child (GtkAdi *self);
void gtk_adi_remove_all_children (GtkAdi *self);
void gtk_adi_set_previous_child (GtkAdi *self);
void gtk_adi_set_next_child	(GtkAdi *self);
void gtk_adi_change_mode (GtkAdi *self, GtkAdiMode mode);
void gtk_adi_change_view (GtkAdi *self, GtkAdiViewType view);
GtkAdiViewType gtk_adi_get_view (GtkAdi *self);
void gtk_adi_change_state (GtkAdi *self, GtkAdiState state);
void gtk_adi_change_color (GtkAdi *self, GtkAdiColorType color);
void gtk_adi_set_child_title_text (GtkAdi *self, GtkWidget *widget,
								   const gchar *title_text);
void gtk_adi_set_child_icon (GtkAdi *self, GtkWidget *widget,
								   const GdkPixbuf * icon);


void gtk_adi_set_child_close_button (GtkAdi *self, GtkWidget *widget,
								     gboolean enabled);

void gtk_adi_set_child_tab (GtkAdi *self, GtkWidget *widget,
								     gboolean enabled);

GtkWidget *gtk_adi_get_child_container (GtkAdi *self, GtkWidget *widget);

void gtk_adi_set_layout (GtkAdi *self, GtkAdiLayout layout);

gint gtk_adi_get_childs_count (GtkAdi *self);

G_END_DECLS

#endif
