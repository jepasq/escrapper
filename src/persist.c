/** \file persist.h
  * The persistence-related functions implementation.
  *
  */

#include "persist.h"

#include <stdlib.h> // USES malloc() and free()

/** Create and return a malloc'ed Persist struct
  *
  * \return a dynamically allocated object that should free with a call to
  *         persist_free().
  *
  */
Persist*
persist_create()
{
  Persist* p = malloc(sizeof(Persist*));
  return p;
}

/** Free the memory used by the given struct
  *
  * \param p The struct pointer to be free.
  *
  */
void
persist_free(Persist* p)
{
  free(p);
}
