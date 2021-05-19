/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "ProjectMetadata.h"
#include "RunCrawler.h"
#include <string>
#include <vector>

class Crawler
{
public:
	/// <summary>
	/// Finds URLs to spider. Currently not used.
	/// </summary>
	/// <returns>A vector of strings representing URLs.</returns>
	std::vector<std::string> crawlRepositories(CrawlableSource crawlableSource);

	/// <summary>
	/// Gets project metadata from the given repository URL. Currently not used.
	/// </summary>
	/// <param name="url">The url to a repository.</param>
	/// <returns>A project metadata file.</returns>
	ProjectMetadata getProjectMetadata(std::string url);
};
