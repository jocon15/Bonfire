#pragma once

#include "../pch.hpp"
#include "../manager/queue_manager.hpp"
#include "../worker/log_worker.hpp"

/*
* Directive for the default background thread delay.
* The client can specify their own delay but the
* default is set to 1 second.
*/
#define DEFAULT_DELAY 1

/*
* This abstract base class provides a template for the loggers
* that implement the multithreaded queue-based logging system
*/
class QueueLogger {
public:
	/**
	* Get the current local date and time
	*
	* @return the date and time in format "D M d h:m:s Y"
	*/
	static std::string GetDateTime();

protected:
	QueueManager m_queueManager = QueueManager();
	unsigned int m_delay;
	std::vector<std::thread> m_threads;
};