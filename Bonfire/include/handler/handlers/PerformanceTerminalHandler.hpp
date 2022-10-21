#pragma once

#include "../PerformanceHandler.hpp"

/*
* Directives that define the different colors that
* can be used in the terminal output on a black 
* background. There are many more directives that
* could be defined for those cases but are excluded
* for clarity purposes.
*/
#define CUSTOM_FOREGROUND_BLUE        0x0001
#define CUSTOM_FOREGROUND_GREEN       0x0002
#define CUSTOM_FOREGROUND_LIGHT_BLUE  0x0003
#define CUSTOM_FOREGROUND_RED         0x0004
#define CUSTOM_FOREGROUND_PINK        0x0005
#define CUSTOM_FOREGROUND_YELLOW      0x0006
#define CUSTOM_FOREGROUND_WHITE       0x0007
#define CUSTOM_FOREGROUND_GREY        0x0008
#define CUSTOM_FOREGROUND_BRIGHT_BLUE 0x0009

/*
* PerformanceTerminalHandler is a subclass of PerformanceHandler. The PTH
* handles the terminal output logic for performance log entries
* targeted to the terminal.
*/
class TerminalHandler : public PerformanceHandler {
public:
	/*
	* Constructor
	*/
	TerminalHandler(std::string format, int level = NOTSET_LEVEL);

	/*
	* Output an entry to the terminal
	*
	* @param member the log entry to be output
	*/
	void Output(QueueMember member) override;

protected:
	/*
	* Apply the format string directives
	*
	* @param member& a reference to a log entry
	* @param letter a specific directive
	*
	* @return the string to inject
	*/
	std::string SortFormatElement(QueueMember& member, char letter) override;
};