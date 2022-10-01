#pragma once

//#include "../handler/Handler.hpp"
#include "../core.hpp"
#include "../queue_member/queue_member.hpp"
#include "../handler/Handler.hpp"
#include "../handler/handlers/FileHandler.hpp"
#include "../handler/handlers/TerminalHandler.hpp"

// definitions for logging levels

#define CRITICAL_LEVEL 40
#define CRITICAL_LEVEL 40
#define ERROR_LEVEL    30
#define WARNING_LEVEL  20
#define INFO_LEVEL     10
#define DEBUG_LEVEL    0

// delay to use for the background thread

#define DEFAULT_DELAY 1

/**
* This class handles the entire logging implementation for the
* threaded logger. The simple setup and interactions through the
* public functions allow for a hassle free experience while having
* all of the annoying multithreading details abstracted away.
* Simply intantiate and log away.
* This class uses a queue to acts as a log entry buffer. The main
* thread adds entries to the queue while the listener removes entries.
* This allows the main thread to perform tasks independent of the
* overhead of writing to a file every time theres a log message.
*/
class BONFIRE_API Logger {
public:
	/**
	* Default constructor
	*/
	Logger();

	/**
	* Constructor
	*
	* @param loggerName the name of the logger
	* @param fileName the name of the file the logger writes to
	* @param logDir the path that the fileName file exists in (not including the fileName)
	* @param level the logging level
	* @param separaor the delimitor character(s) in the log entries
	* @param delay the listener thread delay time between queue checks
	*/
	Logger(std::string loggerName, std::string fileName = "log.txt", std::string logDir = "", std::string level = "INFO", std::string separator = "::", unsigned int delay = 1);

	/**
	* Copy constructor
	*/
	Logger(const Logger&);

	/**
	* Destructor
	*/
	~Logger();

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
	* @param level the logging level
	*/
	void addTerminalHandler(std::string format, std::string level);

	/**
	* Submit a debug entry to the logger
	*
	* @param entry the message to be logged
	*/
	void debug(std::string entry);

	/**
	* Submit a info entry to the logger
	*
	* @param entry the message to be logged
	*/
	void info(std::string entry);

	/**
	* Submit a warning entry to the logger
	*
	* @param entry the message to be logged
	*/
	void warning(std::string entry);

	/**
	* Submit a error entry to the logger
	*
	* @param entry the message to be logged
	*/
	void error(std::string entry);

	/**
	* Submit a critical entry to the logger
	*
	* @param entry the message to be logged
	*/
	void critical(std::string entry);

private:
	std::string m_separator; // needs to be validated if user inputs
	std::string m_loggerName;
	std::string m_fileName;
	std::string m_filePath;
	unsigned int m_delay; // delay in seconds
	int m_level = INFO_LEVEL;


	std::atomic_bool m_stopListener = false;
	std::mutex m_queueMutex;
	std::queue<QueueMember> m_queue;
	std::vector<std::thread> m_threads;
	std::vector<std::unique_ptr<Handler>> m_handlers;

	/**
	* Push a message onto the queue
	*
	* @param level the logging level of the entry
	* @param message the message to log
	*/
	void PushToQueue(std::string level, std::string message);

	/**
	* Get the current local date and time
	*
	* @return the date and time in format "D M d h:m:s Y"
	*/
	std::string GetDateTime();

	/**
	* Validate the passed in logger name
	*
	* @param name the logger name input via the constructor
	*
	* @return the validated name
	*/
	std::string ValidateLoggerName(std::string name);

	/**
	* Validate the passed in file name
	*
	* @param name the file name input via the constructor
	*
	* @return the validated name
	*/
	std::string ValidateFileName(std::string name);

	/**
	* Validate the passed in file path
	*
	* @param path the file pah input via the constructor
	*
	* @return the validated path
	*/
	std::string ValidateFilePath(std::string path);

	/**
	* Validate the passed in separator
	*
	* @param separator the separator input via the constructor
	*
	* @return the validated separator
	*/
	std::string ValidateSeparator(std::string separator);

	/**
	* Translate the string level into an integer value
	*
	* @param level the string level
	*
	* @return the coresponding integer level of the value
	*/
	int TranslateLevel(std::string level);

	/**
	* Listener thread logic. This thread periodically checks the queue for entries to write to the file system.
	*/
	void Listener();

	/**
	* Writing to file logic
	*/
	void OutputHandlers(QueueMember member);
};
