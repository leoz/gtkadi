/* GTK ADI Library
 * gtkadititle.c: ADI Title Widget
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

#include "gtkadititle.h"
#include "gtkadiview.h"
#include "gtkadistock.h"

/* here are local prototypes */
static void gtk_adi_title_class_init (GtkAdiTitleClass *c);
static void gtk_adi_title_close_button_released (GtkAdiTitle *self, GtkWidget *close_button);
static void gtk_adi_title_init (GtkAdiTitle *self);

/* pointer to the class of our parent */
static GtkEventBoxClass *parent_class = NULL;

GType
gtk_adi_title_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiTitleClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_title_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiTitle),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_title_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_EVENT_BOX, "GtkAdiTitle", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiTitle *)g_object_new(gtk_adi_title_get_type(), NULL))

static void 
gtk_adi_title_class_init (GtkAdiTitleClass * c)
{
	parent_class = g_type_class_ref (GTK_TYPE_EVENT_BOX);
}

static void 
gtk_adi_title_init (GtkAdiTitle * self)
{
	gtk_container_set_border_width (GTK_CONTAINER (self), 1);

	self->hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (self), self->hbox);

	self->image = gtk_image_new_from_pixbuf (NULL);
	gtk_box_pack_start (GTK_BOX (self->hbox), self->image, FALSE, FALSE, 0);
	gtk_misc_set_padding (GTK_MISC (self->image), 2, 0);

	self->label = gtk_label_new (NULL);
	gtk_adi_title_set_widget_style (self->label);

	self->vbox = gtk_vbox_new (TRUE, 0);
	gtk_box_pack_end (GTK_BOX (self->hbox), self->vbox, FALSE, FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (self->vbox), 2);

	self->close_button = gtk_button_new ();
	gtk_box_pack_start (GTK_BOX (self->vbox), self->close_button,
						FALSE, FALSE, 0);
	gtk_widget_set_size_request (self->close_button, 16, 16);
	GTK_WIDGET_UNSET_FLAGS (self->close_button, GTK_CAN_FOCUS);

	/* Default GTK close icon could be used also. */
	/*
	self->close_image = gtk_image_new_from_stock ("gtk-close",
												  GTK_ICON_SIZE_MENU);
	*/
	self->close_image = gtk_image_new_from_stock (
							GTK_ADI_STOCK_CLOSE_WINDOW,
							GTK_ICON_SIZE_MENU);
	gtk_container_add (GTK_CONTAINER (self->close_button),
					   self->close_image);
	
	gtk_widget_set_style(self->close_button, gtk_widget_get_style (self->close_button));				   
	
	self->layout = GTK_ADI_HORIZONTAL;
}


void 
gtk_adi_title_set_text_font (GtkAdiTitle * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	
	GtkStyle *style = gtk_widget_get_style(self->label);
	pango_font_description_set_size(style->font_desc, 8 * PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
	gtk_widget_modify_font(self->label, style->font_desc);
}

void 
gtk_adi_title_set_widget_style (GtkWidget * widget)
{
	g_return_if_fail (widget != NULL);
	
	GtkStyle* style = gtk_style_copy (widget->style);

	/* Set size */
	style->xthickness = 0;
	style->ythickness = 0;

	gtk_widget_set_style (widget, style);
	g_object_unref (G_OBJECT (style));
}

static void 
gtk_adi_title_close_button_released (GtkAdiTitle * self, GtkWidget * close_button)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	g_return_if_fail (close_button != NULL);
	
	gtk_adi_view_remove_child (GTK_ADI_VIEW (self->adi_parent),
							   self->adi_child,
	                           TRUE);
}

GtkWidget * 
gtk_adi_title_new (void)
{
	return GTK_WIDGET(GET_NEW);
}

void 
gtk_adi_title_set_child (GtkAdiTitle * self, GtkWidget * adi_child)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	g_return_if_fail (adi_child != NULL);
	
	self->adi_child = adi_child;
	g_signal_connect_swapped ((gpointer) self->close_button, "released",
							  G_CALLBACK (gtk_adi_title_close_button_released),
							  GTK_OBJECT (self));
}

void 
gtk_adi_title_set_parent (GtkAdiTitle * self, GtkWidget * adi_parent)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	g_return_if_fail (adi_parent != NULL);

	self->adi_parent = adi_parent;
}

void 
gtk_adi_title_set_text (GtkAdiTitle *self, const gchar *str)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	
	if (str) {
		gtk_label_set_text(GTK_LABEL(self->label), str);
	}
}

const gchar* 
gtk_adi_title_get_text (GtkAdiTitle *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_TITLE (self), NULL);
	
	return gtk_label_get_text(GTK_LABEL(self->label));
}

void 
gtk_adi_title_set_icon (GtkAdiTitle *self, GdkPixbuf *icon)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	
	if (icon) {
		gtk_image_set_from_pixbuf(GTK_IMAGE(self->image), icon);
	}
}

GdkPixbuf* 
gtk_adi_title_get_icon (GtkAdiTitle *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_TITLE (self), NULL);
	
	return gtk_image_get_pixbuf(GTK_IMAGE(self->image));
}

void
gtk_adi_title_set_layout (GtkAdiTitle *self, GtkAdiLayout layout)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	
	self->layout = layout;
}

GtkAdiLayout
gtk_adi_title_get_layout (GtkAdiTitle *self)
{
	g_return_val_if_fail (self != NULL, GTK_ADI_HORIZONTAL);
	g_return_val_if_fail (GTK_IS_ADI_TITLE (self), GTK_ADI_HORIZONTAL);
	
	return self->layout;
}

void
gtk_adi_title_set_close_button (GtkAdiTitle *self, gboolean enabled)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	
	if (enabled) {
		gtk_widget_show(self->close_button);
	}
	else {
		gtk_widget_hide(self->close_button);
	}
}
