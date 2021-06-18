/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubInterface.h"
#include "GithubClientErrorConverter.h"
#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_form.h"
#include "curl_ios.h"

JSON* GithubInterface::getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler *jsonHandler)
{
	std::stringstream ss;
	curl::curl_ios<std::stringstream> writer(ss);

	curl::curl_easy easy(writer);

	// Set up data
	easy.add<CURLOPT_URL>(query.data());
	easy.add<CURLOPT_FOLLOWLOCATION>(1L);
	easy.add<CURLOPT_USERAGENT>(userAgent.data());
	easy.add<CURLOPT_USERPWD>(userPWD.data());
	easy.add<CURLOPT_TIMEOUT>(5L);
	easy.add<CURLOPT_CONNECTTIMEOUT>(10L);

	// Send query
	try
	{
		LoggerCrawler::logDebug("Executing CURL query", __FILE__, __LINE__);
		easy.perform();
	}
	catch (curl::curl_easy_exception error)
	{
		LoggerCrawler::logWarn("CURL ran into a problem", __FILE__, __LINE__);
		error.print_traceback();
	}
	LoggerCrawler::logDebug("CURL query done", __FILE__, __LINE__);
	long responseCode = easy.get_info<CURLINFO_RESPONSE_CODE>().get();
	std::string type = easy.get_info<CURLINFO_CONTENT_TYPE>().get();

	if (responseCode != 200)
	{
		githubAPIResponse response;
		if (type.find("application/json") != std::string::npos)
		{
			JSON *json = JSON::parse(ss.str(), jsonHandler);
			std::string msg = json->get<std::string, std::string>("message");
			response = GithubClientErrorConverter::convertResponse(responseCode, msg);
			delete json;
		}
		else
		{
			response = GithubClientErrorConverter::convertResponse(responseCode, "");
		}
		handler->handle(response, __FILE__, __LINE__);
	}

	return JSON::parse(ss.str(), jsonHandler);
}

JSON *GithubInterface::getRequest(std::string query)
{
	return getRequest(query, &defaultHandler, &JSONSingletonErrorHandler::getInstance());
}

JSON* GithubInterface::getRequest(std::string query, GithubErrorThrowHandler* handler)
{
	return getRequest(query, handler, &JSONSingletonErrorHandler::getInstance());
}

JSON* GithubInterface::getRequest(std::string query, JSONErrorHandler* handler)
{
	return getRequest(query, &defaultHandler, handler);
}