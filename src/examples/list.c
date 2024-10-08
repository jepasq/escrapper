#include "list.h"

#include <stdio.h> // USES printf()
#include <stdbool.h>  // USES bool

// Created after a endless loop/seghfault in list_flatten

// Forward declarations
void print_len(List*, bool);
// End of forward declarations

/** List example main entry
  *
  * @param argc Unused. The number of command line arguments.
  * @param argv Unused. The array of command line arguments.
  *
  * @return Always 0. Success.
  *
  */
int
main(int argc, char** argv)
{
  List* lst = list_create("aa");
  print_len(lst, false);
  
  list_append(lst, "bb");
  print_len(lst, true);

  printf("Flatten result : %s\n", list_flatten(lst));
  return 0;
}

/** Print the lenght in elements of the given list to stdout
  *
  * @param lst The list to print print.
  * @param now Shouls we add the 'now' word.
  *
  */
void
print_len(List* l, bool now)
{
  printf("- List length is ");
  
  if (now)
    printf("now ");
  
  printf("%d elements.\n", list_len(l));
}

