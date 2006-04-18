/* GTK ADI Library
 * gtkadicolor.c: ADI Color Object
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



#include <string.h> /* memset() */

#include "gtkadicolor.h"

/* From GTK MS-Windows Engine. */
#ifdef G_OS_WIN32
#include <windows.h>
static void
sys_color_to_gtk_color(int id, GdkColor *pcolor)
{
  DWORD color = GetSysColor(id);

  pcolor->pixel = color;
  pcolor->red   = (GetRValue(color) << 8) | GetRValue(color);
  pcolor->green = (GetGValue(color) << 8) | GetGValue(color);
  pcolor->blue  = (GetBValue(color) << 8) | GetBValue(color);
}
#endif

static const GEnumValue _gtk_adi_state_type_values[] = {
	{ GTK_ADI_STATE_INACTIVE, (char *)"GTK_ADI_STATE_INACTIVE", (char *)"inactive" },
	{ GTK_ADI_STATE_ACTIVE, (char *)"GTK_ADI_STATE_ACTIVE", (char *)"active" },
	{ 0, NULL, NULL }
};

GType
gtk_adi_state_type_get_type (void)
{
	static GType type = 0;
	if (type == 0)
		type = g_enum_register_static ("GtkAdiStateType", _gtk_adi_state_type_values);
	return type;
}

/* here are local prototypes */
static void gtk_adi_color_class_init (GtkAdiColorClass *c);
static void gtk_adi_color_init_own (GtkAdiColor *self);
static void gtk_adi_color_init_gtk (GtkAdiColor *self);
static void gtk_adi_color_init_native (GtkAdiColor *self);
static void gtk_adi_color_init (GtkAdiColor *self);

/* pointer to the class of our parent */
static GtkObjectClass *parent_class = NULL;

GType
gtk_adi_color_get_type (void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (GtkAdiColorClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gtk_adi_color_class_init,
			(GClassFinalizeFunc) NULL,
			NULL /* class_data */,
			sizeof (GtkAdiColor),
			0 /* n_preallocs */,
			(GInstanceInitFunc) gtk_adi_color_init,
			NULL
		};

		type = g_type_register_static (GTK_TYPE_OBJECT, "GtkAdiColor", &info, (GTypeFlags)0);
	}

	return type;
}

/* a macro for creating a new object of our type */
#define GET_NEW ((GtkAdiColor *)g_object_new(gtk_adi_color_get_type(), NULL))

static void 
gtk_adi_color_class_init (GtkAdiColorClass *c)
{
	parent_class = g_type_class_ref (GTK_TYPE_OBJECT);
}

static void 
gtk_adi_color_init (GtkAdiColor *self)
{
	self->type = GTK_ADI_COLOR_GTK;
	gtk_adi_color_set (self, self->type);
}


static void 
gtk_adi_color_init_own (GtkAdiColor * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_COLOR (self));
	
	static GdkColor title_inactive = { 0, 0x6000, 0xb000, 0xd000 };
	static GdkColor title_active   = { 0, 0x4000, 0x9000, 0xb000 };
	static GdkColor text_inactive  = { 0, 0xdddd, 0xdddd, 0xdddd };
	static GdkColor text_active    = { 0, 0xffff, 0xffff, 0xffff };
	self->title[GTK_ADI_STATE_INACTIVE] = title_inactive;
	self->title[GTK_ADI_STATE_ACTIVE  ] = title_active;
	self->text [GTK_ADI_STATE_INACTIVE] = text_inactive;
	self->text [GTK_ADI_STATE_ACTIVE  ] = text_active;
}

static void 
gtk_adi_color_init_gtk (GtkAdiColor * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_COLOR (self));
	
	GtkWidget* invis       = gtk_invisible_new ();
	GtkWidget* menu        = gtk_menu_new      ();
	GtkWidget* item        = gtk_menu_item_new ();
	GtkStyle*  invis_style = NULL;
	GtkStyle*  title_style = NULL;

	gtk_widget_ensure_style (invis);
	gtk_object_sink (GTK_OBJECT (invis));
	invis_style = gtk_widget_get_style(invis);
	self->text[GTK_ADI_STATE_INACTIVE]=invis_style->bg[GTK_STATE_NORMAL];
	self->text[GTK_ADI_STATE_ACTIVE]=invis_style->text[GTK_STATE_SELECTED];

	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
	gtk_widget_ensure_style (item);
	gtk_object_sink (GTK_OBJECT (item));
	title_style = gtk_widget_get_style(item);
	self->title[GTK_ADI_STATE_INACTIVE]=title_style->text[GTK_STATE_INSENSITIVE];
	self->title[GTK_ADI_STATE_ACTIVE]=title_style->bg[GTK_STATE_PRELIGHT];

	gtk_widget_destroy(item);
	gtk_widget_destroy(menu);
	//Fixed memory leak on X86
//	g_free(menu);
	gtk_widget_destroy(invis);
}

static void 
gtk_adi_color_init_native (GtkAdiColor * self)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_COLOR (self));
	
	#ifdef G_OS_WIN32
	sys_color_to_gtk_color(COLOR_INACTIVECAPTION,
						   gtk_adi_color_inactive_title (self));
	sys_color_to_gtk_color(COLOR_ACTIVECAPTION,
						   gtk_adi_color_active_title (self));
	sys_color_to_gtk_color(COLOR_INACTIVECAPTIONTEXT,
						   gtk_adi_color_inactive_text (self));
	sys_color_to_gtk_color(COLOR_CAPTIONTEXT,
						   gtk_adi_color_active_text (self));
	#endif
}

void 
gtk_adi_color_set (GtkAdiColor * self, GtkAdiColorType type)
{
	g_return_if_fail (self != NULL);
	g_return_if_fail (GTK_IS_ADI_COLOR (self));
	
	self->type = type;
	switch (self->type)
	{
	case GTK_ADI_COLOR_OWN:
		gtk_adi_color_init_own (self);
		break;
	case GTK_ADI_COLOR_NATIVE:
		gtk_adi_color_init_native (self);
		break;
	case GTK_ADI_COLOR_GTK:
	default:
		gtk_adi_color_init_gtk (self);
		break;
	}
}

GdkColor* 
gtk_adi_color_inactive_title (GtkAdiColor *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_COLOR (self), NULL);

	return &self->title[GTK_ADI_STATE_INACTIVE];
}

GdkColor* 
gtk_adi_color_active_title (GtkAdiColor *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_COLOR (self), NULL);

	return &self->title[GTK_ADI_STATE_ACTIVE];
}

GdkColor* 
gtk_adi_color_inactive_text (GtkAdiColor *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_COLOR (self), NULL);
	
	return &self->text[GTK_ADI_STATE_INACTIVE];
}

GdkColor* 
gtk_adi_color_active_text (GtkAdiColor *self)
{
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (GTK_IS_ADI_COLOR (self), NULL);
	
	return &self->text[GTK_ADI_STATE_ACTIVE];
}

GtkObject* 
gtk_adi_color_new (void)
{
	return GTK_OBJECT(GET_NEW);
}
