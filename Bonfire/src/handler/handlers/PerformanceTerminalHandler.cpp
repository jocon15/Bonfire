#include "../../../include/handler/handlers/PerformanceTerminalHandler.hpp"

// ========== Public Definitions ==========
TerminalHandler::TerminalHandler(std::string format, int level){
	m_format = format;
	m_level = level;
}

void TerminalHandler::Output(QueueMember member){
	// filter
	if (Translators::TranslateLevel(member.level) < m_level) {
		return;
	}

	std::string buildString = BuildFormattedEntry(member);

	// print with color
	bool usingDefaultColor = true;
	unsigned short int newColor;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_WHITE);
	for (unsigned int i = 0; i < buildString.size(); i++) {
		char currChar = buildString.at(i);
		if (buildString.at(i) == '&') {
			// if this is an end color '&' char
			if (!usingDefaultColor) {
				// reset color to default
				usingDefaultColor = true;
				SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_WHITE);
			}
			// this is a start color '&' char
			else {
				// check that next char is in bounds
				if (i + 1 < buildString.size()) {
					// get the new color
					newColor = stoi(buildString.substr(i + 1, 1));

					// change the printer color 
					switch (newColor) {
					case 1:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_BLUE);
						break;
					case 2:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_GREEN);
						break;
					case 3:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_LIGHT_BLUE);
						break;
					case 4:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_RED);
						break;
					case 5:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_PINK);
						break;
					case 6:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_YELLOW);
						break;
					// no case 7 becuase that's a default case
					case 8:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_GREY);
						break;
					case 9:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_BRIGHT_BLUE);
						break;
					default:
						usingDefaultColor = false;
						SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_WHITE);
						break;
					}

					// skip the color directive character
					i++;
				}
			}
		}
		else {
			// print the character in whatever color
			std::cout << buildString.at(i);
		}
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hcon, CUSTOM_FOREGROUND_WHITE);
	std::cout.flush();
}

// ========== Protected Definintions ==========

std::string TerminalHandler::SortFormatElement(QueueMember& member, char letter) {
	if (letter == 'N') {
		return member.loggerName;
	}
	else if (letter == 'L') {
		// inject the respective color directive as well as the level
		if (member.level == "DEBUG")
			return "&1" + member.level + "&";
		else if (member.level == "INFO")
			return "&2" + member.level + "&";
		else if (member.level == "WARNING")
			return "&6" + member.level + "&";
		else
			return "&4" + member.level + "&";
	}
	else if (letter == 'D') {
		return member.datetime;
	}
	else if (letter == 'M') {
		return member.message;
	}
	return "-1";
}