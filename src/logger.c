/** \file logger.c
  * The logger implementation file.
  *
  */

#include "logger.h"

#include <stddef.h>    // USES NULL
#include <string.h>    // USES strlen()
#include <stdlib.h>    // USES malloc() and free()
#include <stdio.h>     // USES fopen(), fclose() etc...

/** The struct that handles all logger-related attributes
  *
  * The logger can log both in a text file and in the terminal. This
  * behavior can be change by selecting another environment :
  *
  * The can be one and only one logger per instance.
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
  tLoggerEnvironment environment;  //!< The logger's environment
  char*              filename;     //!< The filename to log to
  FILE*              file;         //!< The opened file handle
}; // No need for a typedef here. It's a private statis struct

// The infamous static logger
static struct _Logger* logger = NULL;
  
/** Create athe unique static logger
  *
  * After creation, the logger_static_free() function must be called.
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


  logger = malloc(sizeof(logger));
  logger->filename = strdup(filename);
  logger->file = fopen(filename, "w");
  
  return 0;
}

/**  Free the memory used by the logger
  *
  */
void
logger_static_free()
{
  fclose(logger->file);
  free(logger->filename);  //strdup'ed in logger_static_create
  free(logger);
}

/** Log the message to the current logger
  *
  * This function can be use directly but will be used by macros to
  * feed two or three first arguments later.
  *
  * \param file    The file the message come from.
  * \param line    The line the message come from.
  * \param level   The message level.
  * \param message The message to be printed/logged.
  *
  */
void
logger_static_log(const char* file, int line,
		  tLoggerLevel level, const char* message)
{
  char buffer[80];
  char* lvl = logger_static_level_to_str(level);
  sprintf(buffer, "%s:%d %s - %s\n", file, line, "II", message);

  if (logger->environment == LOGENV_PROD)
    printf(buffer);
  
  fprintf(logger->file, buffer);
  fflush(logger->file);
  free(lvl);
}

/** Return a 2 chars dynamically allocated string that represent the given
  * level
  *
  * The returned string must be freed.
  *
  * \param lvl The level to be represented.
  *
  * \return A two character string.
  *
  */
char*
logger_static_level_to_str(tLoggerLevel lvl)
{
  char* ret;
  switch (lvl)
    {
    case LL_INFO: ret = "II";  break;
    case LL_WARN: ret = "WW";  break;
    default:      ret = "EE";
    }
  return strdup(ret);
}
