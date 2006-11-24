/* GTK ADI Library
 * gtkadititle.h: ADI Title Widget
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
#include "gtkaditype.h"

#ifndef __GTK_ADI_TITLE_H__
#define __GTK_ADI_TITLE_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_TITLE	(gtk_adi_title_get_type())
#define GTK_ADI_TITLE(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_title_get_type(), GtkAdiTitle)
#define GTK_ADI_TITLE_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_title_get_type(), GtkAdiTitle const)
#define GTK_ADI_TITLE_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_title_get_type(), GtkAdiTitleClass)
#define GTK_IS_ADI_TITLE(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_title_get_type ())

#define GTK_ADI_TITLE_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_title_get_type(), GtkAdiTitleClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_TITLE__
#define __TYPEDEF_GTK_ADI_TITLE__
typedef struct _GtkAdiTitle GtkAdiTitle;
#endif

#define MAX_LABEL_WIDTH 50

struct _GtkAdiTitle {
	GtkEventBox __parent__;
	/*< public >*/
	GtkWidget *adi_parent;
	GtkWidget *adi_child;
	GtkWidget *hbox;
	GtkWidget *image;
	GtkWidget *label;
	GtkWidget *vbox;
	GtkWidget *close_button;
	GtkWidget *close_image;
	GtkAdiLayout layout;
};

/*
 * Class definition
 */
typedef struct _GtkAdiTitleClass GtkAdiTitleClass;
struct _GtkAdiTitleClass {
	GtkEventBoxClass __parent__;
};


/*
 * Public methods
 */
GType	gtk_adi_title_get_type	(void);
void 	gtk_adi_title_set_text_font	(GtkAdiTitle * self);
void 	gtk_adi_title_set_widget_style	(GtkWidget * widget);
GtkWidget * 	gtk_adi_title_new	(void);
void 	gtk_adi_title_set_child	(GtkAdiTitle * self,
					GtkWidget * adi_child);
void 	gtk_adi_title_set_parent	(GtkAdiTitle * self,
					GtkWidget * adi_parent);
void gtk_adi_title_set_text	(GtkAdiTitle *self, const gchar *str);
const gchar* gtk_adi_title_get_text	(GtkAdiTitle *self);
void gtk_adi_title_set_icon	(GtkAdiTitle *self, const GdkPixbuf *icon);
GdkPixbuf* gtk_adi_title_get_icon (GtkAdiTitle *self);
void gtk_adi_title_set_layout (GtkAdiTitle *self, GtkAdiLayout layout);
GtkAdiLayout gtk_adi_title_get_layout (GtkAdiTitle *self);
void gtk_adi_title_set_close_button (GtkAdiTitle *self, gboolean enabled);
gboolean gtk_adi_title_get_close_button (GtkAdiTitle *self);

G_END_DECLS

#endif /* __GTK_ADI_TITLE_H__ */
