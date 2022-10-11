#pragma once

#include "../QueueLogger.hpp"

class BONFIRE_API CustomLogger: public QueueLogger {
public:
	CustomLogger();

	CustomLogger(unsigned int delay = 1);

	CustomLogger(const CustomLogger&);

	~CustomLogger();

	void ToFile(std::string filepath, std::string entry);

	void ToTerminal(std::string entry);
private:

	// the messages in the queue are just going to use
	// the message attribute of the QueueMember in the queue
	void PushToQueue(std::string entry);
};
