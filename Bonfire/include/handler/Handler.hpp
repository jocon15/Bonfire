#pragma once

#include "../util/Util.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

/*
* This abstract class serves as a template for creating Handler 
* subclasses. When you log something, you might want it to end up 
* in multiple places. For example, you might want to show a critical
* error in the terminal and also in a log file. The client can 
* add a handler via the Logger object. The logger class will then 
* create that handler subclass. Log entries will now end up where
* each handler tells it to go.
*/
class Handler {
public:
	/*
	* Output the log entry
	* 
	* @param member the log entry to be output
	*/
	virtual void Output(QueueMember member) = 0;

protected:
	std::string m_format;
	int m_level;

	/*
	* Build a formatted log entry
	* 
	* @param member the log entry to be formated
	* 
	* @return the formatted entrystring
	*/
	std::string BuildFormattedEntry(QueueMember member);

	/*
	* Build a formatted log entry
	*
	* @param member the log entry to be formated
	*
	* @return the formatted entry string
	*/
	virtual std::string SortFormatElement(QueueMember& member, char letter) = 0;
};