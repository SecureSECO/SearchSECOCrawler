/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "ErrorHandler.h"
#include "JSON.h"
#include "Utility.h"





bool JSON::isEmpty(std::string key)
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
}

bool JSON::isEmpty(int key)
{
	bool empty;
	try
	{
		empty = json->at(key).empty();
	}
	catch (nlohmann::json::type_error)
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::typeError, __FILE__, __LINE__);
		throw 1;
	}
}

bool JSON::isNull(std::string key)
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
}

bool JSON::isNull(int key)
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
}

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
		nlohmann::json *parsed = new nlohmann::json(nlohmann::json::parse(s));
		return new JSON(parsed);
	}
	catch (nlohmann::json::parse_error &e)
	{
		DefaultJSONErrorHandler::getInstance().handle(JSONError::parseError, __FILE__, __LINE__);
		throw 1;
	}
}
