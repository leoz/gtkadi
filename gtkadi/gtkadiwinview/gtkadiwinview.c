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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef HILDON_SUPPORT
#ifdef MAEMO_CHANGES
#include<hildon/hildon-window.h>
#include<hildon/hildon-program.h>
#else
#include<hildon-widgets/hildon-window.h>
#include<hildon-widgets/hildon-program.h>
#endif
#endif

#include "gtkadiwinview.h"
/* #define ADI_DO_TRACE */
#include "gtkadiutils.h"

/* here are local prototypes */
static void gtk_adi_win_view_class_init (GtkAdiWinViewClass *c);
static void gtk_adi_win_view_init (GtkAdiWinView *self);

static void
gtk_adi_win_view_swap_child_windows (GtkWidget *window,
				     GtkAdi *self);

/* pointer to the class of our parent */
static GtkEventBoxClass *parent_class = NULL;

GType
gtk_adi_win_view_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiWinViewClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_win_view_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiWinView),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_win_view_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_ADI_CON_VIEW, "GtkAdiWinView", &info, (GTypeFlags)0);
	}

	return type;
}

static void 
gtk_adi_win_view_class_init (GtkAdiWinViewClass *c)
{
	parent_class = g_type_class_ref (GTK_TYPE_ADI_CON_VIEW);
}

static void 
gtk_adi_win_view_init (GtkAdiWinView *self)
{}

GtkWidget* 
gtk_adi_win_view_new (GtkAdi* adi)
{	
	GtkWidget *self = gtk_adi_con_view_new(adi);
	return self;
}
