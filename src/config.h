#ifndef __CONFIG_H__
#define __CONFIG_H__

#define APPNAME "escrapper"


/** The configuration structure
  *
  */
typedef struct {

} Config;

Config* config_create();
void    config_free(Config*);

char* config_basedir_get();
#endif // !__CONFIG_H__
