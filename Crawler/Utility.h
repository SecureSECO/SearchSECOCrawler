#pragma once
#include <vector>
#include <string>
#include <sstream>
class Utility
{
public:
	/// <summary>
	/// Splits the function based on the delimiter in multiple strings.
	/// </summary>
	/// <param name="string">The string to be splitted.</param>
	/// <param name="delimiter">The delimiter defining where needs to be splitted.</param>
	/// <returns>A vector of strings.</returns>
	static std::vector<std::string> split(std::string string, char delimiter);
};

