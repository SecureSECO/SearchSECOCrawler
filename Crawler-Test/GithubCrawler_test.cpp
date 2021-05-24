#include "pch.h"
#include "GithubInterfaceMock.cpp"
#include <GithubCrawler.h>

TEST(CrawlRepositoriesTest, TestBasic)
{
	std::string jsonString = "[";
	for (int i = 0; i < 100; i++)
	{
		std::string base = "{\"html_url\": \"" + std::to_string(i) + "\", \"id\": 1}";

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
	GithubInterfaceMock *mock = new GithubInterfaceMock();
	mock->defaultJSON = jsonString;
	GithubCrawler githubCrawler(mock);
	CrawlData data = githubCrawler.crawlRepositories(0);
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(data.URLImportanceList[i].first, std::to_string(i));
	}
}

TEST(CrawlRepositoriesTest, TestEnd)
{
	GithubInterfaceMock* mock = new GithubInterfaceMock();
	mock->defaultJSON = R"([{"html_url": "url1", "id": 50}, {"html_url": "url2", "id": 150}, {"html_url": "url3", "id": 250}])";
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
		R"({"owner": {"url": "ownerInfoUrl"}, "license": {"name": "exampleLicense"}, "html_url": "html_url_example.com", "pushed_at": "2002"})";
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
}

TEST(CrawlProjectMetadataTest, TestErrorThrow)
{
	GithubInterfaceMock* mock = new GithubInterfaceMock();
	mock->defaultJSON = R"({"invalid json code"})";
	GithubCrawler githubCrawler(mock);
	EXPECT_THROW(githubCrawler.getProjectMetadata("example.com/owner/repo"), int);
}