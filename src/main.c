/** \file main.c
  * The main entry function implementation file.
  *
  */
    
#include <Elementary.h>

#include "config.h"
#include "persist.h"
#include "scrapper.h"

Scrapper* scrapper;     //!< The general static scrapper object

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
  const char* url = elm_entry_entry_get(ui_get_entry_url());
  printf("New URL is : '%s'\n", url);

  char* msg;
  
  if (scrapper_url_is_valid(url))
    {
      msg = "URL is valid, scrapping...";
      scrapper_set_url(scrapper, url);
    }
  else
    {
      msg = "URL is not valid";
    }
  elm_object_text_set(ui_get_label_status(), msg);
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

  config_basedir_get();

  scrapper = scrapper_create();
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  Persist* pers = persist_create();
  Evas_Object *win = ui_create_win();

  // Callbacks setup
  evas_object_smart_callback_add(ui_get_entry_url(),
				 "changed,user", input_cb, NULL);
  evas_object_smart_callback_add(ui_get_button_scrap(),
				 "clicked", scrap_cb, NULL);
  
  //  elm_win_resize_object_add(win, box);
  //  evas_object_show(box);

  elm_run();

  scrapper_free(scrapper);
  persist_free(pers);
  
  return 0;
}
ELM_MAIN()
  
