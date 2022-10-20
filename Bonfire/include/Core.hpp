#pragma once

#pragma warning( disable : 4251) // DLL derived class interface
#pragma warning( disable : 4275) // DLL class interface
#pragma warning( disable : 4267) // conversion from size_t to unsigned int possible loss of data
#pragma warning( disable : 4996) // deprecated function

// turn off warnings
#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef COMPILING_DLL
	#define BONFIRE_API __declspec(dllexport)
#else
	#define BONFIRE_API __declspec(dllimport)
#endif

#include "../include/logger/loggers/CustomLogger.hpp"
#include "../include/logger/loggers/PerformanceLogger.hpp"