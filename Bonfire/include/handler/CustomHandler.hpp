#pragma once

#include "../pch.hpp"
#include "../util/Util.hpp"

class CustomHandler {
public:
	
	virtual void Output(QueueMember& member) = 0;

protected:

};