#include <stdlib.h> // USES malloc() and free()

#include "config.h"
#include "_config.h"  // USES PROJECT_NAME

#include <unistd.h>    // USES getuid()
#include <sys/types.h> // USES uid_t type
#include <pwd.h>       // USES getpwuid()

#include <string.h>    // USES strcat()

/** Create and return a dynamically allocated Config pointer
  *
  * \return The newly allocated struct.
  *
  */
Config*
config_create()
{
  Config* ret = malloc(sizeof(Config));
  ret->basedir = config_basedir_get();
  return ret;
}

void
config_free(Config* c)
{
  free(c);
}

/** Get the base directory of all config files
  *
  */
char*
config_basedir_get()
{
  char* homedir;

  // From https://stackoverflow.com/a/26696759
  if ((homedir = getenv("HOME")) == NULL)
    homedir = getpwuid(getuid())->pw_dir;

  strcat(homedir, "/.");
  strcat(homedir, PROJECT_NAME);
  strcat(homedir, "/");
  return homedir;
}
