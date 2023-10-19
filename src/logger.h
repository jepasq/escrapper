/** \file logger.h
  * The header file of logger implementation.
  *
  * Please note we don't use the GNU C-defined  \c __FILE__ macro
  * here because
  * it contains full path including all parent directories. Instead, we
  * use an **override** defines at the end of the *CMakeLists.txt* file.
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


#ifdef __FILE_NAME__
/// Log an information message. See logger.h documentation for more.
#  define LOGI(MSG) logger_static_log(__FILE_NAME__, __LINE__, LL_INFO, msg)
/// Log an error message. See logger.h documentation for more.
#  define LOGE(MSG) logger_static_log(__FILE_NAME__, __LINE__, LL_ERR, msg)

#else
// We don't have __FILE_NAME__ : fallback to FILE but it WILL show full path
// (mainly for CI on github actions)


/// Log an information message. See logger.h documentation for more.
#  define LOGI(MSG) logger_static_log(__FILE__, __LINE__, LL_INFO, msg)
/// Log an error message. See LOGI for more info
#  define LOGE(MSG) logger_static_log(__FILE__, __LINE__, LL_ERR, msg)

#endif  /* __FILE_NAME__ */

extern struct _Logger* logger; //!< The global logger defined in impl. file

int logger_static_create(tLoggerEnvironment, const char*);
void logger_static_free();

void logger_static_log(const char*, int, tLoggerLevel, const char*);
char* logger_static_level_to_str(tLoggerLevel);

#endif // !__LOGGER_H__
