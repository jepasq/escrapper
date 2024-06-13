/** \file list.h
  * The header file of a linked list implementation.
  *
  */

#ifndef __LIST_H__
#define __LIST_H__

/** The basic list node
  *
  */
typedef struct node_t {
    void*         val;
    struct node_t * next;
} List;

List* list_create(void);
void  list_free(List*);

#endif // !__LIST_H__


