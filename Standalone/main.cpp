/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences) 
*/
#include <iostream>
#include "RunCrawler.h"

// Input token for debugging, remember to delete when done
#define username "username"
#define token "token"

int main() 
{
	int start = 0;
	for (int i = 0; i < 10; i++)
	{
		CrawlData data = RunCrawler::crawlRepositories("github.com", start, username, token);
		start = data.finalProjectId;
		std::cout << "start: " + (std::to_string(start));
	}

	RunCrawler::findMetadata("github.com/manicolosi/manico-crumbs", username, token);
}