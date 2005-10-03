/* GTK ADI Test
 * main.c
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

#include <gtk/gtk.h>
#include "window.h"

/***************************************************************************/

static char* _id = "$Id$";

/***************************************************************************/

GtkWidget *main_window = NULL;

/***************************************************************************/

int main (int argc, char *argv[])
{
    gtk_set_locale ();
    gtk_init (&argc, &argv);
    
    main_window = create_main_window ();
    gtk_widget_show (main_window);
    g_signal_connect ((gpointer) main_window,
                      "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_main ();
    
    return 0;
}

/***************************************************************************/

#ifdef _MSC_VER
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	return main (__argc, __argv);
}
#endif

/***************************************************************************/
