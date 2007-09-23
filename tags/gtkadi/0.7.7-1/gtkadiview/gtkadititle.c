/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is GtkAdi library.
 *
 * The Initial Developer of the Original Code is
 * Leonid Zolotarev <leonid.zolotarev@gmail.com>.
 * Portions created by the Initial Developer are Copyright (C) 2003-2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s): Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/* #define ADI_DO_TRACE */
#include "gtkadititle.h"
#include "gtkadiview.h"
#include "gtkadistock.h"
#include "gtkadiutils.h"

/* here are local prototypes */
static void gtk_adi_title_class_init (GtkAdiTitleClass *c);
static void gtk_adi_title_close_button_released (GtkWidget *close_button, GtkAdiTitle *self);
static void gtk_adi_title_init (GtkAdiTitle *self);
void gtk_adi_label_size_request(GtkWidget *widget, GtkRequisition *req, gpointer data);

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
	gtk_label_set_line_wrap (GTK_LABEL(self->label), TRUE);
	g_signal_connect(G_OBJECT(self->label), "size-request", G_CALLBACK(gtk_adi_label_size_request), NULL);
    	
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
    
    gtk_button_set_relief (GTK_BUTTON (self->close_button), GTK_RELIEF_NONE);
    gtk_container_set_border_width (GTK_CONTAINER (self->close_button), 0);

	self->close_image = gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU);
    //self->close_image = gtk_image_new_from_stock (
	//						GTK_ADI_STOCK_CLOSE_WINDOW,
	//						GTK_ICON_SIZE_MENU);
	gtk_container_add (GTK_CONTAINER (self->close_button),
					   self->close_image);
	
	gtk_widget_set_style(self->close_button, gtk_widget_get_style (self->close_button));				   
	
//	g_signal_connect_swapped ((gpointer) self->close_button, "released",
//							  G_CALLBACK (gtk_adi_title_close_button_released),
//							  GTK_OBJECT (self));
	g_signal_connect (self->close_button, "released", 
			    G_CALLBACK (gtk_adi_title_close_button_released),
			    self);

	self->layout = GTK_ADI_VERTICAL;
//	self->layout = GTK_ADI_HORIZONTAL;
}

void
gtk_adi_label_size_request(GtkWidget *widget, GtkRequisition *requisition, gpointer data)
{
    GtkRequisition req;
    if(widget)
    {
        gtk_widget_size_request (widget, &req);
        if(req.width > MAX_LABEL_WIDTH)
        {
            requisition->width = MAX_LABEL_WIDTH;
        }else
            requisition->width = req.width;

        if(req.height < MIN_LABEL_HEIGHT)
        {
            requisition->height = MIN_LABEL_HEIGHT;
        }else
            requisition->height = req.height;
    } 
 
}

void 
gtk_adi_title_set_text_font (GtkAdiTitle * self)
{
	GtkStyle *style = NULL;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	
	style = gtk_widget_get_style(self->label);

	pango_font_description_set_size(style->font_desc, 12 * PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
	gtk_widget_modify_font(self->label, style->font_desc);
}

void 
gtk_adi_title_set_widget_style (GtkWidget * widget)
{
	GtkStyle *style = NULL;

	g_return_if_fail (widget != NULL);
	
	style = gtk_style_copy (widget->style);

	/* Set size */
	style->xthickness = 0;
	style->ythickness = 0;

	gtk_widget_set_style (widget, style);
	g_object_unref (G_OBJECT (style));
}

static void 
gtk_adi_title_close_button_released (GtkWidget * close_button, GtkAdiTitle * self)
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
gtk_adi_title_set_icon (GtkAdiTitle *self, const GdkPixbuf *icon)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_TITLE (self));
	if (icon) {
		gtk_image_set_from_pixbuf(GTK_IMAGE(self->image), gdk_pixbuf_scale_simple(icon, 26, 26, GDK_INTERP_NEAREST));
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
	
	ADI_TRACE("ADI title close button set to : %d", enabled)
	
	if (enabled) {
		if (!gtk_widget_get_parent(self->close_button)) {
			gtk_box_pack_start (GTK_BOX (self->vbox), self->close_button,
								FALSE, FALSE, 0);
			gtk_widget_show(self->close_button);
			g_object_unref(self->close_button);
		}
	}
	else {
		g_object_ref(self->close_button);
		gtk_widget_hide(self->close_button);
		gtk_container_remove(GTK_CONTAINER(self->vbox), self->close_button);
	}
}

gboolean gtk_adi_title_get_close_button (GtkAdiTitle *self)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_ADI_TITLE (self), FALSE);
	g_return_val_if_fail (self->close_button != NULL, FALSE);
	
	return GTK_WIDGET_VISIBLE(self->close_button);
}
