/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "JSON.h"
#include "Utility.h"
#include "ErrorHandler.h"

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
			}
		}
		else
		{
			current = current[currentKey];
		}
	}
	if (current.empty())
	{
		return "";
	}
	return current;
	
}


JSON* JSON::parse(std::stringstream s)
{
	JSON* json;
	try
	{
		json = new JSON(nlohmann::json::parse(s));
	}
	catch (std::string error)
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::parseError, __FILE__, __LINE__);
	}
	return json;
}

JSON* JSON::parse(std::string s)
{

	JSON* json;
	try
	{
		json = new JSON(nlohmann::json::parse(s));
	}
	catch (std::string error)
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::parseError, __FILE__, __LINE__);
	}
	return json;
}



