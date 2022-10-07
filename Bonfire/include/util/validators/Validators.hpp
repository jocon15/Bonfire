#pragma once

#include <string>
#include <stdexcept>

namespace Validators {
	/*
	* Validate a logger name
	*
	* @param name the logger name to be validated
	*
	* @return the validated name
	*/
	std::string ValidateLoggerName(std::string name);

	/*
	* Validate a file name
	*
	* @param name the file name to be validated
	*
	* @return the validated name
	*/
	std::string ValidateFileName(std::string name);

	/*
	* Validate a filepath string
	*
	* @param path the file path to be validated
	*
	* @return the validated path
	*/
	std::string ValidateFilePath(std::string path);

	/*
	* Validate a format string
	* 
	* @param format the format to be validated
	* 
	* @return the validated format
	*/
	std::string ValidateFormat(std::string format);
}