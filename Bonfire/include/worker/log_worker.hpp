#pragma once

#include <iostream>
#include <chrono>

#include "../manager/queue_manager.hpp"
#include "../manager/handler_manager.hpp"

class LogWorker {
public:
	static void Listener(QueueManager& queueManager, HandlerManager& handlerManager, unsigned int delay);

private:
	static void OutputAllHandlers(HandlerManager& handlerManager, QueueMember member);

};