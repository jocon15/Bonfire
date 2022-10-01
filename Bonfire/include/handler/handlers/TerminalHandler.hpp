#pragma once

#include "../Handler.hpp"

// termianl handler

// definitions for logging levels

#define CRITICAL_LEVEL 40
#define CRITICAL_LEVEL 40
#define ERROR_LEVEL    30
#define WARNING_LEVEL  20
#define INFO_LEVEL     10
#define DEBUG_LEVEL    0

class TerminalHandler : public Handler {
public:
	TerminalHandler(std::string format, int level = DEBUG_LEVEL);
	void Output(QueueMember member);
private:
	int m_level;
};