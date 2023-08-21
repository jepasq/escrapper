#include <stdlib.h>   // USES EXIT_SUCCESS and EXIT_FAILURE
#include <check.h>

#include "config.h"
#include "scrapper_test.h"

/** The main entry of the unit tests executable
  *
  */
int main(void)
{
  Suite *s = config_suite();
  SRunner *sr = srunner_create(s);

  srunner_add_suite(sr, scrapper_suite());
  
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}
