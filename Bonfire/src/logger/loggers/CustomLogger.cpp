#include "../../../include/logger/loggers/CustomLogger.hpp"

// ========== Public Definitions ==========

CustomLogger::CustomLogger() {
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::Listener, std::ref(m_queueManager), std::ref(m_handlerManager), m_delay));
}

CustomLogger::CustomLogger(unsigned int delay) {

}

CustomLogger::CustomLogger(const CustomLogger&) {

}

CustomLogger::~CustomLogger() {

}

// ========== Private Definitions ==========

