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
