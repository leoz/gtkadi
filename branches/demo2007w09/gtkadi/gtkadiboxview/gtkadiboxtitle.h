/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* GTK ADI Library
 * gtkadiboxtitle.h: ADI Box Title Widget
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
#include "gtkadititle.h"

#ifndef __GTK_ADI_BOX_TITLE_H__
#define __GTK_ADI_BOX_TITLE_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_BOX_TITLE	(gtk_adi_box_title_get_type())
#define GTK_ADI_BOX_TITLE(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_box_title_get_type(), GtkAdiBoxTitle)
#define GTK_ADI_BOX_TITLE_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_box_title_get_type(), GtkAdiBoxTitle const)
#define GTK_ADI_BOX_TITLE_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_box_title_get_type(), GtkAdiBoxTitleClass)
#define GTK_IS_ADI_BOX_TITLE(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_box_title_get_type ())

#define GTK_ADI_BOX_TITLE_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_box_title_get_type(), GtkAdiBoxTitleClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_BOX_TITLE__
#define __TYPEDEF_GTK_ADI_BOX_TITLE__
typedef struct _GtkAdiBoxTitle GtkAdiBoxTitle;
#endif
struct _GtkAdiBoxTitle {
	GtkAdiTitle __parent__;
	/*< public >*/
	GSList * radiobutton_group;
	GtkObject * adi_color;
	GtkWidget * radiobutton;
	GtkWidget * radio_hbox;
};

/*
 * Class definition
 */
typedef struct _GtkAdiBoxTitleClass GtkAdiBoxTitleClass;
struct _GtkAdiBoxTitleClass {
	GtkAdiTitleClass __parent__;
};


/*
 * Public methods
 */
GType	gtk_adi_box_title_get_type	(void);
GtkWidget * 	gtk_adi_box_title_new	(void);
void 	gtk_adi_box_title_set_active	(GtkAdiBoxTitle * self);
void 	gtk_adi_box_title_set_group	(GtkAdiBoxTitle * self,
					GSList * group);
void 	gtk_adi_box_title_set_color	(GtkAdiBoxTitle * self,
					GtkObject * adi_color);
GSList * 	gtk_adi_box_title_get_group	(GtkAdiBoxTitle * self);

G_END_DECLS

#endif
