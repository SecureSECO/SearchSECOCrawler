/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubCrawler.h"
#include <iostream>
CrawlData GithubCrawler::crawlRepositories(int start)
{
	CrawlData crawlData;
	int currentId;
	std::unique_ptr<JSON> json(githubInterface->getRequest("https://api.github.com/repositories?since=" + std::to_string(start)));
	for (int i = 0; i < json->length(); i++)
	{
		if (!json->isEmpty(i))
		{
			JSON branch = json->branch(i);
			currentId = branch.get<std::string, int>("id", true);
			std::string url = branch.get<std::string, std::string>("html_url", true);
			std::string repoUrl = branch.get<std::string, std::string>("url", true);
			crawlData.URLImportanceList.push_back(std::make_pair(url, getImportanceMeasure(repoUrl)));
		}
		else
		{
			break;
		}
	}
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
	std::tuple<std::string, std::string> ownerAndRepo = getOwnerAndRepo(url);
	std::string ownername = std::get<0>(ownerAndRepo);
	std::string reponame = std::get<1>(ownerAndRepo);

	std::string repoUrl = "https://api.github.com/repos/" + ownername + "/" + reponame;


	ProjectMetadata projectMetadata = ProjectMetadata();
	// Get information about repoUrl.
	std::unique_ptr<JSON> json(githubInterface->getRequest(repoUrl));

	// Get information about owner.
	JSON branch = json->branch("owner");
	std::unique_ptr<JSON> ownerData(githubInterface->getRequest(json->branch("owner").get<std::string, std::string>("url")));

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
	return projectMetadata;
}

int GithubCrawler::getImportanceMeasure(std::string repoUrl)
{
	int stars = getStars(repoUrl);
	float parseable = getParseableRatio(repoUrl);
	time_t now = time(0);
	return std::floor(stars * parseable);
}

int GithubCrawler::getStars(std::string repoUrl)
{
	std::unique_ptr<JSON> json(githubInterface->getRequest(repoUrl));
	return json->get<std::string, int>("stargazers_count");
}

float GithubCrawler::getParseableRatio(std::string repoUrl)
{
	std::string languagesUrl = repoUrl + "/languages";
	std::unique_ptr<JSON> json(githubInterface->getRequest(languagesUrl));
	std::vector<std::string> listOfParseableLanguages = {"C", "C++", "Java", "Python"};
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
		return (float) ((float) (parseable) / (float) (total));
	}
	return 0;
}