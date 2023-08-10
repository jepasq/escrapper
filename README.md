# escrapper 

An *EFL*-based web scrapper, indexer and offline viewer.

## Dependencies

On `manjaro` and other *Arch*-based linux distributions :

	sudo pamac install efl cmake gcc doxygen

## Build

This project uses `cmake` :

	mkdir build
	cd build/
	cmake ..
	make

Eventually :

	make check
	
then, from the *build*/ directory :
	
	./escrapper

## API documentation

From the `build/` directory, after the cmake call :

	doxygen
	<your-favorite-browser> html/index.html
