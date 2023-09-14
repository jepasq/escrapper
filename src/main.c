/** \file main.c
  * The main entry function implementation file.
  *
  */
    
#include <Elementary.h>

#include "config.h"
#include "persist.h"
#include "scrapper.h"

#include "_config.h"

Evas_Object* url_entry; //!< The elementary widget used to enter URL 
Evas_Object* status;    //!< The status label
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
  const char* url = elm_entry_entry_get(url_entry);
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
  elm_object_text_set(status, msg);
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
  const char* ce = elm_entry_entry_get(url_entry);
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
  
  //  load_elm_file("main.edj");

  // Create UI manually
  char title[50];
  strcpy(title, PROJECT_NAME);
  strcat(title, " ");
  strcat(title, PROJECT_NUMBER);
  
  Evas_Object *win = elm_win_util_standard_add("Main", title);
  //Evas_Object *win = elm_win_add(NULL, "main_window", ELM_WIN_BASIC);
  elm_win_autodel_set(win, EINA_TRUE);


  Evas_Object* table = elm_table_add(win);
  elm_win_resize_object_add(win, table);
  evas_object_show(table);
  elm_table_padding_set(table, 5, 5);

  Evas_Object* label = elm_label_add(win);
  elm_object_text_set(label, "Enter new URL to scrap then press button :");
  evas_object_show(label);
  elm_table_pack(table, label, 0, 0, 1, 1);

  // The URL entry
  url_entry = elm_entry_add(table);
  evas_object_show(url_entry);
  elm_table_pack(table, url_entry, 0, 1, 1, 1);
  elm_entry_entry_set(url_entry, "https://");
  elm_bg_color_set(url_entry, 250, 127, 250);  // Example color
  evas_object_size_hint_weight_set(url_entry,EVAS_HINT_EXPAND,EVAS_HINT_EXPAND);
  
  
  Evas_Object* scrap_btn = elm_button_add(table);
  elm_object_text_set(scrap_btn, "Scrap!");
  evas_object_show(scrap_btn);
  elm_table_pack(table, scrap_btn, 1, 1, 1, 1);


  Evas_Object* icon = elm_icon_add(win);
  elm_icon_standard_set(icon, "edit-find");  // go-next is also good
  elm_object_part_content_set(scrap_btn, "icon", icon);
  
  status = elm_label_add(win);
  evas_object_show(status);
  elm_table_pack(table, status, 0, 2, 1, 1);

  // Callbacks setup
  evas_object_smart_callback_add(url_entry, "changed,user", input_cb, NULL);
  evas_object_smart_callback_add(scrap_btn, "clicked", scrap_cb, NULL);
  
  //  elm_win_resize_object_add(win, box);
  //  evas_object_show(box);
  evas_object_resize(win, 800, 600); 
  evas_object_show(win);

  elm_run();

  scrapper_free(scrapper);
  persist_free(pers);
  
  return 0;
}
ELM_MAIN()
  
