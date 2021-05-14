/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include <vector>
#include <string>
#include "ProjectMetadata.h"
#include "RunCrawler.h"

class Crawler
{
public:
	/// <summary>
	/// Finds URLs to spider.
	/// </summary>
	/// <returns>A vector of strings representing URLs.</returns>
	std::vector<std::string> crawlRepositories(CrawlableSource crawlableSource);

	/// <summary>
	/// Gets project metadata from the given URL.
	/// </summary>
	/// <returns>A project metadata file.</returns>
	ProjectMetadata getProjectMetadata(std::string url, int &code);
};

