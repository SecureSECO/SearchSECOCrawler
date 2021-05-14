/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

#include <string>
#include <vector>
#include <map>

#include "loguru/loguru.hpp"
#include "Logger.h"

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
	virtual void execute(const char* file, unsigned int line)
	{
	};
};


class LogHandler : public IndividualErrorHandler
{
private:
	const char* msg;
	LogLevel level;
	int code;
public:
	LogHandler(const char* msg, LogLevel level, int code)
	{
		this->msg = msg;
		this->level = level;
		this->code = code;
	}
	void execute(const char* file, unsigned int line) override;
};

class EmptyHandler : public IndividualErrorHandler
{
public:
	void execute(const char* file, unsigned int line) override;
};