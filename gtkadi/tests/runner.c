#include <stdlib.h>
#include <check.h>

extern Suite* create_suite();

START_TEST(test_sanity)
{
	fail_unless(1, "1 is false");
}
END_TEST

Suite* core_suite(void)
{
	Suite *s = suite_create("core");
	TCase *tc = tcase_create("core");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, test_sanity);
	return s;
}

int main(int argc, char* argv[])
{
	int ret;

	/* prepare runner */
	SRunner* sr = srunner_create(core_suite());
	srunner_add_suite(sr, create_suite());

	/* set logfile if requested */
	if (argc == 2)
		srunner_set_xml(sr, argv[1]);

	/* run suite */
	srunner_run_all(sr, CK_ENV);
	ret = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (ret == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
