#include "config.h"
#include <check.h>

#include <string.h>   // USES strstr()

/** The text the basedir must contain */
char* must_contain = ".escrapper";


START_TEST (test_config_create)
{
  Config *c = config_create();
  ck_assert_ptr_ne(c, NULL);
  config_free(c);
}
END_TEST

/// Check that basedir contains .escrapper text
START_TEST (test_config_basedir_contains)
{  
  Config *c = config_create();
  char* bd = config_basedir_get();
  ck_assert_ptr_ne(strstr(bd, must_contain), NULL);
  config_free(c);
}
END_TEST

/// Basedir is a config member
START_TEST (test_config_basedir_member)
{
  Config *c = config_create();
  ck_assert_ptr_ne(strstr(c->basedir, must_contain), NULL);
  config_free(c);
}
END_TEST

/// Basedir is a config member
START_TEST (test_config_basedir_concat)
{
  Config *c = config_create();
  char* ced = config_basedir_concat(c, "aze");
  ck_assert_ptr_ne(strstr(ced, "/aze"), NULL);
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
    tcase_add_test(tc_core, test_config_basedir_contains);
    tcase_add_test(tc_core, test_config_basedir_member);
    tcase_add_test(tc_core, test_config_basedir_concat);
    suite_add_tcase(s, tc_core);

    return s;
}
