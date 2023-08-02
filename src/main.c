#include <Elementary.h>
     
static void
on_click(void *data, Evas_Object *obj, void *event_info)
{
  evas_object_del(data);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
  Evas_Object *win, *btn;
  
  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
  
  win = elm_win_util_standard_add("Main", "Hello, World!");
  elm_win_autodel_set(win, EINA_TRUE);
  
  btn = elm_button_add(win);
  elm_object_text_set(btn, "Goodbye Cruel World");
  elm_win_resize_object_add(win, btn);
  evas_object_smart_callback_add(btn, "clicked", on_click, win);
  evas_object_show(btn);
  
  evas_object_show(win);
  
  elm_run();
  
  return 0;
}
ELM_MAIN()
  
