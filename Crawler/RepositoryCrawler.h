/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include <vector>
#include "RunCrawler.h"
#include "GithubInterface.h"
class RepositoryCrawler
{
private:
	GithubInterface *githubInterface;
public:
	/// <summary>
	/// Returns a list of URLs to be crawled.
	/// </summary>
	/// <param name="crawlableSource">The source which needs to be crawled.</param>
	/// <returns>A list of URLs.</returns>
	std::vector<std::string> crawlRepositories(CrawlableSource crawlableSource);
	RepositoryCrawler(GithubInterface* githubInterface) 
	{
		this->githubInterface = githubInterface;
	}
};

