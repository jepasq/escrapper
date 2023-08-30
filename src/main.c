/** \file main.c
  * The main entry function implementation file.
  *
  */
    
#include <Elementary.h>

#include "config.h"

Evas_Object* url_entry;

/** The Quit button callback
  *
  * In fact it deletes the caller pointed by the data paramater.
  *
  */
static void
on_click(void *data, Evas_Object *obj, void *event_info)
{
  evas_object_del(data);
}

/** A debugging callback used to print emission and source in console
  *
  */
static void
_signal_cb(void *data, Evas_Object *obj, const char *emission,
	   const char *source)
{
   printf("Info received from layout : %s %s\n", emission, source);
}

/** The scrap button has been changed
  *
  */
static void
scrap_cb(void *data, Evas_Object *obj, const char *emission,
	   const char *source)
{
  const char* txt = elm_entry_entry_get(url_entry);
  printf("Text changed : %s !\n", txt);
  /*  url_entry = evas_object_name_child_find(layout, "scrap-url", 8);
  url_entry = edje_object_part_object_get(layout, "scrap-url");
  if (url_entry)
    {
    }
  else
    printf("Cannot get 'scrap-url' object\n");
  */
}

/** The elm/entry input callback
  *
  * See for more :
  * https://docs.enlightenment.org/auto/group__Elm__Entry__Group.html
  *
  * \param data     Always null.
  *
  * \param emission The emitted signal name (i.e. 'changed,user').
  * \param source   The emetter of the callback (i.e. 'scrap-url').
  *
  */
static void
input_cb(void* data, Evas_Object* obj, void* event)
{
  const char* ce = elm_entry_entry_get(url_entry);
  printf("Evas obj. : %s !\n", ce);
}

void
load_elm_file(const char* file)
{
  Evas_Object* win;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  
  win = elm_win_util_standard_add("Main", "Hello, World!");
  elm_win_autodel_set(win, EINA_TRUE);

  Evas_Object* layout = elm_layout_add(win);
  evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND); 
  elm_layout_file_set(layout, file, "escrapper");

  /* Signature not compatible anymore
  elm_layout_signal_callback_add(layout, "clicked", "scrap-btn",scrap_cb,NULL);
  elm_layout_signal_callback_add(layout, "changed,user", "scrap-url",
				 input_cb,NULL);
  */
  
  // Commented out, too verbose
  //  elm_layout_signal_callback_add(layout, "*", "*", _signal_cb, NULL);

  elm_win_resize_object_add(win, layout);
  evas_object_show(layout);
  evas_object_show(win);
}



/** The application main function
  *
  * This function initialize ELM stack and load example.edj compiled file.
  *
  * \param argc Number of command line arguments.
  * \param argv Array of C-string based arguments.
  *
  */
EAPI_MAIN int
elm_main(int argc, char **argv)
{

  config_basedir_get();

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  //  load_elm_file("main.edj");

  // Create UI manually
  Evas_Object *win = elm_win_util_standard_add("Main", "Hello, World!");
  elm_win_autodel_set(win, EINA_TRUE);

  //  Evas_Object* box = elm_box_add(win);


  Evas_Object *table = elm_table_add(win);
  evas_object_show(table);
  url_entry = elm_entry_add(table);
  evas_object_show(url_entry);

  evas_object_smart_callback_add(url_entry, "changed,user", input_cb, NULL);
  
  Evas_Object* scrap_btn = elm_button_add(table);
  elm_object_text_set(scrap_btn, "Scrap!");
  evas_object_show(scrap_btn);

  elm_object_signal_callback_add(scrap_btn, "clicked", "scrap-btn",
				 scrap_cb,NULL);

  
  //  elm_win_resize_object_add(win, box);
  //  evas_object_show(box);
  evas_object_show(win);

  elm_run();
  return 0;
}
ELM_MAIN()
  
