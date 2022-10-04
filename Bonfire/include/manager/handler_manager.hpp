#pragma once

#include <vector>
#include <mutex>
#include <memory>

#include "../handler/Handler.hpp"

class HandlerManager {
public:
	HandlerManager();

	HandlerManager(const HandlerManager&);

	void AddHandler(std::shared_ptr<Handler> handler);

	std::vector<std::shared_ptr<Handler>> GetHandlers();

private:
	std::mutex m_handlersMutex;
	std::vector<std::shared_ptr<Handler>> m_handlers;

};