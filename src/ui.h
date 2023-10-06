/** \file ui.h
  * The header file that contains UI-related functions.
  *
  */

#ifndef __UI_H__
#define __UI_H__

#include <Elementary.h>

/// If not 0, will use a box layout instead of a table
#define UI_USE_BOX 0 // 1

char* ui_create_win(void);
char* ui_create_win_box(void);

Evas_Object* ui_get_entry_url(void);
Evas_Object* ui_get_button_scrap(void);
Evas_Object* ui_get_label_status(void);

const char * ui_get_str_url(void);

void ui_set_str_status(const char*);


#endif // !__UI_H__
