/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

// Crawler includes.
#include "CrawlData.h"
#include "ProjectMetadata.h"


enum class CrawlableSource
{
	NOT_IMPLEMENTED,
	GITLAB,
	GITHUB
};

/// <summary>
/// The entry point of the Crawler.
/// </summary>
class RunCrawler
{
private:
	/// <summary>
	/// Converts an URL to a CrawlableSource.
	/// </summary>
	/// <param name="url">An URL.</param>
	/// <returns>A CrawlableSource.</returns>
	static CrawlableSource makeCrawlableSource(std::string const& url);

	/// <summary>
	/// Crawls projects from GitHub.
	/// </summary>
	/// <param name="data">The basic CrawlData in case of an error.</param>
	/// <param name="start">The start id we have to crawl from.</param>
	/// <param name="username">The username.</param>
	/// <param name="token">The GitHub token.</param>
	/// <returns>Data containing a list of pairs consisiting of one URL and one priority measure,
	/// and an int representing the final project ID we have crawled.</returns>
	static CrawlData crawlGithub(CrawlData data, int start, std::string username, std::string token);

	/// <summary>
	/// Finds metadata from projects on GitHub.
	/// </summary>
	/// <param name="url">The URL to find this metadata from.</param>
	/// <param name="username">The username.</param>
	/// <param name="token">The GitHub token.</param>
	/// <returns>ProjectMetadata from this specific GitHub repository.</returns>
	static ProjectMetadata findMetadataFromGithub(std::string const &url, std::string username, std::string token);

public:
	/// <summary>
	/// Finds repositories that can be spidered.
	/// </summary>
	/// <param name="url">An URL to the site from which needs to be crawled.</param>
	/// <param name="start">The start project ID.</param>
	/// <param name="username">GitHub username.</param>
	/// <param name="token">GitHub authentication token.</param>
	/// <returns>A list of urls, together with their importance measure (represented by an int),
	/// and a final project ID.</returns>
	static CrawlData crawlRepositories(std::string const &url, int start, std::string username, std::string token);

	/// <summary>
	/// Finds project metadata.
	/// </summary>
	/// <param name="url">An URL to a project.</param>
	/// <param name="username">GitHub username.</param>
	/// <param name="token">GitHub authentication token.</param>
	/// <returns>A string that represents a path to the project metadata file.</returns>
	static ProjectMetadata findMetadata(std::string const &url, std::string username, std::string token);

};
