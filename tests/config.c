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
