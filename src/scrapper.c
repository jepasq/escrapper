#include "scrapper.h"

#include <stdlib.h> // USES malloc() and free()

Scrapper* scrapper_create()
{
  Scrapper* s = malloc(sizeof(Scrapper*));
  return s;
}

void scrapper_free(Scrapper* s)
{
  free(s);
}
