/** \file config.h
  * The header file of the config and config files-related functions.
  *
  */

#ifndef __CONFIG_H__
#define __CONFIG_H__

/** The configuration structure
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
char* config_get_value(const char*);


#endif // !__CONFIG_H__
