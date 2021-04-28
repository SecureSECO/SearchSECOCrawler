/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include <vector>
#include <string>
#include "ProjectMetadata.h"
#include "GithubInterface.h"

enum class CrawlableSource
{
	NOT_IMPLEMENTED,
	GITLAB,
	GITHUB
};

class RunCrawler
{
private:
	GithubInterface githubInterface;

	/// <summary>
	/// Converts a URL to a CrawlableSource.
	/// </summary>
	/// <param name="">An URL.</param>
	/// <returns>A CrawlableSource.</returns>
	static CrawlableSource makeCrawlableSource(std::string)
	{

	}

public:
	/// <summary>
	/// Finds repositories that can be spidered. Entry point of the crawler.
	/// </summary>
	/// <param name="source">A source from which can be crawled.</param>
	/// <returns>A vector of strings representing URLs.</returns>
	static std::vector<std::string> crawlRepositories(CrawlableSource source)
	{
		std::vector<std::string> vec;
		return vec;
	}

	/// <summary>
	/// Finds project metadata.
	/// </summary>
	/// <param name="url">An URL to a project.</param>
	/// <returns>A string that represents a path to the project metadata file.</returns>
	static ProjectMetadata findMetadata(std::string url)
	{

	}
};

