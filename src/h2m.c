#include "h2m.h"

#include "h2m_impl.h"

#include <stdlib.h>  // USES malloc()
#include <string.h>  // USES strlen()

/** Replace all newline char (EOL) with a space
 *
 * @param s The char to be copied.
 *
 * @return A dynamically allocated string that must be freed.
 *
 */
char*
h2m_remove_newlines(const char* s)
{

  int l = strlen(s);
  char* ret = (char*) malloc( l + 1);
  for (int i = 0; i < l; ++i)
    {
      char c = s[i];
      ret[i] = (c == '\n') ? ' ' : c;
    }
  ret[l] = '\0';
  return ret;
}

bool
h2m_node_remaining(const char*)
{

}

char*
h2m_remove_node(const char*, const char*, const char*)
{

}


/// TODO : to be implemented
char*
html_to_markdown(char* c)
{
  return c;

};
