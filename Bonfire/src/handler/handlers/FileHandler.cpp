#include "../../../include/handler/handlers/FileHandler.hpp"

// ========== Public Definitions ==========

FileHandler::FileHandler(std::string fileName, std::string logDir, std::string format, int level){
	
	// need to validate these

	m_format = format;
	m_fileName = fileName;
	m_logDir = logDir;
	m_level = level;
}


void FileHandler::Output(QueueMember member) {
	// construct the message
	std::string entry = BuildFormattedEntry(member);


	// if the log needs to be filtered or not
	//if (level >= m_level) {
	//	std::ofstream logFS;

	//	logFS.open(m_filePath + m_fileName, std::ios::app);				//open the file in append mode
	//	logFS << entry << std::endl;
	//	logFS.close();
	//}

	// reference the above code to eventually determine if the level is greater than the current defined level
	std::ofstream logFS;
	logFS.open(m_filePath + m_fileName, std::ios::app);				//open the file in append mode
	logFS << entry << std::endl;
	//logFS.flush();
	logFS.close();
}


// ========== Private Definitions ==========


