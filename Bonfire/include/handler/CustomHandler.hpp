#pragma once

#include "../pch.hpp"
#include "../util/Util.hpp"

/*
* This abstract class serves as a template for creating Custom Handler 
* subclasses. Custom Handlers place more emphasis on customizability
* as opposed to performance.
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