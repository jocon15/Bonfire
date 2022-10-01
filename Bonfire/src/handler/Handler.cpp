#include "../../include/handler/Handler.hpp"

// ========== Public Definitions ==========

// ========== Protected Definitions ==========

std::string Handler::BuildFormattedEntry(QueueMember member){
	std::string buildString;
	unsigned int i = 0;

	for (i = 0; i < m_format.size()-1; i++) {
		if (i == m_format.size()-2) {
			if (m_format.at(i) == '%') {
				std::string returned = SortFormatElement(member, m_format.at(i + 1));
				if (returned != "-1") {
					buildString += returned;
				}
				else {
					buildString += m_format.at(i);
				}
			}
			else {
				buildString += m_format.at(i);
			}
			return buildString;
		}

		if (m_format.at(i) == '%') {
			std::string returned = SortFormatElement(member, m_format.at(i + 1));
			if (returned != "-1") {
				buildString += returned;
				i++;
			}
			else {
				buildString += m_format.at(i);
			}
		}
		else {
			buildString += m_format.at(i);

		}
	}

	if (m_format.at(m_format.size() - 2) != '%') {
		buildString += m_format.at(m_format.size()-1);
	}
	return buildString;
}

// ========== Private Definitions ==========

std::string Handler::SortFormatElement(QueueMember& member, char letter) {
	if (letter == 'N') {
		return member.loggerName;
	}
	else if (letter == 'L') {
		return member.level;
	}
	else if (letter == 'D') {
		return member.datetime;
	}
	else if (letter == 'M') {
		return member.message;
	}
	return "-1";
}