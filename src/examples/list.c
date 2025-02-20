#include "list.h"

#include <stdio.h>    // USES printf()
#include <stdbool.h>  // USES bool
#include <string.h>   // USES strcmp()

// Created after a endless loop/segfault in list_flatten

// Forward declarations
void print_len(List*, bool);
// End of forward declarations

/// Return true if the given array contains a help-related command line flag
bool
has_help(char** argv)
{
  char* s = argv[1];
  if (strcmp(s, "-?") ==0 ||
      strcmp(s, "-h") ==0 ||
      strcmp(s, "--help") ==0)
    return true;

  return false;
}

/// Always return 0 (success status code)
int
usage(char* progname)
{
  printf("Some test around the List type implementation\n");

  printf("\nUsage :\n");
  printf("  %s [-?|-h|-help] : shows this message and ", progname);
  printf("exit with success status.\n");

}

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
  if (argc > 1 && has_help(argv))
      return usage(argv[0]);

  
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
  * @param now Should we add the 'now' word.
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

