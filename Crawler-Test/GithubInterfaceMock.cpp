#include "pch.h"
#include "GithubInterface.h"

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

	JSON* getRequest(std::string query, GithubErrorThrowHandler* handler) override
	{
		return this->getRequest(query);
	}
};