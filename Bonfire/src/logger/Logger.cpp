#include "../../include/logger/Logger.hpp"

// ========== Public Definitions ==========

Logger::Logger() {
	m_loggerName = "root";
	m_fileName = "log.txt";
	m_filePath = "";
	m_level = INFO_LEVEL;
	m_separator = "";
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&Logger::Listener, this));
}

Logger::Logger(std::string loggerName, std::string fileName, std::string logDir, std::string level, std::string separator, unsigned int delay) {
	m_loggerName = ValidateLoggerName(loggerName);
	m_fileName = ValidateFileName(fileName);
	m_filePath = ValidateFilePath(logDir);
	m_level = TranslateLevel(level);
	m_separator = ValidateSeparator(separator);
	m_delay = delay;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&Logger::Listener, this));
}

Logger::Logger(const Logger&) {

}

Logger::~Logger() {
	// tell the thread to begin cleanup
	m_stopListener = true;
	// end the stored threads
	for (auto& t : m_threads) t.join();
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

void Logger::PushToQueue(std::string level, std::string entry) {
	// build entry before aquiring the lock
	std::string logEntry = ConstructEntry(level, entry);
	m_queueMutex.lock();
	m_queue.push(logEntry);
	m_queueMutex.unlock();
}

std::string Logger::ConstructEntry(std::string level, std::string entry) {
	return level +
		m_separator +
		m_loggerName +
		m_separator +
		GetDateTime() +
		m_separator +
		entry;
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

std::string Logger::ValidateLoggerName(std::string name) {
	if (name.find("\\") != -1)
		throw std::invalid_argument("Logger name cannot have escape characters");
	if (name.find(".") != -1)
		throw std::invalid_argument("Logger name cannot have ");
	if (name.length() == 0)
		throw std::invalid_argument("Logger name cannot be empty");
	return name;
}

std::string Logger::ValidateFileName(std::string name) {
	if (name.find("\\") != -1)
		throw std::invalid_argument("Logger name cannot have escape characters");
	return name;
}

std::string Logger::ValidateFilePath(std::string path) {
	if (path.find(".") != -1)
		throw std::invalid_argument("Logger name cannot have ");
	return path;
}

std::string Logger::ValidateSeparator(std::string separator) {
	if (separator.find("\\") != -1)
		throw std::invalid_argument("Logger name cannot have escape characters");
	if (separator.find(".") != -1)
		throw std::invalid_argument("Logger name cannot have ");
	return separator;
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
	while (true) {
		// sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(m_delay));
		// lock the mutex
		m_queueMutex.lock();
		if (!m_queue.empty()) {
			WriteToFile(m_queue.front());
			m_queue.pop();
		}
		m_queueMutex.unlock();
		// chekc to stop
		if (m_stopListener) {
			// finish writitng the rest of the queue
			m_queueMutex.lock();
			for (unsigned int i = 0; i < m_queue.size(); i++) {
				WriteToFile(m_queue.front());
				m_queue.pop();
			}
			m_queueMutex.unlock();
			std::cout << "Listener is done executing" << std::endl;
			return;
		}
	}
}

void Logger::WriteToFile(std::string entry) {
	std::ofstream logFS;

	//std::cout << entry << std::endl;

	logFS.open(m_filePath + m_fileName, std::ios::app);				//open the file in append mode
	logFS << entry << std::endl;
	logFS.close();

};

