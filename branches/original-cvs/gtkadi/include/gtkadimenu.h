/* GTK ADI Library
 * gtkadimenu.h: ADI Menu Widget
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

#include <glib.h>
#include <glib-object.h>


#include <gtk/gtk.h>
#include "gtkadi.h"

#ifndef __GTK_ADI_MENU_H__
#define __GTK_ADI_MENU_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_MENU	(gtk_adi_menu_get_type())
#define GTK_ADI_MENU(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_menu_get_type(), GtkAdiMenu)
#define GTK_ADI_MENU_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_menu_get_type(), GtkAdiMenu const)
#define GTK_ADI_MENU_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_menu_get_type(), GtkAdiMenuClass)
#define GTK_IS_ADI_MENU(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_menu_get_type ())

#define GTK_ADI_MENU_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_menu_get_type(), GtkAdiMenuClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_MENU__
#define __TYPEDEF_GTK_ADI_MENU__
typedef struct _GtkAdiMenu GtkAdiMenu;
#endif
struct _GtkAdiMenu {
	GtkMenuItem __parent__;
	/*< public >*/
	GtkObject * cmd;
	GtkTooltips * tooltips;
	GtkWidget * menu;
	GtkWidget * item_new;
	GtkWidget * item_new_h;
	GtkWidget * item_new_v;
	GtkWidget * sep_new;
	GtkWidget * item_cls;
	GtkWidget * item_cls_all;
	GtkWidget * sep_cls;
	GtkWidget * item_next;
	GtkWidget * item_prev;
	GtkWidget * sep_nav;
	GtkWidget * item_tile_h;
	GtkWidget * item_tile_v;
	GtkWidget * sep_tile;
	GtkWidget * item_mode;
	GtkWidget * menu_mode;
	GtkWidget * item_paned;
	GtkWidget * item_box;
	GtkWidget * item_fix;
	GtkWidget * sep_mode;
};

/*
 * Class definition
 */
typedef struct _GtkAdiMenuClass GtkAdiMenuClass;
struct _GtkAdiMenuClass {
	GtkMenuItemClass __parent__;
};


/*
 * Public methods
 */
GType	gtk_adi_menu_get_type	(void);
void 	gtk_adi_menu_mode_set	(GtkAdiMenu * self,
					GtkAdiMode mode);
void 	gtk_adi_menu_fix_set	(GtkAdiMenu * self,
					GtkAdiState state);
GtkWidget * 	gtk_adi_menu_new	(GtkObject * cmd);
void 	gtk_adi_menu_set_close_items	(GtkAdiMenu * self,
					gboolean enable);
void 	gtk_adi_menu_set_nav_items	(GtkAdiMenu * self,
					gboolean next,
					gboolean prev);
void 	gtk_adi_menu_set_tile_items	(GtkAdiMenu * self,
					gboolean tile_h,
					gboolean tile_v);
GtkWidget * 	gtk_adi_menu_get_submenu	(GtkAdiMenu * self);

G_END_DECLS

#endif
