# escrapper

An [EFL](https://en.wikipedia.org/wiki/Enlightenment_Foundation_Libraries)-based
web scrapper, indexer and offline viewer.

This is mainly a desktop application where the user can add the 
[URL](https://en.wikipedia.org/wiki/URL) of a website and 
[crawl](https://en.wikipedia.org/wiki/Web_crawler) it.

Once indexed and parsed, the website can then be viewed offline via the
main application UI. The data and its persistance is done using a 
*mongodb* server.

# Starting

It's non-standard for C source code but the main entry function for the 
binary linking is called elm_main().

To learn more on the API, you can start from the Config or the Scrapper 
structs.

Another important part is the _Logger struct and the logger.h header file 
that prevent the output to be printed in unit tests and backup the output 
in a *log file*.

You can also read the file list to know more about the project organisation.

# UI switch

In ui.h is defined a special macro used to chose the *User Interface I* layout
version between *box* and *table*. If you define `UI_USE_BOX` with a value 
greater than 0, you will use **box** version :

	#define UI_USE_BOX 1

# License

`escrapper` is licensed under GPLv3 license. It is free software: you can 
redistribute it and/or modify it under the terms of the 
*GNU General Public License* as published by the **Free Software Foundation**, 
either version 3 of the License, or (at your option) any later version.
