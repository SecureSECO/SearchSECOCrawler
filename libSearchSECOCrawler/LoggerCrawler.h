/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

// External includes.
#include <string>


class LoggerCrawler
{
private:
	/// <summary>
	/// Combines a message and an error code into a correctly formatted error message.
	/// </summary>
	/// <param name="message">The original message to format.</param>
	/// <param name="code">The error code.</param>
	/// <returns>A correctly formatted error message.</returns>
	static std::string getMessage(std::string message, int code);

public:
	/// <summary>
	/// Logs a message at Debug-level verbosity.
	/// </summary>
	/// <param name="file">The file in which this function is called.</param>
	/// <param name="line">The line from which this function is called.</param>
	static void logDebug(std::string message, const char* file, unsigned int line);

	/// <summary>
	/// Logs a message at Info-level verbosity.
	/// </summary>
	/// <param name="file">The file in which this function is called.</param>
	/// <param name="line">The line from which this function is called.</param>
	static void logInfo(std::string message, const char* file, unsigned int line);

	/// <summary>
	/// Logs a Warning.
	/// </summary>
	/// <param name="file">The file in which this function is called.</param>
	/// <param name="line">The line from which this function is called.</param>
	static void logWarn(std::string message, const char* file, unsigned int line);

	/// <summary>
	/// Logs a Fatal (Error) message. This does not terminate execution, that responsibility lies 
	/// with the Controller component.
	/// </summary>
	/// <param name="file">The file in which this function is called.</param>
	/// <param name="line">The line from which this function is called.</param>
	/// <param name="code">The error code.</param>
	static void logFatal(std::string message, const char* file, unsigned int line, int code);
};
