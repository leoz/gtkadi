/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* GTK ADI Library
 * gtkadiwinview.h: ADI Window View
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
#include "gtkadiconview.h"

#ifndef __GTK_ADI_WIN_VIEW_H__
#define __GTK_ADI_WIN_VIEW_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_WIN_VIEW	(gtk_adi_win_view_get_type())
#define GTK_ADI_WIN_VIEW(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_win_view_get_type(), GtkAdiWinView)
#define GTK_ADI_WIN_VIEW_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_win_view_get_type(), GtkAdiWinView const)
#define GTK_ADI_WIN_VIEW_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_win_view_get_type(), GtkAdiWinViewClass)
#define GTK_IS_ADI_WIN_VIEW(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_win_view_get_type ())

#define GTK_ADI_WIN_VIEW_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_win_view_get_type(), GtkAdiWinViewClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_WIN_VIEW__
#define __TYPEDEF_GTK_ADI_WIN_VIEW__
typedef struct _GtkAdiWinView GtkAdiWinView;
#endif
struct _GtkAdiWinView {
	GtkAdiConView __parent__;
};

/*
 * Class definition
 */
typedef struct _GtkAdiWinViewClass GtkAdiWinViewClass;
struct _GtkAdiWinViewClass {
	GtkAdiConViewClass __parent__;
        void (* focus_child) (GtkAdiWinView * view);	
};

/*
 * Public methods
 */
GType gtk_adi_win_view_get_type (void);
GtkWidget* gtk_adi_win_view_new	(GtkAdi* adi);

G_END_DECLS

#endif /* __GTK_ADI_WIN_VIEW_H__ */
