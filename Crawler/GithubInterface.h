/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "ErrorHandler.h"
#include "JSON.h"
#include <string>

#define waitTime 15
#define checksPerSecond 4

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
	/// Requests data from Github and returns a pointer to a JSON variable.
	/// </summary>
	/// <param name="query">The query to be send to Github.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	virtual JSON *getRequest(std::string query);

	/// <summary>
	/// Requests data from Github and returns a pointer to a JSON variable.
	/// </summary>
	/// <param name="query">The query to be send to Github.</param>
	/// <param name="handler">A pointer to a GithubErrorThrowHandler class.</param>
	/// <param name="jsonHandler"> A pointer to a JSONErrorHandler class.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	virtual JSON *getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler* jsonHandler);
	virtual JSON* getRequest(std::string query, GithubErrorThrowHandler* handler);
	virtual JSON* getRequest(std::string query, JSONErrorHandler* jsonHandler);
};
