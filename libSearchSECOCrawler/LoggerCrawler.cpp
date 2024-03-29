/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
*/

// Crawler includes.
#include "LoggerCrawler.h"

// External includes.
#include "loguru/loguru.hpp"

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

void LoggerCrawler::logFatal(std::string message, const char *file, unsigned int line, int code)
{
	loguru::log(loguru::Verbosity_ERROR, file, line, "%s", getMessage(message, code).c_str());
}

std::string LoggerCrawler::getMessage(std::string message, int code)
{
	std::string c = std::to_string(BASE + code);
	std::string s = "E" + c + " - " + message;
	return s;
}
