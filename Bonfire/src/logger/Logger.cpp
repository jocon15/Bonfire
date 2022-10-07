#include "../../include/logger/Logger.hpp"

// ========== Public Definitions ==========

Logger::Logger() {
	m_loggerName = "root";
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::Listener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
}

Logger::Logger(std::string loggerName, unsigned int delay) {
	m_loggerName = loggerName;
	m_delay = delay;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::Listener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
}

Logger::Logger(const Logger&) {
	m_loggerName = "root";
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::Listener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
}

Logger::~Logger() {
	// tell the listener thread to begin cleanup
	m_queueManager.SetSignalStop();
	// end the stored threads
	for (auto& t : m_threads) t.join();
}

void Logger::addFileHandler(std::string fileName, std::string logDir, std::string format, std::string level) {
	std::string validatedFileName = Validators::ValidateFileName(fileName);
	std::string validatedLogDir = Validators::ValidateFilePath(logDir);
	std::string validattedFormat = Validators::ValidateFormat(format);
	int intLevel = Translators::TranslateLevel(level);

	// add a file handler to the list
	m_handlerManager.AddHandler(std::shared_ptr<Handler>(new FileHandler(
		validatedFileName, validatedLogDir, validattedFormat, intLevel)));
}

void Logger::addTerminalHandler(std::string format, std::string level) {
	std::string validatedFormat = Validators::ValidateFormat(format);
	int intLevel = Translators::TranslateLevel(level);

	// add a terminal handler to the list
	m_handlerManager.AddHandler(std::shared_ptr<Handler>(new TerminalHandler(validatedFormat, intLevel)));
}

void Logger::debug(std::string message) {
	PushToQueue("DEBUG", message);
}

void Logger::info(std::string message) {
	PushToQueue("INFO", message);
}

void Logger::warning(std::string message) {
	PushToQueue("WARNING", message);
}

void Logger::error(std::string message) {
	PushToQueue("ERROR", message);
}

void Logger::critical(std::string message) {
	PushToQueue("CRITICAL", message);
}

// ========== Private Definitions ==========

void Logger::PushToQueue(std::string level, std::string message) {
	QueueMember member = QueueMember();
	member.loggerName = m_loggerName;
	member.level = level;
	member.datetime = GetDateTime();
	member.message = message;

	m_queueManager.Push(member);
}

std::string Logger::GetDateTime() {
	std::string dateTime;
	time_t t;														//t passed as argument in function time()
	struct tm* tt;													//declaring variable for localtime()
	time(&t);														//passing argument to time()
	tt = localtime(&t);
	dateTime = asctime(tt);
	dateTime.erase(remove(dateTime.begin(),
		dateTime.end(), '\n'), dateTime.end());
	return dateTime;
}
