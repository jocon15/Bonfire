#pragma once

#include "../PerformanceHandler.hpp"

/*
* PerformanceFileHandler is a subclass of PerformanceHandler. The PFH
* handles the file output logic for performance log entries
* targeted to the log file.
*/
class FileHandler : public PerformanceHandler {
public:
	/**
	* Constructor 
	* 
	* @param fileName the filePath of the desired log file
	* @param format the format string for the log entries
	* @param level the base logging level to filter entries
	*/
	FileHandler(std::string filePath="log.txt", std::string format="%L %N %D %M", int level = NOTSET_LEVEL);

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
	std::string m_filePath;
};