/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "LoggerCrawler.h"
#include "loguru/loguru.hpp"
#include <stdlib.h>
#include <string>
#define BASE 100

void LoggerCrawler::logInfo(const char *message, const char *file, unsigned int line, int code)
{
	loguru::log(loguru::Verbosity_INFO, file, line, "%s", getMessage(message, code).c_str());
}
void LoggerCrawler::logWarn(const char *message, const char *file, unsigned int line, int code)
{
	loguru::log(loguru::Verbosity_WARNING, file, line, "%s", getMessage(message, code).c_str());
}
void LoggerCrawler::logFatal(const char *message, const char *file, unsigned int line, int code)
{
	loguru::log(loguru::Verbosity_ERROR, file, line, "%s", getMessage(message, code).c_str());
}
void LoggerCrawler::logDebug(const char *message, const char *file, unsigned int line, int code)
{
	loguru::log(1, file, line, "%s", getMessage(message, code).c_str());
}

std::string LoggerCrawler::getMessage(const char *message, int code)
{
	std::string c = std::to_string(BASE + code);
	std::string s = "E" + c + ": " + message;
	return s;
}