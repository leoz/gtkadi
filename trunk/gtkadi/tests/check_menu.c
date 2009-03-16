#include <gtk/gtk.h>
#include <check.h>
#include "debug.h"

#include "gtkadi.h"
#include "gtkadimenu.h"

GtkAdi* self = NULL;
GtkAdiMenu* selfmenu = NULL;

void setup(void)
{
	GtkWidget* adi;
	GtkWidget* widget;

	/* initialize gtk */
	gtk_init(NULL, NULL);

	/* create adi instance */
	adi = gtk_adi_new();
	self = g_object_ref(GTK_ADI(adi));

	/* create menu */
	widget = gtk_adi_create_menu(self);
	fail_if(widget == NULL, "failed to create menu");
	selfmenu = g_object_ref(GTK_ADI_MENU(widget));
}

void teardown(void)
{
	fail_if(self == NULL, "adi not created");

	if (!gtk_adi_can_exit(self))
		gtk_adi_remove_all_children(self);
	fail_unless(gtk_adi_can_exit(self), "adi not ready to exit");

	g_object_unref(selfmenu);
	g_object_unref(self);

	gtk_widget_destroy(GTK_WIDGET(self));
	self = NULL;
}

START_TEST(test_get_menu)
{
	GtkWidget* widget;
	GtkWidget* submenu;

	widget = gtk_adi_get_menu(self);

	fail_if(widget == NULL, "failed to get menu");
	fail_unless(GTK_IS_ADI_MENU(widget), "menu has wrong type");

	submenu = gtk_adi_menu_get_submenu(GTK_ADI_MENU(widget));
	fail_if(widget == NULL, "failed to get submenu");
}
END_TEST

START_TEST(test_mode_set)
{
	gtk_adi_menu_mode_set(selfmenu, GTK_ADI_PANED);
	fail_unless(gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(selfmenu->item_paned)),
			"item_paned is not checked");
	fail_if(gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(selfmenu->item_box)),
			"item_box is checked");

	gtk_adi_menu_mode_set(selfmenu, GTK_ADI_BOX);
	fail_if(gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(selfmenu->item_paned)),
			"item_paned is checked");
	fail_unless(gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(selfmenu->item_box)),
			"item_box is not checked");

	gtk_adi_menu_mode_set(selfmenu, GTK_ADI_INVISIBLE);
}
END_TEST

START_TEST(test_fix_set)
{
	gtk_adi_menu_fix_set(selfmenu, GTK_ADI_MOVABLE);
	gtk_adi_menu_fix_set(selfmenu, GTK_ADI_FIXED);
}
END_TEST

START_TEST(test_set_close_items)
{
}
END_TEST

START_TEST(test_set_nav_items)
{
}
END_TEST

START_TEST(test_set_tile_items)
{
	gtk_adi_menu_set_tile_items(selfmenu, TRUE, TRUE);
	gtk_adi_menu_set_tile_items(selfmenu, FALSE, TRUE);
	gtk_adi_menu_set_tile_items(selfmenu, TRUE, FALSE);
	gtk_adi_menu_set_tile_items(selfmenu, FALSE, FALSE);
}
END_TEST

void add_test_functions(TCase* tc)
{
	tcase_add_test(tc, test_get_menu);
	tcase_add_test(tc, test_mode_set);
	tcase_add_test(tc, test_fix_set);
	tcase_add_test(tc, test_set_close_items);
	tcase_add_test(tc, test_set_nav_items);
	tcase_add_test(tc, test_set_tile_items);
}

Suite* create_suite(void)
{
	Suite* s = suite_create("gtkadimenu");

	TCase* tc = tcase_create("basic");
	tcase_add_checked_fixture(tc, setup, teardown);
	add_test_functions(tc);
	suite_add_tcase(s, tc);

	return s;
}
