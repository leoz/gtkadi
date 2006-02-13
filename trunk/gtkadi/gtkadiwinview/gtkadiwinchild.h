/* GTK ADI Library
 * gtkadiwinchild.h: ADI Window Child
 * Copyright (C) 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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
#include <gtkaditype.h>

#ifndef __GTK_ADI_WIN_CHILD_H__
#define __GTK_ADI_WIN_CHILD_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_WIN_CHILD	(gtk_adi_win_child_get_type())
#define GTK_ADI_WIN_CHILD(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_win_child_get_type(), GtkAdiWinChild)
#define GTK_ADI_WIN_CHILD_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_win_child_get_type(), GtkAdiWinChild const)
#define GTK_ADI_WIN_CHILD_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_win_child_get_type(), GtkAdiWinChildClass)
#define GTK_IS_ADI_WIN_CHILD(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_win_child_get_type ())

#define GTK_ADI_WIN_CHILD_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_win_child_get_type(), GtkAdiWinChildClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_WIN_CHILD__
#define __TYPEDEF_GTK_ADI_WIN_CHILD__
typedef struct _GtkAdiWinChild GtkAdiWinChild;
#endif
struct _GtkAdiWinChild {
	GtkWindow __parent__;
	/*< public >*/
	GtkWidget *widget;
	GtkAdiLayout layout;
	gboolean show_close;
};

/*
 * Class definition
 */
typedef struct _GtkAdiWinChildClass GtkAdiWinChildClass;
struct _GtkAdiWinChildClass {
	GtkWindowClass __parent__;
};


/*
 * Public methods
 */
GType gtk_adi_win_child_get_type (void);
GtkWidget* gtk_adi_win_child_new (GtkWidget *widget, GtkAdiLayout layout);

G_END_DECLS

#endif /* __GTK_ADI_WIN_CHILD_H__ */
