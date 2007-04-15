/* GTK ADI Library
 * gtkadistock.h: ADI Stock Items
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
 
#include <glib.h>

#ifndef __GTK_ADI_STOCK_H__
#define __GTK_ADI_STOCK_H__

G_BEGIN_DECLS

#define GTK_ADI_STOCK_CLOSE                "gtk_adi_close"
#define GTK_ADI_STOCK_CLOSE_ALL            "gtk_adi_close_all"
#define GTK_ADI_STOCK_CLOSE_WINDOW         "gtk_adi_close_window"
#define GTK_ADI_STOCK_FIX                  "gtk_adi_fix"
#define GTK_ADI_STOCK_NEW                  "gtk_adi_new"
#define GTK_ADI_STOCK_NEW_HORIZONTALLY     "gtk_adi_new_horizontally"
#define GTK_ADI_STOCK_NEW_VERTICALLY       "gtk_adi_new_vertically"
#define GTK_ADI_STOCK_NEXT                 "gtk_adi_next"
#define GTK_ADI_STOCK_PREVIOUS             "gtk_adi_previous"
#define GTK_ADI_STOCK_TILE_HORIZONTALLY    "gtk_adi_tile_horizontally"
#define GTK_ADI_STOCK_TILE_VERTICALLY      "gtk_adi_tile_vertically"
#define GTK_ADI_STOCK_WINDOW               "gtk_adi_window"
#define GTK_ADI_STOCK_WINDOWS              "gtk_adi_windows"

void gtk_adi_stock_init (void);

G_END_DECLS

#endif /* __GTK_ADI_STOCK_H__ */
