#pragma once

#ifdef GE_PLATFORM_WINDOWS
	#ifdef COMPILING_DLL
		#define BONFIRE_API __declspec(dllexport)
	#else
		#define BONFIRE_API __declspec(dllimport)
	#endif
#else
	#error Game Engine only supports Windows!
#endif

// turn off warnings

#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <string>
#include <mutex>
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <fstream>
#include <stdexcept>
#include <ctime>

//#include "handler/Handler.hpp"
#include "logger/Logger.hpp"
//#include "handler/handlers/FileHandler.hpp"
//#include "handler/handlers/TerminalHandler.hpp"

// definitions for logging levels

#define CRITICAL_LEVEL 40
#define CRITICAL_LEVEL 40
#define ERROR_LEVEL    30
#define WARNING_LEVEL  20
#define INFO_LEVEL     10
#define DEBUG_LEVEL    0

// delay to use for the background thread

#define DEFAULT_DELAY 1