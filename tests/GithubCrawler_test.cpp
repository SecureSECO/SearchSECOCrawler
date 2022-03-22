/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

// Test includes.
#include "pch.h"

// Crawler includes.
#include "ErrorHandler.h"
#include "GithubCrawler.h"
#include "GithubInterfaceMock.h"


int finalVal()
{
	float percentage = (1.0 + 4.0 + 8.0 + 16.0) / 31.0;
	int stars = 50;
	int bytes = (int)(1.0 + 4.0 + 8.0 + 16.0);
	return 20000000 * percentage * std::log(stars + 1) * std::log(std::log(bytes + 1) + 1);
}

int finalTimeout(int i)
{
	int bytes = (i+1)*(1.0 + 4.0 + 8.0*20 + 16.0);
	int stars = 50;
	double maxTimeout = 1800000 + 800000 * sqrt(stars);

	return std::min((double)(180000 + 5000 * sqrt(bytes)), maxTimeout);
}

/*TEST(CrawlRepositoriesTest, TestBasic)
{
	std::string jsonString = "[";
	for (int i = 0; i < 100; i++)
	{
		std::string base = "{\"html_url\": \"" + std::to_string(i) + "\", \"id\": 25" + ", \"url\": \"fake_url\"}";

		if (i == 99)
		{
			jsonString.append(base);
		}
		else
		{
			jsonString.append(base + ", ");
		}
	}
	jsonString.append("]");
	std::string languagesString = R"({"C": 1, "Ruby": 2, "C#": 4, "Python": 8, "Java": 16})";
	std::string projectString = R"({"stargazers_count": 50})";
	GithubInterfaceMock *mock = new GithubInterfaceMock();
	mock->queryToJsonMap = {
		{"https://api.github.com/repositories?since=0", jsonString},
		{"fake_url", projectString},
	};
	mock->defaultJSON = languagesString;
	GithubCrawler githubCrawler(mock);
	CrawlData data = githubCrawler.crawlRepositories(0);
	int val = finalVal();
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(std::get<0>(data.URLImportanceList[i]), std::to_string(i));
		
		EXPECT_EQ(std::get<1>(data.URLImportanceList[i]), val);

		EXPECT_EQ(std::get<2>(data.URLImportanceList[i]), finalTimeout(i));
	}
}

TEST(CrawlRepositoriesTest, TestEnd)
{
	GithubInterfaceMock *mock = new GithubInterfaceMock();
	std::string jsonString =
		R"([{"html_url": "url1", "id": 50, "url": "fake_url"},
		{"html_url": "url2", "id": 150, "url": "fake_url"}, 
		{"html_url": "url3", "id": 250, "url": "fake_url"}])";
	std::string projectString = R"({"stargazers_count": 0})";
	std::string languagesString = R"({"C": 100000})";
	mock->queryToJsonMap = {
		{"https://api.github.com/repositories?since=0", jsonString},
		{"fake_url", projectString},
	};
	mock->defaultJSON = languagesString;
	GithubCrawler githubCrawler(mock);
	CrawlData data = githubCrawler.crawlRepositories(0);

	EXPECT_EQ(data.URLImportanceList.size(), 3);
	EXPECT_EQ(data.finalProjectId, 250);
}

TEST(CrawlRepositoriesTest, TestErrorThrow)
{
	GithubInterfaceMock *mock = new GithubInterfaceMock();
	mock->defaultJSON = R"({"invalid json code"})";
	GithubCrawler githubCrawler(mock);
	EXPECT_THROW(githubCrawler.crawlRepositories(0), int);
}*/

TEST(CrawlProjectMetadataTest, TestBasic)
{
	GithubInterfaceMock *mock = new GithubInterfaceMock();

	std::string baseJSONString =
		R"({"owner": {"url": "ownerInfoUrl"}, "license": {"name": "exampleLicense"}, 
		"html_url": "html_url_example.com", "pushed_at": "2002", "default_branch": "notMaster"})";
	std::string baseOwnerJSONString = R"({"email": "example@example.com"})";

	mock->queryToJsonMap = {
		{"https://api.github.com/repos/owner/repo", baseJSONString},
		{"ownerInfoUrl", baseOwnerJSONString},
	};
	GithubCrawler githubCrawler(mock);
	ProjectMetadata pm = githubCrawler.getProjectMetadata("example.com/owner/repo");
	EXPECT_EQ(pm.authorMail, "example@example.com");
	EXPECT_EQ(pm.authorName, "owner");
	EXPECT_EQ(pm.license, "exampleLicense");
	EXPECT_EQ(pm.name, "repo");
	EXPECT_EQ(pm.url, "html_url_example.com");
	EXPECT_EQ(pm.version, "2002");
	EXPECT_EQ(pm.defaultBranch, "notMaster");
}

TEST(CrawlProjectMetadataTest, TestErrorThrow)
{
	GithubInterfaceMock *mock = new GithubInterfaceMock();
	mock->defaultJSON = R"({"invalid json code"})";
	GithubCrawler githubCrawler(mock);
	EXPECT_THROW(githubCrawler.getProjectMetadata("example.com/owner/repo"), int);
}
