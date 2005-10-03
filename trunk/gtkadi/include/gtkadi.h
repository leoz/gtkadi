/* GTK ADI Library
 * gtkadi.h: ADI Widget
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

#ifndef __GTK_ADI_H__
#define __GTK_ADI_H__

G_BEGIN_DECLS

typedef GtkWidget* (*GtkAdiCreateChildFunc) (void);
typedef GdkPixbuf* (*GtkAdiCreateIconFunc)  (GtkWidget* widget);
typedef gchar*     (*GtkAdiCreateTitleFunc) (void);


/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI	(gtk_adi_get_type())
#define GTK_ADI(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_get_type(), GtkAdi)
#define GTK_ADI_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_get_type(), GtkAdi const)
#define GTK_ADI_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_get_type(), GtkAdiClass)
#define GTK_IS_ADI(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_get_type ())

#define GTK_ADI_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_get_type(), GtkAdiClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI__
#define __TYPEDEF_GTK_ADI__
typedef struct _GtkAdi GtkAdi;
#endif
struct _GtkAdi {
	GtkEventBox __parent__;
	/*< public >*/
	GtkAdiCreateChildFunc child_func;
	GtkAdiCreateIconFunc icon_func;
	GtkAdiCreateTitleFunc title_func;
	GtkObject * cmd;
	GtkWidget * box_view;
	GtkWidget * tab_view;
	GtkWidget * cur_view;
};

/*
 * Class definition
 */
typedef struct _GtkAdiClass GtkAdiClass;
struct _GtkAdiClass {
	GtkEventBoxClass __parent__;
};


/*
 * Public methods
 */
GType	gtk_adi_get_type	(void);
GtkWidget * 	gtk_adi_new	(void);
void 	gtk_adi_set_child_func	(GtkAdi * self,
					GtkAdiCreateChildFunc child_func);
void 	gtk_adi_set_icon_func	(GtkAdi * self,
					GtkAdiCreateIconFunc icon_func);
void 	gtk_adi_set_title_func	(GtkAdi * self,
					GtkAdiCreateTitleFunc title_func);
GtkWidget * 	gtk_adi_create_toolbar	(GtkAdi * self);
GtkWidget * 	gtk_adi_create_menu	(GtkAdi * self);
void 	gtk_adi_user_add_child	(GtkAdi * self);
void 	gtk_adi_user_add_child_with_layout	(GtkAdi * self,
					GtkAdiLayout layout);
gboolean 	gtk_adi_can_previous_child	(GtkAdi * self);
gboolean 	gtk_adi_can_next_child	(GtkAdi * self);
gboolean 	gtk_adi_can_tile_h	(GtkAdi * self);
gboolean 	gtk_adi_can_tile_v	(GtkAdi * self);
gboolean 	gtk_adi_has_children	(GtkAdi * self);
void 	gtk_adi_remove_current_child	(GtkAdi * self);
void 	gtk_adi_remove_all_children	(GtkAdi * self);
void 	gtk_adi_set_previous_child	(GtkAdi * self);
void 	gtk_adi_set_next_child	(GtkAdi * self);
void 	gtk_adi_change_mode	(GtkAdi * self,
					GtkAdiMode mode);
void 	gtk_adi_change_state	(GtkAdi * self,
					GtkAdiState state);
void 	gtk_adi_change_color	(GtkAdi * self,
					GtkAdiColorType color);

G_END_DECLS

#endif
