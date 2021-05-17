/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "IndividualErrorHandler.h"
void LogHandler::execute(const char *file, unsigned int line)
{
	switch (level)
	{
	case LogLevel::INFO:
		Logger::logInfo(msg, file, line, code);
		break;
	case LogLevel::WARN:
		Logger::logWarn(msg, file, line, code);
		break;
	case LogLevel::ERROR:
		Logger::logFatal(msg, file, line, code);
		break;
	case LogLevel::DEBUG:
		Logger::logDebug(msg, file, line, code);
		break;
	}
}