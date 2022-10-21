#pragma once

#include "../CustomHandler.hpp"

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
* CustomTerminalHandler is a subclass of CustomHandler. The CTH
* handles the terminal output logic for custom log entries
* targeted to the terminal.
*/
class CustomTerminalHandler: public CustomHandler {
public:
	/**
	* Output an entry to the terminal
	*
	* @param member the log entry to be output
	*/
	void Output(QueueMember& member) override;
};