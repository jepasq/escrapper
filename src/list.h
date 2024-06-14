/** \file list.h
  * The header file of a linked list implementation.
  *
  */

#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h> // USES size_t

/** The basic list node
  *
  * This list always contains at least one element.
  *
  */
typedef struct node_t {
    void*         val;
    struct node_t * next;
} List;

List* list_create(void*);
void  list_free(List*);

size_t  list_len(List*);


#endif // !__LIST_H__


