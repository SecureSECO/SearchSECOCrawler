/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
� Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "nlohmann/json.hpp"
#include "ErrorHandler.h"


/// <summary>
/// Returns a default value for a given type T. Returns T() if no specialization can be found.
/// </summary>
/// <typeparam name="T">The type.</typeparam>
/// <returns>A default value of the given type.</returns>







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
	template<class T> T getDefault()
	{
		return T();
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
	/// Can get a value from a JSON structure. In case the field is empty returns a default value. Uses internalGet().
	/// </summary>
	/// <param name="key">The key on which needs to be indexed.</param>
	/// <param name="expectNonEmpty">
	/// Whether the program should return an error to the user when the field found is empty.</param>
	/// <returns>A value of type T.</returns>
	
	template<class T>
	T get(std::string key, bool expectNonEmpty = false)
	{
		nlohmann::json result = internalGet(key);
		T finalResult;
		if (result.empty())
		{
			if (expectNonEmpty)
			{
				DefaultJSONErrorHandler::getInstance().handle(JSONError::fieldEmptyError, __FILE__, __LINE__);
				throw 1;
			}
			else
			{
				return getDefault<T>();
			}
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


//template <class T> inline T JSON::getDefault()
//{
//	return T();
//}

template <> inline int JSON::getDefault<int>()
{
	return 0;
}
template <> inline std::string JSON::getDefault<std::string>()
{
	return "";
}
template <> inline bool JSON::getDefault<bool>()
{
	return false;
}