/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "RunCrawler.h"
#include "GithubCrawler.h"
#include "GithubInterface.h"
#include "Utility.h"
#include <sstream>

#define THREAD_NAME "crawler"

CrawlableSource RunCrawler::makeCrawlableSource(std::string const &url)
{
	if (url.find("github") != std::string::npos)
	{
		return CrawlableSource::GITHUB;
	}
	else
	{
		return CrawlableSource::NOT_IMPLEMENTED;
	}
}

CrawlData RunCrawler::crawlRepositories(std::string const &url, int start, std::string username, std::string token)
{
	loguru::set_thread_name(THREAD_NAME);

	CrawlData data;
	data.finalProjectId = start;

	if (username == "" || token == "")
	{
		LoggerCrawler::logWarn("No valid github authentication supplied", __FILE__, __LINE__);
		return data;
	}

	switch (makeCrawlableSource(url))
	{
	case CrawlableSource::NOT_IMPLEMENTED:
	{
		LoggerCrawler::logWarn("URL \"" + url + "\" is from an unsupported source", __FILE__, __LINE__);
		errno = 0;
		return data;
	}
	case CrawlableSource::GITHUB:
	{
		LoggerCrawler::logDebug("Detected GitHub as the source to crawl repositories from", __FILE__, __LINE__);
		try
		{
			GithubCrawler githubCrawler(username, token);
			CrawlData data = githubCrawler.crawlRepositories(start);
			LoggerCrawler::logInfo("Returning successful", __FILE__, __LINE__);
			return data;
		}
		catch (int e)
		{
			LoggerCrawler::logInfo("Returning empty", __FILE__, __LINE__);
			errno = e;
			return data;
		}
	}
	default:
	{
		LoggerCrawler::logInfo("Returning empty", __FILE__, __LINE__);
		errno = 1;
		return data;
	}
	}
}

ProjectMetadata RunCrawler::findMetadata(std::string const &url, std::string username, std::string token)
{
	loguru::set_thread_name(THREAD_NAME);

	if (username == "" || token == "")
	{
		LoggerCrawler::logWarn("No valid github authentication supplied", __FILE__, __LINE__);
		return ProjectMetadata();
	}

	LoggerCrawler::logInfo("Finding metadata for the repository at \"" + url + "\"", __FILE__, __LINE__);

	switch (makeCrawlableSource(url))
	{
	case CrawlableSource::GITHUB:
		try
		{
			LoggerCrawler::logDebug("Detected GitHub as the source of the repository", __FILE__, __LINE__);

			GithubCrawler githubCrawler(username, token);
			ProjectMetadata p = githubCrawler.getProjectMetadata(url);
			errno = 0;
			return p;
		}
		catch (int e)
		{
			LoggerCrawler::logInfo("Returning empty", __FILE__, __LINE__);
			errno = e;
			return ProjectMetadata();
		}
	default:
		LoggerCrawler::logWarn("URL \"" + url + "\" is from an unsupported source. Returning empty", __FILE__,
							   __LINE__);
		errno = 1;
		return ProjectMetadata();
	}
}
