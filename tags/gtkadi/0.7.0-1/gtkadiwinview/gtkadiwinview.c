/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* GTK ADI Library
 * gtkadiwinview.c: ADI Window View
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