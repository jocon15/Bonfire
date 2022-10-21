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

namespace bf{

	/**
	* The PerformanceLogger class is a subclass of the QueueLogger.
	* It uses its parent class to untilize the multithreaded
	* queue-based logging system. PerformanceLogger provides a 
	* standard logging format with limited options. For a more 
	* customized experience, check out CustomLogger.
	*/
	class BONFIRE_API PerformanceLogger : public QueueLogger {
	public:
		/**
		* Default constructor
		*/
		PerformanceLogger();

		/**
		* Constructor
		*
		* @param loggerName the name of the logger
		* @param delay the background thread delay in milliseconds
		*/
		PerformanceLogger(std::string loggerName, unsigned int delay = 1000);

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
		void addFileHandler(std::string filePath, std::string format, std::string level);

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
		inline void debug(std::string message) {
			PushToQueue("DEBUG", message);
		}

		/**
		* Submit a info entry to the logger
		*
		* @param message the message to be logged
		*/
		inline void info(std::string message) {
			PushToQueue("INFO", message);
		}

		/**
		* Submit a warning entry to the logger
		*
		* @param message the message to be logged
		*/
		inline void warning(std::string message) {
			PushToQueue("WARNING", message);
		}

		/**
		* Submit a error entry to the logger
		*
		* @param message the message to be logged
		*/
		inline void error(std::string message) {
			PushToQueue("ERROR", message);
		}

		/**
		* Submit a critical entry to the logger
		*
		* @param message the message to be logged
		*/
		inline void critical(std::string message) {
			PushToQueue("CRITICAL", message);
		}

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
}