#pragma once

#include "../QueueLogger.hpp"
#include "../../Core.hpp"

class BONFIRE_API CustomLogger: public QueueLogger {
public:
	//CustomLogger();

	CustomLogger(unsigned int delay = 1);

	CustomLogger(const CustomLogger&);

	~CustomLogger();

	void ToFile(std::string filePath, std::string entry);

	void ToTerminal(std::string entry);

private:
	//debug
	/*QueueManager m_queueManager = QueueManager();
	unsigned int m_delay;
	std::vector<std::thread> m_threads;
	static std::string GetDateTime();*/
	//debug

	CustomTerminalHandler m_terminalHandler = CustomTerminalHandler();
	CustomFileHandler m_fileHandler = CustomFileHandler();
	// the messages in the queue are just going to use
	// the message attribute of the QueueMember in the queue
	void PushToQueue(std::string type, std::string entry);
};
