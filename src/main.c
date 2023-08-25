/** \file main.c
  * The main entry function implementation file.
  *
  */
    
#include <Elementary.h>

#include "config.h"

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
   printf("Scrap buttion has been pressed!\n");
}

static void
input_cb(void *data, Evas_Object *obj, const char *emission,
	   const char *source)
{
  printf("Text changed : %s!\n", (char*)data);
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
  
  Evas_Object *win, *layout;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  
  win = elm_win_util_standard_add("Main", "Hello, World!");
  elm_win_autodel_set(win, EINA_TRUE);

  layout = elm_layout_add(win);
  elm_layout_file_set(layout, "main.edj", "escrapper");

  elm_layout_signal_callback_add(layout, "clicked", "scrap-btn",scrap_cb,NULL);
  elm_layout_signal_callback_add(layout, "changed", "scrap-url",input_cb,NULL);
  
  
  // Commented out, too verbose
  //  elm_layout_signal_callback_add(layout, "*", "*", _signal_cb, NULL);


  elm_win_resize_object_add(win, layout);
  evas_object_show(layout);
  evas_object_show(win);
  
  elm_run();
  return 0;
}
ELM_MAIN()
  
