/** \file list.h
  * The header file of a linked list implementation.
  *
  */

#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h> // USES size_t

/** The basic list node mainly used to flatten curl easy WRITEDATA stream
  *
  * This list always contains at least one element : the first value.
  *
  * The values_len member is used to exactly know the full lenght of the
  * flatten list, to avoid a complete unneeded traversal before final
  * concat.
  *
  * This list was primarly created to handle curl_easy response and to be
  * flatten at the end.
  *
  */
typedef struct node_t {
  void*          val;      //!< The current node value (casted to void pointer) 
  struct node_t* next;       //!< The next node
  size_t         values_len; //!< Sum of all values 
} List;

List*  list_create(void*);
void   list_free(List*);

size_t list_len(List*);

void   list_append(List*, void*);
char*  list_flatten(List*);

#endif // !__LIST_H__


