#pragma once

#include "../Handler.hpp"

// definitions for logging levels

#define CRITICAL_LEVEL 40
#define CRITICAL_LEVEL 40
#define ERROR_LEVEL    30
#define WARNING_LEVEL  20
#define INFO_LEVEL     10
#define DEBUG_LEVEL    0

class FileHandler : public Handler {
public:
	FileHandler(std::string fileName, std::string logDir = "", int level = DEBUG_LEVEL);
	void Output(std::string entry, int level);
private:
	std::string m_fileName;
	std::string m_filePath;
	std::string m_logDir;
	int m_level;
};