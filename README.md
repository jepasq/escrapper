# escrapper 

An *EFL*-based web scrapper, indexer and offline viewer.

## Dependencies

On `manjaro` and other *Arch*-based linux distributions :

	sudo pamac install efl cmake gcc doxygen check

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
