/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences) 
*/
#include <iostream>
#include "RunCrawler.h"
int main() 
{
	int start = 0;
	CrawlData data = RunCrawler::crawlRepositories("github.com", start);
	/*start = data.finalProjectId;
	std::cout << "start: " + (std::to_string(start));*/

	RunCrawler::findMetadata("github.com/manicolosi/manico-crumbs");
}