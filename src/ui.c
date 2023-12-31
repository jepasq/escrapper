/** \file ui.c
  * The implementation of the UI-related functions.
  *
  */

#include "ui.h"

#include "_config.h"  // USES PROJECT_NAME and PROJECT_NUMBER

Evas_Object* url_entry;    //!< The elementary widget used to enter URL 
Evas_Object* status;       //!< The status label
Evas_Object* scrap_btn;    //!< The status label


/** Get the entry that should contain the user entered URL
  *
  * \return The evas object entry.
  *
  */
Evas_Object*
ui_get_entry_url()
{
  return url_entry;
}

/** Get the Scrap button
  *
  * Mainly used to setup callback.
  *
  * \return The object you must click to start scrapping.
  *
  */
Evas_Object*
ui_get_button_scrap()
{
  return scrap_btn;
}

/** Get the status label object
  *
  * \return The object, not the text it contains.
  *
  */
Evas_Object*
ui_get_label_status(void)
{
  return status;
}


/** Create the UI based on a table
  *
  * Once the UI is created, you must call elm_run().
  *
  * \return the ui version string
  *
  */
char*
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

  return "table";
}


/** Return the URL from the entry widget
  *
  * \return The contry of the entry as a C string
  *
  */
const char*
ui_get_str_url()
{
  return elm_entry_entry_get(ui_get_entry_url());
}


/** Set the content text of the status label
  *
  * \param str The new status.
  *
  */
void
ui_set_str_status(const char* str)
{
  elm_object_text_set(ui_get_label_status(), str);
}


/** Create and return elm window (box-based version)
  *
  * Mainly tested to fix a bug where the URL entry isn't large enough.
  *
  * \return the ui version string
  *
  */
char*
ui_create_win_box(void)
{
    Evas_Object *win, *background; 

    win = elm_win_add(NULL, "main_window", ELM_WIN_BASIC);
    elm_win_autodel_set(win, EINA_TRUE);
    evas_object_size_hint_min_set(win, 600, 400); 

    char title[50];
    strcpy(title, PROJECT_NAME);
    strcat(title, " ");
    strcat(title, PROJECT_NUMBER);
    elm_win_title_set(win, title);
    
    //    evas_object_smart_callback_add(win, "delete,request", win_del, NULL); 

    //    background = elm_bg_add(win);

    // Background
    /*
    evas_object_size_hint_weight_set(background, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND); 
    //    elm_win_resize_object_add(win, background); 
    evas_object_show(background); 
    */
    
    // Parent box
    Evas_Object* box = elm_box_add(win);

    Evas_Object* box2 = elm_box_add(win);
    //elm_bg_color_set(box2, 125, 250, 250);
    evas_object_show(box2);

    elm_box_horizontal_set(box2, EINA_TRUE);
    Evas_Object* url = elm_entry_add(win);
    evas_object_size_hint_weight_set(url, EVAS_HINT_EXPAND, 0.0);
    elm_bg_color_set(url, 250, 127, 250);
    evas_object_show(url);
    elm_box_pack_end(box2, url);

    // Scrap button
    scrap_btn = elm_button_add(win);
    elm_object_text_set(scrap_btn, "Scrap");
    elm_box_pack_end(box2, scrap_btn);
    evas_object_show(scrap_btn);

    Evas_Object* icon = elm_icon_add(win);
    elm_icon_standard_set(icon, "edit-find");  // go-next is also good
    elm_object_part_content_set(scrap_btn, "icon", icon);

    elm_box_pack_end(box, box2);
    evas_object_show(box);

    // Status label
    status = elm_label_add(win);
    evas_object_show(status);
    elm_box_pack_end(box, status);
    
    evas_object_show(win);
    return "box";
}

