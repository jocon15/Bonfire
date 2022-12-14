#pragma once

#include "../../pch.hpp"

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