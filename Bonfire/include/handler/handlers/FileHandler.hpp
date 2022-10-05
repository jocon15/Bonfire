#pragma once

#include "../Handler.hpp"

class FileHandler : public Handler {
public:
	FileHandler(std::string fileName="log.txt", std::string logDir="", std::string format="%L %N %D %M", int level = DEBUG_LEVEL);
	void Output(QueueMember member) override;
protected:
	std::string BuildFormattedEntry(QueueMember member) override;
private:
	std::string m_fileName;
	std::string m_filePath;
	std::string m_logDir;
	std::string SortFormatElement(QueueMember& member, char letter);
};