/** \file main.c
  * The main entry function implementation file.
  *
  */
    
#include <Elementary.h>

#include "config.h"

Evas_Object* layout;

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
  Evas_Object* url_entry = evas_object_name_child_find(layout, "scrap-url", 8);
  if (url_entry)
    {
      const char* txt = elm_entry_entry_get(url_entry);
      printf("Text changed : %s !\n", txt);
    }
  else
    printf("Cannot get 'scrap-url' object\n");
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
input_cb(void *data, Evas_Object *obj, const char *emission,
	   const char *source)
{
  Edje_Entry_Change_Info* info = data;
  if (info)
    {
      //      const char* ce = elm_entry_entry_get(obj);
      // see https://docs.enlightenment.org/auto/struct__Edje__Entry__Change__Info.html
      printf("Evas obj. : %s !\n", info->insert);

     
    }
  else
      printf("Can't get Edje_Entry_Change_Info struct\n");
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
  
  Evas_Object *win;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  
  win = elm_win_util_standard_add("Main", "Hello, World!");
  elm_win_autodel_set(win, EINA_TRUE);

  layout = elm_layout_add(win);
  evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND); 
  elm_layout_file_set(layout, "main.edj", "escrapper");

  elm_layout_signal_callback_add(layout, "clicked", "scrap-btn",scrap_cb,NULL);
  elm_layout_signal_callback_add(layout, "changed,user", "scrap-url",
				 input_cb,NULL);
  
  // Commented out, too verbose
  //  elm_layout_signal_callback_add(layout, "*", "*", _signal_cb, NULL);

  elm_win_resize_object_add(win, layout);
  evas_object_show(layout);
  evas_object_show(win);
  
  elm_run();
  return 0;
}
ELM_MAIN()
  
