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
	for (int i = 0; i < maxResultsPerPage; i++)
	{
		if (!json->isEmpty(std::to_string(i)))
		{
			currentId = json->get<int>(std::to_string(i) + "/id", true);
			std::string url = json->get<std::string>(std::to_string(i) + "/url", true);
			crawlData.URLImportanceList.push_back(std::make_pair(url, 1));
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
	std::unique_ptr<JSON> ownerData(githubInterface->getRequest(json->get<std::string>("owner/url")));

	std::string email = ownerData->get<std::string>("email");

	projectMetadata.authorName = ownername;
	projectMetadata.authorMail = email;
	projectMetadata.name = reponame;
	projectMetadata.url = json->get<std::string>("html_url");
	projectMetadata.license = json->get<std::string>("license/name");
	projectMetadata.version = json->get<std::string>("pushed_at");
	return projectMetadata;
}