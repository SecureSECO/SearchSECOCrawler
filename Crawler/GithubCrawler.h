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
    GithubInterface* githubInterface;
public:
    GithubCrawler(GithubInterface* githubInterface)
    {
        this->githubInterface = githubInterface;
    }

    std::vector<std::string> crawlRepositories()
    {
        JSON *json = githubInterface->getRequest("https://api.github.com/repositories");
        JSON josn = *json;
        std::vector<std::string> vec;
        for (int i = 0; i < 100; i++)
        {
            vec.push_back(josn.get(std::to_string(i) + "/url"));
        }
        return vec;
    }

};

