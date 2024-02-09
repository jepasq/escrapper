/** \file persist.c
  * The persistence-related functions implementation.
  *
  */

#include "persist.h"

#include <stdlib.h> // USES malloc() and free()
#include <assert.h> // USES assert()
#include <stdio.h>  // USES sprintf()

#include "constants.h"  // USES EXIT_ status

#include "logger.h"
#include "config.h"

/** Check for the given value. Print an error if NULL then assert value
 *
 * \param value The value to be NULL-checked.
 * \param cfg   The config object used to retieve value.
 * \param key   The config key.
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
  * The returned struct will have feed fields with the values found in
  * your user's directory, mainly retrieved using config_get_value() calls.
  *
  * The retrieved values are then checked with a check_value() for each
  * field.
  *
  * \param test_db If true, will prepend dbname with '-test' for unit tests.
  *
  * \return A dynamically allocated object that should free with a call to
  *         persist_free().
  *
  */
Persist*
persist_create(bool test_db)
{
  bson_error_t error = {0};
  
  Persist* p = malloc(sizeof(Persist));
  
  Config* cfg = config_create();
  char* uri = config_get_value(cfg, "mongo_uri");
  check_value(uri, cfg, "mongo_uri");
  char* usr = config_get_value(cfg, "mongo_user");
  check_value(usr, cfg, "mongo_user");
  char* pwd = config_get_value(cfg, "mongo_pwd");
  check_value(pwd, cfg, "mongo_pwd");
  
  int port = 27017;
  char connstr[180];

  if (test_db)
    {
      //  sprintf(connstr, "mongodb+srv://%s:%s@%s:%d", usr, pwd, uri, port);
      sprintf(connstr, "mongodb://%s:%s@%s:%d", usr, pwd, uri, port);
    }
  else
    {
      sprintf(connstr, "mongodb://%s:%s@%s-test:%d", usr, pwd, uri, port);
    }
      
  char msg[180];
  sprintf(msg, "Trying to connect to '%s'\n", connstr);
  LOGI(msg);
  
  mongoc_init();
  p->client = mongoc_client_new(connstr);
  if (!p->client) {
    char msg[180];
    sprintf(msg, "Mongodb client is NULL. Maybe the mongodb server is OFF.\n"
	    "  Connstring was '%s'", connstr);
    LOGE(msg);
    exit(EXIT_NO_MONGO_SERVER);
  }
  
  mongoc_server_api_t* api = mongoc_server_api_new (MONGOC_SERVER_API_V1);
  if (!mongoc_client_set_server_api (p->client, api, &error))
    {
      LOGE(error.message);
      exit(EXIT_MONGO_SERVER_API);
  }

  
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
  mongoc_database_destroy(p->pagesdb);
  mongoc_client_destroy(p->client);
  mongoc_cleanup();
  free(p);
}
