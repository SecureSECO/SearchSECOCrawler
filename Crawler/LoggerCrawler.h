/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

#include <string>

class LoggerCrawler
{
private:
	static std::string getMessage(const char *message, int code);

public:
	static void logDebug(std::string message, const char* file, unsigned int line);
	static void logInfo(std::string message, const char* file, unsigned int line);
	static void logWarn(std::string message, const char* file, unsigned int line);
	static void logFatal(std::string message, const char* file, unsigned int line, int code);
};
