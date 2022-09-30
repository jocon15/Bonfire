#include "../../../include/handler/handlers/FileHandler.hpp"

// ========== Public Definitions ==========

FileHandler::FileHandler(std::string fileName, std::string logDir, int level){
	//m_loggerName = loggerName; // superclass Handler variable
	m_fileName = fileName;
	m_logDir = logDir;
	m_level = level;
}


void FileHandler::Output(std::string entry, int level) {
	// if the log needs to be filtered or not
	if (level >= m_level) {
		std::ofstream logFS;

		logFS.open(m_filePath + m_fileName, std::ios::app);				//open the file in append mode
		logFS << entry << std::endl;
		logFS.close();
	}
}


// ========== Private Definitions ==========


