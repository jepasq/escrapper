/** \file scrapper.c
  * The implementation file of Scrapper structure related functions.
  *
  */

#include "scrapper.h"

#include <stdlib.h> // USES malloc() and free()
#include <assert.h> // USES assert()
#include <string.h> // USES strdup

#include <curl/curl.h>

/** Create and malloc a new Scrapper struct
  *
  * The scrapper is initialized with empty current_url;
  * The returned object must be freed with a call to scrapper_free().
  *
  * \return A newly malloc'ed Scrapper object.
  *
  */
Scrapper* scrapper_create()
{
  Scrapper* s = malloc(sizeof(Scrapper*));
  s->current_url = "";
  return s;
}

/** Free the memory used by the given Scrapper
  *
  * \param s A scrapper pointer.
  *
  */
void scrapper_free(Scrapper* s)
{
  free(s);
}

/** Set the current_url value for the given Scrapper
  *
  * \param s A scrapper pointer.
  * \param u The new URL.
  *
  */
void
scrapper_set_url(Scrapper* s, const char* u)
{
  assert(s && "Is a valid scrapper");
  s->current_url = strdup(u);
}

/** Run the scrappe with the given scrapper
  *
  * You can change the scrapped URL using the scrapper_set_url() function.
  *
  * \param s The scrapper to run on.
  *
  * \return A malloc'ed result. This should be freed when not anymore in use.
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

/** Check if the parameter is a valid URL
  *
  * \param url The url to check
  *
  */
bool
scrapper_url_is_valid(const char* url)
{
  if (url == NULL)
    return false;
  
  CURLUcode rc;
  CURLU* u = curl_url();
  rc = curl_url_set(u, CURLUPART_URL, url, 0);
  curl_url_cleanup(u);
  if (rc != 0)
    {
      // See https://curl.se/libcurl/c/libcurl-errors.htmlfor numeric value
      // meaning
      printf("Url '%s' is not valid : %d\n", url, rc);
      return false;
    }
  return true;
}

