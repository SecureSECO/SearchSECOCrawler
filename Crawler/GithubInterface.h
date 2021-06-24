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

class GithubInterface
{
private:
	std::string userAgent;
	std::string userPWD;
	GithubErrorThrowHandler defaultHandler;

	/// <summary>
	/// Execute a curl query in a try catch, with a timeout to ensure that it always stops after a certain time.
	/// </summary>
	/// <param name="easy">The curl object.</param>
	void executeCurlQueryWithTimeout(curl::curl_easy &easy);

	/// <summary>
	/// Add information to the curl query.
	/// </summary>
	/// <param name="query">The query that has to be added to the curl object.</param>
	/// <param name="easy">The curl object.</param>
	void addEasyInformation(std::string query, curl::curl_easy &easy);

	/// <summary>
	/// Handles a github error if one happened during the execution of the curl query.
	/// </summary>
	/// <param name="easy">The curl object.</param>
	/// <param name="ss">The stringstream that is written to by the curl object.</param>
	/// <param name="handler">The github handler.</param>
	/// <param name="jsonHandler">The JSON handler.</param>
	void handleGithubError(curl::curl_easy &easy, std::stringstream &ss, GithubErrorThrowHandler *handler,
						   JSONErrorHandler *jsonHandler);

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
	/// <param name="query">The query to be sent to Github.</param>
	/// <param name="handler">A pointer to a GithubErrorThrowHandler class.</param>
	/// <param name="jsonHandler"> A pointer to a JSONErrorHandler class.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	virtual JSON *getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler *jsonHandler);

	/// <summary>
	/// Requests data from Github and returns a pointer to a JSON variable.
	/// </summary>
	/// <param name="query">The query to be sent to Github.</param>
	/// <param name="handler">A pointer to a GithubErrorThrowHandler class.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	virtual JSON* getRequest(std::string query, GithubErrorThrowHandler* handler);
};
