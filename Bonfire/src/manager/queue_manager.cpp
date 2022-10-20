#include "../../include/manager/queue_manager.hpp"

// ========== Public Definitions ==========

QueueManager::QueueManager() {

}


QueueManager::QueueManager(const QueueManager&) {

}

void QueueManager::Push(QueueMember& member) {
	m_queueMutex.lock();
	m_queue.push(member);
	m_queueMutex.unlock();
}

QueueMember QueueManager::Pop() {
	QueueMember returnMember;
	// let it error if it tries to pop 
	// when the queue is empty
	m_queueMutex.lock();
	returnMember = m_queue.front();
	m_queue.pop();
	m_queueMutex.unlock();
	return returnMember;
}