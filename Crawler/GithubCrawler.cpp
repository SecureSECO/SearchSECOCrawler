/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubCrawler.h"
#include <iostream>
CrawlData GithubCrawler::crawlRepositories(int start)
{
	auto strStart = std::to_string(start);

	LoggerCrawler::logDebug("Starting crawling at index " + strStart, __FILE__, __LINE__);
	CrawlData crawlData;
	int currentId;
	std::unique_ptr<JSON> json(githubInterface->getRequest("https://api.github.com/repositories?since=" + strStart));
	
	int progress,
		previousLog = 0,
		percentageSteps = 10;
	
	int length = json->length();
	int bound = std::min(length, maxResultsPerPage);
	for (int i = 0; i < bound; i++)
	{
		progress = (i / double(maxResultsPerPage)) * 100;
		if (previousLog + percentageSteps < progress)
		{
			previousLog += percentageSteps;
			LoggerCrawler::logInfo(std::to_string(previousLog) + "% done...", __FILE__, __LINE__);
		}

		JSON branch = json->branch(i);
		currentId = branch.get<std::string, int>("id", true);
		std::string url = branch.get<std::string, std::string>("html_url", true);
		std::string repoUrl = branch.get<std::string, std::string>("url", true);
		crawlData.URLImportanceList.push_back(std::make_pair(url, getImportanceMeasure(repoUrl)));

	}
	LoggerCrawler::logInfo("100% done, finished crawling one page (" + std::to_string(maxResultsPerPage) + " repositories)", __FILE__, __LINE__);
	crawlData.finalProjectId = currentId;
	return crawlData;
}

std::tuple<std::string, std::string> GithubCrawler::getOwnerAndRepo(std::string const& url)
{
	std::vector<std::string> split = Utility::split(url, '/');
	int segCount = split.size();

	std::string ownername = split[segCount - 2];
	std::string reponame = split[segCount - 1];

	return std::tuple<std::string, std::string>{ownername, reponame};
}

ProjectMetadata GithubCrawler::getProjectMetadata(std::string url)
{
	LoggerCrawler::logDebug("Finding owner and repository...", __FILE__, __LINE__);
	std::tuple<std::string, std::string> ownerAndRepo = getOwnerAndRepo(url);
	std::string ownername = std::get<0>(ownerAndRepo);
	std::string reponame = std::get<1>(ownerAndRepo);

	std::string repoUrl = "https://api.github.com/repos/" + ownername + "/" + reponame;


	ProjectMetadata projectMetadata = ProjectMetadata();
	// Get information about repoUrl.
	LoggerCrawler::logDebug("Getting information about the repository...", __FILE__, __LINE__);
	std::unique_ptr<JSON> json(githubInterface->getRequest(repoUrl));

	// Get information about owner.
	JSON branch = json->branch("owner");
	LoggerCrawler::logDebug("Getting information about the owner...", __FILE__, __LINE__);
	std::unique_ptr<JSON> ownerData(githubInterface->getRequest(branch.get<std::string, std::string>("url")));

	std::string email = ownerData->get<std::string, std::string>("email");

	projectMetadata.authorName = ownername;
	projectMetadata.authorMail = email;
	projectMetadata.name = reponame;
	projectMetadata.url = json->get<std::string, std::string>("html_url", true);
	if (json->exists("license"))
	{
		projectMetadata.license = json->branch("license").get<std::string, std::string>("name");
	}
	else
	{
		projectMetadata.license = "";
	}
	projectMetadata.version = json->get<std::string, std::string>("pushed_at");
	projectMetadata.defaultBranch = json->get<std::string, std::string>("default_branch");
	LoggerCrawler::logInfo("Successfully found all relevant metadata, returning.", __FILE__, __LINE__);
	return projectMetadata;
}

int GithubCrawler::getImportanceMeasure(std::string repoUrl)
{
	int stars = getStars(repoUrl);
	std::pair<float, int> parseable = getParseableRatio(repoUrl);
	return 20000000 * std::get<0>(parseable) * std::log(stars + 1) * std::log(std::log(std::get<1>(parseable) + 1) + 1);
}

int GithubCrawler::getStars(std::string repoUrl)
{
	std::unique_ptr<JSON> json(githubInterface->getRequest(repoUrl));
	return json->get<std::string, int>("stargazers_count");
}

std::pair<float, int> GithubCrawler::getParseableRatio(std::string repoUrl)
{
	std::string languagesUrl = repoUrl + "/languages";
	std::unique_ptr<JSON> json(githubInterface->getRequest(languagesUrl));
	std::vector<std::string> listOfParseableLanguages = {"C", "C++", "Java", "C#"};
	int total = 0;
	int parseable = 0;
	int length = json->length();
	for (int i = 0; i < length; i++)
	{
		total += json->getIndex<int>(i);
	}
	for (std::string language : listOfParseableLanguages)
	{
		if (json->exists(language))
		{
			parseable += json->get<std::string, int>(language);
		}
	}
	if (total != 0)
	{
		return std::pair((float) ((float) (parseable) / (float) (total)), parseable);
	}
	return std::pair(0.0, 0);
}
