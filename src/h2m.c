#include "h2m.h"

#include "h2m_impl.h"

#include <stdlib.h>  // USES malloc()
#include <string.h>  // USES strlen()
#include <stdio.h>   // USES sprintf()

// You must free the result if result is non-NULL. (from
// https://stackoverflow.com/a/779960)
char* str_replace(const char *orig, char *rep, const char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = (char*) orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

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

/** Replace the named node (open and close tags) with the given text
 *
 *  @return A new aloocated string that *must* be freed.
 *
 *  @param with_o Replace opening tag with with string.
 *  @param with_c Replace closing tag with with string.
 *
 */
char*
h2m_replace_node_c(const char* source, const char* tag,
		 const char* with_o, const char* with_c)
{
  char otag[200], ctag[200];

  sprintf(otag, "<%s>", tag);
  sprintf(ctag, "</%s>", tag);

  char* ret2 = str_replace(source, otag, with_o);
  return str_replace(ret2, ctag, with_c);
}


/** Replace the named node (open and close tags) with the given text
 *
 *  @return A new aloocated string that *must* be freed.
 *
 */
char*
h2m_replace_node(const char* source, const char* tag, const char* with)
{
  return h2m_replace_node_c(source, tag, with, with);
}

/// TODO : to be implemented
char*
html_to_markdown(char* c)
{
  char* tmp;
  char* ret = malloc(strlen(c) + 1);
  
  tmp = h2m_replace_node(c, "bold", "**");
  strcpy(ret, tmp);
  free(tmp);
  
  tmp = h2m_replace_node(ret, "strong", "**");
  strcpy(ret, tmp);
  free(tmp);
  
  tmp = h2m_replace_node(ret, "i", "*");
  strcpy(ret, tmp);
  free(tmp);
  
  tmp = h2m_replace_node(ret, "em", "*");
  strcpy(ret, tmp);
  free(tmp);
  
  return ret;
};
