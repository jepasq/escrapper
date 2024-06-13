#include "list.h"

#include <stdlib.h> // USES malloc()

List*
list_create(void)
{
  List* l = malloc(sizeof(List));
  return l;
}

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

  if (l->val == NULL)
    return 0;
  else
    return 1;
}

