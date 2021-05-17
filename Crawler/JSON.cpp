/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "JSON.h"
#include "ErrorHandler.h"
#include "Utility.h"

std::string JSON::get(std::string key)
{
	std::vector<std::string> seglist = Utility::split(key, '/');
	nlohmann::basic_json<>::value_type current = json;
	int size = seglist.size();
	for (int i = 0; i < size; i++)
	{
		std::string currentKey = seglist[i];
		if (current.is_array())
		{
			if (Utility::hasOnlyDigits(currentKey))
			{
				current = current[std::stoi(currentKey)];
			}
			else
			{
				DefaultJSONErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
				throw 1;
			}
		}
		else
		{
			if (current.find(currentKey) != current.end())
			{
				current = current[currentKey];
			}
			else
			{
				DefaultJSONErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
				throw 1;
			}
		}
	}
	if (current.empty())
	{
		return "";
	}
	return current;
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
