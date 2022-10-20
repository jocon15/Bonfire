#pragma once

#include "../pch.hpp"
#include "../util/queue/QueueMember.hpp"

/*
* This class is responsible for managinng the queue
* between the Logger instance and the LogWorker
* instance. The QueueManager houses the queue
* of log entries that the client has submited. This
* class is designed to be accessed by multiple
* threads and uses a mutex to facilitate safe
* read/write.
*/
class QueueManager {
public:
	/*
	* Constructor
	*/
	QueueManager();

	/*
	* Copy constructor
	*/
	QueueManager(const QueueManager&);

	/*
	* Push a log entry onto the stack
	* 
	* @param member& a reference to a log entry
	*/
	void Push(QueueMember& member);

	/*
	* Pop a log entry off of the stack
	* 
	* @return a log entry
	*/
	QueueMember Pop();

	/*
	* Signal to the worker threads to start 
	* cleanup and end join the main thread
	*/
	inline void SetSignalStop() {
		m_signalCleanup = true;
	}

	/*
	* Check the status of the stop signal
	* 
	* @return to stop or not to stop
	*/
	inline bool GetSignalStop() {
		return m_signalCleanup;
	}

	/*
	* Get the current size of the queue
	* 
	* @return the size of the queue
	*/
	inline unsigned int GetQueueSize() {
		return static_cast<unsigned int>(m_queue.size());
	}

private:
	std::mutex m_queueMutex;
	std::queue<QueueMember> m_queue;
	std::atomic_bool m_signalCleanup = false;
};