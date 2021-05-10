#include "ErrorHandler.h"

DefaultGithubErrorHandler::DefaultGithubErrorHandler()
{
	std::map<githubAPIResponse, IndividualErrorHandler*> handlers = {
		{githubAPIResponse::OK, new EmptyHandler()},
		{githubAPIResponse::JSONError, new LogHandler("Fatal error in JSON code.", LogLevel::ERROR)},
		{githubAPIResponse::badCredentials, new LogHandler("Wrong credentials, check if the token is correct.", LogLevel::ERROR)},
		{githubAPIResponse::forbidden, new LogHandler("Github returned 403 forbidden. This could be because you are not authenticated, because you already made too many login attempts or because your token has exceeded the rate limit.", LogLevel::ERROR)},
		{githubAPIResponse::badGateway, new LogHandler("Bad gateway error.", LogLevel::ERROR)},
		{githubAPIResponse::urlNotFound, new LogHandler("URL not found. Please check if the URL you gave as input is correct.", LogLevel::ERROR)},
		{githubAPIResponse::unknownError, new LogHandler("An unknown error occured.", LogLevel::ERROR)}
	};
	replaceAllHandlers(handlers);
}


DefaultGenericErrorHandler::DefaultGenericErrorHandler()
{
	std::map<genericError, IndividualErrorHandler*> handlers = {
		{genericError::basicError, new EmptyHandler()},

	};
	replaceAllHandlers(handlers);
}




