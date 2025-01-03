#ifndef __HTML_TO_MARKDOWN_IMPL_H_
#define __HTML_TO_MARKDOWN_IMPL_H_

/* This header is private and it shouldn't be used by end user
 * It is mainly used to unit test for private functions.
 *
 * These functions are implement in the h2m.c file.
 *
 */


/** Replace all the newline characters with a space
 *
 */
char* h2m_remove_newlines(const char*);

/** Does the given node still contain a open/close pair
 *
 */
bool h2m_node_remaining(const char*);

/** Remove the named node (open and close tags)
 *
 */
char* h2m_remove_node(const char*, const char*, const char*);

#endif // !__HTML_TO_MARKDOWN_IMPL_H_
