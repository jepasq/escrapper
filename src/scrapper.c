/** \file scrapper.c
  * The implementation file of Scrapper structure related functions.
  *
  */

#include "scrapper.h"

#include <stdlib.h> // USES malloc() and free()
#include <assert.h> // USES assert()
#include <string.h> // USES strdup

#include <curl/curl.h>

#include "logger.h"   // uses LOGI()

#include "h2m.h"


/** Callback used with curl easy
  *
  * See more online at https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
  *
  * \param ptr    your string variable a.k.a delivered data.
  * \param size   Is always 1.
  * \param count  Size of delivered data.
  * \param stream stream userdata used when calling CURLOPT_WRITEDATA.
  *
  * \return This function can return CURL_WRITEFUNC_PAUSE to pause the transfer.
  *
  */
size_t
callback_func(void *ptr, size_t size, size_t count, void *stream)
{

  List* l = (List*)ptr;
  list_append(l, stream);
  
  printf("CallbackF=='%s'", list_flatten(l));
  return size*count;
}
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
  s->content_list = list_create("");
  return s;
}

/** Free the memory used by the given Scrapper
  *
  * \param s A scrapper pointer.
  *
  */
void scrapper_free(Scrapper* s)
{
  list_free(s->content_list);
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
  LOGI("Inside scrapper_run...");
  CURL* session;
  CURLcode curl_code;
  long http_code = 0;
    
  curl_global_init(CURL_GLOBAL_ALL);
  session = curl_easy_init();
  if (!session)
    {
      LOGE("Invalid curl_easy session");
    }
  else
    {
      curl_easy_setopt(session, CURLOPT_URL, s->current_url);
      // Speed up and disable print in terminal
      curl_easy_setopt(session, CURLOPT_NOBODY, 1); 

      // Set a callback function
      curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, callback_func);
      curl_easy_setopt(session, CURLOPT_WRITEDATA, &s->content_list);
	
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
      ret->markdownContent = html_to_markdown(list_flatten(s->content_list));
      printf("HTTP code : '%d'", http_code);
      printf("Received data : '%s'", ret->markdownContent);
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
  * \return Return true if the URL is valid according to liburl's
  *         curl_url_set() function, instead, or if URL is NULL, return false.
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
      char msg[80];
      sprintf(msg, "Url '%s' is not valid : %d\n", url, rc);
      LOGI(msg);
      return false;
    }
  return true;
}


/** Prepend the https:// protocol to the given text
  *
  * The returned string memory is dynamically allocated using malloc() thus
  * it must be free'd using free().
  *
  * @param url The string you must prepend https string to.
  *
  * @return A new dynamically allocated string.
  *
  */
char*
scrapper_prepend_https(const char* url)
{
  if (url == NULL)
    return NULL;

  char* ret = (char*) malloc(strlen(url) + 9); // 9= 'https://' + \0
  strcpy(ret, "https://");
  strcat(ret, url);
  return ret;
}

