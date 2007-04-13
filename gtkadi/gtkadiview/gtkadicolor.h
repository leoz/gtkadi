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
