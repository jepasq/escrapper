#include "h2m_impl.h"

#include <stdio.h> // USES printf()
#include <stdbool.h>  // USES bool

// Created after a endless segfault in h2m_remove_newlines

/** HTML to Markdown example main entry
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
  const char* t1 = "Text with \n Newline\n";
  char*       t2 = h2m_remove_newlines(t1);
  
  printf("t1 : %s\ny2 : %s", t1, t2);
  return 0;
}

