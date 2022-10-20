#pragma once

#include "../CustomHandler.hpp"

class CustomFileHandler: public CustomHandler {
public:
	/**
	* Default Constructor
	*/
	CustomFileHandler();

	/*
	* Constructor
	* 
	* @param filePath the path of the file to write to
	*/
	CustomFileHandler(std::string filePath);

	/*
	* Update the target file path
	* 
	* @param filePath the path of the new target file
	*/
	inline void UpdateFilePath(std::string filePath) {
		m_filePath = filePath;
	}

	/*
	* Output an entry to the terminal
	*
	* @param member the log entry to be output
	*/
	void Output(QueueMember& member) override;
private:
	std::string m_filePath;
};