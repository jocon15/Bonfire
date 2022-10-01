#include "../../include/logger/Logger.hpp"

// ========== Public Definitions ==========

Logger::Logger() {
	m_loggerName = "root";
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&Logger::Listener, this));
}

Logger::Logger(std::string loggerName, unsigned int delay) {
	m_loggerName = loggerName;
	m_delay = delay;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&Logger::Listener, this));
}

Logger::Logger(const Logger&) {

}

Logger::~Logger() {
	// tell the listener thread to begin cleanup
	m_stopListener = true;
	// end the stored threads
	for (auto& t : m_threads) t.join();
}

void Logger::addFileHandler(std::string fileName, std::string logDir, std::string format, std::string level){
	std::string validatedFileName = Validators::ValidateFileName(fileName);
	std::string validatedLogDir = Validators::ValidateFilePath(logDir);
	std::string validattedFormat = Validators::ValidateFormat(format);
	int intLevel = TranslateLevel(level);

	// add a file handler to the list
	m_handlers.push_back(std::unique_ptr<Handler>(new FileHandler(
		validatedFileName, validatedLogDir, validattedFormat, intLevel)));
}

void Logger::addTerminalHandler(std::string format, std::string level){
	std::string validatedFormat = Validators::ValidateFormat(format);
	int intLevel = TranslateLevel(level);

	// add a terminal handler to the list
	m_handlers.push_back(std::unique_ptr<Handler>(new TerminalHandler(validatedFormat, intLevel)));
}

void Logger::debug(std::string entry) {
	if (m_level < DEBUG_LEVEL)
		return;
	PushToQueue("DEBUG", entry);
}

void Logger::info(std::string entry) {
	if (m_level < INFO_LEVEL)
		return;
	PushToQueue("INFO", entry);
}

void Logger::warning(std::string entry) {
	if (m_level < WARNING_LEVEL)
		return;
	PushToQueue("WARNING", entry);
}

void Logger::error(std::string entry) {
	if (m_level < ERROR_LEVEL)
		return;
	PushToQueue("ERROR", entry);
}

void Logger::critical(std::string entry) {
	if (m_level < CRITICAL_LEVEL)
		return;
	PushToQueue("CRITICAL", entry);
}

// ========== Private Definitions ==========

void Logger::PushToQueue(std::string level, std::string message) {
	// build entry before aquiring the lock
	// std::string logEntry = ConstructEntry(level, message);

	QueueMember member = QueueMember();
	member.loggerName = m_loggerName;
	member.level = level;
	member.datetime = GetDateTime();
	member.message = message;

	m_queueMutex.lock();
	m_queue.push(member);
	m_queueMutex.unlock();
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

int Logger::TranslateLevel(std::string level) {
	if (level == "debug" || level == "DEBUG")
		return DEBUG_LEVEL;
	else if (level == "info" || level == "INFO")
		return INFO_LEVEL;
	else if (level == "warning" || level == "WARNING")
		return WARNING_LEVEL;
	else if (level == "error" || level == "ERROR")
		return ERROR_LEVEL;
	else
		return CRITICAL_LEVEL;
}

void Logger::Listener() {

	std::cout << "Listener thread started" << std::endl;

	while (true) {
		// sleep for m_delay seconds
		
		std::this_thread::sleep_for(std::chrono::seconds(m_delay));

		m_queueMutex.lock();
		if (!m_queue.empty()) {
			OutputHandlers(m_queue.front());
			m_queue.pop();
		}
		m_queueMutex.unlock();
		// check to stop (start cleanup)
		if (m_stopListener) {
			// finish logging the rest of the entries in the queue
			m_queueMutex.lock();
			for (unsigned int i = 0; i < m_queue.size(); i++) {
				OutputHandlers(m_queue.front());
				m_queue.pop();
			}
			m_queueMutex.unlock();
			return;
		}
	}
}

void Logger::OutputHandlers(QueueMember member) {
	// loop through all the handlers and tell them to 
	// perform their implementation of Output
	for (unsigned int i = 0; i < m_handlers.size(); i++) {
		m_handlers.at(i)->Output(member);
	}
}
