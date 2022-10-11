#pragma once

#include "../../pch.hpp"

/*
* This struct defines the individual data
* structure of the log entries when they 
* are in the queue. These values will be 
* used individually in the formatting 
* phase so they need to be seperate in
* this fashion
*/
struct QueueMember {
	std::string loggerName;
	std::string level;
	std::string datetime;
	std::string message;
	std::string type;
};