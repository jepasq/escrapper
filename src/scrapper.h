/** \file scrapper.h
  * The header file of Scrapper work functions.
  *
  */

#ifndef __SCRAPPER_H__
#define __SCRAPPER_H__

#include "list.h"

#include <stdbool.h>  // USES bool

/** The scrapper configuration and running object
  *
  */
typedef struct
{
  /** current URL, eventually a cache etc... */
  char* current_url;
  /** To-be-flatten list or received network packet */
  List* content_list; 
} Scrapper;

Scrapper* scrapper_create();
void scrapper_free(Scrapper*);

void scrapper_set_url(Scrapper*, const char*);

/** The result of a scrapper run
  *
  * The result of a scrapping action. Mainly returned (and malloc'ed) by
  * scrapper_run() function.
  *
  */
typedef struct
{
  /** The HTTP status code
    *  https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
    */
  int   httpStatusCode;
  char* pageTitle;       //!< The title of the webpage   
  char* markdownContent; //!< Cuurently unused char*
  
} ScrapperResult;

ScrapperResult* scrapper_run(Scrapper*);

bool  scrapper_url_is_valid(const char*);
char* scrapper_prepend_https(const char*);


#endif // !__SCRAPPER_H__
