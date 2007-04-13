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

#define GETTEXT_PACKAGE "gtk20"
#include <glib/gi18n-lib.h>
#include <gtk/gtk.h>

#include <gtkadi.h>
#include <gtkadiutils.h>

#ifdef HILDON_SUPPORT
#include <hildon-widgets/hildon-app.h>
#endif /* HILDON_SUPPORT */

#include "widgets.h"
#include "toolbar.h"
#include "menu.h"
#include "child.h"

/***************************************************************************/

GtkWidget* _adi = NULL;

/***************************************************************************/

static void
_init_adi (void)
{
	if ( !_adi ) {
		_adi = gtk_adi_new ();
		gtk_adi_set_child_func (GTK_ADI(_adi), _create_child );
		/* Try your own child window.
		gtk_adi_set_win_func   (GTK_ADI(_adi), _create_window);
		*/
		gtk_adi_set_icon_func  (GTK_ADI(_adi), _create_icon  );
		gtk_adi_set_title_func (GTK_ADI(_adi), _create_title );
	}
}

/***************************************************************************/

gchar*
get_gtk_adi_version_string (void)
{
	gchar* text = NULL;
	text = g_strdup_printf (_(": GtkAdi is %d.%d.%d"),
		                    gtk_adi_major_version,
							gtk_adi_minor_version,
							gtk_adi_micro_version);
	return text;
}

/***************************************************************************/

void
set_main_window_title (GtkWidget *main_window)
{
	gchar* vers = get_gtk_adi_version_string ();
	gchar* text = NULL;
	text = g_strdup_printf (_("GTK ADI Test %s"), vers);
	
	#ifdef HILDON_SUPPORT
	hildon_app_set_title (HILDON_APP (main_window), text);
	#else
	gtk_window_set_title (GTK_WINDOW (main_window), text);
	#endif /* HILDON_SUPPORT */

	g_free (text);
	g_free (vers);
}

/***************************************************************************/

GtkWidget*
create_adi (void)
{
	_init_adi ();
	return _adi;
}

/***************************************************************************/

GtkWidget*
create_menubar (GtkWidget *main_window)
{
	GtkWidget* menubar = NULL;
	_init_adi ();
	menubar = _create_menu (_adi, main_window);
	gtk_widget_show_all (menubar);
	return menubar;
}

/***************************************************************************/

GtkWidget*
create_toolbar (void)
{
	GtkWidget* toolbar = NULL;
	_init_adi ();
	toolbar = gtk_adi_create_toolbar (GTK_ADI(_adi));
	_create_toolbar(_adi, toolbar);
	gtk_widget_show_all (toolbar);
	return toolbar;
}

/***************************************************************************/
