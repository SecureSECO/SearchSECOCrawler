﻿/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

#include "IndividualErrorHandler.h"
#include "Utility.h"
#include <map>

/// <summary>
/// Template class for error handling so we can for different enums handle the error differently.
/// </summary>
/// <typeparam name="TResponse">The template class.</typeparam>
template <class TResponse> class ErrorHandler
{
private:
	std::map<TResponse, IndividualErrorHandler *> errorHandlingDictionary;

protected:
	void replaceAllHandlers(std::map<TResponse, IndividualErrorHandler *> githubErrorHandlingDictionary)
	{
		this->errorHandlingDictionary = githubErrorHandlingDictionary;
	}

public:
	// Template function definitions have to be in the same file as the class definition, see:
	// https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c

	ErrorHandler()
	{
		errorHandlingDictionary = std::map<TResponse, IndividualErrorHandler *>{};
	}

	/// <summary>
	/// Handle a given response.
	/// </summary>
	/// <param name="response">The response that needs to be handled.</param>
	/// <param name="file">The file location this function is called from.</param>
	/// <param name="line">The line number this function is called from.</param>
	void handle(TResponse response, const char *file, unsigned int line)
	{
		auto *handler = errorHandlingDictionary[response];
		handler->execute(file, line);
	}

	/// <summary>
	/// Replace a single handler for a given response with a new one.
	/// </summary>
	/// <param name="response">The response for which a new handler needs to be set.</param>
	/// <param name="handler">The handler which should now handle the response.</param>
	void replaceSingleHandler(TResponse response, IndividualErrorHandler *handler)
	{
		delete errorHandlingDictionary[response];
		errorHandlingDictionary[response] = handler;
	}

	int getCode(TResponse response)
	{
		return Utility::getCode(response);
	}
};

/// <summary>
/// A different github error handler that uses LogThrowHandlers,
/// which in addition to just logging a message also throw.
/// </summary>
class GithubErrorThrowHandler : public ErrorHandler<githubAPIResponse>
{
private:
	std::map<githubAPIResponse, IndividualErrorHandler*> handlers = {
		{githubAPIResponse::OK, new EmptyHandler()}
	};
public:
	GithubErrorThrowHandler();
};

/// <summary>
/// An error handler that handles JSON errors.
/// </summary>
class JSONErrorHandler : public ErrorHandler<JSONError>
{
public:
	JSONErrorHandler()
	{
		std::map<JSONError, const char*> messages = {
			{JSONError::branchError, "Couldn't find the given index in JSON structure."},
			{JSONError::parseError, "Error while parsing JSON structure."},
			{JSONError::typeError,
			 "Error while converting JSON type to standard type. Perhaps something is wrong in the program code?"},
			{JSONError::fieldEmptyError,
			"Field was empty in JSON structure while it shouldn't have been."
			"Perhaps something changed in the external API?"},
			{JSONError::outOfRangeError, "Index was out of range in JSON structure."}
		};

		std::map<JSONError, IndividualErrorHandler*> handlers;

		// Partially Taken from https://stackoverflow.com/questions/26281979/c-loop-through-map.
		for (auto const& keyvalue : messages)
		{
			handlers.insert(
				{ keyvalue.first, new LogHandler(keyvalue.second, LogLevel::ERROR, getCode(keyvalue.first)) });
		}

		replaceAllHandlers(handlers);
	}
};

/// <summary>
/// An error handler that handles JSON errors and is a singleton error handler.
/// We use this as the default JSON error handler that every JSON variable has access to.
/// </summary>
class JSONSingletonErrorHandler : public JSONErrorHandler
{
private:
	JSONSingletonErrorHandler() : JSONErrorHandler()
	{

	}

public:
	// C++ singleton design pattern is taken from:
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern.
	static JSONSingletonErrorHandler &getInstance()
	{
		static JSONSingletonErrorHandler instance; // Guaranteed to be destroyed.
												 // Instantiated on first use.
		return instance;
	}
};
