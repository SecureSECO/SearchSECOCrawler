/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences) 
*/

#include "RunCrawler.h"
int main() 
{
	int c;
	//RunCrawler::findMetadata("github.com/torvalds/linux", c);
	RunCrawler::crawlRepositories("github.com", 100, c);
}