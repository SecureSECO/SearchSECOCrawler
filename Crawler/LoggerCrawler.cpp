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

void LoggerCrawler::logDebug(std::string message, const char *file, unsigned int line)
{
	loguru::log(loguru::Verbosity_1, file, line, "%s", message.c_str());
}

void LoggerCrawler::logInfo(std::string message, const char *file, unsigned int line)
{
	loguru::log(loguru::Verbosity_INFO, file, line, "%s", message.c_str());
}

void LoggerCrawler::logWarn(std::string message, const char *file, unsigned int line)
{
	loguru::log(loguru::Verbosity_WARNING, file, line, "%s", message.c_str());
}

void LoggerCrawler::logFatal(std::string message, const char *file, unsigned int line)
{
	loguru::log(loguru::Verbosity_ERROR, file, line, "%s", message.c_str());
}
