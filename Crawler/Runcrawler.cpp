/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "RepositoryCrawler.h"
#include "RunCrawler.h"

CrawlableSource RunCrawler::makeCrawlableSource(std::string)
{
    return CrawlableSource::NOT_IMPLEMENTED;
}
std::vector<std::string> RunCrawler::crawlRepositories(CrawlableSource source)
{
	RepositoryCrawler repositoryCrawler(new GithubInterface("SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b"));
	std::vector<std::string> vec;
	return vec;
}

ProjectMetadata RunCrawler::findMetadata(std::string url)
{

    // Split url into parts
    std::stringstream inp;
    inp.str(url);
    std::vector<std::string> split;
    std::string seg;
    while (std::getline(inp, seg, '/'))
    {
        split.push_back(seg);
    }
    int segCount = split.size();

    // Get owner and repo name
    std::string ownername = split[segCount - 2];
    std::string reponame = split[segCount - 1];

    std::string repoUrl = "https://api.github.com/repos/" + ownername + "/" + reponame;


    GithubInterface *githubInterface = new GithubInterface("SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b");
    auto json = githubInterface->getRequest(repoUrl);
    auto ownerData = githubInterface->getRequest(json->get("owner/url"));
    std::string email = "";
    if (ownerData->get("email") != "")
    {
        email = ownerData->get("email");
    }

    ProjectMetadata *projectMetadata = new ProjectMetadata();
    projectMetadata->authorName = ownername;
    projectMetadata->authorMail = email;
    projectMetadata->name = reponame;
    projectMetadata->url = json->get("html_url");
    projectMetadata->license = json->get("license/name");
    projectMetadata->version = json->get("updated_at");
    return *projectMetadata;
}
