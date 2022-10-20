#include "../../../include/logger/loggers/PerformanceLogger.hpp"

namespace bf {

	// ========== Public Definitions ==========

	PerformanceLogger::PerformanceLogger() {
		m_loggerName = "root";
		m_delay = DEFAULT_DELAY;

		// start the listener thread and add it to the stored threads
		m_threads.push_back(std::thread(&LogWorker::PerformanceListener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
	}

	PerformanceLogger::PerformanceLogger(std::string loggerName, unsigned int delay) {
		m_loggerName = loggerName;
		m_delay = delay;

		// start the listener thread and add it to the stored threads
		m_threads.push_back(std::thread(&LogWorker::PerformanceListener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
	}

	PerformanceLogger::PerformanceLogger(const PerformanceLogger&) {
		m_loggerName = "root";
		m_delay = DEFAULT_DELAY;

		// start the listener thread and add it to the stored threads
		m_threads.push_back(std::thread(&LogWorker::PerformanceListener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
	}

	PerformanceLogger::~PerformanceLogger() {
		// tell the listener thread to begin cleanup
		m_queueManager.SetSignalStop();

		// end the stored threads
		for (auto& t : m_threads) t.join();
	}

	void PerformanceLogger::addFileHandler(std::string filePath, std::string format, std::string level) {
		std::string validatedFilePath = Validators::ValidateFilePath(filePath);
		std::string validattedFormat = Validators::ValidateFormat(format);
		int intLevel = Translators::TranslateLevel(level);

		// add a file handler to the list
		m_handlerManager.AddHandler(std::shared_ptr<PerformanceHandler>(new FileHandler(
			validatedFilePath, validattedFormat, intLevel)));
	}

	void PerformanceLogger::addTerminalHandler(std::string format, std::string level) {
		std::string validatedFormat = Validators::ValidateFormat(format);
		int intLevel = Translators::TranslateLevel(level);

		// add a terminal handler to the list
		m_handlerManager.AddHandler(std::shared_ptr<PerformanceHandler>(new TerminalHandler(validatedFormat, intLevel)));
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
}