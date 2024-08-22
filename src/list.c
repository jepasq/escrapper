#include "list.h"

#include <stdlib.h> // USES malloc()
#include <assert.h> // USES assert()
#include <string.h> // USES strlen()

#include <stdio.h>


/** Create an empty list with a first NULL-value element
  *
  * \param val The head element value.
  *
  * \return The newly cerate dynamically-allocated list.
  *
  */
List*
list_create(void* val)
{
  assert(val && "List val can't be NULL");
  List* l = malloc(sizeof(List));
  l->val = val;
  l->values_len = strlen((char*)val);
  l->next = NULL;
  return l;
}

/** Free a dynamically-allocated list
  *
  * \param The list.
  *
  */
void
list_free(List* l)
{
  free(l);
}

/** Returns the length of the list in element
  *
  * \param l The list to return the length for.
  *
  * \return The list length in number of elements as size_t.
  *
  */
size_t
list_len(List* l)
{
  if (l == NULL)
    return 0;

  size_t len = 1;
  List* l1 = l;
  while (l1->next)
    {
      len++;
      l1 = l1->next;
    }
    return len;
}

/** Append the given value at the end of the list
  *
  * \param l   The list to append the value to.
  * \param val The value to be added.
  *
  */
void
list_append(List* l, void* val)
{
  List* l1 = l;
  while (l1->next)
    {
      l1 = l->next;
    }
  List* l2 = list_create(val);
  l1->values_len += strlen(val);
  l1->next = l2;
}

/** Flatten the given list and return its char* representation
  *
  * All its element will be joined to a char*.
  *
  * \param l The list to be processed.
  *
  * \return A newly dynamically allocated char array. Must be free() after
  *         usage.
  *
  */
char*
list_flatten(List* l)
{
  printf("> Flattening a list of %d values_len\n", l->values_len);
  
  char* ret = malloc(sizeof(char) * (l->values_len + 1));

  List* l1 = l;
  strcpy(ret, l1->val);
  while (l1->next)
    {
      l1 = l1->next;
      strcat(ret, l1->val);
    }
  return ret;
}
