#include "../../../include/logger/loggers/CustomLogger.hpp"

// ========== Public Definitions ==========

//CustomLogger::CustomLogger() {
//	m_delay = DEFAULT_DELAY;
//
//	// start the listener thread and add it to the stored threads
//	m_threads.push_back(std::thread(&LogWorker::CustomListener, std::ref(m_queueManager), std::ref(m_terminalHandler), std::ref(m_fileHandler), m_delay));
//}

CustomLogger::CustomLogger(unsigned int delay) {
	m_delay = delay;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::CustomListener, std::ref(m_queueManager), std::ref(m_terminalHandler), std::ref(m_fileHandler), m_delay));
}

CustomLogger::CustomLogger(const CustomLogger&) {
	m_delay = DEFAULT_DELAY;

	// start the listener thread and add it to the stored threads
	m_threads.push_back(std::thread(&LogWorker::CustomListener, std::ref(m_queueManager), std::ref(m_terminalHandler), std::ref(m_fileHandler), m_delay));
}

CustomLogger::~CustomLogger() {
	// tell the listener thread to begin cleanup
	m_queueManager.SetSignalStop();

	// end the stored threads
	for (auto& t : m_threads) t.join();
}

void CustomLogger::ToFile(std::string filePath, std::string entry) {
	m_fileHandler.UpdateFilePath(filePath);
	PushToQueue("file", entry);
}

void CustomLogger::ToTerminal(std::string entry) {
	PushToQueue("terminal", entry);
}

// ========== Protected Definitions ==========

void CustomLogger::PushToQueue(std::string type, std::string entry) {
	QueueMember member = QueueMember();
	member.type = type;
	member.message = entry;

	m_queueManager.Push(member);
}

//std::string CustomLogger::GetDateTime() {
//	std::string dateTime;
//	time_t t;                                    //t passed as argument in function time()
//	struct tm* tt;                               //declaring variable for localtime()
//	time(&t);                                    //passing argument to time()
//	tt = localtime(&t);
//	dateTime = asctime(tt);
//	dateTime.erase(remove(dateTime.begin(),
//		dateTime.end(), '\n'), dateTime.end());
//	return dateTime;
//}