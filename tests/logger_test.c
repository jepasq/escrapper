#include "logger_test.h"

#include "src/logger.h"

#include <stdio.h>   // USES fopen(), fclose()
#include <sys/stat.h> // USES stat()

#define LOG_FILENAME "logfile-test.log"

/** Returns size of file in bytes or -1 if file not found */
int
get_file_size(const char* filename)
{
  int size;
  // Standard library version (not sure it compiles)
  /** 
  FILE* file = fopen(filename, "r");
  int ret = fseek(file, 0, SEEK_END);;
  size = ftell(file);
  fclose(file);
  */

  // Posix-only version
  struct stat st;
  if (stat(filename, &st) != 0) // stat() returns -1 if an error occured
    return -1;
  size = st.st_size;
  
  return size;
}

/// A Scrapper struct unit tests suite
START_TEST (test_logger_create)
{
  int ret;
  
  // Real file, return 0
  ret = logger_static_create(LOGENV_TEST, "logger_unittest.log");
  ck_assert_int_eq(ret, 0);

  // Can't open empty log file
  ret = logger_static_create(LOGENV_TEST, "");
  ck_assert_int_ne(ret, 0);

  // Can't open NULL log file
  ret = logger_static_create(LOGENV_TEST, NULL);
  ck_assert_int_ne(ret, 0);
  
  logger_static_free();
}
END_TEST

/// Check for the size of an inexistant file
START_TEST (test_logger_check_inexistant_file_size)
{
  int s = get_file_size("inexistant_file.na.me");
  ck_assert_int_eq(s, -1);
}
END_TEST

/** Test, checin its size, that logging a message in PROD effectively
  * write something in the given file
  *
  * It will also write with an inexistant log file because its initial
  * size will be -1.
  *
  */
START_TEST (test_logger_log_in_file)
{
  int size1, size2;
  logger_static_create(LOGENV_PROD, LOG_FILENAME);
  size1 = get_file_size(LOG_FILENAME);

  // For instance, use it directly, after implementation, we'll use macros
  logger_static_log("here.c", 123, LL_INFO, "Message to be printed!!!");
  
  size2 = get_file_size(LOG_FILENAME);
  ck_assert_int_ne(size1, size2);
  logger_static_free();
}
END_TEST

START_TEST (test_logger_level_to_str)
{
  char* val;
  
  val = logger_static_level_to_str(LL_INFO);
  ck_assert_str_eq(val, "II");
  free (val);

  val = logger_static_level_to_str(LL_WARN);
  ck_assert_str_eq(val, "WW");
  free (val);

  val = logger_static_level_to_str(LL_ERR);
  ck_assert_str_eq(val, "EE");
  free (val);
}
END_TEST

/// \return A Scrapper struct unit tests suite
Suite*
logger_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Logger");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_logger_create);
    tcase_add_test(tc_core, test_logger_check_inexistant_file_size);
    tcase_add_test(tc_core, test_logger_log_in_file);
    tcase_add_test(tc_core, test_logger_level_to_str);
    suite_add_tcase(s, tc_core);

    return s;
}
