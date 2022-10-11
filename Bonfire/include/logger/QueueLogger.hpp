#pragma once

// this Abstract Base Class is going to provide a framework for the loggers that 
// want to implement the queue based multithreaded system
// they have shared pointers to 

#include "../Core.hpp"
#include "../manager/queue_manager.hpp"
#include "../worker/log_worker.hpp"

/*
* Directive for the default background thread delay.
* The client can specify their own delay but the
* default is set to 1 second.
*/
#define DEFAULT_DELAY 1

class QueueLogger {
protected:
	QueueManager m_queueManager = QueueManager();
	unsigned int m_delay;
	std::vector<std::thread> m_threads;
public:
	/**
	* Get the current local date and time
	*
	* @return the date and time in format "D M d h:m:s Y"
	*/
	std::string GetDateTime();
};