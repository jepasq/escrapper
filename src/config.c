#include <stdlib.h> // USES malloc() and free()

#include "config.h"



Config*
config_create()
{
  return malloc(sizeof(Config));
}

void
config_free(Config* c)
{
  free(c);
}
