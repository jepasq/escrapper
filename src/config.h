#ifndef __CONFIG_H__
#define __CONFIG_H__

/** The configuration structure
  *
  */
typedef struct {
  char* basedir; //!< The basedir of all config files
} Config;

Config* config_create();
void    config_free(Config*);

char* config_basedir_get();
#endif // !__CONFIG_H__
