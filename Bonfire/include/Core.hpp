#pragma once

#ifdef COMPILING_DLL
	#define BONFIRE_API __declspec(dllexport)
#else
	#define BONFIRE_API __declspec(dllimport)
#endif

// turn off warnings
#define _CRT_SECURE_NO_WARNINGS

#include "../include/logger/loggers/CustomLogger.hpp"
#include "../include/logger/loggers/PerformanceLogger.hpp"