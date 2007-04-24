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

#include "gtkadiboxtitle.h"
#include "gtkadiview.h"
#include "gtkadicolor.h"

/* here are local prototypes */
static void gtk_adi_box_title_class_init (GtkAdiBoxTitleClass * c) G_GNUC_UNUSED;
static void gtk_adi_box_title_set_text_color (GtkAdiBoxTitle * self) G_GNUC_UNUSED;
static void gtk_adi_box_title_set_own_color (GtkAdiBoxTitle * self, gboolean is_active) G_GNUC_UNUSED;
static void gtk_adi_box_title_set_widget_color (GtkAdiBoxTitle * self, GtkWidget * widget, gboolean is_active) G_GNUC_UNUSED;
static void gtk_adi_box_title_radiobutton_toggled (GtkAdiBoxTitle * self, GtkWidget * radiobutton) G_GNUC_UNUSED;
static void gtk_adi_box_title_init (GtkAdiBoxTitle * self) G_GNUC_UNUSED;

/* pointer to the class of our parent */
static GtkAdiTitleClass *parent_class = NULL;

GType
gtk_adi_box_title_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiBoxTitleClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_box_title_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiBoxTitle),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_box_title_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_ADI_TITLE, "GtkAdiBoxTitle", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiBoxTitle *)g_object_new(gtk_adi_box_title_get_type(), NULL))

static void 
gtk_adi_box_title_class_init (GtkAdiBoxTitleClass * c G_GNUC_UNUSED)
{
	parent_class = g_type_class_ref (GTK_TYPE_ADI_TITLE);
}

static void 
gtk_adi_box_title_init (GtkAdiBoxTitle * self G_GNUC_UNUSED)
{
	self->radiobutton = gtk_radio_button_new (NULL);
	gtk_box_pack_start (GTK_BOX (GTK_ADI_TITLE(self)->hbox), self->radiobutton, TRUE, TRUE, 0);
	gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON (self->radiobutton), FALSE);
	gtk_widget_set_size_request (self->radiobutton, -1, 17);
	GTK_WIDGET_UNSET_FLAGS (self->radiobutton, GTK_CAN_FOCUS);

	self->radio_hbox = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (self->radiobutton), self->radio_hbox);

	gtk_box_pack_start (GTK_BOX (self->radio_hbox), GTK_ADI_TITLE(self)->label, FALSE, FALSE, 0);

	g_signal_connect_swapped ((gpointer) self->radiobutton, "toggled",
	G_CALLBACK (gtk_adi_box_title_radiobutton_toggled),
	GTK_OBJECT (self));

	g_signal_connect_swapped ((gpointer) self, "button_release_event",
	G_CALLBACK (gtk_adi_box_title_set_active),
	GTK_OBJECT (self));
}


static void 
gtk_adi_box_title_set_text_color (GtkAdiBoxTitle * self)
{
	GdkColor*   active = NULL;
	GdkColor* inactive = NULL;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_TITLE (self));
	
	active   = gtk_adi_color_active_text   (GTK_ADI_COLOR(self->adi_color));
	inactive = gtk_adi_color_inactive_text (GTK_ADI_COLOR(self->adi_color));

	gtk_widget_modify_fg (GTK_ADI_TITLE(self)->label, GTK_STATE_NORMAL  , inactive);
	gtk_widget_modify_fg (GTK_ADI_TITLE(self)->label, GTK_STATE_ACTIVE  , active);
	gtk_widget_modify_fg (GTK_ADI_TITLE(self)->label, GTK_STATE_PRELIGHT, active);
}

static void 
gtk_adi_box_title_set_own_color (GtkAdiBoxTitle * self, gboolean is_active)
{
	GdkColor* color = NULL;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_TITLE (self));
	
	if ( self->adi_color != NULL ) {
		if ( is_active == TRUE ) {
			color = gtk_adi_color_active_title   (GTK_ADI_COLOR(self->adi_color));
		}
		else {
			color = gtk_adi_color_inactive_title (GTK_ADI_COLOR(self->adi_color));
		}
	}

	if ( color == NULL ) {
		return;
	}

	gtk_widget_modify_bg (GTK_WIDGET(self), GTK_STATE_NORMAL, color);
}

