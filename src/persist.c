/** \file persist.h
  * The persistence-related functions implementation.
  *
  */

#include "persist.h"

#include <stdlib.h> // USES malloc() and free()
#include <assert.h> // USES assert()
#include <stdio.h>  // USES sprintf()

#include "logger.h"
#include "config.h"

/** Check for the given value. Print an error if NULL
 *
 */
void
check_value(const char* value, Config* cfg, const char* key)
{
  if (value == NULL)
    {
      char msg[180];
      sprintf(msg, "ERR: Can't find config file '%s'\n",
	      config_basedir_concat(cfg, key));
      LOGE(msg);
      assert(value);
    }
}


/** Create and return a malloc'ed Persist struct
  *
  * \return a dynamically allocated object that should free with a call to
  *         persist_free().
  *
  */
Persist*
persist_create()
{
  Persist* p = malloc(sizeof(Persist*));

  Config* cfg = config_create();
  char* uri = config_get_value(cfg, "mongo_uri");
  check_value(uri, cfg, "mongo_uri");
  char* usr = config_get_value(cfg, "mongo_user");
  char* pwd = config_get_value(cfg, "mongo_pwd");
  return p;
}

/** Free the memory used by the given struct
  *
  * \param p The struct pointer to be free.
  *
  */
void
persist_free(Persist* p)
{
  free(p);
}
