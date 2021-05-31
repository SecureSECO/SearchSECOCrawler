/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
#include "nlohmann/json.hpp"
#include "ErrorHandler.h"
#include <optional>

/// <summary>
/// Adapter class for JSON formatting.
/// </summary>

class JSON
{
private:
	nlohmann::json *json;

	std::optional<std::vector<nlohmann::json>> items; // An optional list of items.
	// Allows us to check with if(items) whether the variable is intialized.


	template <class T> nlohmann::json internalGet(nlohmann::json current, T key)
	{
		return nlohmann::json::parse("{}");
	}

	/// <summary>
	/// Gets the given value and checks whether it is empty. Uses internalGet().
	/// </summary>
	/// <typeparam name="T">The type of the key.</typeparam>
	/// <param name="current">The json variable in which needs to be indexed.</param>
	/// <param name="key">The key.</param>
	/// <param name="expectNonEmpty">Whether the program should throw an error to the user when the field found is empty.</param>
	/// <returns>A nlohmann::json variable.</returns>
	template <class T>
	nlohmann::json internalSafeGet(nlohmann::json current, T key, bool expectNonEmpty)
	{
		nlohmann::json result = internalGet<T>(current, key);
		if (result.is_null() || result.empty())
		{
			if (expectNonEmpty)
			{
				DefaultJSONErrorHandler::getInstance().handle(JSONError::fieldEmptyError, __FILE__, __LINE__);
				throw 1;
			}
		}
		return result;
	}






	/// <summary>
	/// Returns a default value for a given type O. Returns O() if no specialization can be found.
	/// </summary>
	/// <typeparam name="O">The type of the output.</typeparam>
	/// <returns>A default value of the given type.</returns>

	template <class O> O getDefault()
	{
		return O();
	}



public:
	JSON(nlohmann::json *json)
	{
		this->json = json;
	}
	JSON()
	{
		nlohmann::json basic = nlohmann::json::parse("{}");
		this->json = &basic;
	}

	/// <summary>
	/// Gets the length of the nlohmann::json inside this JSON variable.
	/// </summary>
	/// <returns>The length of the nlohmann::json variable.</returns>
	int length();

	/// <summary>
	/// Gets the value sitting at position "index". Constructs a new list of items if none was present.
	/// </summary>
	/// <typeparam name="O">The type of the output.</typeparam>
	/// <param name="index">The index.</param>
	/// <returns>The value at the position of the index.</returns>
	template<class O>
	O getIndex(int index)
	{
		if (items)
		{
			return items.value()[index];
		}
		else
		{
			std::vector<nlohmann::json> vec;
			nlohmann::json jj = *json;
			for (nlohmann::json::iterator it = jj.begin(); it != jj.end(); ++it)
			{
				vec.push_back(*it);
			}
			items = vec;
			return items.value()[index];
		}
	}

	/// <summary>
	/// Can get a value from a JSON structure. In case the field is empty returns a default value. Uses internalGet().
	/// </summary>
	/// <param name="key">The key on which needs to be indexed.</param>
	/// <param name="expectNonEmpty">
	/// Whether the program should throw an error to the user when the field found is empty.</param>
	/// <returns>A value of type T.</returns>
	template<class T, class O>
	O get(T key, bool expectNonEmpty = false)
	{
		nlohmann::json result = internalSafeGet<T>(*json, key, expectNonEmpty);
		if (result.empty() || result.is_null())
		{
			return getDefault<O>();
		}
		O finalResult;
		try
		{
			finalResult = (O)result;
		}
		catch (nlohmann::json::type_error)
		{
			DefaultJSONErrorHandler::getInstance().handle(JSONError::typeError, __FILE__, __LINE__);
			throw 1;
		}
		return finalResult;
	}

	/// <summary>
	/// Gets a value for which there is need to branch several times.
	/// </summary>
	/// <typeparam name="T">The type of the key.</typeparam>
	/// <typeparam name="O">The type of the output.</typeparam>
	/// <param name="keys">The list of keys.</param>
	/// <param name="expectNonEmpty">Whether this function should raise an error when nothing was found.</param>
	/// <returns>The value found, or a default value if expectNonEmpty was false and nothing was found.</returns>
	template <class T, class O> 
	O repeatedGet(std::vector<T> const &keys, bool expectNonEmpty = false)
	{
		nlohmann::json current = *json;
		for (int i = 0; i < keys.size(); i++)
		{
			T key = keys[i];
			current = internalSafeGet(current, key, expectNonEmpty);
			if (current.empty() || current.is_null())
			{
				if (i == keys.size() - 1)
				{
					return getDefault<O>();
				}
				else
				{
					DefaultJSONErrorHandler::getInstance().handle(JSONError::fieldEmptyError, __FILE__, __LINE__);
					throw 1;
				}
			}
		}
		O finalResult;
		try
		{
			finalResult = (O)current;
		}
		catch (nlohmann::json::type_error)
		{
			DefaultJSONErrorHandler::getInstance().handle(JSONError::typeError, __FILE__, __LINE__);
			throw 1;
		}
		return finalResult;
	}

