#pragma once

#include "../../util/Util.hpp"
#include "../QueueLogger.hpp"
#include "../../Core.hpp"
#include "../../handler/PerformanceHandler.hpp"
#include "../../handler/handlers/PerformanceFileHandler.hpp"
#include "../../handler/handlers/PerformanceTerminalHandler.hpp"

/* 
* Directives for each of the individual log 
* levels. These levels follow the conventional
* Python log levels defined here:
* https://docs.python.org/3/library/logging.html
*/
#define CRITICAL_LEVEL 50
#define ERROR_LEVEL    40
#define WARNING_LEVEL  30
#define INFO_LEVEL     20
#define DEBUG_LEVEL    10
#define NOTSET_LEVEL   0	

/**
* This class handles the entire logging implementation for the
* threaded logger. The simple setup and interactions through the
* public functions allow for a hassle free experience while having
* all of the annoying multithreading details abstracted away.
* Simply intantiate and log away.
* This class uses a queue to act as a log entry buffer. The main
* thread adds entries to the queue while the listener removes entries.
* This allows the main thread to perform tasks independent of the
* overhead of writing to a file every time theres a log message.
* The client should add handlers to define how and where the entries
* should be logged.
*/
class BONFIRE_API PerformanceLogger: public QueueLogger {
public:
	/**
	* Default constructor
	*/
	PerformanceLogger();

	/**
	* Constructor
	*
	* @param loggerName the name of the logger
	* @param delay the listener thread delay time between queue checks
	*/
	PerformanceLogger(std::string loggerName, unsigned int delay = 1);

	/**
	* Copy constructor
	*/
	PerformanceLogger(const PerformanceLogger&);

	/**
	* Destructor
	*/
	~PerformanceLogger();

	/**
	* Add a file handler
	*
	* @param fileName the name of the log file
	* @param logDir the path that the fileName file exists in (not including the fileName)
	* @param level the logging level
	*/
	void addFileHandler(std::string fileName, std::string logDir, std::string format, std::string level);

	/**
	* Add a terminal handler
	*
	* @param message the logging level
	*/
	void addTerminalHandler(std::string format, std::string level);

	/**
	* Submit a debug entry to the logger
	*
	* @param message the message to be logged
	*/
	void debug(std::string message);

	/**
	* Submit a info entry to the logger
	*
	* @param message the message to be logged
	*/
	void info(std::string message);

	/**
	* Submit a warning entry to the logger
	*
	* @param message the message to be logged
	*/
	void warning(std::string message);

	/**
	* Submit a error entry to the logger
	*
	* @param message the message to be logged
	*/
	void error(std::string message);

	/**
	* Submit a critical entry to the logger
	*
	* @param message the message to be logged
	*/
	void critical(std::string message);

private:
	HandlerManager m_handlerManager = HandlerManager();
	std::string m_loggerName;

	/**
	* Push a message onto the queue
	*
	* @param level the logging level of the entry
	* @param message the message to log
	*/
	void PushToQueue(std::string level, std::string message);
};
