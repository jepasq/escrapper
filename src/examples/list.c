#include "list.h"

#include <stdio.h>

// Created after a endless loop/seghfault in list_flatten

int
main(int atgc, char** argv)
{
  List* lst = list_create("aa");
  list_append(lst, "bb");
  printf("%s\n", list_flatten(lst));
  return 0;
}
