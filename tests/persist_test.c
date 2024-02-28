#include "persist_test.h"

/// A Scrapper struct unit tests suite
START_TEST (test_persist_create)
{
  /* unit test code */
  Persist *p = persist_create(true);
  ck_assert_ptr_ne(p, NULL);

  persist_free(p);
}
END_TEST

/// Save an test document
START_TEST (test_persist_save)
{
  /* unit test code */
  Persist *p = persist_create(true);

  ScrapperResult sr;
  persist_save(p, &sr);
  //ck_assert_ptr_ne(p, NULL);

  persist_free(p);
}
END_TEST



/** The persistence test suite
  *
  * \return The check Suite.
  *
  */
Suite*
persist_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Persist");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_persist_create);
    tcase_add_test(tc_core, test_persist_save);
    
    return s;
}
