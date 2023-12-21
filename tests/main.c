#include <stdlib.h>   // USES system(), EXIT_SUCCESS and EXIT_FAILURE
#include <stdio.h>    // USES printf()
#include <check.h>

#include "src/logger.h"

#include "config.h"
#include "logger_test.h"
#include "persist_test.h"
#include "scrapper_test.h"

/** This test is used to check if a simple call to our main binary, without
  * any argument because we had an invalid pointer error sometimes.
  *
  */
START_TEST (test_main_invalid_pointer)
{
  int return_code = system("./escrapper > /dev/null");
  ck_assert_int_eq(return_code, 0);
}
END_TEST

/// Created to check for the main binary call
Suite*
main_suite(void)
{
  Suite *s;
  TCase *tc_main;

  s = suite_create("Escrapper");

  /* Core test case */
  tc_main = tcase_create("Main");
  tcase_add_test(tc_main, test_main_invalid_pointer);
  suite_add_tcase(s, tc_main);
      
  return s;
}


/** The main entry of the unit tests executable
  *
  */
int main(void)
{
  // Create logger or print error
  int lret = logger_static_create(LOGENV_TEST, "escrapper-tests.log");
  if (lret)
    printf("Error creating logger : %d!\n", lret);
      
  SRunner *sr = srunner_create(main_suite());

  srunner_add_suite(sr, config_suite());
  srunner_add_suite(sr, scrapper_suite());
  srunner_add_suite(sr, persist_suite());
  srunner_add_suite(sr, logger_suite());
  
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
      
  logger_static_free();

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
