#pragma once

#include "../../pch.hpp"
/*
* Deirectives for each of the individual log
* levels. These levels follow the conventional
* Python log levels defined here
* https://docs.python.org/3/library/logging.html
*/
#define CRITICAL_LEVEL 50
#define ERROR_LEVEL    40
#define WARNING_LEVEL  30
#define INFO_LEVEL     20
#define DEBUG_LEVEL    10
#define NOTSET_LEVEL   0

namespace Translators {
	/*
	* Translate the string level into an integer value
	*
	* @param level the string level
	*
	* @return the coresponding integer level of the value
	*/
	int TranslateLevel(std::string level);
}