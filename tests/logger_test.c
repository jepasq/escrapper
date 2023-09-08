#include "logger_test.h"

#include "src/logger.h"

/// A Scrapper struct unit tests suite
START_TEST (test_logger_create)
{
  int ret;
  
  // Real file, return 0
  ret = logger_static_create(LOGENV_TEST, "logger_unittest.log");
  ck_assert_int_eq(ret, 0);

  // Can't open empty log file
  ret = logger_static_create(LOGENV_TEST, "");
  ck_assert_int_ne(ret, 0);

  // Can't open NULL log file
  ret = logger_static_create(LOGENV_TEST, NULL);
  ck_assert_int_ne(ret, 0);
  
  logger_static_free();
}
END_TEST


Suite*
logger_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Logger");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_logger_create);
    suite_add_tcase(s, tc_core);

    return s;
}
