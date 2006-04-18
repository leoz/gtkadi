/* GTK ADI Test
 * child.h
 * Copyright (C) 2003 - 2005, Leonid Zolotarev <leonid.zolotarev@gmail.com>
 *
 * Licensed under the terms of the BSD license, see file COPYING
 * for details.
 *
 * $Id$
 */
#ifndef __CHILD_H__
#define __CHILD_H__

#include <gtk/gtk.h>

GtkWidget* _create_child (void);

GdkPixbuf* _create_icon (GtkWidget* widget);

gchar* _create_title (void);

#endif /* __CHILD_H__ */
