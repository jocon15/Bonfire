#pragma once

#include "../QueueLogger.hpp"
#include "../../Core.hpp"

namespace bf {

	class BONFIRE_API CustomLogger : public QueueLogger {
	public:
		/**
		* Constructor
		* 
		* @param delay the background thread delay in milliseconds
		*/
		CustomLogger(unsigned int delay = 1000);

		/**
		* Copy constructor
		*/
		CustomLogger(const CustomLogger&);

		/*
		* Destructr
		*/
		~CustomLogger();

		/**
		* Write an entry to a file
		* 
		* @param filePath the path of the target file
		* @param entry the entry to write to the file
		*/
		void ToFile(std::string filePath, std::string entry);

		/**
		* Print an entry in the terminal
		*
		* @param entry the entry to write to the file
		*/
		void ToTerminal(std::string entry);

	private:
		CustomTerminalHandler m_terminalHandler = CustomTerminalHandler();
		CustomFileHandler m_fileHandler = CustomFileHandler();

		/*
		* Push an entry to the queue
		* 
		* @param type the type of entry being added
		* @param type the entry to add
		*/
		void PushToQueue(std::string type, std::string entry);
	};

}
