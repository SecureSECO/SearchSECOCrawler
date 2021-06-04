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

JSON* GithubInterface::getRequest(std::string query, GithubErrorThrowHandler *handler, bool errorShouldBeFatal = true)
{
	std::stringstream ss;
	curl::curl_ios<std::stringstream> writer(ss);

	curl::curl_easy easy(writer);

	// Set up data
	easy.add<CURLOPT_URL>(query.data());
	easy.add<CURLOPT_FOLLOWLOCATION>(1L);
	easy.add<CURLOPT_USERAGENT>(userAgent.data());
	easy.add<CURLOPT_USERPWD>(userPWD.data());

	// Send query
	try
	{
		LoggerCrawler::logDebug("Executing CURL query", __FILE__, __LINE__);
		easy.perform();
	}
	catch (curl::curl_easy_exception error)
	{
		LoggerCrawler::logWarn("CURL ran into a problem", __FILE__, __LINE__);
		auto errors = error.get_traceback();
		error.print_traceback();
	}
	long responseCode = easy.get_info<CURLINFO_RESPONSE_CODE>().get();
	githubAPIResponse response = GithubClientErrorConverter::convertResponse(responseCode);
	if (response != githubAPIResponse::OK)
	{
		handler->handle(response, __FILE__, __LINE__);
	}

	return JSON::parse(ss.str());
}

JSON *GithubInterface::getRequest(std::string query, bool errorShouldBeFatal = true)
{
	return getRequest(query, &defaultHandler, errorShouldBeFatal);
}
