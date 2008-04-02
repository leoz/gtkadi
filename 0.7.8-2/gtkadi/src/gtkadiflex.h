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
