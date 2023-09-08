/** \file logger.h
  * The header file of logger implementation.
  *
  */

#ifndef __LOGGER_H__
#define __LOGGER_H__

typedef enum {
  LOGENV_PROD,      //!< We're in production mod (the default)
  LOGENV_TEST,      //!< We're in test mode, io in terminal is blocked
} tLoggerEnvironment;

int logger_static_create(tLoggerEnvironment, const char*);

void logger_static_free();

#endif // !__LOGGER_H__
