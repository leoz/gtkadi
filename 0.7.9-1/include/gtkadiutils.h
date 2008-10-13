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
 
#include <glib/gprintf.h>
#include "gtkadi.h"

#ifndef __GTK_ADI_UTILS_H__
#define __GTK_ADI_UTILS_H__

G_BEGIN_DECLS

/* GtkAdi version. */
GLIB_VAR const guint gtk_adi_major_version;
GLIB_VAR const guint gtk_adi_minor_version;
GLIB_VAR const guint gtk_adi_micro_version;
/*
#define ADI_DO_TRACE
*/
#ifdef ADI_DO_TRACE
#define ADI_TRACE(msg,...) g_printf("ADI: "msg"\n",__VA_ARGS__);
#define ADI_TRACE_MSG(msg) g_printf("ADI: "msg"\n");
#else
#define ADI_TRACE(msg,...)
#define ADI_TRACE_MSG(msg)
#endif /* ADI_DO_TRACE */

void
gtk_adi_internal_send_signal (GtkAdi* adi, gchar *signame, GtkWidget *widget);

G_END_DECLS

#endif /* __GTK_ADI_UTILS_H__ */
