#include "scrapper_test.h"
#include <check.h>

#include <stdlib.h>   // USES free()


/** The URL that should trigger a 404 HTTP error
  *
  * Check it with :
  *   curl -sw '%{http_code}' URL
  *
  */
#define URL_404 "https://google.com/non-accessible-page"

// A shortcut to check if an URL is valid
#define URL_CHECK(a,b) ck_assert_int_eq(scrapper_url_is_valid(a), b)

/// A Scrapper struct unit tests suite
START_TEST (test_scrapper_create)
{
  Scrapper *c = scrapper_create();
  ck_assert_ptr_ne(c, NULL);

  ck_assert_str_eq(c->current_url, "");

  scrapper_free(c);
}
END_TEST

START_TEST (test_scrapper_set_url)
{
  /* unit test code */
  Scrapper *c = scrapper_create();
  ck_assert_ptr_ne(c, NULL);

  scrapper_set_url(c, "new_URL");
  ck_assert_str_eq(c->current_url, "new_URL");

  scrapper_free(c);
}
END_TEST

/// Run Should get a 404 status code for a non-existant URL
START_TEST (test_scrapper_run_404)
{
  /* unit test code */
  Scrapper *c = scrapper_create();
  ck_assert_ptr_ne(c, NULL);

  scrapper_set_url(c, URL_404);
  
  ScrapperResult* resp = scrapper_run(c);
  ck_assert_int_eq(resp->httpStatusCode, 404);
  
  scrapper_free(c);
}
END_TEST


START_TEST (test_scrapper_check_url)
{
  URL_CHECK("https://example.com", true);
  URL_CHECK("http://exaampl3.com", true);
  URL_CHECK("https://google.com/search?param", true);

  URL_CHECK("examsdple.com", false);      // Missing protocol
  URL_CHECK("http:exaampl3.com", false);  // Missing protocol separator
  URL_CHECK("examsdple", false);          // Invalid

  URL_CHECK(NULL, false);          // Invalid
  URL_CHECK("",   false);          // Invalid
}
END_TEST

START_TEST (test_scrapper_prepend_https)
{
  char* ret = scrapper_prepend_https("aze");
  ck_assert_str_eq(ret, "https://aze");
  free(ret);
  
  ck_assert_ptr_eq(scrapper_prepend_https(NULL),  NULL);
}
END_TEST


Suite*
scrapper_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Scrapper");

  /* Core test case */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_scrapper_create);
  tcase_add_test(tc_core, test_scrapper_set_url);
  tcase_add_test(tc_core, test_scrapper_check_url);
  tcase_add_test(tc_core, test_scrapper_prepend_https);
  suite_add_tcase(s, tc_core);
    
  TCase* tc_long = tcase_create("ScrapperLong");
  tcase_set_timeout(tc_long, 20); // Set timeout to 20s
  tcase_add_test(tc_long, test_scrapper_run_404);
  suite_add_tcase(s, tc_long);
  
  return s;
}
