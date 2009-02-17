/* vim:set ts=2 sw=4 sts=2 et cindent: */
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
