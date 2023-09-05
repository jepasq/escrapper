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

/** Return a concatenated file with basedir
  *
  * Teh goal of this function is to get 
  *
  * \param c  The config struct used to retrieve basedir.
  * \param fn The filename to append to basedir.
  *
  * \return The concatenated strings.
  *
  */
char*
config_basedir_concat(Config* c, const char* fn)
{
  char* ret = c->basedir;
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
  * \return NULL in case of error.
  *
  */
char*
config_get_value(Config* config, const char* key)
{
  if ((key == NULL) || (strlen(key) < 1))
    return  NULL;

  char* filen = config_basedir_concat(config, key);
  printf("Testing key file '%s'\n", filen);

  // USe config_get_file_content here
  
  return "value";
}

/** Return the content of the given file or NULL if not found
  *
  * The returned string, if not NULL is malloc'ed and must
  * be freed with a free() call.
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

  FILE *fptr = fopen(filename, "r");
  if (fptr == NULL)
    {
      if (errno == ENOENT)
	  printf("File doesn't exist '%s'.\n", filename);
      else
	  printf("Can't open file '%s' : '%d'\n", filename, errno);

      return NULL;
    }
  // Store the content of the file

  // Read the content and store it inside myString
  fgets(myString, 100, fptr);

  // Print the file content
  printf("File '%s' content is '%s'\n", filename, myString);

  // Close the file
  fclose(fptr);

  return strdup(myString);
}

