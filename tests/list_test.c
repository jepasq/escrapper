#include "list_test.h"

/// A Scrapper struct unit tests suite
START_TEST (test_list_create)
{
  /* unit test code */
  List *l = list_create();
  ck_assert_ptr_ne(l, NULL);

  ck_assert_ptr_eq(l->next, NULL);

  list_free(l);
}
END_TEST

/** The list test suite
  *
  * \return The check Suite.
  *
  */
Suite*
list_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("List");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_list_create);
    
    return s;
}
