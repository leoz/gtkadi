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
#include "gtkaditoolbar.h"
#include "gtkadimenu.h"
#include "gtkadi.h"

#ifndef __GTK_ADI_CMD_H__
#define __GTK_ADI_CMD_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_CMD	(gtk_adi_cmd_get_type())
#define GTK_ADI_CMD(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_cmd_get_type(), GtkAdiCmd)
#define GTK_ADI_CMD_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_cmd_get_type(), GtkAdiCmd const)
#define GTK_ADI_CMD_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_cmd_get_type(), GtkAdiCmdClass)
#define GTK_IS_ADI_CMD(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_cmd_get_type ())

#define GTK_ADI_CMD_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_cmd_get_type(), GtkAdiCmdClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_CMD__
#define __TYPEDEF_GTK_ADI_CMD__
typedef struct _GtkAdiCmd GtkAdiCmd;
#endif
struct _GtkAdiCmd {
	GtkObject __parent__;
	/*< public >*/
	GtkAdi * adi;
	GtkTooltips * tooltips;
	GtkAdiToolbar * toolbar;
	GtkAdiMenu * menu;
};

/*
 * Class definition
 */
typedef struct _GtkAdiCmdClass GtkAdiCmdClass;
struct _GtkAdiCmdClass {
	GtkObjectClass __parent__;
};


/*
 * Public methods
 */
GType gtk_adi_cmd_get_type (void);
GtkObject* gtk_adi_cmd_new (GtkAdi *adi);
GtkTooltips* gtk_adi_cmd_get_tooltips (GtkAdiCmd *self);
GtkAdiToolbar* gtk_adi_cmd_create_toolbar (GtkAdiCmd *self);
GtkAdiMenu* gtk_adi_cmd_create_menu	(GtkAdiCmd *self);
GtkWidget* gtk_adi_cmd_get_toolbar (GtkAdiCmd *self);
GtkWidget* gtk_adi_cmd_get_menu (GtkAdiCmd *self);
void 	gtk_adi_cmd_set_nav_buttons	(GtkAdiCmd * self);
void 	gtk_adi_cmd_set_close_buttons	(GtkAdiCmd * self);
void 	gtk_adi_cmd_set_tile_buttons	(GtkAdiCmd * self);
void 	gtk_adi_cmd_new_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_new_h_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_new_v_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_close_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_close_all_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_next_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_prev_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_tile_h_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_tile_v_clicked	(GtkAdiCmd * self,
					gpointer user_data);
void 	gtk_adi_cmd_mode_changed	(GtkAdiCmd * self,
					GtkAdiMode mode);
void 	gtk_adi_cmd_view_changed	(GtkAdiCmd * self,
					GtkAdiViewType view);
void 	gtk_adi_cmd_set_view	(GtkAdiCmd * self,
					GtkAdiViewType view);
void 	gtk_adi_cmd_fix_toggled	(GtkAdiCmd * self,
					GtkAdiState state);

G_END_DECLS

#endif /* __GTK_ADI_CMD_H__ */
