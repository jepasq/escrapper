#include "list.h"

#include <stdio.h>

// Created after a endless loop/seghfault in list_flatten

int
main(int atgc, char** argv)
{
  List* lst = list_create("aa");
  printf("- List len is %d elem.\n", list_len(lst));
  
  list_append(lst, "bb");
  printf("- List len is %d elem.\n", list_len(lst));

  printf("Flatten result : %s\n", list_flatten(lst));
  return 0;
}
