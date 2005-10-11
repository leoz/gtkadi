/* GTK ADI Library
 * gtkadicmd.h: ADI Cmd Object
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
#include <glib/gprintf.h>
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
GType	gtk_adi_cmd_get_type	(void);
GtkObject * 	gtk_adi_cmd_new	(GtkAdi * adi);
GtkTooltips * 	gtk_adi_cmd_get_tooltips	(GtkAdiCmd * self);
GtkAdiToolbar * 	gtk_adi_cmd_create_toolbar	(GtkAdiCmd * self);
GtkAdiMenu * 	gtk_adi_cmd_create_menu	(GtkAdiCmd * self);
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
void 	gtk_adi_cmd_fix_toggled	(GtkAdiCmd * self,
					GtkAdiState state);
					
#ifdef ADI_DO_TRACE
#define ADI_TRACE(msg,...) g_printf("ADI: "msg"\n",__VA_ARGS__);
#else
#define ADI_TRACE(msg,...)
#endif /* ADI_DO_TRACE */

G_END_DECLS

#endif /* __GTK_ADI_CMD_H__ */
