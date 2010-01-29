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
#define MIN_LABEL_HEIGHT 55

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
