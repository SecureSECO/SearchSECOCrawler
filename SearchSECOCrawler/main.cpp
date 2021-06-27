/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences) 
*/

// Crawler includes.
#include "RunCrawler.h"

// External includes.
#include <iostream>

// Input token for debugging, remember to delete when done
#define username "username"
#define token "token"


int main() 
{
	int start = 0;
	RunCrawler::crawlRepositories("github.com", start, username, token);
}
