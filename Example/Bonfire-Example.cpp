#include "Bonfire.hpp"

int main(int argc, char* argv[]) {
	

	/*
	* Instantiage a logger object.
	* 
	* Give the logger a name and a delay size in seconds.
	*/
	Logger logger = Logger("bonFireLogger", 1);
	

	/*
	* Add a file handler to the logger.
	*/
	logger.addFileHandler("log.txt", "", "%L--%N--%D--%M", "INFO");


	/*
	* Add a terminal handler to the logger
	*/
	logger.addTerminalHandler("[%L] [&5%N&] [%D] [%M]", "INFO");


	/*
	* Log away
	*/
	logger.info("Hello world");

	logger.debug("For debug purposes only");

	logger.warning("Uh oh something's wrong!");

	logger.error("There's an error");

	logger.info("vhwrgwhrgi");
	logger.critical("Oh no, I think I might fall");
}