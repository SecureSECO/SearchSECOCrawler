#include "GithubInterfaceMock.cpp"
#include "pch.h"
#include <GithubCrawler.h>

TEST(CrawlRepositoriesTest, TestBasic)
{
	std::string jsonString = "[";
	for (int i = 0; i < 100; i++)
	{
		std::string base = "{\"url\": \"" + std::to_string(i) + "\"}";
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
	std::vector<std::string> vec = githubCrawler.crawlRepositories();
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(vec[i], std::to_string(i));
	}
}

TEST(CrawlRepositoriesTest, TestErrorCode)
{
	GithubInterfaceMock *mock = new GithubInterfaceMock();
	mock->defaultJSON = R"({"invalid json code"})";
	GithubCrawler githubCrawler(mock);
	EXPECT_ANY_THROW(githubCrawler.crawlRepositories());
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
	int c = 0;
	ProjectMetadata pm = githubCrawler.getProjectMetadata("example.com/owner/repo", c);
	EXPECT_EQ(pm.authorMail, "example@example.com");
	EXPECT_EQ(pm.authorName, "owner");
	EXPECT_EQ(pm.license, "exampleLicense");
	EXPECT_EQ(pm.name, "repo");
	EXPECT_EQ(pm.url, "html_url_example.com");
	EXPECT_EQ(pm.version, "2002");
}

TEST(CrawlProjectMetadataTest, TestErrorCode)
{
	GithubInterfaceMock *mock = new GithubInterfaceMock();
	mock->defaultJSON = R"({"invalid json code"})";
	GithubCrawler githubCrawler(mock);
	int c = 0;
	ProjectMetadata pm = githubCrawler.getProjectMetadata("example.com/owner/repo", c);
	EXPECT_EQ(c, 1);
}