/** \file config.c
  * The config files-related implementation file.
  *
  */

#include <stdlib.h> // USES malloc() and free()

#include "config.h"
#include "_config.h"  // USES PROJECT_NAME

#include <unistd.h>    // USES getuid()
#include <sys/types.h> // USES uid_t type
#include <pwd.h>       // USES getpwuid()

#include <string.h>    // USES strcat() and strlen()
#include <stdio.h>     // USES printf()
#include <errno.h>     // USES errno

#include "logger.h"

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

/** Free the memory malloc'ed for an object instanciated with config_create()
  *
  * \param c A pointer to fhe object to be freed.
  *
  */
void
config_free(Config* c)
{
  free(c);
}

/** Get the base directory of all config files
  *
  * \return The concatenated result of $HOME and PROJECT_NAME. Must be freed.
  *
  */
char*
config_basedir_get()
{
  char* homedir;

  // From https://stackoverflow.com/a/26696759
  if ((homedir = getenv("HOME")) == NULL)
    homedir = getpwuid(getuid())->pw_dir;

  char* ret=(char*)malloc(strlen(homedir) + 3 + strlen(PROJECT_NAME) + 1);
  snprintf(ret, 100, "%s/.%s/", homedir, PROJECT_NAME);
  return ret;
}

/** Return a concatenated file with basedir
  *
  * Teh goal of this function is to get 
  *
  * \param c  The config struct used to retrieve basedir.
  * \param fn The filename to append to basedir.
  *
  * \return The concatenated strings in a newly allocated string.
  *         Should be freed.
  *
  */
char*
config_basedir_concat(Config* c, const char* fn)
{
  char* ret = (char*)malloc(strlen(c->basedir) + strlen(fn) + 1);
  strcpy(ret, c->basedir);
  strcat(ret, fn);
  return ret;
}

/** Return the value of the given configuration key
  *
  * It will retrieve and return the content of the file found at the
  * <tt>{basedir}/key</tt> location where the basedir is the string returned
  * by the config_basedir_get() function.
  *
  * Note: will always return NULL if key is NULL or an empty string.
  *
  * \param config The config struct used to retrieve basedir.
  * \param key    The string key used to identify the config file.
  *
  * \return NULL in case of error.
  *
  */
char*
config_get_value(Config* config, const char* key)
{
  if ((key == NULL) || (strlen(key) < 1))
    return  NULL;

  printf("%s\n", config->basedir);

  char* filen = config_basedir_concat(config, key);
  char msg[180];
  sprintf(msg, "Testing key file '%s'\n", filen);
  LOGI(msg);

  char* ctn = config_get_file_content(filen);
  if (ctn == NULL)
    return NULL;

  // Should work (from https://stackoverflow.com/a/28462221)
  //  ctn[strcspn(ctn, "\n")] = 0;
  
  char* ret = strdup(ctn);
  free(ctn);
  // Use config_get_file_content here
  
  return ret;
}

/** Return the content of the given file or NULL if not found
  *
  * The returned string, if not NULL is malloc'ed and must
  * be freed with a free() call.
  *
  * Will remove any trailing EOL character if needed.
  *
  * \param filename The full path of the file.
  *
  * \return The content ot NULL if not found.
  *
  */
char*
config_get_file_content(const char* filename)
{
  char myString[100];
  char msg[80];

  FILE *fptr = fopen(filename, "r");
  if (fptr == NULL)
    {
      if (errno == ENOENT)
	sprintf(msg, "File doesn't exist '%s'.\n", filename);
      else
	sprintf(msg, "Can't open file '%s' : '%d'\n", filename, errno);
      LOGI(msg);
      return NULL;
    }
  // Read the content and store it inside myString
  fgets(myString, 100, fptr);

  // Print the file content
  sprintf(msg, "File '%s' content is '%s'\n", filename, myString);
  LOGI(msg);
  
  // Close the file
  fclose(fptr);

  if (myString[strlen(myString) - 1] == '\n')
    return (char*)memcpy(myString, myString, strlen(myString) - 1);
  else
    return strdup(myString);
}

