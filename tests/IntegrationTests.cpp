/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "pch.h"
#include "GithubInterface.h"
#include "RunCrawler.h"
#include <GithubCrawler.h>
#include <chrono>
#include <string>
const static std::string repoBaseUrl = "https://api.github.com/repos/crawlerintegrationtesting/";
const static std::string emptyRepoUrl = repoBaseUrl + "emptyproject";
const static std::string projectWithCode = repoBaseUrl + "notemptyproject";

TEST(CrawlProjectMetadataTest, TestLiveEmptyProject)
{
	ProjectMetadata projectMetadata =
		RunCrawler::findMetadata(emptyRepoUrl, "crawlerintegrationtesting", "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");
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
	ProjectMetadata projectMetadata = RunCrawler::findMetadata(projectWithCode, "crawlerintegrationtesting",
															   "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");
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
	GithubCrawler githubCrawler("crawlerintegrationtesting", "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");
	CrawlData projectMetadata = githubCrawler.crawlRepositories(372484242);
	EXPECT_EQ(std::get<0>(projectMetadata.URLImportanceList[0]),
			  "https://github.com/crawlerintegrationtesting/notemptyproject");
}

TEST(TestCrawlRepositories, TestNotImplemented)
{
	EXPECT_EQ(RunCrawler::crawlRepositories("NotImplementedCrawlableSite", 0, "crawlerintegrationtesting",
											"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").URLImportanceList.size(), 0);
}

TEST(TestFindMetadata, TestNotImplemented)
{
	EXPECT_TRUE(RunCrawler::findMetadata("NotImplementedCrawlableSite", "crawlerintegrationtesting",
										 "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").url.empty());
}

TEST(TestCrawlRepositories, TestBasicCrawling)
{
	CrawlData data = RunCrawler::crawlRepositories("github", 0, "crawlerintegrationtesting",
												   "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");
	EXPECT_TRUE(data.URLImportanceList.size() <= 100);
	std::map<std::string, bool> uniqueURLs;
	for (int i = 0; i < data.URLImportanceList.size(); i++)
	{
		std::string url = std::get<0>(data.URLImportanceList[i]);
		EXPECT_TRUE(uniqueURLs.count(url) == 0);
		uniqueURLs[url] = true;
	}
}