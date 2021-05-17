/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "nlohmann/json.hpp"

/// <summary>
/// Adapter class for JSON formatting.
/// </summary>

class JSON
{
private:
	nlohmann::json json;

public:
	JSON(nlohmann::json json)
	{
		this->json = json;
	}
	JSON()
	{
		this->json = nlohmann::json::parse("{}");
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
	/// Creates a JSON variable based on a map.
	/// </summary>
	/// <param name="map">The map that needs to be parsed.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	static JSON *parse(std::map<int, std::string> map);

	/// <summary>
	/// Parses a string/stringstream to JSON.
	/// </summary>
	/// <param name="s">The stringstream/string.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	static JSON *parse(std::stringstream s);
	static JSON *parse(std::string s);
};
