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

CrawlData RunCrawler::crawlRepositories(std::string const& url, int start, int &code)
{
	loguru::set_thread_name(THREAD_NAME);

	CrawlData data;
	switch (makeCrawlableSource(url))
	{
	case CrawlableSource::NOT_IMPLEMENTED:
		return data;
	case CrawlableSource::GITHUB:
	{
		try
		{
			GithubCrawler githubCrawler;
			CrawlData data = githubCrawler.crawlRepositories(start);
			return data;
		}
		catch (int e)
		{
			code = e;
		}
	}
	default:
		return data;
	}
}

ProjectMetadata RunCrawler::findMetadata(std::string const& url, int &code)
{
	loguru::set_thread_name(THREAD_NAME);

	switch (makeCrawlableSource(url))
	{
	case CrawlableSource::GITHUB:
		try
		{
			GithubCrawler githubCrawler;
			ProjectMetadata p = githubCrawler.getProjectMetadata(url);
			return p;
		}
		catch (int e)
		{
			code = e;
		}
	default:
		return ProjectMetadata();
	}
}
