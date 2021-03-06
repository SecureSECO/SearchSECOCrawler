/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
? Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

// Crawler includes.
#include "ErrorHandler.h"
#include "JSON.h"

#define WAITTIME 5
// If the token is incorrect we wait a little bit more than a year.
#define INCORRECT_TOKEN_DELAY 526000


class GithubInterface
{
private:
	std::string userAgent;
	std::string userPWD;
	GithubErrorThrowHandler defaultHandler;

public:
	GithubInterface(std::string userAgent, std::string userPWD)
	{
		this->userAgent = userAgent;
		this->userPWD = userPWD;
	}

	/// <summary>
	/// Requests data from GitHub and returns a pointer to a JSON variable.
	/// </summary>
	/// <param name="query">The query to be send to GitHub.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	virtual JSON *getRequest(std::string query);

	/// <summary>
	/// Requests data from GitHub and returns a pointer to a JSON variable.
	/// </summary>
	/// <param name="query">The query to be sent to GitHub.</param>
	/// <param name="handler">A pointer to a GithubErrorThrowHandler class.</param>
	/// <param name="jsonHandler"> A pointer to a JSONErrorHandler class.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	virtual JSON *getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler *jsonHandler);

	/// <summary>
	/// Requests data from GitHub and returns a pointer to a JSON variable.
	/// </summary>
	/// <param name="query">The query to be sent to GitHub.</param>
	/// <param name="handler">A pointer to a GithubErrorThrowHandler class.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	virtual JSON* getRequest(std::string query, GithubErrorThrowHandler* handler);
};
