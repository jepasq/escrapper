/** \file main.c
  * The main entry function implementation file.
  *
  */
    
#include <Elementary.h>
     
static void
on_click(void *data, Evas_Object *obj, void *event_info)
{
  evas_object_del(data);
}

static void
_signal_cb(void *data, Evas_Object *obj, const char *emission,
	   const char *source)
{
   printf("Info received from layout : %s %s\n", emission, source);
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
  Evas_Object *win, *layout;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  
  win = elm_win_util_standard_add("Main", "Hello, World!");
  elm_win_autodel_set(win, EINA_TRUE);

  layout = elm_layout_add(win);
  elm_layout_file_set(layout, "main.edj", "escrapper");

  // Commented out, too verbose
  //  elm_layout_signal_callback_add(layout, "*", "*", _signal_cb, NULL);

  elm_win_resize_object_add(win, layout);
  evas_object_show(layout);
  evas_object_show(win);
  
  elm_run();
  return 0;
}
ELM_MAIN()
  
