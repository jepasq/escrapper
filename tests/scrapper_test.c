#include "scrapper_test.h"
#include <check.h>

/// A Scrapper struct unit tests suite
START_TEST (test_scrapper_create)
{
  /* unit test code */
  Scrapper *c = scrapper_create();
  ck_assert_ptr_ne(c, NULL);

  ck_assert_str_eq(c->current_url, "");

  scrapper_free(c);
}
END_TEST


START_TEST (test_scrapper_set_url)
{
  /* unit test code */
  Scrapper *c = scrapper_create();
  ck_assert_ptr_ne(c, NULL);

  scrapper_set_url(c, "new_URL");
  ck_assert_str_eq(c->current_url, "new_URL");

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
    tcase_add_test(tc_core, test_scrapper_set_url);
    suite_add_tcase(s, tc_core);

    return s;
}
