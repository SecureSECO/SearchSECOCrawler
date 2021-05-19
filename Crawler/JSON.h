/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "nlohmann/json.hpp"
#include "ErrorHandler.h"

/// <summary>
/// Adapter class for JSON formatting.
/// </summary>

class JSON
{
private:
	nlohmann::json json;

	/// <summary>
	/// Gets the key in the JSON variable.
	/// Use forward slashes (/) to branch deeper in the JSON structure, e.g.
	/// json->get("a/b/c") = json["a"]["b"]["c"].
	/// </summary>
	/// <param name="key">The key representing what value needs to be returned.</param>
	/// <returns>The value if found, and NULL otherwise.</returns>
	nlohmann::json internalGet(std::string key);

	template<class T> 
	T getDefault();

	template <> int getDefault<int>()
	{
		return 0;
	}
	template <> std::string getDefault<std::string>()
	{
		return "";
	}
	template <> bool getDefault<bool>()
	{
		return false;
	}


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
	/// Gets a string, int or bool respectively. Uses get().
	/// </summary>
	/// <param name="key">The key on which needs to be indexed.</param>
	/// <returns>A string, int or bool of the value found respectively.</returns>
	
	template<class T>
	T get(std::string key)
	{
		nlohmann::json result = internalGet(key);
		T finalResult;
		if (result.empty())
		{
			return getDefault<T>();
		}
		try
		{
			finalResult = (T)result;
		}
		catch (nlohmann::json::type_error)
		{
			DefaultJSONErrorHandler::getInstance().handle(JSONError::typeError, __FILE__, __LINE__);
			throw 1;
		}
		return finalResult;
	}





	/// <summary>
	/// Parses a string/stringstream to JSON.
	/// </summary>
	/// <param name="s">The stringstream/string.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	static JSON *parse(std::stringstream s);
	static JSON *parse(std::string s);
};

