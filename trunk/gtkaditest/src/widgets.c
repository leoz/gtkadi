/* GTK ADI Test
 * widgets.c
 * Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * $Id$
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#define GETTEXT_PACKAGE "gtk20"
#include <glib/gi18n-lib.h>
#include <gtk/gtk.h>

#include <gtkadi.h>
#include <gtkadiutils.h>

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
		gtk_adi_set_child_func (GTK_ADI(_adi), _create_child);
		gtk_adi_set_icon_func  (GTK_ADI(_adi), _create_icon );
		gtk_adi_set_title_func (GTK_ADI(_adi), _create_title);
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
	gtk_window_set_title (GTK_WINDOW (main_window), text);
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
create_menubar (void)
{
	GtkWidget* menubar = NULL;
	_init_adi ();
	menubar = _create_menu (_adi);
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
