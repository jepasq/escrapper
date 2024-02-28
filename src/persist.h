/** \file persist.h
  * The header of the persistence functions.
  *
  */

#ifndef __PERSIST_H__
#define __PERSIST_H__


#include <mongoc/mongoc.h>  // USES mongo_client_t

#include "scrapper.h"       // USES ScrapperResult

/** The struct used in persistence work
  *
  */
typedef struct
{
  mongoc_client_t*   client;   //!< The mongo C client instance
  mongoc_database_t* pagesdb;  //!< The pages collection
} Persist;

Persist* persist_create(bool test_db);
void     persist_free(Persist*);

void persist_save(Persist*, const ScrapperResult*);


#endif // __PERSIST_H__
