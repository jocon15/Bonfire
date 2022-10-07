#include "../../../include/util/translators/translators.hpp"

int Translators::TranslateLevel(std::string level) {
	if (level == "notset" || level == "NOTSET")
		return NOTSET_LEVEL;
	else if (level == "debug" || level == "DEBUG")
		return DEBUG_LEVEL;
	else if (level == "info" || level == "INFO")
		return INFO_LEVEL;
	else if (level == "warning" || level == "WARNING")
		return WARNING_LEVEL;
	else if (level == "error" || level == "ERROR")
		return ERROR_LEVEL;
	else
		return CRITICAL_LEVEL;
}