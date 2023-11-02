#include "config.h"
#include <check.h>

#include <string.h>   // USES strstr()

#include <unistd.h>   // USES getcwd()
#include <limits.h>   // USES PATH_MAX


/** The text the basedir must contain */
char* must_contain = ".escrapper";

/// Test the config struct can be instantiated
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

/// We can get the full path of a config file by its name
START_TEST (test_config_basedir_concat)
{
  Config *c = config_create();
  char* ced = config_basedir_concat(c, "aze");
  ck_assert_ptr_ne(strstr(ced, "/aze"), NULL);
  config_free(c);
}
END_TEST

/// See if baseduir change if concat is called twice
START_TEST (test_config_basedir_concat_twice)
{
  Config *c = config_create();
  char*c1 = strdup(c->basedir);
  
  char* ced = config_basedir_concat(c, "aze");
  ck_assert_str_eq(c->basedir, c1);

  char* ce2 = config_basedir_concat(c, "again");
  ck_assert_str_eq(c->basedir, c1);
  
  config_free(c);
}
END_TEST


START_TEST (test_config_get_value_str_null)
{
  char* val;
  const char* key = "inexistant-key";
  
  Config *c = config_create();
  val = config_get_value(c, key);
  ck_assert_ptr_eq(val, NULL);    // This key shouldn't exist
  val = config_get_value(c, NULL);
  ck_assert_ptr_eq(val, NULL);    // This key shouldn't exist

  val = config_get_value(c, "");
  ck_assert_ptr_eq(val, NULL);    // This key shouldn't exist
  config_free(c);
}
END_TEST

START_TEST (test_config_get_content)
{
  char* c;

  // Non-existant file must return NULL
  c=config_get_file_content("/dev/inexting-device-should-return-NULL");
  ck_assert_ptr_eq(c, NULL);

  // Whatever the content of the device we get, we can find it
  c=config_get_file_content("Doxyfile");
  ck_assert_ptr_ne(c, NULL);
}


#include <stdio.h>
START_TEST (test_config_eol)
{
  char* c;
  // This file is generated with cmake's configure_fuile() function
  c=config_get_file_content("fixtures/config_eol");
  ck_assert_ptr_ne(c, NULL);

  printf("%s\n", c );
  char cl = c[strlen(c) - 1];  // Get last char
  ck_assert_int_ne(cl, '\n');  // Shouldn't be an EOL char
}

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
    tcase_add_test(tc_core, test_config_basedir_concat_twice);
    tcase_add_test(tc_core, test_config_get_value_str_null);
    tcase_add_test(tc_core, test_config_get_content);

    tcase_add_test(tc_core, test_config_eol);

    suite_add_tcase(s, tc_core);

    return s;
}
