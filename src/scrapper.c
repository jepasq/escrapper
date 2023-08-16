#include "scrapper.h"

#include <stdlib.h> // USES malloc() and free()
#include <assert.h> // USES assert()

Scrapper* scrapper_create()
{
  Scrapper* s = malloc(sizeof(Scrapper*));
  s->current_url = "";
  return s;
}

void scrapper_free(Scrapper* s)
{
  free(s);
}

void
scrapper_set_url(Scrapper* s, const char* u)
{
  assert(s && "Is a valid scrapper");
  s->current_url = strdup(u);
}
