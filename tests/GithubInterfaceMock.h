/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

// Crawler includes.
#include "GithubInterface.h"

class GithubInterfaceMock : public GithubInterface
{
public:
	std::map<std::string, std::string> queryToJsonMap = std::map<std::string, std::string>();
	std::string defaultJSON;

	GithubInterfaceMock(std::string userAgent = "", std::string userPWD = "") : GithubInterface(userAgent, userPWD) {}

	JSON *getRequest(std::string query) override;

	JSON *getRequest(std::string query, GithubErrorThrowHandler *handler) override;

	JSON *getRequest(std::string query, GithubErrorThrowHandler *handler, JSONErrorHandler *handler2) override;
};
