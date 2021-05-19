/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubCrawler.h"
#include <iostream>
std::vector<std::string> GithubCrawler::crawlRepositories(int start)
{
	std::vector<std::string> vec;
	std::unique_ptr<JSON> json(githubInterface->getRequest("https://api.github.com/repositories?since=" + std::to_string(start)));
	for (int i = 0; i < 100; i++)
	{
		if (json->get<int>(std::to_string(i) + "/id", true) < start + 100)
		{
			std::string url = json->get<std::string>(std::to_string(i) + "/url", true);
			vec.push_back(url);
			std::cout << url << std::endl;
		}
		else
		{
			break;
		}
	}

	return vec;
}

std::tuple<std::string, std::string> GithubCrawler::getOwnerAndRepo(std::string url)
{
	std::vector<std::string> split = Utility::split(url, '/');
	int segCount = split.size();

	std::string ownername = split[segCount - 2];
	std::string reponame = split[segCount - 1];

	return std::tuple<std::string, std::string>{ownername, reponame};
}

ProjectMetadata GithubCrawler::getProjectMetadata(std::string url, int &code)
{
	std::tuple<std::string, std::string> ownerAndRepo = getOwnerAndRepo(url);
	std::string ownername = std::get<0>(ownerAndRepo);
	std::string reponame = std::get<1>(ownerAndRepo);

	std::string repoUrl = "https://api.github.com/repos/" + ownername + "/" + reponame;

	JSON json;
	JSON ownerData;
	ProjectMetadata projectMetadata = ProjectMetadata();
	try
	{
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
	}
	catch (int e)
	{
		code = e;
	}
	return projectMetadata;
}