/* GTK ADI Test
 * widgets.h
 * Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * $Id$
 */
#ifndef __WIDGETS_H__
#define __WIDGETS_H__

#include <gtk/gtk.h>

gchar* get_gtk_adi_version_string (void);

void set_main_window_title (GtkWidget *main_window);

GtkWidget* create_adi (void);

GtkWidget* create_toolbar (void);

GtkWidget* create_menubar (GtkWidget *main_window);

#endif /* __WIDGETS_H__ */
