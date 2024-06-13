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
