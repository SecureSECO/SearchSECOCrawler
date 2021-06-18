#include "pch.h"
#include "RunCrawler.h"
#include <GithubCrawler.h>
#include <string>
#include <chrono>
#include "GithubInterface.h"
const static std::string repoBaseUrl = "https://api.github.com/repos/crawlerintegrationtesting/";
const static std::string emptyRepoUrl = repoBaseUrl + "emptyproject";
const static std::string projectWithCode = repoBaseUrl + "notemptyproject";

TEST(CrawlProjectMetadataTest, TestLiveEmptyProject)
{
	ProjectMetadata projectMetadata = RunCrawler::findMetadata(emptyRepoUrl, "SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b");
	EXPECT_EQ(projectMetadata.authorMail, "");
	EXPECT_EQ(projectMetadata.authorName, "crawlerintegrationtesting");
	EXPECT_EQ(projectMetadata.defaultBranch, "main");
	EXPECT_EQ(projectMetadata.license, "");
	EXPECT_EQ(projectMetadata.name, "emptyproject");
	EXPECT_EQ(projectMetadata.url, "https://github.com/crawlerintegrationtesting/emptyproject");
	EXPECT_EQ(projectMetadata.version, "2021-05-31T11:25:39Z");
}

TEST(CrawlProjectMetadataTest, TestLiveNonEmptyProject)
{
	ProjectMetadata projectMetadata = RunCrawler::findMetadata(projectWithCode, "SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b");
	EXPECT_EQ(projectMetadata.authorMail, "");
	EXPECT_EQ(projectMetadata.authorName, "crawlerintegrationtesting");
	EXPECT_EQ(projectMetadata.defaultBranch, "master");
	EXPECT_EQ(projectMetadata.license, "MIT License");
	EXPECT_EQ(projectMetadata.name, "notemptyproject");
	EXPECT_EQ(projectMetadata.url, "https://github.com/crawlerintegrationtesting/notemptyproject");
	EXPECT_EQ(projectMetadata.version, "2021-05-31T12:33:29Z");
}

TEST(CrawlRepositoriesTest, TestFindUrl)
{
	GithubCrawler githubCrawler("SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b");
	CrawlData projectMetadata = githubCrawler.crawlRepositories(372484242);
	EXPECT_EQ(projectMetadata.URLImportanceList[0].first, "https://github.com/crawlerintegrationtesting/notemptyproject");
}

TEST(TestCrawlRepositories, TestNotImplemented)
{
	EXPECT_EQ(RunCrawler::crawlRepositories("NotImplementedCrawlableSite", 0, "SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b").URLImportanceList.size(), 0);
}

TEST(TestFindMetadata, TestNotImplemented)
{
	EXPECT_TRUE(RunCrawler::findMetadata("NotImplementedCrawlableSite", "SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b").url.empty());
}

TEST(TestCrawlRepositories, TestBasicCrawling)
{
	CrawlData data = RunCrawler::crawlRepositories("github", 0, "SoftwareProj2021", "8486fe6129f2cce8687e5c9ce540918d42f7cb0b");
	EXPECT_TRUE(data.URLImportanceList.size() <= 100);
	std::map<std::string, bool> uniqueURLs;
	for (int i = 0; i < data.URLImportanceList.size(); i++)
	{
		std::string url = data.URLImportanceList[i].first;
		EXPECT_TRUE(uniqueURLs.count(url) == 0);
		uniqueURLs[url] = true;
	}

}