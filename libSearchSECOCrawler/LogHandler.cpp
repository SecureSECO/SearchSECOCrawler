/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "IndividualErrorHandler.h"
#include "LoggerCrawler.h"
void LogHandler::execute(const char *file, unsigned int line)
{
	switch (level)
	{
		case LogLevel::INFO:
			LoggerCrawler::logInfo(msg, file, line);
			break;
		case LogLevel::WARN:
			LoggerCrawler::logWarn(msg, file, line);
			break;
		case LogLevel::ERROR:
			LoggerCrawler::logFatal(msg, file, line, code);
			break;
		case LogLevel::DEBUG:
			LoggerCrawler::logDebug(msg, file, line);
			break;
	}
}
