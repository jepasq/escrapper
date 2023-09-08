/** \file logger.h
  * The header file of logger implementation.
  *
  */

#ifndef __LOGGER_H__
#define __LOGGER_H__

/** Defines the logger environment
  *
  */
typedef enum {
  LOGENV_PROD,      //!< We're in production mod (the default)
  LOGENV_TEST,      //!< We're in test mode, io in terminal is blocked
} tLoggerEnvironment;

/** Defines the level of a log message
  *
  */
typedef enum {
  LL_INFO,
  LL_WARN,
  LL_ERR,
} tLoggerLevel;

int logger_static_create(tLoggerEnvironment, const char*);
void logger_static_free();

void logger_static_log(const char*, int, tLoggerLevel, const char*);


#endif // !__LOGGER_H__
