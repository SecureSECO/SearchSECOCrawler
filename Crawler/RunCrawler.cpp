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

std::vector<std::string> RunCrawler::crawlRepositories(CrawlableSource source, int &code)
{
	std::vector<std::string> vec;
	switch (source)
	{
	case CrawlableSource::NOT_IMPLEMENTED:
		return vec;
	case CrawlableSource::GITHUB:
	{
		try
		{
			GithubCrawler githubCrawler;
			return githubCrawler.crawlRepositories();
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
			return githubCrawler.getProjectMetadata(url, code);
		}
		catch (int e)
		{
			code = e;
		}
	default:
		return ProjectMetadata();
	}
}
