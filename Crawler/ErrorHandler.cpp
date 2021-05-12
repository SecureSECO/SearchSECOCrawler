/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "ErrorHandler.h"

DefaultGithubErrorHandler::DefaultGithubErrorHandler()
{
	std::map<githubAPIResponse, const char*> messages = {
		{githubAPIResponse::JSONError, "Fatal error in JSON code."},
		{githubAPIResponse::badCredentials, "Wrong credentials, check if the token is correct."},
		{githubAPIResponse::forbidden, "Github returned 403 forbidden. This could be because you are not authenticated, because you already made too many login attempts or because your token has exceeded the rate limit."},
		{githubAPIResponse::badGateway, "Bad gateway error."},
		{githubAPIResponse::urlNotFound, "URL not found. Please check if the URL you gave as input is correct."},
		{githubAPIResponse::unknownError, "An unknown error occured."}
	};
	std::map<githubAPIResponse, IndividualErrorHandler*> handlers;
	handlers.insert({ githubAPIResponse::OK, new EmptyHandler() });

	// Taken from https://stackoverflow.com/questions/26281979/c-loop-through-map.
	for (auto const& keyvalue : messages)
	{
		handlers.insert({ keyvalue.first, new LogHandler(keyvalue.second, LogLevel::ERROR, getCode(keyvalue.first)) });
	}
	replaceAllHandlers(handlers);
}



DefaultGenericErrorHandler::DefaultGenericErrorHandler()
{
	std::map<genericError, IndividualErrorHandler*> handlers = {
		{genericError::basicError, new EmptyHandler()},

	};
	replaceAllHandlers(handlers);
}




