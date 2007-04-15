/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* GTK ADI Library
 * gtkadiutils.c: Utility functions
 * Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
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
#include <config.h>
#endif

#include <gtk/gtk.h>
#include "gtkadiutils.h"

const guint gtk_adi_major_version = GTK_ADI_MAJOR_VERSION;
const guint gtk_adi_minor_version = GTK_ADI_MINOR_VERSION;
const guint gtk_adi_micro_version = GTK_ADI_MICRO_VERSION;

void
gtk_adi_internal_send_signal (GtkAdi* adi, gchar *signame, GtkWidget *widget)
{
    g_signal_emit_by_name(G_OBJECT(adi), signame,  widget);
}

