/* GTK ADI Library
 * gtkaditype.h: ADI Types
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

#ifndef __GTK_ADI_TYPE_H__
#define __GTK_ADI_TYPE_H__

G_BEGIN_DECLS

typedef enum {
	GTK_ADI_VIEW_BOX,
	GTK_ADI_VIEW_TAB
} GtkAdiViewType;

typedef enum {
	GTK_ADI_PANED,
	GTK_ADI_BOX
} GtkAdiMode;

typedef enum {
	GTK_ADI_MOVABLE,
	GTK_ADI_FIXED
} GtkAdiState;

typedef enum {
	GTK_ADI_HORIZONTAL,
	GTK_ADI_VERTICAL
} GtkAdiLayout;

typedef enum {
	GTK_ADI_COLOR_GTK,
	GTK_ADI_COLOR_OWN,
	GTK_ADI_COLOR_NATIVE
} GtkAdiColorType;

G_END_DECLS

#endif /* __GTK_ADI_TYPE_H__ */
