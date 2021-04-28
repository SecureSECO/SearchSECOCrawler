/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include <string>
#include "JSON.h"
class GithubInterface
{
private:
	std::string userAgent;
	std::string userPWD;
public:
	GithubInterface(std::string userAgent, std::string userPWD) {
		this->userAgent = userAgent;
		this->userPWD = userPWD;
	}

	/// <summary>
	/// Returns the JSON pointer.
	/// </summary>
	/// <param name="query"></param>
	/// <returns></returns>
	JSON* getRequest(std::string query);

};

