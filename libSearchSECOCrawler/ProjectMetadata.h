/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include <string>

/// <summary>
/// A struct having fields for all the data that we need from a GitHub repository.
/// </summary>
struct ProjectMetadata
{
	std::string version;
	std::string license;
	std::string name;
	std::string url;
	std::string authorName;
	std::string authorMail;
	std::string defaultBranch;
};