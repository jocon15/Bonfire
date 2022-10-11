#pragma once

#include "../CustomHandler.hpp"

class CustomFileHandler: public CustomHandler {
public:
	CustomFileHandler();

	CustomFileHandler(std::string filePath);

	void UpdateFilePath(std::string filePath);

	void Output(QueueMember& member) override;
private:
	std::string m_filePath;
};