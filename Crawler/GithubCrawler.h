/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "Crawler.h"
#include "GithubInterface.h"
#define listOfParseableLanguages {"C", "C++", "Java", "C#", "Python", "JavaScript" };

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


	/// <summary>
	/// Uses getOwnerAndRepo() to construct a repoUrl from a standard URL.
	/// </summary>
	/// <param name="url">The URL.</param>
	/// <returns>An URL to a repository.</returns>
	std::string getRepoUrl(std::string url);


	/// <summary>
	/// Get the number of stars of the given project.
	/// </summary>
	/// <param name="repoUrl">The project URL (with api. in front).</param>
	/// <returns>A number indicating the number of stars in the project.</returns>
	int getStars(std::string repoUrl, GithubErrorThrowHandler* handler);

	/// <summary>
	/// Gets the fraction of parseable lines of code to the total number of lines of code.
	/// </summary>
	/// <param name="repoUrl">The project URL (with api. in front).</param>
	/// <returns>The total number of parseable lines divided by the total number of lines, and 0 if the total is 0.</returns>
	std::pair<float, int> getParseableRatio(std::string repoUrl);

	/// <summary>
	/// Creates a project metadata variable and fills it with the necessary information.
	/// </summary>
	/// <param name="json">The JSON from which the data has to be taken.</param>
	/// <param name="ownerAndRepo">A tuple from which the owner and repository name can be found.</param>
	/// <returns>A project metadata variable.</returns>
	ProjectMetadata constructProjectMetadata(JSON* json, std::tuple<std::string, std::string> ownerAndRepo);

	/// <summary>
	/// Constructs a new githuberrorhandler that has the loggers of 403 and 404 replaced.
	/// </summary>
	GithubErrorThrowHandler* getCorrectGithubHandler();

	/// <summary>
	/// Constructs a new githuberrorhandler that has the logger of 422 replaced.
	/// </summary>
	GithubErrorThrowHandler* getGithubHandlerForJSONError();

	/// <summary>
	/// Constructs a new JSONErrorHandler that gives a warning for the parse error instead of an error.
	/// </summary>
	JSONErrorHandler* getCorrectJSONHandler();

public:
	GithubCrawler(GithubInterface *githubInterface)
	{
		this->githubInterface = std::unique_ptr<GithubInterface>(githubInterface);
	}

	GithubCrawler(std::string username, std::string token)
	{
		this->githubInterface = std::unique_ptr<GithubInterface>(
			new GithubInterface(username, token));
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

	/// <summary>
	/// Gets the importance measure of a given project.
	/// </summary>
	/// <param name="repoUrl">The project URL (with api. in front).</param>
	/// <returns>An int representing the importance measure.</returns>
	int getImportanceMeasure(int stars, std::pair<float, int> percentageAndBytes);
};
