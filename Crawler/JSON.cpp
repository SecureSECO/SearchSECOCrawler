/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "ErrorHandler.h"
#include "JSON.h"
#include "Utility.h"





int JSON::length()
{
	return json->size();
}


JSON *JSON::parse(std::stringstream s)
{
	return parse(s.str());
}

JSON *JSON::parse(std::string s)
{
	try
	{
		nlohmann::json*parsed = new nlohmann::json(nlohmann::json::parse(s));
		return new JSON(parsed);
	}
	catch (nlohmann::json::parse_error &e)
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::parseError, __FILE__, __LINE__);
		throw 1;
	}
}
