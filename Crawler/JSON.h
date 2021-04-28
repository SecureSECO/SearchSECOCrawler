/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include <sstream>
#include "nlohmann/json.hpp"
/// <summary>
/// Adapter class for JSON formatting.
/// </summary>
class JSON
{
private:
	nlohmann::json json;
	/// <summary>
	/// Splits the function based on the delimiter in multiple strings.
	/// </summary>
	/// <param name="string">The string to be splitted.</param>
	/// <param name="delimiter">The delimiter defining where needs to be splitted.</param>
	/// <returns>A vector of strings.</returns>
	std::vector<std::string> split(std::string string, char delimiter);

public:
	JSON(nlohmann::json json) {
		this->json = json;
	}
	/// <summary>
	/// Gets the key in the JSON variable.
	/// Use forward slashes (/) to branch deeper in the JSON structure, e.g.
	/// json->get("a/b/c") = json["a"]["b"]["c"].
	/// </summary>
	/// <param name="key">The key representing what value needs to be returned.</param>
	/// <returns>The value if found, and NULL otherwise.</returns>
	std::string get(std::string key);

	/// <summary>
	/// Parses a string/stringstream to JSON.
	/// </summary>
	/// <param name="s">The stringstream/string. </param>
	/// <returns>A pointer to a JSON variable.</returns>
	static JSON* parse(std::stringstream s);
	static JSON* parse(std::string s);

};

