/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "Crawler.h"
#include "GithubInterface.h"

class GithubCrawler : public Crawler
{
private:
	const int maxResultsPerPage = 100;
	std::unique_ptr<GithubInterface> githubInterface;

	/// <summary>
	/// Gets the owner and repository name from a given URL.
	/// </summary>
	/// <param name="url">The URL from which the owner and repository name should be retrieved.</param>
	/// <returns>A tuple consisting of the owner name and repository name in place one and two respectively.</returns>
	std::tuple<std::string, std::string> getOwnerAndRepo(std::string const& url);

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
	/// Returns a list of repositories based on a start project ID.
	/// Returns all the repositories with project ID in the interval [projectID, projectID+100)
	/// </summary>
	/// <param name="start">The start project ID.</param>
	/// <returns>A vector consisting of strings representing URLs to repositories.</returns>
	CrawlData crawlRepositories(int start);

	/// <summary>
	/// Gets project metadata from the given repository URL.
	/// </summary>
	/// <param name="url">The url to a repository.</param>
	/// <returns>A project metadata file.</returns>
	ProjectMetadata getProjectMetadata(std::string url);
};
