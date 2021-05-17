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
	std::unique_ptr<GithubInterface> githubInterface;
	std::tuple<std::string, std::string> getOwnerAndRepo(std::string url);

public:
	GithubCrawler(GithubInterface *githubInterface)
	{
		this->githubInterface = std::unique_ptr<GithubInterface>(githubInterface);
	}

	GithubCrawler()
	{
		this->githubInterface = std::unique_ptr<GithubInterface>(
			new GithubInterface("SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b"));
	}

	/// <summary>
	/// Returns a list of repositories.
	/// </summary>
	/// <returns>A vector consisting of strings representing URLs to repositories.</returns>
	std::vector<std::string> crawlRepositories();

	ProjectMetadata getProjectMetadata(std::string url, int &code);
};
