#include "../../include/worker/log_worker.hpp"

// ========== Public Definitions ===========

void LogWorker::Listener(QueueManager& queueManager, HandlerManager& handlerManager, unsigned int delay) {
	QueueMember member;

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(delay));

		if (queueManager.GetQueueSize() > 0) {
			// the queue is not empty
			member = queueManager.Pop();
			OutputAllHandlers(handlerManager, member);
		}
		std::this_thread::sleep_for(std::chrono::seconds(delay));
		// check to stop (start cleanup)
		if (queueManager.GetSignalStop()) {
			// finish logging the rest of the entries in the queue
			for (unsigned int i = 0; i < queueManager.GetQueueSize(); i++) {
				member = queueManager.Pop();
				OutputAllHandlers(handlerManager, member);
			}
			return;
		}
	}
}

// ========== Private Definitions ===========

void LogWorker::OutputAllHandlers(HandlerManager& handlerManager, QueueMember member) {
	// loop through all the handlers and tell them to 
	// perform their implementation of Output

	std::vector<std::shared_ptr<Handler>> handlers = handlerManager.GetHandlers();

	for (unsigned int i = 0; i < handlers.size(); i++) {
		handlers.at(i)->Output(member);
	}
}