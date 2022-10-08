#include "Bonfire.hpp"

int main(int argc, char* argv[]) {

	/* Instantiage a logger object.
	*  Give the logger a name and a delay size in seconds. */
	Logger logger = Logger("bonFireLogger", 1);
	

	/* Add a file handler to the logger */
	logger.addFileHandler("log.txt", "", "%L--%N--%D--%M", "DEBUG");


	/* Add a terminal handler to the logger	*/
	logger.addTerminalHandler("[%L] [&5%N&] [%D] [%M]", "DEBUG");


	/* Log away */
	logger.debug("For debug purposes only1");
	logger.debug("For debug purposes only2");
	logger.info("Hello world1");
	logger.info("Hello world2");
	logger.warning("Uh oh something's wrong!");
	logger.error("There's an error");
	logger.critical("Oh no, I think I might fall1");
	logger.critical("Oh no, I think I might fall2");
}