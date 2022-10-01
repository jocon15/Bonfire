#pragma once

//#include "../Core.hpp"
#include "../util/Util.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

// so the syntax here is 
// Handler* handler1 = new FileHandler();  remember to use shared/unique pointer

class Handler {
public:
	virtual void Output(QueueMember member) = 0;
protected:
	//std::string m_loggerName;
	
	//Handler(std::string loggerName);
	std::string m_format;

	std::string BuildFormattedEntry(QueueMember member);

private:
	std::string SortFormatElement(QueueMember& member, char letter);
};