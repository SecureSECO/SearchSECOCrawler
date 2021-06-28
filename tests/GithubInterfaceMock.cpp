/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

// Test includes.
#include "pch.h"
#include "GithubInterfaceMock.h"


JSON *GithubInterfaceMock::getRequest(std::string query)
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

JSON *GithubInterfaceMock::getRequest(std::string query, GithubErrorThrowHandler *handler)
{
	return this->getRequest(query);
}

JSON *GithubInterfaceMock::getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler *handler2)
{
	return this->getRequest(query);
}
