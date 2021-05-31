#include "pch.h"
#include "GithubCrawler.h"
#include <string>
const static std::string repoBaseUrl = "https://api.github.com/repos/crawlerintegrationtesting/";
const static std::string emptyRepoUrl = repoBaseUrl + "emptyproject";
const static std::string projectWithCode = repoBaseUrl + "notemptyproject";


TEST(CrawlRepositoriesTest, TestLiveEmptyProject)
{
	GithubCrawler githubCrawler;
	ProjectMetadata projectMetadata = githubCrawler.getProjectMetadata(emptyRepoUrl);
	EXPECT_EQ(projectMetadata.authorMail, "");
	EXPECT_EQ(projectMetadata.authorName, "crawlerintegrationtesting");
	EXPECT_EQ(projectMetadata.defaultBranch, "main");
	EXPECT_EQ(projectMetadata.license, "");
	EXPECT_EQ(projectMetadata.name, "emptyproject");
	EXPECT_EQ(projectMetadata.url, "https://github.com/crawlerintegrationtesting/emptyproject");
	EXPECT_EQ(projectMetadata.version, "2021-05-31T11:25:39Z");
}

TEST(CrawlRepositoriesTest, TestLiveNonEmptyProject)
{
	GithubCrawler githubCrawler;
	ProjectMetadata projectMetadata = githubCrawler.getProjectMetadata(projectWithCode);
	EXPECT_EQ(projectMetadata.authorMail, "");
	EXPECT_EQ(projectMetadata.authorName, "crawlerintegrationtesting");
	EXPECT_EQ(projectMetadata.defaultBranch, "master");
	EXPECT_EQ(projectMetadata.license, "MIT License");
	EXPECT_EQ(projectMetadata.name, "notemptyproject");
	EXPECT_EQ(projectMetadata.url, "https://github.com/crawlerintegrationtesting/notemptyproject");
	EXPECT_EQ(projectMetadata.version, "2021-05-31T12:33:29Z");
}