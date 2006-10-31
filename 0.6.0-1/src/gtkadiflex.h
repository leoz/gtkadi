/* GTK ADI Library
 * gtkadiflex.h: ADI Flex Object
 * Copyright (C) 2005 - 2006, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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

#ifndef __GTK_ADI_FLEX_H__
#define __GTK_ADI_FLEX_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_FLEX	(gtk_adi_flex_get_type())
#define GTK_ADI_FLEX(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_flex_get_type(), GtkAdiFlex)
#define GTK_ADI_FLEX_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_flex_get_type(), GtkAdiFlex const)
#define GTK_ADI_FLEX_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_flex_get_type(), GtkAdiFlexClass)
#define GTK_IS_ADI_FLEX(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_flex_get_type ())

#define GTK_ADI_FLEX_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_flex_get_type(), GtkAdiFlexClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_FLEX__
#define __TYPEDEF_GTK_ADI_FLEX__
typedef struct _GtkAdiFlex GtkAdiFlex;
#endif
struct _GtkAdiFlex {
	GtkObject __parent__;
	/*< public >*/
	GtkAdi *adi;
	GtkAdiLayout __layout;
	GtkAdiLayout __layout_minor;
	GtkAdiLayout __layout_major;
	gint __minor;
	gint __major;
	gint __total;
};

/*
 * Class definition
 */
typedef struct _GtkAdiFlexClass GtkAdiFlexClass;
struct _GtkAdiFlexClass {
	GtkObjectClass __parent__;
};

/*
 * Public methods
 */
GType gtk_adi_flex_get_type	(void);
GtkObject* gtk_adi_flex_new	(GtkAdi *adi);
GtkAdiLayout gtk_adi_flex_add_layout (GtkAdiFlex *self);
void gtk_adi_flex_remove_layout (GtkAdiFlex *self, GtkAdiLayout layout);

G_END_DECLS

#endif /* __GTK_ADI_FLEX_H__ */
