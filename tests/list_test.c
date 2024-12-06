#include "list_test.h"

#include <string.h>   // USES strcmp()
#include <stdio.h>

START_TEST (test_list_create)
{
  /* unit test code */
  List *l = list_create("aze");
  ck_assert_ptr_ne(l, NULL);

  ck_assert_ptr_eq(l->next, NULL);
  ck_assert_int_eq(list_len(l), 1); // List minimum is always 1 (first node)

  ck_assert_int_eq(l->values_len, 3);

  list_free(l);
}
END_TEST

START_TEST (test_list_len)
{
  ck_assert_int_eq(list_len(NULL), 0);

  List* l = list_create("aze");
  ck_assert_int_eq(list_len(l), 1);
  
  list_append( l, "zer" );
  ck_assert_int_eq(list_len(l), 2);

  list_append( l, "1" );
  list_append( l, "22" );
  list_append( l, "33" );
  ck_assert_int_eq(list_len(l), 5);

  
  list_free(l);
}
END_TEST

START_TEST (test_list_append)
{
  List *l = list_create("aze");
  ck_assert_int_eq(list_len(l), 1);

  ck_assert_int_eq(l->values_len, 3);
  list_append(l, "zer");
  
  ck_assert_int_eq(list_len(l), 2);
  ck_assert_int_eq(l->values_len, 6);
  
  list_free(l);
}
END_TEST


START_TEST (test_list_flatten)
{
  List *l = list_create("aaa");

  list_append(l, "bbb");
  list_append(l, "ccc");

  ck_assert_int_eq(strcmp(list_flatten(l), "aaabbbccc"), 0);
  
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
    tcase_add_test(tc_core, test_list_len);
    tcase_add_test(tc_core, test_list_append);
    tcase_add_test(tc_core, test_list_flatten);
    suite_add_tcase(s, tc_core);
    
    return s;
}
