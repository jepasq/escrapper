/** @file h2m_impl.h
 *  This header is private and it shouldn't be used by end user
 *  It is mainly used to unit test for private functions.
 *
 *  These functions are implemented in the h2m.c file.
 *
 */

#ifndef __HTML_TO_MARKDOWN_IMPL_H_
#define __HTML_TO_MARKDOWN_IMPL_H_

#include <stdlib.h>  // You will need free()
#include <stdbool.h> // USES bool type

/** Replace all the newline characters with a space
 *
 */
char* h2m_remove_newlines(const char*);

/** Does the given node still contain a open/close pair
 *
 */
bool h2m_node_remaining(const char*);

char* h2m_replace_node_c(const char*, const char*, const char*, const char*);
char* h2m_replace_node(const char*, const char*, const char*);

#endif // !__HTML_TO_MARKDOWN_IMPL_H_
