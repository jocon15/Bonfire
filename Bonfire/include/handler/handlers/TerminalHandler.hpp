#pragma once

#include "../Handler.hpp"

#define CUSTOM_FOREGROUND_BLUE        0x0001
#define CUSTOM_FOREGROUND_GREEN       0x0002
#define CUSTOM_FOREGROUND_LIGHT_BLUE  0x0003
#define CUSTOM_FOREGROUND_RED         0x0004
#define CUSTOM_FOREGROUND_PINK        0x0005
#define CUSTOM_FOREGROUND_YELLOW      0x0006
#define CUSTOM_FOREGROUND_WHITE       0x0007
#define CUSTOM_FOREGROUND_GREY        0x0008
#define CUSTOM_FOREGROUND_BRIGHT_BLUE 0x0009

class TerminalHandler : public Handler {
public:
	TerminalHandler(std::string format, int level = DEBUG_LEVEL);
	void Output(QueueMember member) override;
protected:
	std::string BuildFormattedEntry(QueueMember member) override;
private:
	std::string SortFormatElement(QueueMember& member, char letter);
};