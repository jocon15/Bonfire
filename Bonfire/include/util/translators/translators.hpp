#pragma once

#include <string>

#define CRITICAL_LEVEL 40
#define CRITICAL_LEVEL 40
#define ERROR_LEVEL    30
#define WARNING_LEVEL  20
#define INFO_LEVEL     10
#define DEBUG_LEVEL    0

namespace Translators {
	/**
	* Translate the string level into an integer value
	*
	* @param level the string level
	*
	* @return the coresponding integer level of the value
	*/
	int TranslateLevel(std::string level);
}