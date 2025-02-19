/** \file main.c
  * The main entry function implementation file.
  *
  */
    
#include <Elementary.h>
#include <assert.h>

#include "constants.h"  // USES EXIT_ status
#include "config.h"
#include "logger.h"     // USES logger_static_create() and logger_static_free()
#include "persist.h"
#include "scrapper.h"
#include "ui.h"

Scrapper* scrapper = NULL;  //!< The general static scrapper object

// Forward declarations
int help(void);
// End of forward declarations


/** The Quit button callback
  *
  * In fact it deletes the caller pointed by the data paramater.
  *
  * Note : not in use aactually.
  *
  * \param data       The emmiter object.
  * \param obj        Not used.
  * \param event_info Not used.
  *
  */
static void
on_click(void *data, Evas_Object *obj, void *event_info)
{
  evas_object_del(data);
}

/** A debugging callback used to print emission and source in console
  *
  * \param data     Nor used.
  * \param obj      Not used.
  * \param emission The name of the emitter value.
  * \param source   The source string.
  *
  */
static void
_signal_cb(void *data, Evas_Object *obj, const char *emission,
	   const char *source)
{
   printf("Info received from layout : %s %s\n", emission, source);
}

/** The scrap button has been clicked
  *
  * It checks the URL we get from the elm entry using the
  * scrapper_url_is_valid
  *
  * \param data     Nor used.
  * \param obj      Not used.
  * \param event    Not used.
  *
  */
static void
scrap_cb(void *data, Evas_Object *obj, void* event)
{
  const char* url = ui_get_str_url();
  printf("New URL is : '%s'\n", url);

  char* msg;
  
  if (scrapper_url_is_valid(url))
    {
      ui_set_str_status("URL is valid, scrapping...");
      scrapper_set_url(scrapper, url);
      ScrapperResult* res = scrapper_run(scrapper);
      msg = "URL visited. content added to DB.";
    }
  else
    {
      msg = "URL is not valid";
    }
  
  ui_set_str_status(msg);
  
}

/** The elm/entry input callback
  *
  * See for more :
  * https://docs.enlightenment.org/auto/group__Elm__Entry__Group.html
  *
  * \param data  Always null.
  * \param obj   The evas object that emitted the signal.
  * \param event The event parametter.
  *
  */
static void
input_cb(void* data, Evas_Object* obj, void* event)
{
  const char* ce = elm_entry_entry_get(ui_get_entry_url());
  //  printf("Evas obj. : %s !\n", ce);
}

/** Run a newly instanciated scrapper on the given URL
 * 
 *  @param url The URL to be scrapped.
 *
 *  @return Whatever the scrapper result is equal to HTTP 200.
 *
 */
static int
run_scrapper_on(char* url)
{
  LOGI("Creating persistence object");
  Persist* pers = persist_create(false);
	
  scrapper_set_url(scrapper, url);
  ScrapperResult* res = scrapper_run(scrapper);
  persist_free(pers);
  
  return (res->httpStatusCode == 200);
}

/** The application main function
  *
  * This function initialize ELM stack and load example.edj compiled file.
  *
  * \param argc Number of command line arguments.
  * \param argv Array of C-string based arguments.
  *
  * \return Always 0.
  *
  */
EAPI_MAIN int
elm_main(int argc, char **argv)
{
  if (logger_static_create (LOGENV_PROD, "escrapper.log"))
    printf("Error creating logger!\n");

  char* cbasedir = config_basedir_get();
  char msg[80];
  char url[120];
  sprintf(msg, "Config basedir is '%s'", cbasedir);
  LOGI(msg);

  if (strcmp(argv[1], "-h") == 0)
    return help();
  
  // Create the static instance
  scrapper = scrapper_create();
  strcpy(url, argv[1]);
  /** Try to scrap eventual URL passed in argv */
  if (argc > 1)
    if (scrapper_url_is_valid(url))
      {
	assert(url && "URL is valid");
	char msg[80];
	sprintf(msg, "arg1 is an URL ('%s'), trying to scrap it !!", url);
	LOGI(msg);

	return run_scrapper_on(url);
      }
    else
      {
	char* urlp = scrapper_prepend_https(url);
	sprintf(msg, "arg1 is not a valid URL ('%s'), trying with '%s' !!",
		url, urlp);
	if (scrapper_url_is_valid(urlp))
	  {
	    int ret = run_scrapper_on(urlp);
	    free(urlp);
	    return ret;
	  }
	else
	  {
	    free(urlp);
	    char msg[80];
	    sprintf(msg, "Can't get a valid URL from '%s', Bye !!", url);
	    LOGI(msg);
	    exit(EXIT_INVALID_URL);
	  }
      }
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  char* ui = 
#if UI_USE_BOX > 0
  ui_create_win_box();
#else
  ui_create_win();
#endif
  printf("Using '%s' UI version\n", ui);
  
  // Callbacks setup
  /*evas_object_smart_callback_add(ui_get_entry_url(),
    "changed,user", input_cb, NULL);*/
  evas_object_smart_callback_add(ui_get_button_scrap(),
				 "clicked", scrap_cb, NULL);
  elm_run();

  scrapper_free(scrapper);
  //  persist_free(pers);
  logger_static_free();
  
  return 0;
}
ELM_MAIN()


/** Print to stdout a short introfuction and usable options
 *
 *  @return Alwasy 0 to be chained with main()'s return value.
 *
 */
int
help(void)
{
  printf("escrapper logger\n");

  printf("\nUsage :\n");
  printf("  escrapper [-h] <URL>\n");

  printf("\nOptions :\n");
  printf("  -h   Show this help/usage message ans exit peacefully\n");

  
  return 0; // Always quit peacefully
}
