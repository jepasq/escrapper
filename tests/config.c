#include "config.h"
#include <check.h>

START_TEST (test_config_create)
{
  /* unit test code */
  Config *c = config_create();
  ck_assert_ptr_ne(c, NULL);
  config_free(c);
}
END_TEST

/// A config struct unit tests suite
Suite*
config_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Config");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_config_create);
    suite_add_tcase(s, tc_core);

    return s;
}
