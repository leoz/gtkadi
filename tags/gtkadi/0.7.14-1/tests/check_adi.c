#include <gtk/gtk.h>
#include <check.h>
#include "debug.h"

#include "gtkadi.h"
#include "gtkadistock.h"

GtkAdi* self = NULL;

GtkWidget* create_adi_child(void)
{
	GtkWidget* widget;
	widget = gtk_label_new("this is adi child");
	PRINT("created adi child '%s' (%p)", gtk_widget_get_name(widget), widget);
	return widget;
}

gchar* create_adi_title(void)
{
	gchar* title;
	title = g_strdup("title");
	return title;
}

GdkPixbuf* create_adi_icon(GtkWidget* widget)
{
	GdkPixbuf* icon;
	icon = gtk_widget_render_icon(widget, GTK_ADI_STOCK_WINDOW, GTK_ICON_SIZE_MENU, NULL);
	return icon;
}

void setup_default(void)
{
	GtkWidget* adi;

	fail_if(self, "adi already created");

	/* initialize gtk and create main window */
	gtk_init(NULL, NULL);

	/* create adi instance */
	adi = gtk_adi_new();
	fail_if(adi == NULL, "failed to create adi");

	self = g_object_ref(GTK_ADI(adi));

	/* setup user functions */
	gtk_adi_set_child_func(self, create_adi_child);
	fail_unless(self->child_func == create_adi_child, "failed to set child function");
	gtk_adi_set_title_func(self, create_adi_title);
	fail_unless(self->title_func == create_adi_title, "failed to set title function");
	gtk_adi_set_icon_func(self, create_adi_icon);
	fail_unless(self->icon_func == create_adi_icon, "failed to set icon function");
}

void init_initial_child(void)
{
	GtkWidget* widget;
	GtkWidget* parent;

	widget = create_adi_child();
	parent = gtk_widget_get_parent(widget);

	gtk_adi_add(self, widget);

	/* adi puts children into some spacer, so parent should change */
	fail_if(gtk_widget_get_parent(widget) == parent, "failed to add widget");
	fail_unless(gtk_adi_has_children(self), "adi claims to have no children");
	fail_unless(gtk_adi_get_childs_count(self) == 1, "invalid child count after add");
}

void init_boxview(void)
{
	gtk_adi_change_view(self, GTK_ADI_VIEW_BOX);

	fail_unless(self->cur_view == self->box_view, "failed to change to box view");
	fail_unless(gtk_adi_get_view(self) == GTK_ADI_VIEW_BOX, "invalid type for box view");
}

void init_tabview(void)
{
	gtk_adi_change_view(self, GTK_ADI_VIEW_TAB);

	fail_unless(self->cur_view == self->tab_view, "failed to change to tab view");
	fail_unless(gtk_adi_get_view(self) == GTK_ADI_VIEW_TAB, "invalid type for tab view");
}

void init_winview(void)
{
	gtk_adi_change_view(self, GTK_ADI_VIEW_WIN);

	fail_unless(self->cur_view == self->win_view, "failed to change to win view");
	fail_unless(gtk_adi_get_view(self) == GTK_ADI_VIEW_WIN, "invalid type for win view");
}

void teardown(void)
{
	fail_if(self == NULL, "adi not created");

	if (!gtk_adi_can_exit(self))
		gtk_adi_remove_all_children(self);
	fail_unless(gtk_adi_can_exit(self), "adi not ready to exit");

	g_object_unref(self);
	gtk_widget_destroy(GTK_WIDGET(self));
	self = NULL;
}

START_TEST(test_add)
{
	int num;
	GtkWidget* widget;
	GtkWidget* parent;

	widget = create_adi_child();
	parent = gtk_widget_get_parent(widget);
	num = gtk_adi_get_childs_count(self) + 1;

	gtk_adi_add(self, widget);

	fail_if(gtk_widget_get_parent(widget) == parent, "failed to add widget");
	fail_unless(gtk_adi_has_children(self), "adi claims to have no children");
	fail_unless(gtk_adi_get_childs_count(self) == num, "invalid child count after add");
}
END_TEST

START_TEST(test_user_add_child)
{
	int count;

	count = gtk_adi_get_childs_count(self);

	gtk_adi_user_add_child(self);
	fail_unless(gtk_adi_get_childs_count(self) == count + 1, "failed to add child");
}
END_TEST

START_TEST(test_user_add_child_with_layout)
{
	int count;

	count = gtk_adi_get_childs_count(self) + 1;
	gtk_adi_user_add_child_with_layout(self, GTK_ADI_HORIZONTAL);

	fail_unless(gtk_adi_get_childs_count(self) == count, "failed to add with horizontal layout");

	count = gtk_adi_get_childs_count(self) + 1;
	gtk_adi_user_add_child_with_layout(self, GTK_ADI_VERTICAL);

	fail_unless(gtk_adi_get_childs_count(self) == count, "failed to add with vertical layout");
}
END_TEST

