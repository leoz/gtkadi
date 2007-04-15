/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* GTK ADI Library
 * gtkadiflex.c: ADI Flex Object
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

#include "gtkadiutils.h"
#include "gtkadiview.h"
#include "gtkadiflex.h"
#include <math.h>

/* here are local prototypes */
static void gtk_adi_flex_class_init (GtkAdiFlexClass * c);
static void gtk_adi_flex_init (GtkAdiFlex * self);

/* pointer to the class of our parent */
static GtkObjectClass *parent_class = NULL;

GType
gtk_adi_flex_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiFlexClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_flex_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiFlex),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_flex_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_OBJECT, "GtkAdiFlex", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiFlex *)g_object_new(gtk_adi_flex_get_type(), NULL))

static void 
gtk_adi_flex_class_init (GtkAdiFlexClass *c)
{
	parent_class = g_type_class_ref (GTK_TYPE_OBJECT);
}

static void 
gtk_adi_flex_init (GtkAdiFlex *self)
{
	self->adi = NULL;
	self->__layout = GTK_ADI_VERTICAL;
	self->__layout_minor = GTK_ADI_VERTICAL;
	self->__layout_major = GTK_ADI_VERTICAL;
	self->__minor = 0;
	self->__major = 0;
	self->__total = 0;
}

GtkObject*
gtk_adi_flex_new (GtkAdi *adi)
{
	GtkObject *object = NULL;

	g_return_val_if_fail (adi != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI (adi), NULL);
	
	object = GTK_OBJECT(GET_NEW);

	GTK_ADI_FLEX(object)->adi = adi;
	return object;
}

GtkAdiLayout
gtk_adi_flex_add_layout (GtkAdiFlex *self)
{
	if (self->__total <= 0) {
		self->__layout_major = gtk_adi_view_get_layout (GTK_ADI_VIEW(GTK_ADI(self->adi)->cur_view));
		if (self->__layout_major == GTK_ADI_HORIZONTAL) {
			self->__layout_minor = GTK_ADI_VERTICAL;
		}
		else {
			self->__layout_minor = GTK_ADI_HORIZONTAL;
		}
		self->__layout = self->__layout_major;
	}
	
	if (self->__layout == self->__layout_major) {
		self->__layout = self->__layout_minor;
	}
	else {
		self->__layout = self->__layout_major;
	}
	
	self->__total++;
	
	if (self->__minor < (self->__total - sqrt(self->__total) + 1)) {
		self->__layout = self->__layout_minor;
	}
	
	if (self->__layout == self->__layout_minor) {
		self->__minor++;
	}
	else {
		self->__major++;
	}
	
	ADI_TRACE ( "__layout_minor: %d: __layout_major %d",
	             self->__layout_minor, self->__layout_major );
	ADI_TRACE ( "__total %d: __minor %d: __major %d",
	             self->__total, self->__minor, self->__major );

	return self->__layout;
}

void
gtk_adi_flex_remove_layout (GtkAdiFlex *self, GtkAdiLayout layout)
{
}
