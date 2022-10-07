#include "../../../include/handler/handlers/FileHandler.hpp"

// ========== Public Definitions ==========

FileHandler::FileHandler(std::string fileName, std::string logDir, std::string format, int level){
	m_format = format;
	m_fileName = fileName;
	m_logDir = logDir;
	m_level = level;
}

void FileHandler::Output(QueueMember member) {
	// filter
	if (Translators::TranslateLevel(member.level) < m_level) {
		return;
	}
	
	std::string entry = BuildFormattedEntry(member);

	std::ofstream logFS;
	logFS.open(m_filePath + m_fileName, std::ios::app);
	logFS << entry << std::endl;
	logFS.flush();
	logFS.close();
}

// ========== Protected Definitions ==========

std::string FileHandler::SortFormatElement(QueueMember& member, char letter) {
	if (letter == 'N')
		return member.loggerName;
	else if (letter == 'L')
		return member.level;
	else if (letter == 'D')
		return member.datetime;
	else if (letter == 'M')
		return member.message;
	return "-1";
}

// ========== Private Definitions ==========