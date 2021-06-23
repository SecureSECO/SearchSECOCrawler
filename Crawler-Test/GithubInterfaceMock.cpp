/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubInterface.h"
#include "pch.h"

class GithubInterfaceMock : public GithubInterface
{
  public:
	std::map<std::string, std::string> queryToJsonMap = std::map<std::string, std::string>();
	std::string defaultJSON;
	GithubInterfaceMock(std::string userAgent = "", std::string userPWD = "") : GithubInterface(userAgent, userPWD)
	{
	}

	JSON *getRequest(std::string query) override
	{
		if (queryToJsonMap.find(query) == queryToJsonMap.end())
		{
			return JSON::parse(defaultJSON);
		}
		else
		{
			return JSON::parse(queryToJsonMap[query]);
		}
	}

	JSON *getRequest(std::string query, GithubErrorThrowHandler *handler) override
	{
		return this->getRequest(query);
	}

	JSON *getRequest(std::string query, JSONErrorHandler *handler) override
	{
		return this->getRequest(query);
	}

	JSON *getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler *handler2) override
	{
		return this->getRequest(query);
	}
};