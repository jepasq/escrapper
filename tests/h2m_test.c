#include "h2m_test.h"

/// A Scrapper struct unit tests suite
START_TEST (test_h2m_bold)
{
  ck_assert_str_eq(html_to_markdown("<bold>aze</bold>"),     "**aze**");
  ck_assert_str_eq(html_to_markdown("<strong>aze</strong>"), "**aze**");
}
END_TEST

START_TEST (test_h2m_italic)
{
  ck_assert_str_eq(html_to_markdown("<i>aze</i>"),   "*aze*");
  ck_assert_str_eq(html_to_markdown("<em>aze</em>"), "*aze*");
}
END_TEST

// Very strong but only once in markdown
START_TEST (test_h2m_double_bold)
{
  ck_assert_str_eq(html_to_markdown("<strong><strong>aze</strong></strong>"),
		   "*aze*");
}
END_TEST

// Very strong but only once in markdown
START_TEST (test_h2m_bold_and_italic)
{
  ck_assert_str_eq(html_to_markdown("<em><strong>aze</strong></em>"),
		   "***aze***");
}
END_TEST


/** The persistence test suite
  *
  * \return The check Suite.
  *
  */
Suite*
h2m_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("HtmlToMarkdown");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_h2m_bold);
    tcase_add_test(tc_core, test_h2m_italic);
    tcase_add_test(tc_core, test_h2m_double_bold);
    tcase_add_test(tc_core, test_h2m_bold_and_italic);
    suite_add_tcase(s, tc_core);
    
    return s;
}
