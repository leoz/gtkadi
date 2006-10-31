/* GTK ADI Library
 * gtkadicolor.h: ADI Color Object
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

#ifndef __GTK_ADI_COLOR_H__
#define __GTK_ADI_COLOR_H__

G_BEGIN_DECLS

typedef enum {
	GTK_ADI_STATE_INACTIVE = 0,
	GTK_ADI_STATE_ACTIVE = 1
} GtkAdiStateType;
#define GTK_TYPE_ADI_STATE_TYPE gtk_adi_state_type_get_type()
GType gtk_adi_state_type_get_type (void);


/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_COLOR	(gtk_adi_color_get_type())
#define GTK_ADI_COLOR(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_color_get_type(), GtkAdiColor)
#define GTK_ADI_COLOR_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_color_get_type(), GtkAdiColor const)
#define GTK_ADI_COLOR_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_color_get_type(), GtkAdiColorClass)
#define GTK_IS_ADI_COLOR(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_color_get_type ())

#define GTK_ADI_COLOR_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_color_get_type(), GtkAdiColorClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_COLOR__
#define __TYPEDEF_GTK_ADI_COLOR__
typedef struct _GtkAdiColor GtkAdiColor;
#endif
struct _GtkAdiColor {
	GtkObject __parent__;
	/*< public >*/
	GdkColor title[2];
	GdkColor text[2];
	GtkAdiColorType type;
};

/*
 * Class definition
 */
typedef struct _GtkAdiColorClass GtkAdiColorClass;
struct _GtkAdiColorClass {
	GtkObjectClass __parent__;
};


/*
 * Public methods
 */
GType	gtk_adi_color_get_type	(void);
void 	gtk_adi_color_set	(GtkAdiColor * self,
					GtkAdiColorType type);
GdkColor * 	gtk_adi_color_inactive_title	(GtkAdiColor * self);
GdkColor * 	gtk_adi_color_active_title	(GtkAdiColor * self);
GdkColor * 	gtk_adi_color_inactive_text	(GtkAdiColor * self);
GdkColor * 	gtk_adi_color_active_text	(GtkAdiColor * self);
GtkObject * 	gtk_adi_color_new	(void);

G_END_DECLS

#endif
