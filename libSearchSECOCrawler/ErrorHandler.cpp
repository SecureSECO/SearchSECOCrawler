/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "ErrorHandler.h"

GithubErrorThrowHandler::GithubErrorThrowHandler()
{
	std::map<githubAPIResponse, const char *> messages = {
		{githubAPIResponse::JSONError, "Fatal error in JSON code."},
		{githubAPIResponse::badCredentials, "Wrong credentials, check if the token is correct."},
		{githubAPIResponse::rateLimitExceeded,
		 "This could be because you are not authenticated, because you already made too "
		 "many login attempts or because your token has exceeded the rate limit."},
		{githubAPIResponse::forbidden, "You aren't allowed to access this repository."},
		{githubAPIResponse::badGateway, "Bad gateway error."},
		{githubAPIResponse::urlNotFound, "URL not found. Please check if the URL you gave as input is correct."},
		{githubAPIResponse::unknownError, "An unknown error occured."}};
	for (auto const &keyvalue : messages)
	{
		handlers.insert(
			{keyvalue.first, new LogThrowHandler(keyvalue.second, LogLevel::ERROR, getCode(keyvalue.first))});
	}
	replaceAllHandlers(handlers);
}

JSONErrorHandler::JSONErrorHandler()
{
	std::map<JSONError, const char *> messages = {
		{JSONError::branchError, "Couldn't find the given index in JSON structure."},
		{JSONError::parseError, "Error while parsing JSON structure."},
		{JSONError::typeError,
			"Error while converting JSON type to standard type. Perhaps something is wrong in the program code?"},
		{JSONError::fieldEmptyError, "Field was empty in JSON structure while it shouldn't have been."
										"Perhaps something changed in the external API?"},
		{JSONError::outOfRangeError, "Index was out of range in JSON structure."}};

	std::map<JSONError, IndividualErrorHandler *> handlers;

	// Partially Taken from https://stackoverflow.com/questions/26281979/c-loop-through-map.
	for (auto const &keyvalue : messages)
	{
		handlers.insert(
			{keyvalue.first, new LogHandler(keyvalue.second, LogLevel::ERROR, getCode(keyvalue.first))});
	}

	replaceAllHandlers(handlers);
}