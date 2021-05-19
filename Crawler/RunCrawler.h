/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "ProjectMetadata.h"
#include <string>
#include <vector>

enum class CrawlableSource
{
	NOT_IMPLEMENTED,
	GITLAB,
	GITHUB
};

class RunCrawler
{
private:
	/// <summary>
	/// Converts an URL to a CrawlableSource.
	/// </summary>
	/// <param name="url">An URL.</param>
	/// <returns>A CrawlableSource.</returns>
	static CrawlableSource makeCrawlableSource(std::string const& url);

public:
	/// <summary>
	/// Finds repositories that can be spidered. Entry point of the crawler.
	/// </summary>
	/// <param name="url">An URL to the site from which needs to be crawled.</param>
	/// <param name="start">The start project ID.</param>
	/// <param name="code">A code, where 0 indicates that this function succeeded and 1 indicates a failure.</param>
	/// <returns>A list of urls.</returns>
	static std::vector<std::string> crawlRepositories(std::string const &url, int start, int &code);

	/// <summary>
	/// Finds project metadata.
	/// </summary>
	/// <param name="url">An URL to a project.</param>
	/// <returns>A string that represents a path to the project metadata file.</returns>
	static ProjectMetadata findMetadata(std::string const& url, int &code);
};
