# escrapper 

An *EFL*-based web scrapper, indexer and offline viewer.

## Dependencies

On `manjaro` and other *Arch*-based linux distributions :

	sudo pamac install efl cmake gcc doxygen check pcre2 mongo-c-driver

On debian-based distributions, such as ubuntu :

	sudo apt-get install libefl-all-dev libcurl4-gnutls-dev check

`check` is only needed if you want to build and run unit tests.

## Build

This project uses `cmake` :

	mkdir build
	cd build/
	cmake ..
	make

then, from the *build*/ directory :
	
	./escrapper

Eventually, to run unit tests :

	./escrapper-tests
	
## API documentation

From the `build/` directory, after the cmake call :

	doxygen
	<your-favorite-browser> html/index.html

## Ext directory

The `edje-mode.el` file is used as emacs major mode to edit edje files you
can find in **ui** directory. To install it, copy or link it in your
*.emacs.d* directory.

It was initially found at https://www.emacswiki.org/emacs/edje-mode.el

```elisp
(add-to-list 'load-path (concat user-emacs-directory "edje-mode/" ))
(load "edje-mode")
(add-to-list 'auto-mode-alist '("\\.edc\\'" . edje-mode))
```

## Configuration

The `escrapper` binary will try to open etxt files in `~/.escrapper/`
directory 

* mongo_uri : The URI without the protocol. Often the IP and the dbname (i.e
  **127.0.0.1/dbname**).
* mongo_user : The mongodb user name.
* mongo_pwd : The user password saved as a clear non-obfsucated string.

## systemd relationship

Actually, a *systemd* command is used to test if the **mongodb** daemon is 
running. It may fail if your distribution uses an alternative. This solution
is implemented in the `persist_mongo_is_running()` function.
