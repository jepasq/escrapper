/** \file logger.c
  * The logger implementation file.
  *
  */

#include "logger.h"

#include <stddef.h>    // USES NULL
#include <string.h>   // USES strlen()

/** The struct that handles all logger-related attributes
  *
  * The logger can log both in a text file and in the terminal. This
  * behavior can be change by selecting another environment :
  *
  * - In LOGENV_PROD mode, it will log in both medium;
  * - In LOGENV_TEST one, it will only log in file to let the terminal
  *   output as clean as possible.
  *
  * According to the 
  *
  */
struct _Logger
{
  tLoggerEnvironment environment;  // The logger's environment
  char*              filename;     // The filename to log to
}; // No need for a typedef here. It's a private statis struct

static struct _Logger logger;
  
/** Create athe unique static logger
  *
  * \param env      The initial environment.
  * \param filename The relative file to create.
  *
  * \return 0 if the logger was succefully created, !0 in case of error.
  *
  */
int
logger_static_create(tLoggerEnvironment env, const char* filename)
{
  if (filename == NULL)
    return -1;

  if (strlen(filename)<1)
    return -2;

  
  return 0;
}

void
logger_static_free()
{

}
