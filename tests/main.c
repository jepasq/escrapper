#include <stdlib.h>   // USES EXIT_SUCCESS and EXIT_FAILURE
#include <stdio.h>    // USES printf()
#include <check.h>

#include "src/logger.h"

#include "config.h"
#include "logger_test.h"
#include "persist_test.h"
#include "scrapper_test.h"

/** The main entry of the unit tests executable
  *
  */
int main(void)
{
  if (logger_static_create (LOGENV_TEST, "escrapper-tests.log"))
    printf("Error creating logger!\n");
      
  Suite *s = config_suite();
  SRunner *sr = srunner_create(s);

  srunner_add_suite(sr, scrapper_suite());
  srunner_add_suite(sr, persist_suite());
  srunner_add_suite(sr, logger_suite());
  
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
      
  logger_static_free();

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
