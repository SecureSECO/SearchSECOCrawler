/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

// Crawler includes.
#include "ErrorList.h"

// External includes.
#include <string>
#include <vector>


class Utility
{
public:
	/// <summary>
	/// Splits the function based on the delimiter in multiple strings.
	/// </summary>
	/// <param name="string">The string to be splitted.</param>
	/// <param name="delimiter">The delimiter defining where needs to be splitted.</param>
	/// <returns>A vector of strings.</returns>
	static std::vector<std::string> split(std::string string, char delimiter);

	/// <summary>
	/// Converts an enum to a specific code so that we can specify that code in the error message.
	/// </summary>
	/// <param name="response">The GitHub error.</param>
	/// <returns>An int representing an error code.</returns>
	static int getCode(githubAPIResponse response)
	{
		return (int)response;
	}

	/// <summary>
	/// Converts an enum to a specific code so that we can specify that code in the error message.
	/// </summary>
	/// <param name="response">The JSON error.</param>
	/// <returns>An int representing an error code.</returns>
	static int getCode(JSONError error)
	{
		return (int)error + getCode(githubAPIResponse::count);
	}
};
