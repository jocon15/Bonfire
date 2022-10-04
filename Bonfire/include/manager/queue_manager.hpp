#pragma once

#include <mutex>
#include <queue>

#include "../util/queue/QueueMember.hpp"

class QueueManager {
public:

	QueueManager();

	QueueManager(const QueueManager&);

	void Push(QueueMember& member);

	QueueMember Pop();

	void SetSignalStop();

	bool GetSignalStop();

	unsigned int GetQueueSize();

private:
	std::mutex m_queueMutex;
	std::queue<QueueMember> m_queue;
	std::atomic_bool m_signalCleanup = false;
};