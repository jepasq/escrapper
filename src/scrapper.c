#include "scrapper.h"

#include <stdlib.h> // USES malloc() and free()
#include <assert.h> // USES assert()
#include <string.h> // USES strdup

#include <curl/curl.h>

Scrapper* scrapper_create()
{
  Scrapper* s = malloc(sizeof(Scrapper*));
  s->current_url = "";
  return s;
}

void scrapper_free(Scrapper* s)
{
  free(s);
}

void
scrapper_set_url(Scrapper* s, const char* u)
{
  assert(s && "Is a valid scrapper");
  s->current_url = strdup(u);
}

/** Run the scrappe with the given scrapper
  *
  *
  *
  */
ScrapperResult*
scrapper_run(Scrapper* s)
{
  CURL* session;
  CURLcode curl_code;
  long http_code = 0;
    
  curl_global_init(CURL_GLOBAL_ALL);
  session = curl_easy_init();
  if (session)
    {
      curl_easy_setopt(session, CURLOPT_URL, s->current_url);
      // Speed up and disable print in terminal
      curl_easy_setopt(session, CURLOPT_NOBODY, 1); 
      
      curl_code = curl_easy_perform(session);
      curl_easy_getinfo (session, CURLINFO_RESPONSE_CODE, &http_code);
      curl_easy_cleanup(session);
    }
  curl_global_cleanup();
  
  // Return
  ScrapperResult* ret = malloc(sizeof(ScrapperResult));
  if (curl_code != CURLE_ABORTED_BY_CALLBACK)
    {
      ret->httpStatusCode = http_code;
    }
  else
    {
      ret->httpStatusCode = -1;
    }
  return ret;
}
