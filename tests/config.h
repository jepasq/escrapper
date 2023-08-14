#ifndef __CONFIG_TEST_H__
#define __CONFIG_TEST_H__

#include "config.h"

/// A config struct unit tests suite
Suite * config_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Config");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_config_create);
    suite_add_tcase(s, tc_core);

    return s;
}

#endif // !__CONFIG_TEST_H__
