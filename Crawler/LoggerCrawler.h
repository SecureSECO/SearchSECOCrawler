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
	/// <summary>
	/// Formats a string and an error code to a correctly formatted error message.
	/// </summary>
	static std::string getMessage(const char *message, int code);

public:
	/// <summary>
	/// Logs a message at Debug-level verbosity.
	/// </summary>
	static void logDebug(std::string message, const char* file, unsigned int line);

	/// <summary>
	/// Logs a message at Info-level verbosity.
	/// </summary>
	static void logInfo(std::string message, const char* file, unsigned int line);

	/// <summary>
	/// Logs a Warning.
	/// </summary>
	static void logWarn(std::string message, const char* file, unsigned int line);

	/// <summary>
	/// Logs a Fatal (Error) message. This does not terminate execution, that responsibility lies 
	/// with the Controller component.
	/// </summary>
	static void logFatal(std::string message, const char* file, unsigned int line, int code);
};
