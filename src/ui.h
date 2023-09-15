/** \file ui.h
  * The header file that conatins UI-related functions.
  *
  */

#ifndef __UI_H__
#define __UI_H__

#include <Elementary.h>

Evas_Object* ui_create_win(void);

Evas_Object* ui_get_entry_url(void);
Evas_Object* ui_get_button_scrap(void);
Evas_Object* ui_get_label_status(void);

const char * ui_get_str_url(void);

void ui_set_str_url(const char*);


#endif // !__UI_H__
