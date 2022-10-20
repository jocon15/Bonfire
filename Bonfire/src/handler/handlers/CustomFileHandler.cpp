#include "../../../include/handler/handlers/CustomFileHandler.hpp"

// ========== Public Definitions ==========

CustomFileHandler::CustomFileHandler() {

}

CustomFileHandler::CustomFileHandler(std::string filePath) {
	m_filePath = filePath;
}

void CustomFileHandler::Output(QueueMember& member) {
	std::ofstream logFS;
	logFS.open(m_filePath, std::ios::app);
	logFS << member.message << std::endl;
	logFS.flush();
	logFS.close();
}
