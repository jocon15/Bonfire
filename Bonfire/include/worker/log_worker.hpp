#pragma once

#include <iostream>
#include <chrono>

#include "../manager/queue_manager.hpp"
#include "../manager/handler_manager.hpp"

/*
* This class serves as the background thread.
* The thread consistently checks the queue 
* via the QueueManger for new log entries. 
* As entries are addedto the queue by the 
* Logger instance, this background thread 
* logs them using the handlers defined in 
* the HandlerManager.
*/
class LogWorker {
public:
	/*
	* Listener logic that the background thread runs
	* 
	* @param queueManager& a reference to the QueueManager instance
	* @param handlerManager& a reference to the HandlerManager 
	*/
	static void Listener(QueueManager& queueManager, HandlerManager& handlerManager, unsigned int delay);

private:
	/*
	* Logic that calls the output function of all the handlers in HandlerManager
	* 
	* @param handlerManager& a reference to the HandlerManager
	* @param member the log entry to be logged
	*/
	static void OutputAllHandlers(HandlerManager& handlerManager, QueueMember member);
};