#pragma once

//#include "../Core.hpp"
#include <string>
#include <fstream>


// so the syntax here is 
// Handler* handler1 = new FileHandler();  remember to use shared/unique pointer

class Handler {
public:
	Handler();
	virtual void Output(std::string entry, int level) = 0;
protected:
	//std::string m_loggerName;
	
	//Handler(std::string loggerName);
	

private:
	
};;