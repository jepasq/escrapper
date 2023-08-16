#include "scrapper_test.h"
#include <check.h>

/// A Scrapper struct unit tests suite
START_TEST (test_scrapper_create)
{
  /* unit test code */
  Scrapper *c = scrapper_create();
  ck_assert_ptr_ne(c, NULL);
  scrapper_free(c);
}
END_TEST


Suite*
scrapper_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Scrapper");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_scrapper_create);
    suite_add_tcase(s, tc_core);

    return s;
}
