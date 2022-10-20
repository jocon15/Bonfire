#pragma once

#include "../pch.hpp"
#include "../util/Util.hpp"

/*
* This abstract class serves as a template for creating CustomHandler 
* subclasses. The custom logger is a more flexible logger that places
* emphasis on customized style as opposed to performance. CustomHandler
*/
class CustomHandler {
public:
	/*
	* Output the log entry
	*
	* @param member the log entry to be output
	*/
	virtual void Output(QueueMember& member) = 0;
};