#include "pch.h"
#include "GithubInterfaceMock.cpp"
#include <GithubCrawler.h>

TEST(CrawlRepositoriesTest, TestBasic)
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
	float percentage = (1.0 + 4.0 + 16.0) / 31.0;
	int stars = 50;
	int bytes = (int)(1.0 + 4.0 + 16.0);
	int finalval = 20000000 * percentage * std::log(stars + 1) * std::log(std::log(bytes + 1) + 1); 
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(data.URLImportanceList[i].first, std::to_string(i));
		EXPECT_EQ(data.URLImportanceList[i].second, finalval);
	}
}

TEST(CrawlRepositoriesTest, TestEnd)
{
	GithubInterfaceMock* mock = new GithubInterfaceMock();
	std::string jsonString = R"([{"html_url": "url1", "id": 50, "url": "fake_url"}, {"html_url": "url2", "id": 150, "url": "fake_url"}, {"html_url": "url3", "id": 250, "url": "fake_url"}])";
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
	GithubInterfaceMock* mock = new GithubInterfaceMock();
	mock->defaultJSON = R"({"invalid json code"})";
	GithubCrawler githubCrawler(mock);
	EXPECT_THROW(githubCrawler.crawlRepositories(0), int);
}

TEST(CrawlProjectMetadataTest, TestBasic)
{
	GithubInterfaceMock *mock = new GithubInterfaceMock();

	std::string baseJSONString =
		R"({"owner": {"url": "ownerInfoUrl"}, "license": {"name": "exampleLicense"}, "html_url": "html_url_example.com", "pushed_at": "2002", "default_branch": "notMaster"})";
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
	GithubInterfaceMock* mock = new GithubInterfaceMock();
	mock->defaultJSON = R"({"invalid json code"})";
	GithubCrawler githubCrawler(mock);
	EXPECT_THROW(githubCrawler.getProjectMetadata("example.com/owner/repo"), int);
}