START_TEST(test_set_current_child)
{
	GtkWidget* widget;

	widget = create_adi_child();
	gtk_adi_add(self, widget);
	gtk_adi_set_current_child(self, widget);
}
END_TEST

START_TEST(test_set_current_widget)
{
	GtkWidget* widget;

	widget = create_adi_child();
	gtk_adi_add(self, widget);
	gtk_adi_set_current_widget(self, widget);
}
END_TEST

START_TEST(test_remove_current_child)
{
	int count;
	GtkWidget* widget;

	count = gtk_adi_get_childs_count(self);
	widget = create_adi_child();
	gtk_adi_add(self, widget);
	gtk_adi_remove_current_child(self);

	fail_unless(gtk_adi_get_childs_count(self) == count, "failed to remove child");
}
END_TEST

START_TEST(test_remove_all_children)
{
	GtkWidget* widget;

	widget = create_adi_child();
	gtk_adi_add(self, widget);
	gtk_adi_remove_all_children(self);

	fail_if(gtk_adi_has_children(self), "failed to remove all children");
}
END_TEST

START_TEST(test_set_next_previous_child)
{
	/* TODO needs better testing */
	GtkWidget* a;
	GtkWidget* b;

	gtk_adi_remove_all_children(self);

	a = create_adi_child();
	b = create_adi_child();

	gtk_adi_add(self, a);
	gtk_adi_add(self, b);

	/* focus is now on b */
	fail_unless(gtk_adi_can_previous_child(self), "cannot change to previous child");
	fail_if(gtk_adi_can_next_child(self), "child out of bounds");
	gtk_adi_set_previous_child(self);

	/* focus is now on a */
	fail_unless(gtk_adi_can_next_child(self), "cannot change to next child");
	fail_if(gtk_adi_can_previous_child(self), "child out of bounds");
	gtk_adi_set_next_child(self);
}
END_TEST

START_TEST(test_change_mode)
{
	/* TODO needs better testing */
	gtk_adi_change_mode(self, GTK_ADI_PANED);
	gtk_adi_change_mode(self, GTK_ADI_BOX);
	gtk_adi_change_mode(self, GTK_ADI_INVISIBLE);
}
END_TEST

START_TEST(test_change_view)
{
	gtk_adi_change_view(self, GTK_ADI_VIEW_BOX);
	fail_unless(self->cur_view == self->box_view, "failed to change to box view");
	fail_unless(gtk_adi_get_view(self) == GTK_ADI_VIEW_BOX, "invalid type for box view");

	gtk_adi_change_view(self, GTK_ADI_VIEW_TAB);
	fail_unless(self->cur_view == self->tab_view, "failed to change to tab view");
	fail_unless(gtk_adi_get_view(self) == GTK_ADI_VIEW_TAB, "invalid type for tab view");

	gtk_adi_change_view(self, GTK_ADI_VIEW_WIN);
	fail_unless(self->cur_view == self->win_view, "failed to change to win view");
	fail_unless(gtk_adi_get_view(self) == GTK_ADI_VIEW_WIN, "invalid type for win view");
}
END_TEST

START_TEST(test_change_state)
{
	/* TODO needs better testing */
	gtk_adi_change_state(self, GTK_ADI_MOVABLE);
	gtk_adi_change_state(self, GTK_ADI_FIXED);
}
END_TEST

START_TEST(test_set_layout)
{
	/* TODO needs better testing */
	gtk_adi_set_layout(self, GTK_ADI_HORIZONTAL);
	gtk_adi_set_layout(self, GTK_ADI_VERTICAL);
}
END_TEST

START_TEST(test_change_color)
{
	/* TODO needs better testing */
	gtk_adi_change_color(self, GTK_ADI_COLOR_GTK);
	gtk_adi_change_color(self, GTK_ADI_COLOR_OWN);
	gtk_adi_change_color(self, GTK_ADI_COLOR_NATIVE);
}
END_TEST

START_TEST(test_set_child_title_text)
{
	gchar* title;
	GtkWidget* widget;

	title = create_adi_title();
	widget = create_adi_child();

	/* widget isn't adi child */
	gtk_adi_set_child_title_text(self, widget, (const gchar*) title);

	/* widget is adi child */
	gtk_adi_add(self, widget);
	gtk_adi_set_child_title_text(self, widget, (const gchar*) title);

	g_free(title);
}
END_TEST

