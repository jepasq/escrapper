/** \file ui.c
  * The implementation of the UI-related functions.
  *
  */

#include "ui.h"

#include "_config.h"  // USES PROJECT_NAME and PROJECT_NUMBER

Evas_Object* url_entry;    //!< The elementary widget used to enter URL 
Evas_Object* status;       //!< The status label
Evas_Object* scrap_btn;    //!< The status label

Evas_Object*
ui_get_entry_url()
{
  return url_entry;
}

Evas_Object*
ui_get_button_scrap()
{
  return scrap_btn;
}

Evas_Object*
ui_get_label_status(void)
{
  return status;
}


/** Create the UI based on a table
  *
  * Once the UI is created, you must call elm_run().
  *
  * \return The window object
  *
  */
Evas_Object*
ui_create_win()
{
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
  
  scrap_btn = elm_button_add(table);
  elm_object_text_set(scrap_btn, "Scrap!");
  evas_object_show(scrap_btn);
  elm_table_pack(table, scrap_btn, 1, 1, 1, 1);

  Evas_Object* icon = elm_icon_add(win);
  elm_icon_standard_set(icon, "edit-find");  // go-next is also good
  elm_object_part_content_set(scrap_btn, "icon", icon);
  
  status = elm_label_add(win);
  evas_object_show(status);
  elm_table_pack(table, status, 0, 2, 1, 1);

  evas_object_resize(win, 800, 600); 
  evas_object_show(win);
}
