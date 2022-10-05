#pragma once

#include <string>

struct QueueMember {
	std::string loggerName;
	std::string level;
	std::string datetime;
	std::string message;
};