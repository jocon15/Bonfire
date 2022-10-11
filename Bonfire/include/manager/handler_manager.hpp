#pragma once

#include "../pch.hpp"

#include "../handler/PerformanceHandler.hpp"

/*
* This class is responsible for managinng handlers 
* between the Logger instance and the LogWorker 
* instance. The HandlerManager houses the vector
* of handlers that the client has defined. This 
* class is designed to be accessed by multiple 
* threads and uses a mutex to facilitate safe 
* read/write.
*/
class HandlerManager {
public:
	/*
	* Constructor
	*/
	HandlerManager();

	/*
	* Copy constructor
	*/
	HandlerManager(const HandlerManager&);

	/*
	* Add a handler to the vector of handlers
	* 
	* @param handler a shared pointer to a handler instance
	*/
	void AddHandler(std::shared_ptr<PerformanceHandler> handler);

	/*
	* Get the vector of handlers
	* 
	* @return a vector of shared pointers to handler instances
	*/
	std::vector<std::shared_ptr<PerformanceHandler>> GetHandlers();

private:
	std::mutex m_handlersMutex;
	std::vector<std::shared_ptr<PerformanceHandler>> m_handlers;
};