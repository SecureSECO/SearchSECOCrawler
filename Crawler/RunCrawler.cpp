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

CrawlableSource RunCrawler::makeCrawlableSource(std::string const& url)
{
	return CrawlableSource::GITHUB;
}

CrawlData RunCrawler::crawlRepositories(std::string const& url, int start)
{
	loguru::set_thread_name(THREAD_NAME);

	CrawlData data;
	switch (makeCrawlableSource(url))
	{
	case CrawlableSource::NOT_IMPLEMENTED:
	{
		LoggerCrawler::logWarn("URL \"" + url + "\" is from an unsupported source", __FILE__, __LINE__);
		return data;
	}
	case CrawlableSource::GITHUB:
	{
		LoggerCrawler::logDebug("Detected GitHub as the source to crawl repositories from", __FILE__, __LINE__);
		try
		{
			GithubCrawler githubCrawler;
			CrawlData data = githubCrawler.crawlRepositories(start);
			return data;
		}
		catch (int e)
		{
			errno = e;
			return data;
		}
	}
	default:
		return data;
	}
}

ProjectMetadata RunCrawler::findMetadata(std::string const& url)
{
	loguru::set_thread_name(THREAD_NAME);

	LoggerCrawler::logInfo("Finding metadata for the repository at \"" + url + "\"", __FILE__, __LINE__);

	switch (makeCrawlableSource(url))
	{
	case CrawlableSource::GITHUB:
		try
		{
			LoggerCrawler::logDebug("Detected GitHub as the source of the repository", __FILE__, __LINE__);

			GithubCrawler githubCrawler;
			ProjectMetadata p = githubCrawler.getProjectMetadata(url);
			return p;
		}
		catch (int e)
		{
			errno = e;
			LoggerCrawler::logInfo("Returning empty", __FILE__, __LINE__);
			return ProjectMetadata();
		}
	default:
		LoggerCrawler::logWarn("URL \"" + url + "\" is from an unsupported source. Returning empty", __FILE__, __LINE__);
		return ProjectMetadata();
	}
}
