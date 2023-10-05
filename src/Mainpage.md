# escrapper

An [EFL](https://en.wikipedia.org/wiki/Enlightenment_Foundation_Libraries)-based
web scrapper, indexer and offline viewer.

# Starting

Its non-standard for C source code, the main entry is called elm_main().

To learn more on the API, you can start from the Config or the Scrapper 
structs.

Another important part is the _Logger struct and the logger.h header file 
that prevent the output to be printed in unit tests and backup the output 
in a *log file*.

You can also read the file list to know more about the project organisation.

# UI switch

In ui.h is defined a special macro used to chose the UI version between
*box* and *table*. If you define `UI_USE_BOX` with a value greater than 0,
you will use **box** version :

	#define UI_USE_BOX 1

# License

`escrapper` is licensed under GPLv3 license.
