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
#include "gtkadititle.h"

#ifndef __GTK_ADI_BOX_TITLE_H__
#define __GTK_ADI_BOX_TITLE_H__

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_ADI_BOX_TITLE	(gtk_adi_box_title_get_type())
#define GTK_ADI_BOX_TITLE(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_box_title_get_type(), GtkAdiBoxTitle)
#define GTK_ADI_BOX_TITLE_CONST(obj)	G_TYPE_CHECK_INSTANCE_CAST((obj), gtk_adi_box_title_get_type(), GtkAdiBoxTitle const)
#define GTK_ADI_BOX_TITLE_CLASS(klass)	G_TYPE_CHECK_CLASS_CAST((klass), gtk_adi_box_title_get_type(), GtkAdiBoxTitleClass)
#define GTK_IS_ADI_BOX_TITLE(obj)	G_TYPE_CHECK_INSTANCE_TYPE((obj), gtk_adi_box_title_get_type ())

#define GTK_ADI_BOX_TITLE_GET_CLASS(obj)	G_TYPE_INSTANCE_GET_CLASS((obj), gtk_adi_box_title_get_type(), GtkAdiBoxTitleClass)

/*
 * Main object structure
 */
#ifndef __TYPEDEF_GTK_ADI_BOX_TITLE__
#define __TYPEDEF_GTK_ADI_BOX_TITLE__
typedef struct _GtkAdiBoxTitle GtkAdiBoxTitle;
#endif
struct _GtkAdiBoxTitle {
	GtkAdiTitle __parent__;
	/*< public >*/
	GSList * radiobutton_group;
	GtkObject * adi_color;
	GtkWidget * radiobutton;
	GtkWidget * radio_hbox;
};

/*
 * Class definition
 */
typedef struct _GtkAdiBoxTitleClass GtkAdiBoxTitleClass;
struct _GtkAdiBoxTitleClass {
	GtkAdiTitleClass __parent__;
};


/*
 * Public methods
 */
GType	gtk_adi_box_title_get_type	(void);
GtkWidget * 	gtk_adi_box_title_new	(void);
void 	gtk_adi_box_title_set_active	(GtkAdiBoxTitle * self);
void 	gtk_adi_box_title_set_group	(GtkAdiBoxTitle * self,
					GSList * group);
void 	gtk_adi_box_title_set_color	(GtkAdiBoxTitle * self,
					GtkObject * adi_color);
GSList * 	gtk_adi_box_title_get_group	(GtkAdiBoxTitle * self);

G_END_DECLS

#endif
