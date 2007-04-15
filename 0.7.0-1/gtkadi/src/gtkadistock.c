/* vim:set ts=2 sw=4 sts=2 et cindent: */
/* GTK ADI Library
 * gtkadistock.c: ADI Stock Items
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

//#define GETTEXT_PACKAGE "gtk20"
#include <glib/gi18n-lib.h>
#include <gtk/gtk.h>
#include <gtk/gtkiconfactory.h>
#include "gtkadistock.h"
#include "icons/gtkadiicons.h"

#define GTK_ADI_STOCK_SIZE    3

static GtkIconFactory *gtk_adi_icon_factory = NULL;

static GtkStockItem gtk_adi_stock_items[] =
{
	{ GTK_ADI_STOCK_CLOSE            , N_("_Close")     , 0, 0, NULL },
	{ GTK_ADI_STOCK_CLOSE_ALL        , N_("Close _All") , 0, 0, NULL },
	{ GTK_ADI_STOCK_CLOSE_WINDOW     , N_("_Close")     , 0, 0, NULL },
	{ GTK_ADI_STOCK_FIX              , N_("_Fix")       , 0, 0, NULL },
	{ GTK_ADI_STOCK_NEW              , N_("_New")       , 0, 0, NULL },
	{ GTK_ADI_STOCK_NEW_HORIZONTALLY , N_("New _Hor.")  , 0, 0, NULL },
	{ GTK_ADI_STOCK_NEW_VERTICALLY   , N_("New _Vert.") , 0, 0, NULL },
	{ GTK_ADI_STOCK_NEXT             , N_("_Next")      , 0, 0, NULL },
	{ GTK_ADI_STOCK_PREVIOUS         , N_("_Prev.")     , 0, 0, NULL },
	{ GTK_ADI_STOCK_TILE_HORIZONTALLY, N_("_Tile Hor.") , 0, 0, NULL },
	{ GTK_ADI_STOCK_TILE_VERTICALLY  , N_("Ti_le Vert."), 0, 0, NULL },
	{ GTK_ADI_STOCK_WINDOW           , NULL             , 0, 0, NULL },
	{ GTK_ADI_STOCK_WINDOWS          , NULL             , 0, 0, NULL }
};

typedef struct {
    GtkIconSize size;
    const guint8 *pixbuf;
} gtk_adi_icon_t;

static struct {
    const gchar *stock_id;
	gtk_adi_icon_t icons[GTK_ADI_STOCK_SIZE];
}
gtk_adi_icons[] = 
{
	{ GTK_ADI_STOCK_CLOSE,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_close_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_close_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_close_24}
	}
	},
	{ GTK_ADI_STOCK_CLOSE_ALL,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_close_all_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_close_all_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_close_all_24}
	}
	},
	{ GTK_ADI_STOCK_FIX,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_fix_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_fix_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_fix_24}
	}
	},
	{ GTK_ADI_STOCK_NEW,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_new_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_new_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_new_24}
	}
	},
	{ GTK_ADI_STOCK_NEW_HORIZONTALLY,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_new_horizontally_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_new_horizontally_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_new_horizontally_24}
	}
	},
	{ GTK_ADI_STOCK_NEW_VERTICALLY,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_new_vertically_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_new_vertically_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_new_vertically_24}
	}
	},
	{ GTK_ADI_STOCK_NEXT,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_next_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_next_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_next_24}
	}
	},
	{ GTK_ADI_STOCK_PREVIOUS,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_previous_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_previous_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_previous_24}
	}
	},
	{ GTK_ADI_STOCK_TILE_HORIZONTALLY,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_tile_horizontally_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_tile_horizontally_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_tile_horizontally_24}
	}
	},
	{ GTK_ADI_STOCK_TILE_VERTICALLY,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_tile_vertically_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_tile_vertically_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_tile_vertically_24}
	}
	},
	{ GTK_ADI_STOCK_WINDOWS,
	{
		{GTK_ICON_SIZE_MENU         , stock_adi_windows_16},
		{GTK_ICON_SIZE_BUTTON       , stock_adi_windows_24},
		{GTK_ICON_SIZE_LARGE_TOOLBAR, stock_adi_windows_24}
	}
	},

};

static struct {
    const gchar *stock_id;
    const guint8 *pixbuf;
}
gtk_adi_window_icons[] = 
{
	{ GTK_ADI_STOCK_CLOSE_WINDOW, stock_adi_close_window_10 },
	{ GTK_ADI_STOCK_WINDOW      , stock_adi_window_14       }
};

static void
gtk_adi_stock_add_icons (GtkIconSet *set,
						 GtkIconSize size,
						 const guint8 *inline_data)
{
	GtkIconSource *source;
	GdkPixbuf *pixbuf;

	source = gtk_icon_source_new ();
	gtk_icon_source_set_size (source, size);
	gtk_icon_source_set_size_wildcarded(source, FALSE);

	pixbuf = gdk_pixbuf_new_from_inline (-1, inline_data, FALSE, NULL);
	gtk_icon_source_set_pixbuf (source, pixbuf);
	g_object_unref (pixbuf);

	gtk_icon_set_add_source (set, source);
	gtk_icon_source_free (source);
}

static void
gtk_adi_stock_add (const gchar *stock_id,
				   gtk_adi_icon_t *icons)
{
	gint i;
	GtkIconSet *set;

	set = gtk_icon_set_new ();

	for (i = 0; i < GTK_ADI_STOCK_SIZE; i++) {
		gtk_adi_stock_add_icons (set,
			                    icons[i].size,
			                    icons[i].pixbuf);
	}

	gtk_icon_factory_add (gtk_adi_icon_factory, stock_id, set);
	gtk_icon_set_unref (set);
}

static void
gtk_adi_add_stock_icon (const gchar *stock_id,
						const guint8 *inline_data)
{
	GtkIconSource *source;
	GtkIconSet *set;
	GdkPixbuf *pixbuf;

	source = gtk_icon_source_new ();

	gtk_icon_source_set_size (source, GTK_ICON_SIZE_MENU);
	gtk_icon_source_set_size_wildcarded (source, FALSE);

	pixbuf = gdk_pixbuf_new_from_inline (-1, inline_data, FALSE, NULL);

	gtk_icon_source_set_pixbuf (source, pixbuf);
	g_object_unref (pixbuf);

	set = gtk_icon_set_new ();

	gtk_icon_set_add_source (set, source);
	gtk_icon_source_free (source);

	gtk_icon_factory_add (gtk_adi_icon_factory, stock_id, set);

	gtk_icon_set_unref (set);
}

void
gtk_adi_stock_init (void)
{
	gint i;
	if (!gtk_adi_icon_factory) {
		gtk_adi_icon_factory = gtk_icon_factory_new ();
		for (i = 0; i < G_N_ELEMENTS (gtk_adi_icons); i++) {
			gtk_adi_stock_add (gtk_adi_icons[i].stock_id,
				               gtk_adi_icons[i].icons);
		}
		for (i = 0; i < G_N_ELEMENTS (gtk_adi_window_icons); i++) {
			gtk_adi_add_stock_icon (gtk_adi_window_icons[i].stock_id,
				                    gtk_adi_window_icons[i].pixbuf);
		}
		gtk_icon_factory_add_default (gtk_adi_icon_factory);
		gtk_stock_add_static (gtk_adi_stock_items,
			                  G_N_ELEMENTS (gtk_adi_stock_items));
	}
}
