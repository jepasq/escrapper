#include "persist_test.h"

/// A Scrapper struct unit tests suite
START_TEST (test_persist_create)
{
  Persist *p = persist_create(true);
  ck_assert_ptr_ne(p, NULL);

  persist_free(p);
}
END_TEST

/// Simply test the collection pointer isn't NULL
START_TEST (test_persist_pagescoll)
{
  Persist *p = persist_create(true);
  ck_assert_ptr_ne(p->pagescoll, NULL);
  persist_free(p);
}
END_TEST

/// Simple test the returned document count isn't negative
START_TEST (test_persist_count)
{
  /* unit test code */
  Persist *p = persist_create(true);

  int64_t c = persist_count(p);
  ck_assert_int_gt(c, -1);

  persist_free(p);
}
END_TEST


/// Save an test document
START_TEST (test_persist_save)
{
  /* unit test code */
  Persist *p = persist_create(true);

  int64_t c = persist_count(p);
  
  ScrapperResult sr;
  persist_save(p, &sr);

  ck_assert_int_eq(c+1, persist_count(p));

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
    tcase_add_test(tc_core, test_persist_pagescoll);
    tcase_add_test(tc_core, test_persist_count);
    tcase_add_test(tc_core, test_persist_save);
    
    return s;
}