START_TEST(test_set_child_icon)
{
	GdkPixbuf* icon;
	GtkWidget* widget;

	widget = create_adi_child();
	icon = create_adi_icon(widget);

	/* widget isn't adi child */
	gtk_adi_set_child_icon(self, widget, (const GdkPixbuf*) icon);

	/* widget is adi child */
	gtk_adi_add(self, widget);
	gtk_adi_set_child_icon(self, widget, (const GdkPixbuf*) icon);

	g_object_unref(icon);
}
END_TEST

START_TEST(test_set_child_close_button)
{
	GtkWidget* widget;

	widget = create_adi_child();
	gtk_adi_add(self, widget);

	gtk_adi_set_child_close_button(self, widget, TRUE);
	gtk_adi_set_child_close_button(self, widget, FALSE);
}
END_TEST

START_TEST(test_set_child_tab)
{
	GtkWidget* widget;

	widget = create_adi_child();
	gtk_adi_add(self, widget);

	gtk_adi_set_child_tab(self, widget, TRUE);
	gtk_adi_set_child_tab(self, widget, FALSE);
}
END_TEST

START_TEST(test_get_child_container)
{
	/* XXX get_child_container function missing from boxview and tabview */
	GtkWidget* container;
	GtkWidget* widget;

	widget = create_adi_child();
	container = gtk_adi_get_child_container(self, widget);
	fail_unless(container == NULL, "got container for outside widget");

	gtk_adi_add(self, widget);
	container = gtk_adi_get_child_container(self, widget);
	fail_if(container == NULL, "failed to get container");
}
END_TEST

void add_test_functions(TCase* tc)
{
	tcase_add_test(tc, test_add);
	tcase_add_test(tc, test_user_add_child);
	tcase_add_test(tc, test_user_add_child_with_layout);
	tcase_add_test(tc, test_set_current_widget);
	tcase_add_test(tc, test_set_current_child); /* TODO not sure how this works */
	tcase_add_test(tc, test_remove_current_child);
	tcase_add_test(tc, test_remove_all_children);
	tcase_add_test(tc, test_set_next_previous_child);
	tcase_add_test(tc, test_change_mode);
	tcase_add_test(tc, test_change_view);
	tcase_add_test(tc, test_change_state);
	tcase_add_test(tc, test_set_layout);
	tcase_add_test(tc, test_change_color);
	tcase_add_test(tc, test_set_child_title_text);
	tcase_add_test(tc, test_set_child_icon);
	tcase_add_test(tc, test_set_child_close_button);
	tcase_add_test(tc, test_set_child_tab);
	tcase_add_test(tc, test_get_child_container);
}

Suite* create_suite(void)
{
	Suite* s = suite_create("gtkadi");

	/* boxview */
	TCase* boxview = tcase_create("boxview");
	tcase_add_checked_fixture(boxview, setup_default, teardown);
	tcase_add_checked_fixture(boxview, init_boxview, NULL);
	add_test_functions(boxview);
	suite_add_tcase(s, boxview);

	TCase* boxview_child = tcase_create("boxview with initial child");
	tcase_add_checked_fixture(boxview_child, setup_default, teardown);
	tcase_add_checked_fixture(boxview_child, init_boxview, NULL);
	tcase_add_checked_fixture(boxview_child, init_initial_child, NULL);
	add_test_functions(boxview_child);
	suite_add_tcase(s, boxview_child);

	/* tabview */
	TCase* tabview = tcase_create("tabview");
	tcase_add_checked_fixture(tabview, setup_default, teardown);
	tcase_add_checked_fixture(tabview, init_tabview, NULL);
	add_test_functions(tabview);
	suite_add_tcase(s, tabview);

	TCase* tabview_child = tcase_create("tabview with child");
	tcase_add_checked_fixture(tabview_child, setup_default, teardown);
	tcase_add_checked_fixture(tabview_child, init_tabview, NULL);
	tcase_add_checked_fixture(tabview_child, init_initial_child, NULL);
	add_test_functions(tabview_child);
	suite_add_tcase(s, tabview_child);

	/* winview */
	TCase* winview = tcase_create("winview");
	tcase_add_checked_fixture(winview, setup_default, teardown);
	tcase_add_checked_fixture(winview, init_winview, NULL);
	add_test_functions(winview);
	suite_add_tcase(s, winview);

	TCase* winview_child = tcase_create("winview with child");
	tcase_add_checked_fixture(winview_child, setup_default, teardown);
	tcase_add_checked_fixture(winview_child, init_winview, NULL);
	tcase_add_checked_fixture(winview_child, init_initial_child, NULL);
	add_test_functions(winview_child);
	suite_add_tcase(s, winview_child);

	return s;
}
