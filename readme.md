# Bonfire

## Overview
Bonfire is a lighweight threaded logger written in C\++ and designed for C\++. Single threaded logic would require a logger to open and close the file every time the logger needed to write an entry to the file. This is a tremendous amount of overhead that could be delegated to a different thread. Bonfire is designed to do exactly that, offload most of the overhead of file operations to a different thread.

## QuickStart
To start using the logger:
1. Inlclude the header
2. Instantiate a Logger object
3. Log away!




```
#include "Bonfire.hpp"

int main(int argc, char* argv[]) {
	/* Instantiage a logger object */
	Logger logger = Logger("bonFireLogger", 1);

	/ *Add a file handler to the logger */
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
```
### Example Terminal Output
![img](https://github.com/jocon15/Bonfire/blob/master/docs/images/terminal_example.png?raw=true)

### Example File Output
![img](https://github.com/jocon15/Bonfire/blob/master/docs/images/file_example.png?raw=true)

## A Queue Between Two Threads
The Logger class has a queue to mediate between the two threads. When the main thread logs a message ex: `log.info("task complete!");`, the message is added to the queue. When you instantiated the logger object, a background listener thread was started that periodically checks the queue for any data to write. If there is data present, the listener thread write the data to the designate log file. This relieves the burden of file interactions from the main thread.

When the Logger destructor is called, the listener thread finishes writing the remaining data in the queue to the file. Then joins the main thread.

## Log Levels
The log levels follow the log levels defined in Python.

| Level  |
|--------|
|DEBUG   |
|INFO    |
|WARNING |
|ERROR   |
|CRITICAL|

## Handlers