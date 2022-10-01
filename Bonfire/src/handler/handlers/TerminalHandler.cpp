#include "../../../include/handler/handlers/TerminalHandler.hpp"

// ========== Public Definitions ==========
TerminalHandler::TerminalHandler(std::string format, int level){
	m_format = format;
	m_level = level;
}

void TerminalHandler::Output(QueueMember member){
	std::string buildString = BuildFormattedEntry(member);

	// print the entry with colors
	// https://www.youtube.com/watch?v=MvX4tVETjHk

	// different colors on one line
	// https://stackoverflow.com/questions/27400292/colored-text-in-windows-command-prompt-in-one-line

	std::cout << buildString << std::endl;

	/*
	* 1 - blue
	* 2 - green
	* 3 - cyan
	* 4 - red
	* 5 - purple
	* 6 - yellow
	* 7 - default white
	* 8 - grey
	* 9 - bright blue
	* 10 - bright green
	* 11 - bright cyan
	* 12 - bright red
	* 13 - pink
	* 14 - yellow
	* 15 - bright white
	*/

	//const unsigned short int DEFAULT_COLOR = 7;
	//unsigned short int color = DEFAULT_COLOR;
	//unsigned short int newColor;
	//HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hcon, DEFAULT_COLOR);

	//for (unsigned int i = 0; i < buildString.size(); i++) {
	//	if (buildString.at(i) == '&') {
	//		// if this is an end color char
	//		if (color != DEFAULT_COLOR) {
	//			// reset color to default
	//			SetConsoleTextAttribute(hcon, DEFAULT_COLOR);
	//		}
	//		// this is a start color char
	//		else {
	//			// check that next char is in bounds
	//			if (i + 1 < buildString.size()) {
	//				// get the new color
	//				newColor = buildString.at(i + 1);
	//				// set the new color
	//				SetConsoleTextAttribute(hcon, newColor);
	//				// skip past the color number
	//				i++;
	//			}
	//		}
	//	}
	//	else {
	//		// print the character in whatever color
	//		std::cout << buildString.at(i);
	//	}
	//}
	//std::cout << std::endl;
	//SetConsoleTextAttribute(hcon, DEFAULT_COLOR);
	// set color back to default

}

// ========== Private Definitions ==========


