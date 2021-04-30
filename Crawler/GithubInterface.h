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
	GithubInterface(std::string userAgent, std::string userPWD) 
	{
		this->userAgent = userAgent;
		this->userPWD = userPWD;
	}

	/// <summary>
	/// Requests data from Github and returns a pointer to a JSON variable.
	/// </summary>
	/// <param name="query">The query to be send to Github.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	JSON* getRequest(std::string query);

};

