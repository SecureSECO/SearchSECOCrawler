/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "Crawler.h"
#include "GithubInterface.h"

class GithubCrawler : public Crawler
{
private:
	GithubInterface* githubInterface;
public:
	GithubCrawler(GithubInterface* githubInterface)
	{
		this->githubInterface = githubInterface;
	}

	/// <summary>
	/// Returns a list of repositories.
	/// </summary>
	/// <returns>A vector consisting of strings representing URLs to repositories.</returns>
	std::vector<std::string> crawlRepositories();

};

