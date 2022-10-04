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
	logFS.flush();
	logFS.close();
}

// ========== Protected Definitions ==========

std::string FileHandler::BuildFormattedEntry(QueueMember member) {
	std::string buildString;
	unsigned int i = 0;

	for (i = 0; i < m_format.size() - 1; i++) {
		if (i == m_format.size() - 2) {
			if (m_format.at(i) == '%') {
				std::string returned = SortFormatElement(member, m_format.at(i + 1));
				if (returned != "-1") {
					buildString += returned;
				}
				else {
					buildString += m_format.at(i);
				}
			}
			else {
				buildString += m_format.at(i);
			}
			return buildString;
		}

		if (m_format.at(i) == '%') {
			std::string returned = SortFormatElement(member, m_format.at(i + 1));
			if (returned != "-1") {
				buildString += returned;
				i++;
			}
			else {
				buildString += m_format.at(i);
			}
		}
		else {
			buildString += m_format.at(i);

		}
	}

	if (m_format.at(m_format.size() - 2) != '%') {
		buildString += m_format.at(m_format.size() - 1);
	}
	return buildString;
}

// ========== Private Definitions ==========

std::string FileHandler::SortFormatElement(QueueMember& member, char letter) {
	if (letter == 'N') {
		return member.loggerName;
	}
	else if (letter == 'L') {
		return member.level;
	}
	else if (letter == 'D') {
		return member.datetime;
	}
	else if (letter == 'M') {
		return member.message;
	}
	return "-1";
}