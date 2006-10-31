/* GTK ADI Library
 * gtkaditoolbar.h: ADI Toolbar Widget
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
