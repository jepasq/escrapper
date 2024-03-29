#ifndef __ESCRAPPER_CONSTANTS_H__
#define __ESCRAPPER_CONSTANTS_H__

/** \file constants.h
  * A macros-based consstant list. Mainly created for exit statuses.
  *
  */

// Exit statuses

// Define some exit status related to error with mongodb server
#define EXIT_NO_MONGO_SERVER  1 //!< Can't find MongoDB server
#define EXIT_MONGO_SERVER_API 2 //!< Can't create server API preferences struct
#define EXIT_INVALID_URL      3 //!< URL is invalid

#endif // !__ESCRAPPER_CONSTANTS_H__
