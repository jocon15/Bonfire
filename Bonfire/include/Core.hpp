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

#include "logger/Logger.hpp"

