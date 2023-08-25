#ifndef __SCRAPPER_H__
#define __SCRAPPER_H__

/** The scrapper configuration and running object
  *
  */
typedef struct _Scrapper
{
  /** current URL, eventually a cache etc... */
  char* current_url;
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
typedef struct _ScrapperResult
{
  /** The HTTP status code
    *  https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
    */
  int   httpStatusCode;   
  char* markdownContent; //!< Cuurently unused char*
  
} ScrapperResult;

ScrapperResult* scrapper_run(Scrapper*);


#endif // !__SCRAPPER_H__
