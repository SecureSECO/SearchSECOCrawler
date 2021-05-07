/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include <string>
struct ProjectMetadata
{
	std::string version;
	std::string license;
	std::string name;
	std::string url;
	std::string authorName;
	std::string authorMail;

	/// <summary>
	/// Converts this ProjectMetadata to a string.
	/// </summary>
	/// <returns>A string representing the project metadata. </returns>
	std::string toString();
};