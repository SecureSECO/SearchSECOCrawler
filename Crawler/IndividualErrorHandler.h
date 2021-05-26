/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

#include <map>
#include <string>
#include <vector>

#include "LoggerCrawler.h"
#include "loguru/loguru.hpp"

enum class LogLevel
{
	INFO,
	WARN,
	ERROR,
	DEBUG
};

class IndividualErrorHandler
{
public:
	/// <summary>
	/// A generic execute function which reacts to when an error occurs.
	/// </summary>
	/// <param name="file">The file in which this function is called from.</param>
	/// <param name="line">The line from which this function is called from.</param>
	virtual void execute(const char *file, unsigned int line){};
};

/// <summary>
/// A handler that logs errors to console.        
/// </summary>
class LogHandler : public IndividualErrorHandler
{
private:
	const char *msg;
	LogLevel level;
	int code;

public:
	LogHandler(const char *msg, LogLevel level, int code)
	{
		this->msg = msg;
		this->level = level;
		this->code = code;
	}
	/// <summary>
	/// A generic execute function which reacts to when an error occurs.
	/// </summary>
	/// <param name="file">The file in which this function is called from.</param>
	/// <param name="line">The line from which this function is called from.</param>
	void execute(const char *file, unsigned int line) override;
};

/// <summary>
/// A handler that does nothing.
/// </summary>
class EmptyHandler : public IndividualErrorHandler
{
public:
	/// <summary>
	/// A generic execute function which reacts to when an error occurs.
	/// </summary>
	/// <param name="file">The file in which this function is called from.</param>
	/// <param name="line">The line from which this function is called from.</param>
	void execute(const char *file, unsigned int line) override;
};