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

#ifndef __GTK_ADI_TOOLBAR_H__
#define __GTK_ADI_TOOLBAR_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_TOOLBAR	(gtk_adi_toolbar_get_type())
#define GTK_ADI_TOOLBAR(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_toolbar_get_type(), GtkAdiToolbar)
#define GTK_ADI_TOOLBAR_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_toolbar_get_type(), GtkAdiToolbar const)
#define GTK_ADI_TOOLBAR_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_toolbar_get_type(), GtkAdiToolbarClass)
#define GTK_IS_ADI_TOOLBAR(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_toolbar_get_type ())

#define GTK_ADI_TOOLBAR_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_toolbar_get_type(), GtkAdiToolbarClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_TOOLBAR__
#define __TYPEDEF_GTK_ADI_TOOLBAR__
typedef struct _GtkAdiToolbar GtkAdiToolbar;
#endif
struct _GtkAdiToolbar {
	GtkToolbar __parent__;
	/*< public >*/
	GtkObject * cmd;
	GtkTooltips * tooltips;
	GtkWidget * btn_new;
	GtkWidget * btn_new_h;
	GtkWidget * btn_new_v;
	GtkWidget * sep_new;
	GtkWidget * btn_cls;
	GtkWidget * btn_cls_all;
	GtkWidget * sep_cls;
	GtkWidget * btn_next;
	GtkWidget * btn_prev;
	GtkWidget * sep_nav;
	GtkWidget * btn_tile_h;
	GtkWidget * btn_tile_v;
	GtkWidget * sep_tile;
	
	GtkWidget * itm_mode;
	GtkWidget * cmb_mode;
	GtkWidget * tgl_fix;
	GtkWidget * sep_mode;
	
	GtkWidget * itm_view;
	GtkWidget * cmb_view;
	GtkWidget * sep_view;
};

/*
 * Class definition
 */
typedef struct _GtkAdiToolbarClass GtkAdiToolbarClass;
struct _GtkAdiToolbarClass {
	GtkToolbarClass __parent__;
};
G_END_DECLS


/*
 * Public methods
 */
GType gtk_adi_toolbar_get_type (void);
GtkWidget* 	gtk_adi_toolbar_new	(GtkObject *cmd);

void gtk_adi_toolbar_mode_set (GtkAdiToolbar *self, GtkAdiMode mode);
void gtk_adi_toolbar_view_set (GtkAdiToolbar *self, GtkAdiViewType view);
void gtk_adi_toolbar_fix_set (GtkAdiToolbar *self, GtkAdiState state);
void gtk_adi_toolbar_set_close_buttons (GtkAdiToolbar *self, gboolean enable);
void gtk_adi_toolbar_set_nav_buttons (GtkAdiToolbar *self,
					gboolean next,
					gboolean prev);
void gtk_adi_toolbar_set_tile_buttons (GtkAdiToolbar *self,
					gboolean tile_h,
					gboolean tile_v);

G_END_DECLS

#endif
