/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

// External includes.
#include <string>
#include <vector>
#include <map>


/// <summary>
/// Data which is returned when crawling. First value in the pair is the URL found,
/// second is the importance of the given URL. The finalProjectId is the last project ID found while crawling.
/// </summary>
struct CrawlData
{
	std::vector<std::pair<std::string, int>> URLImportanceList;
	std::map<std::string, int> languages;
	int finalProjectId;
};
