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
#include <future>
#include <thread>

JSON* GithubInterface::getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler *jsonHandler)
{
	std::stringstream ss;
	curl::curl_ios<std::stringstream> writer(ss);
	curl::curl_easy easy(writer);
	// Set up data
	addEasyInformation(query, easy);
	
	executeCurlQueryWithTimeout(easy);
	LoggerCrawler::logDebug("CURL query done", __FILE__, __LINE__);
	long responseCode = easy.get_info<CURLINFO_RESPONSE_CODE>().get();
	
	if (responseCode != 200)
	{
		handleGithubError(easy, ss, handler, jsonHandler);
	}

	return JSON::parse(ss.str(), jsonHandler);
}

void GithubInterface::executeCurlQueryWithTimeout(curl::curl_easy &easy)
{
	// Put the curl query in an async task to allow for a timeout.
	std::future<void> future = std::async(std::launch::async, [&easy]() {
		try
		{
			LoggerCrawler::logDebug("Executing CURL query", __FILE__, __LINE__);
			easy.perform();
		}
		catch (curl::curl_easy_exception error)
		{
			LoggerCrawler::logWarn("CURL ran into a problem", __FILE__, __LINE__);
			error.print_traceback();
			throw 0;
		}
	});
	std::future_status status;
	// Wait for the curl query to start and return a result.
	// If the status is 'deferred', then our async task has not yet started.
	do
	{
		status = future.wait_for(std::chrono::seconds(waitTime));
	} while (status == std::future_status::deferred);

	// If the status is not ready (and not deferred either as we have already started the curl query), 
	// we have a timeout.
	if (status != std::future_status::ready)
	{
		LoggerCrawler::logWarn("CURL ran into a timeout", __FILE__, __LINE__);
		throw 0;
	}
}

void GithubInterface::addEasyInformation(std::string query, curl::curl_easy &easy)
{
	easy.add<CURLOPT_URL>(query.data());
	easy.add<CURLOPT_FOLLOWLOCATION>(1L);
	easy.add<CURLOPT_USERAGENT>(userAgent.data());
	easy.add<CURLOPT_USERPWD>(userPWD.data());
}

void GithubInterface::handleGithubError(curl::curl_easy &easy, std::stringstream &ss, GithubErrorThrowHandler *handler,
					   JSONErrorHandler *jsonHandler)
{
	std::string type = easy.get_info<CURLINFO_CONTENT_TYPE>().get();
	long responseCode = easy.get_info<CURLINFO_RESPONSE_CODE>().get();
	githubAPIResponse response;

	// If the type is JSON, we received a message next to our code in JSON format.
	if (type.find("application/json") != std::string::npos)
	{
		JSON *json = JSON::parse(ss.str(), jsonHandler);
		std::string msg = json->get<std::string, std::string>("message");

		// Use the message we received besides the code to find out what exactly was the error we received.
		response = GithubClientErrorConverter::convertResponse(responseCode, msg);
		delete json;
	}
	else //Otherwise, we can just use the responsecode to see what has happened.
	{
		response = GithubClientErrorConverter::convertResponse(responseCode, "");
	}
	handler->handle(response, __FILE__, __LINE__);
} 

JSON *GithubInterface::getRequest(std::string query)
{
	return getRequest(query, &defaultHandler, &JSONSingletonErrorHandler::getInstance());
}

JSON* GithubInterface::getRequest(std::string query, GithubErrorThrowHandler* handler)
{
	return getRequest(query, handler, &JSONSingletonErrorHandler::getInstance());
}