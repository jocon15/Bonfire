#include "../../include/logger/QueueLogger.hpp"

// ========== Public Definitions ==========

//QueueLogger::QueueLogger() {
//
//}

//QueueLogger::QueueLogger(const QueueLogger&) {
//
//}

std::string QueueLogger::GetDateTime() {
	std::string dateTime;
	time_t t;                                    //t passed as argument in function time()
	struct tm* tt;                               //declaring variable for localtime()
	time(&t);                                    //passing argument to time()
	tt = localtime(&t);
	dateTime = asctime(tt);
	dateTime.erase(remove(dateTime.begin(),
		dateTime.end(), '\n'), dateTime.end());
	return dateTime;
}
