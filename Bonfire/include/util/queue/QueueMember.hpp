// this file holds the QueueMember struct that needs to be used by both the Logger class and the Handler subclasses
// therefore, it is in its own seperate file

#pragma once

#include <string>

struct QueueMember {
	std::string loggerName;
	std::string level;
	std::string datetime;
	std::string message;
};