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
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, s->current_url);
    //    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
    
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
	      curl_easy_strerror(res));
    
    curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}
