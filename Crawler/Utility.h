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


	/// <summary>
	/// Checks if a string consists only of digits.
	/// </summary>
	/// <param name="s">The string that needs to be checked.</param>
	/// <returns>A boolean indicating whether the given string only consists of digits.</returns>
	static bool hasOnlyDigits(std::string s);
};

