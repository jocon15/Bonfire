#include "../../../include/handler/handlers/TerminalHandler.hpp"

// ========== Public Definitions ==========
TerminalHandler::TerminalHandler(std::string format, int level){
	m_format = format;
	m_level = level;
}

void TerminalHandler::Output(QueueMember member){
	std::string entry = BuildFormattedEntry(member);

	// print the entry with colors
	// https://www.youtube.com/watch?v=MvX4tVETjHk

	std::cout << entry << std::endl;
}

// ========== Private Definitions ==========


