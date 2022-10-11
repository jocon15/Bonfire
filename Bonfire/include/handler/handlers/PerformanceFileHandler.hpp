#pragma once

#include "../PerformanceHandler.hpp"

/* 
* The FileHandler class is a subclass of the Handler class.
* As discussed in the Handler class, this subclass is 
* created by the Logger object. FileHandler implements the
* virtual methods defined in Handler to output the log 
* entry to a file.
*/
class FileHandler : public PerformanceHandler {
public:
	/**
	* Constructor 
	* 
	* @param fileName the filename of the desired log file
	* @param logDir the path of the log file 
	* @param format the format string for the log entries
	* @param level the base logging level to filter entries
	*/
	FileHandler(std::string fileName="log.txt", std::string logDir="", std::string format="%L %N %D %M", int level = NOTSET_LEVEL);

	/**
	* Output an entry to the file
	* 
	* @param member the log entry to be output
	*/
	void Output(QueueMember member) override;
	
protected:
	/**
	* Apply the format string directives
	*
	* @param member& a reference to a log entry
	* @param letter a specific directive
	*
	* @return the string to inject
	*/
	std::string SortFormatElement(QueueMember& member, char letter) override;

private:
	std::string m_fileName;
	std::string m_filePath;
	std::string m_logDir;
};