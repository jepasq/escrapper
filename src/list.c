#include "list.h"

#include <stdlib.h> // USES malloc()
#include <assert.h> // USES assert()

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
  */
size_t
list_len(List* l)
{
  if (l == NULL)
    return 0;

  if (l->next == NULL)
    return 1;
  else
    return 333;
}

