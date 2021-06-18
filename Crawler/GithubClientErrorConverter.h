/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

#include "ErrorList.h"
#include <string>
class GithubClientErrorConverter
{
public:
	/// <summary>
	/// Converts most errors that can be received by using the github REST API and converts them into a readable format.
	/// </summary>
	/// <param name="code">The GitHub code to convert.</param>
	/// <returns>A githubAPIResponse enum.</returns>
	static githubAPIResponse convertResponse(long code, std::string message);
};