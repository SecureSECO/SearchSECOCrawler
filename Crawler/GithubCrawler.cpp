/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubCrawler.h"
std::vector<std::string> GithubCrawler::crawlRepositories()
{
	JSON json;
	std::vector<std::string> vec;
	try
	{
		json = *githubInterface->getRequest("https://api.github.com/repositories");
		for (int i = 0; i < 100; i++)
		{
			vec.push_back(json.get(std::to_string(i) + "/url"));
		}
	}
	catch (int e)
	{
		throw e;
	}

	return vec;
}