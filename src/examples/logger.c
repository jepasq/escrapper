#include "logger.h"

#include <stdio.h>   // USES printf

// Mainly to test logger varargs handling.

int
main(int argc, char** argv)
{
  int lr = logger_static_create(LOGENV_TEST, "logger-test.log");
  if (lr != 0)
    {
      printf("ERROR: can't create logger instance : %d", lr);
      return lr;
    }
  
  // No varargs
  logger_static_log(__FILE_NAME__, __LINE__, LL_INFO, "Simple message");

  // Testing some standard values
    logger_static_log(__FILE_NAME__, __LINE__, LL_INFO,
		      "Simple integer message : %d", 123);

  
  void logger_static_free();
  return 0;
}
