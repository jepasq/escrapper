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


typedef struct _ScrapperResult
{
  int   httpStatusCode;
  char* markdownContent;
  
} ScrapperResult;



#endif // !__SCRAPPER_H__
