# escrapper 

An EFL-based  web scrapper, indexer and offline viewer.

## Dependencies

	sudo pamac install efl

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
