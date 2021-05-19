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

CrawlableSource RunCrawler::makeCrawlableSource(std::string)
{
	return CrawlableSource::GITHUB;
}

std::vector<std::string> RunCrawler::crawlRepositories(std::string url, int start, int &code)
{
	std::vector<std::string> vec;
	switch (makeCrawlableSource(url))
	{
	case CrawlableSource::NOT_IMPLEMENTED:
		return vec;
	case CrawlableSource::GITHUB:
	{
		try
		{
			GithubCrawler githubCrawler;
			std::vector<std::string> urls = githubCrawler.crawlRepositories(start);
			return urls;
		}
		catch (int e)
		{
			code = e;
		}
	}
	default:
		return vec;
	}
}

ProjectMetadata RunCrawler::findMetadata(std::string url, int &code)
{
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
