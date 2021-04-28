/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
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

