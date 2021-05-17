/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubCrawler.h"
std::vector<std::string> GithubCrawler::crawlRepositories()
{
	std::vector<std::string> vec;
	std::unique_ptr<JSON> json(githubInterface->getRequest("https://api.github.com/repositories"));
	for (int i = 0; i < 100; i++)
	{
		vec.push_back(json->get(std::to_string(i) + "/url"));
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
		std::unique_ptr<JSON> ownerData(githubInterface->getRequest(json->get("owner/url")));

		std::string email = ownerData->get("email");

		projectMetadata.authorName = ownername;
		projectMetadata.authorMail = email;
		projectMetadata.name = reponame;
		projectMetadata.url = json->get("html_url");
		projectMetadata.license = json->get("license/name");
		projectMetadata.version = json->get("pushed_at");
	}
	catch (int e)
	{
		code = e;
	}
	return projectMetadata;
}