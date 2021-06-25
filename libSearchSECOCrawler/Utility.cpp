/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

// Crawler includes.
#include "Utility.h"

// External includes.
#include <sstream>


// Copied from https://stackoverflow.com/questions/10058606/splitting-a-string-by-a-character/10058756.
std::vector<std::string> Utility::split(std::string string, char delimiter)
{
	std::stringstream ss(string);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(ss, segment, delimiter))
	{
		seglist.push_back(segment);
	}
	return seglist;
}
