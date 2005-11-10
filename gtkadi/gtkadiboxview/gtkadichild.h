/* GTK ADI Library
 * gtkadichild.h: ADI Child Widget
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

#ifndef __GTK_ADI_CHILD_H__
#define __GTK_ADI_CHILD_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_CHILD	(gtk_adi_child_get_type())
#define GTK_ADI_CHILD(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_child_get_type(), GtkAdiChild)
#define GTK_ADI_CHILD_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_child_get_type(), GtkAdiChild const)
#define GTK_ADI_CHILD_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_child_get_type(), GtkAdiChildClass)
#define GTK_IS_ADI_CHILD(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_child_get_type ())

#define GTK_ADI_CHILD_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_child_get_type(), GtkAdiChildClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_CHILD__
#define __TYPEDEF_GTK_ADI_CHILD__
typedef struct _GtkAdiChild GtkAdiChild;
#endif
struct _GtkAdiChild {
	GtkFrame __parent__;
	/*< public >*/
	GtkWidget * box;
	GtkWidget * title;
	GtkWidget * separator;
	GtkWidget * widget;
	gboolean show_tab;
};

/*
 * Class definition
 */
typedef struct _GtkAdiChildClass GtkAdiChildClass;
struct _GtkAdiChildClass {
	GtkFrameClass __parent__;
};


/*
 * Public methods
 */
GType	gtk_adi_child_get_type	(void);
GtkWidget * 	gtk_adi_child_new	(void);
void 	gtk_adi_child_set_active	(GtkAdiChild * self);
void 	gtk_adi_child_set_group	(GtkAdiChild * self,
					GSList * group);
void 	gtk_adi_child_set_color	(GtkAdiChild * self,
					GtkObject * adi_color);
void 	gtk_adi_child_set_widget	(GtkAdiChild * self,
					GtkWidget * widget);
void gtk_adi_child_remove_widget (GtkAdiChild * self);
void 	gtk_adi_child_set_parent	(GtkAdiChild * self,
					GtkWidget * adi_parent);
void 	gtk_adi_child_set_text	(GtkAdiChild * self,
					const gchar * str);
void 	gtk_adi_child_set_icon	(GtkAdiChild * self,
					GdkPixbuf * icon);
GSList * 	gtk_adi_child_get_group	(GtkAdiChild * self);
void gtk_adi_child_set_layout (GtkAdiChild *self, GtkAdiLayout layout);
GtkAdiLayout gtk_adi_child_get_layout (GtkAdiChild *self);
void gtk_adi_child_set_close_button (GtkAdiChild *self, gboolean enabled);

G_END_DECLS

#endif
