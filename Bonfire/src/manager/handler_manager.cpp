#include "../../include/manager/handler_manager.hpp"

// ========== Public Definitions ==========

HandlerManager::HandlerManager() {

}

HandlerManager::HandlerManager(const HandlerManager&) {

}

void HandlerManager::AddHandler(std::shared_ptr<Handler> handler) {
	m_handlersMutex.lock();
	m_handlers.push_back(handler);
	m_handlersMutex.unlock();
}

std::vector<std::shared_ptr<Handler>> HandlerManager::GetHandlers() {
	std::vector<std::shared_ptr<Handler>> returnVec;
	m_handlersMutex.lock();
	returnVec = m_handlers;
	m_handlersMutex.unlock();
	return returnVec;
}

// ========== Private Definitions ==========