	/// <summary>
	/// Branch on a given key.
	/// </summary>
	/// <typeparam name="T">The type of the key.</typeparam>
	/// <param name="key">The key.</param>
	/// <returns>A JSON variable which is branched on the key.</returns>
	template <class T> JSON branch(T key)
	{
		nlohmann::json *result = new nlohmann::json(json->at(key)); 
		return JSON(result);
	}


	/// <summary>
	/// Checks whether the given key returns an empty field. 
	/// Empty fields are typically of the form: 
	/// "field": {}
	/// </summary>
	/// <param name="key">The key on which needs to be indexed.</param>
	/// <returns>A boolean indicating whether the field found was empty or not.</returns>
	template<class T> bool isEmpty(T key)
	{
		bool empty;
		try
		{
			empty = json->at(key).empty();
		}
		catch (nlohmann::json::type_error)
		{
			DefaultJSONErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
			throw 1;
		}
		return empty;
	}

	/// <summary>
	/// Checks whether the given key returns a null field. 
	/// </summary>
	/// <param name="key">The key on which needs to be indexed.</param>
	/// <returns>A boolean indicating whether the field found was null or not.</returns>
	template<class T> bool isNull(T key)
	{
		bool empty;
		try
		{
			empty = json->at(key).is_null();
		}
		catch (nlohmann::json::type_error)
		{
			DefaultJSONErrorHandler::getInstance().handle(JSONError::typeError, __FILE__, __LINE__);
			throw 1;
		}
		return empty;
	}

	/// <summary>
	/// Checks whether the given key is contained in the JSON structure.
	/// </summary>
	/// <typeparam name="T">The type of the key.</typeparam>
	/// <param name="key">The key.</param>
	/// <returns>A boolean indicating whether the key was found in the JSON structure.</returns>
	template<class T> bool contains(T key)
	{
		bool empty;
		try
		{
			empty = json->contains(key);
		}
		catch (nlohmann::json::type_error)
		{
			DefaultJSONErrorHandler::getInstance().handle(JSONError::typeError, __FILE__, __LINE__);
			throw 1;
		}
		return empty;
	}

	/// <summary>
	/// Checks whether the given key is contained in the JSON structure and 
	/// whether it is associated with a null/empty field.
	/// </summary>
	/// <typeparam name="T"> The type of the key.</typeparam>
	/// <param name="key">The key on which needs to be indexed.</param>
	/// <returns>A boolean which is true when the key was found in the JSON structure,
	/// the value associated to the key was not null and the value was not empty. This boolean is false otherwise.</returns>
	template<class T> bool exists(T key)
	{
		if (contains(key))
		{
			return (!isNull(key) && !isEmpty(key));
		}
		return false;
	}


	/// <summary>
	/// Parses a string/stringstream to JSON.
	/// </summary>
	/// <param name="s">The stringstream/string.</param>
	/// <returns>A pointer to a JSON variable.</returns>
	static JSON *parse(std::stringstream s);
	static JSON *parse(std::string s);

	~JSON()
	{
		delete json;
	}

};

template <> inline int JSON::getDefault<int>()
{
	return 0;
}
template <> inline std::string JSON::getDefault<std::string>()
{
	return "";
}
template <> inline const char * JSON::getDefault<const char *>()
{
	return "";
}
template <> inline bool JSON::getDefault<bool>()
{
	return false;
}

template <> inline nlohmann::json JSON::internalGet<int>(nlohmann::json current, int key)
{
	if (key < current.size())
	{
		return current[key];
	}
	else
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
		throw 1;
	}
}

template <> inline nlohmann::json JSON::internalGet<const char *>(nlohmann::json current, const char *key)
{
	if (current.find(key) != current.end())
	{
		return current[key];
	}
	else
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
		throw 1;
	}
}

template <> inline nlohmann::json JSON::internalGet<std::string>(nlohmann::json current, std::string key)
{
	return internalGet<const char *>(current, key.c_str());
}