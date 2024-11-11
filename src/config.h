/** \file config.h
  * The header file of the config and config files-related functions.
  *
  * Not to be confused with config.h.in that is cmake-processed.
  *
  */

#ifndef __CONFIG_H__
#define __CONFIG_H__

/** The configuration structure containing values extracted from config files.
 *
 * The files are stored in a directory named $HOME/$PROJECT_NAME where
 * $HOME is the home directory environment variable, and PROJECT_NAME
 * is defined in cmake-generated @c config.h.
 *
 */
typedef struct
{
  char* basedir; //!< The basedir of all config files
} Config;

Config* config_create();
void    config_free(Config*);

char* config_basedir_get();
char* config_basedir_concat(Config*, const char*);

// Key/value work
char* config_get_value(Config*, const char*);
char* config_get_file_content(const char*);


#endif // !__CONFIG_H__
