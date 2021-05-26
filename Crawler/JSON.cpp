/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "ErrorHandler.h"
#include "JSON.h"
#include "Utility.h"

nlohmann::json JSON::internalGet(std::string const& key)
{
	std::vector<std::string> seglist = Utility::split(key, '/');
	nlohmann::json current = json;
	int size = seglist.size();
	for (int i = 0; i < size; i++)
	{
		std::string currentKey = seglist[i];
		current = branch(current, currentKey);
	}
	return current;
}

nlohmann::json JSON::branch(nlohmann::json current, std::string const& key)
{
	if (current.is_array())
	{
		if (Utility::hasOnlyDigits(key))
		{
			return current[std::stoi(key)];
		}
		else
		{
			DefaultJSONErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
			throw 1;
		}
	}
	else
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
}


bool JSON::isNotNull(nlohmann::json base, std::string key)
{
	int nextSlash = key.find("/");
	std::string before = key.substr(0, nextSlash);
	std::string after = key.substr(nextSlash + 1, key.npos - nextSlash - 1);
	nlohmann::json val = branch(base, before);
	if (!val.is_null() && val != NULL)
	{
		if (nextSlash != std::string::npos)
		{
			return isNotNull(val, after);
		}
		return true;
	}
	return false;
}

bool JSON::isEmpty(std::string key)
{
	nlohmann::json result = internalGet(key);
	return result.empty();
}


JSON *JSON::parse(std::stringstream s)
{
	return parse(s.str());
}

JSON *JSON::parse(std::string s)
{
	try
	{
		return new JSON(nlohmann::json::parse(s));
	}
	catch (nlohmann::json::parse_error &e)
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::parseError, __FILE__, __LINE__);
		throw 1;
	}
}
