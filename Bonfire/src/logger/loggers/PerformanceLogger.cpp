#include "../../../include/logger/loggers/PerformanceLogger.hpp"

// ========== Public Definitions ==========

PerformanceLogger::PerformanceLogger() {
	m_loggerName = "root";
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::Listener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
}

PerformanceLogger::PerformanceLogger(std::string loggerName, unsigned int delay) {
	m_loggerName = loggerName;
	m_delay = delay;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::Listener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
}

PerformanceLogger::PerformanceLogger(const PerformanceLogger&) {
	m_loggerName = "root";
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::Listener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
}

PerformanceLogger::~PerformanceLogger() {
	// tell the listener thread to begin cleanup
	m_queueManager.SetSignalStop();

	// end the stored threads
	for (auto& t : m_threads) t.join();
}

void PerformanceLogger::addFileHandler(std::string fileName, std::string logDir, std::string format, std::string level) {
	std::string validatedFileName = Validators::ValidateFileName(fileName);
	std::string validatedLogDir = Validators::ValidateFilePath(logDir);
	std::string validattedFormat = Validators::ValidateFormat(format);
	int intLevel = Translators::TranslateLevel(level);

	// add a file handler to the list
	m_handlerManager.AddHandler(std::shared_ptr<Handler>(new FileHandler(
		validatedFileName, validatedLogDir, validattedFormat, intLevel)));
}

void PerformanceLogger::addTerminalHandler(std::string format, std::string level) {
	std::string validatedFormat = Validators::ValidateFormat(format);
	int intLevel = Translators::TranslateLevel(level);

	// add a terminal handler to the list
	m_handlerManager.AddHandler(std::shared_ptr<Handler>(new TerminalHandler(validatedFormat, intLevel)));
}

void PerformanceLogger::debug(std::string message) {
	PushToQueue("DEBUG", message);
}

void PerformanceLogger::info(std::string message) {
	PushToQueue("INFO", message);
}

void PerformanceLogger::warning(std::string message) {
	PushToQueue("WARNING", message);
}

void PerformanceLogger::error(std::string message) {
	PushToQueue("ERROR", message);
}

void PerformanceLogger::critical(std::string message) {
	PushToQueue("CRITICAL", message);
}

// ========== Private Definitions ==========

void PerformanceLogger::PushToQueue(std::string level, std::string message) {
	QueueMember member = QueueMember();
	member.loggerName = m_loggerName;
	member.level = level;
	member.datetime = GetDateTime();
	member.message = message;

	m_queueManager.Push(member);
}