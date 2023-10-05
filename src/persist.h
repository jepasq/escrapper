/** \file persist.h
  * The header of the persistence functions.
  *
  */

#ifndef __PERSIST_H__
#define __PERSIST_H__

/** The struct used in persistence work
  *
  */
typedef struct {
  
} Persist;

Persist* persist_create();
void     persist_free(Persist*);


#endif // __PERSIST_H__