static void 
gtk_adi_box_title_set_widget_color (GtkAdiBoxTitle * self, GtkWidget * widget, gboolean is_active)
{
	GdkColor* color = NULL;
	GtkStyle* style = NULL;

	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_TITLE (self));
	g_return_if_fail (widget != NULL);
	
	style = gtk_style_copy (widget->style);

	if ( self->adi_color != NULL ) {
		if ( is_active == TRUE ) {
			color = gtk_adi_color_active_title   (GTK_ADI_COLOR(self->adi_color));
		}
		else {
			color = gtk_adi_color_inactive_title (GTK_ADI_COLOR(self->adi_color));
		}
	}

	/* Set size */
	style->xthickness = 0;
	style->ythickness = 0;


	if ( color != NULL ) {
	    style->bg[GTK_STATE_NORMAL  ] = *color;
	    style->bg[GTK_STATE_ACTIVE  ] = *color;
	    style->bg[GTK_STATE_PRELIGHT] = *color;
//		return;


	/* Set colors */

	    style->fg[GTK_STATE_NORMAL  ] = style->bg[GTK_STATE_NORMAL  ];
	    style->fg[GTK_STATE_ACTIVE  ] = style->bg[GTK_STATE_ACTIVE  ];
	    style->fg[GTK_STATE_PRELIGHT] = style->bg[GTK_STATE_PRELIGHT];

	}
	
	gtk_widget_set_style (widget, style);
	g_object_unref (G_OBJECT (style));
}

static void 
gtk_adi_box_title_radiobutton_toggled (GtkAdiBoxTitle * self, GtkWidget * radiobutton)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_TITLE (self));
	g_return_if_fail (radiobutton != NULL);
	
	if ( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radiobutton)) ) {
		gtk_adi_view_set_current_child (GTK_ADI_VIEW (GTK_ADI_TITLE(self)->adi_parent),
										GTK_ADI_TITLE(self)->adi_child);
		gtk_adi_box_title_set_own_color (self, TRUE);
		gtk_adi_box_title_set_widget_color (self, radiobutton, TRUE);
	}
	else {
		gtk_adi_box_title_set_own_color (self, FALSE);
		gtk_adi_box_title_set_widget_color (self, radiobutton, FALSE);
	}
}


GtkWidget* 
gtk_adi_box_title_new (void)
{
	return GTK_WIDGET(GET_NEW);
}

void 
gtk_adi_box_title_set_active (GtkAdiBoxTitle * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_TITLE (self));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->radiobutton), TRUE);
}

void 
gtk_adi_box_title_set_group (GtkAdiBoxTitle * self, GSList * group)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_TITLE (self));
	
	self->radiobutton_group = group;
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (self->radiobutton), self->radiobutton_group);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->radiobutton), TRUE);
}

void 
gtk_adi_box_title_set_color (GtkAdiBoxTitle * self, GtkObject * adi_color)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_BOX_TITLE (self));
	g_return_if_fail (adi_color != NULL);
	
	self->adi_color = adi_color;
	gtk_adi_box_title_radiobutton_toggled (self, self->radiobutton);
	gtk_adi_box_title_set_text_color (self);
	gtk_adi_title_set_text_font (GTK_ADI_TITLE(self));
}

GSList * 
gtk_adi_box_title_get_group (GtkAdiBoxTitle * self)
{
	g_return_val_if_fail (self != NULL, (GSList * )0);
	g_return_val_if_fail (GTK_IS_ADI_BOX_TITLE (self), (GSList * )0);
	
	return gtk_radio_button_get_group (GTK_RADIO_BUTTON (self->radiobutton));
}
