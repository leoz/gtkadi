#include <gtk/gtk.h>
#include <check.h>
#include "debug.h"

#include "gtkadi.h"
#include "gtkaditoolbar.h"

GtkAdi* self = NULL;
GtkAdiToolbar* selftoolbar = NULL;

void setup(void)
{
	GtkWidget* adi;
	GtkWidget* widget;

	/* initialize gtk */
	gtk_init(NULL, NULL);

	/* create adi instance */
	adi = gtk_adi_new();
	self = g_object_ref(GTK_ADI(adi));

	/* create toolbar */
	widget = gtk_adi_create_toolbar(self);
	fail_if(widget == NULL, "failed to create toolbar");
	selftoolbar = g_object_ref(GTK_ADI_TOOLBAR(widget));
}

void teardown(void)
{
	fail_if(self == NULL, "adi not created");

	if (!gtk_adi_can_exit(self))
		gtk_adi_remove_all_children(self);
	fail_unless(gtk_adi_can_exit(self), "adi not ready to exit");

	g_object_unref(selftoolbar);
	g_object_unref(self);

	gtk_widget_destroy(GTK_WIDGET(self));
	self = NULL;
}

START_TEST(test_get_toolbar)
{
	GtkWidget* widget;

	widget = gtk_adi_get_toolbar(self);

	fail_if(widget == NULL, "failed to get toolbar");
	fail_unless(GTK_IS_ADI_TOOLBAR(widget), "toolbar has wrong type");
}
END_TEST

START_TEST(test_mode_set)
{
	gtk_adi_toolbar_mode_set(selftoolbar, GTK_ADI_PANED);
	gtk_adi_toolbar_mode_set(selftoolbar, GTK_ADI_BOX);
	gtk_adi_toolbar_mode_set(selftoolbar, GTK_ADI_INVISIBLE);
}
END_TEST

START_TEST(test_view_set)
{
	gtk_adi_toolbar_view_set(selftoolbar, GTK_ADI_VIEW_BOX);
	gtk_adi_toolbar_view_set(selftoolbar, GTK_ADI_VIEW_TAB);
	gtk_adi_toolbar_view_set(selftoolbar, GTK_ADI_VIEW_WIN);
}
END_TEST

START_TEST(test_fix_set)
{
	gtk_adi_toolbar_fix_set(selftoolbar, GTK_ADI_MOVABLE);
	gtk_adi_toolbar_fix_set(selftoolbar, GTK_ADI_FIXED);
}
END_TEST

START_TEST(test_set_close_buttons)
{
}
END_TEST

START_TEST(test_set_nav_buttons)
{
}
END_TEST

START_TEST(test_set_tile_buttons)
{
	gtk_adi_toolbar_set_tile_buttons(selftoolbar, TRUE, TRUE);
	gtk_adi_toolbar_set_tile_buttons(selftoolbar, FALSE, TRUE);
	gtk_adi_toolbar_set_tile_buttons(selftoolbar, TRUE, FALSE);
	gtk_adi_toolbar_set_tile_buttons(selftoolbar, FALSE, FALSE);
}
END_TEST

void add_test_functions(TCase* tc)
{
	tcase_add_test(tc, test_get_toolbar);
	tcase_add_test(tc, test_mode_set);
	tcase_add_test(tc, test_view_set);
	tcase_add_test(tc, test_fix_set);
	tcase_add_test(tc, test_set_close_buttons);
	tcase_add_test(tc, test_set_nav_buttons);
	tcase_add_test(tc, test_set_tile_buttons);
}

Suite* create_suite(void)
{
	Suite* s = suite_create("gtkaditoolbar");

	TCase* tc = tcase_create("basic");
	tcase_add_checked_fixture(tc, setup, teardown);
	add_test_functions(tc);
	suite_add_tcase(s, tc);

	return s;
}
