#ifndef __SCRAPPER_H__
#define __SCRAPPER_H__

/** The scrapper configuration and running object
  *
  */
typedef struct _Scrapper
{
/** current URL, eventually a cache etc... */
} Scrapper;

typedef struct _ScrapperResult
{
  int   httpStatusCode;
  char* markdownContent;
  
} ScrapperResult;


Scrapper* scrapper_create();
void scrapper_free(Scrapper*);

#endif // !__SCRAPPER_H__
