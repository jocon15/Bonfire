#include "../../include/worker/log_worker.hpp"

// ========== Public Definitions ===========

void LogWorker::PerformanceListener(QueueManager& queueManager, HandlerManager& handlerManager, unsigned int delay) {
	QueueMember member;

	while (true) {
		// wait delay seconds and allow some logs to be added to the queue
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		if (queueManager.GetQueueSize() > 0) {
			// the queue is not empty
			member = queueManager.Pop();
			OutputAllHandlers(handlerManager, member);
		}
		// check to stop (start cleanup)
		if (queueManager.GetSignalStop()) {
			// finish logging the rest of the entries in the queue
			int size = queueManager.GetQueueSize();
			for (unsigned int i = 0; i < unsigned(size); i++) {
				member = queueManager.Pop();
				OutputAllHandlers(handlerManager, member);
			}
			return;
		}
	}
}

void LogWorker::CustomListener(QueueManager& queueManager, CustomTerminalHandler& terminalHandler, CustomFileHandler& fileHandler, unsigned int delay) {
	QueueMember member;

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		if (queueManager.GetQueueSize() > 0) {
			// the queue is not empty
			member = queueManager.Pop();
			OutputEntry(terminalHandler, fileHandler, member);
		}
		// check to stop (start cleanup)
		if (queueManager.GetSignalStop()) {
			// finish logging the rest of the entries in the queue
			int size = queueManager.GetQueueSize();
			for (unsigned int i = 0; i < unsigned(size); i++) {
				member = queueManager.Pop();
				OutputEntry(terminalHandler, fileHandler, member);
			}
			return;
		}
	}
}

// ========== Private Definitions ===========

void LogWorker::OutputAllHandlers(HandlerManager& handlerManager, QueueMember& member) {
	// get a vector of current handlers
	std::vector<std::shared_ptr<PerformanceHandler>> handlers = handlerManager.GetHandlers();

	// tell each handler to output the log entry
	for (unsigned int i = 0; i < handlers.size(); i++) {
		handlers.at(i)->Output(member);
	}
}


void LogWorker::OutputEntry(CustomTerminalHandler& terminalHandler, CustomFileHandler& fileHandler, QueueMember& member) {
	if (member.type == "terminal") {
		terminalHandler.Output(member);
	}
	else if (member.type == "file") {
		fileHandler.Output(member);
	}
	else {
		// unrecognized output type
	}
}