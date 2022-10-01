#include "../../../include/util/validators/Validators.hpp"

std::string Validators::ValidateLoggerName(std::string name) {
	if (name.find("\\") != -1)
		throw std::invalid_argument("Logger name cannot have escape characters");
	if (name.find(".") != -1)
		throw std::invalid_argument("Logger name cannot have ");
	if (name.size() == 0)
		throw std::invalid_argument("Logger name cannot be empty");
	return name;
}

std::string Validators::ValidateFileName(std::string name) {
	if (name.find("\\") != -1)
		throw std::invalid_argument("Logger name cannot have escape characters");
	if (name.find(" ") != -1)
		throw std::invalid_argument("Logger name cannot have spaces");
	if (name.size() == 0)
		throw std::invalid_argument("Logger name cannot be empty");
	return name;
}

std::string Validators::ValidateFilePath(std::string path) {
	if (path.find(".") != -1)
		throw std::invalid_argument("Directory cannot have periods");
	if (path.find(" ") != -1)
		throw std::invalid_argument("Directory cannot have spaces");
	return path;
}

std::string Validators::ValidateFormat(std::string format){
	// NOT IMPLEMENTED YET

	return format;
}