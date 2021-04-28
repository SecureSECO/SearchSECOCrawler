#include "Utility.h"
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