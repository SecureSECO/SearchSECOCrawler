#pragma once
#include <vector>
#include "RunCrawler.h"
#include "GithubInterface.h"
class RepositoryCrawler
{
private:
	GithubInterface *githubInterface;
public:
	std::vector<std::string> crawlRepositories(CrawlableSource crawlableSource);
	RepositoryCrawler(GithubInterface* githubInterface) {
		this->githubInterface = githubInterface;

	}
};

