/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

// Crawler includes.
#include "ErrorHandler.h"
#include "JSON.h"


int JSON::length()
{
	return json->size();
}

JSON *JSON::parse(std::string s)
{
	return parse(s, &JSONSingletonErrorHandler::getInstance());
}

JSON *JSON::parse(std::string s, JSONErrorHandler *handler)
{
	try
	{
		nlohmann::json *parsed = new nlohmann::json(nlohmann::json::parse(s));
		return new JSON(parsed);
	}
	catch (nlohmann::json::parse_error &e)
	{
		handler->handle(JSONError::parseError, __FILE__, __LINE__);
		throw 1;
	}
}

template <class O> O JSON::getDefault()
{
	return O();
}

template <> int JSON::getDefault<int>()
{
	return 0;
}
template <> std::string JSON::getDefault<std::string>()
{
	return "";
}
template <> const char *JSON::getDefault<const char *>()
{
	return "";
}
template <> bool JSON::getDefault<bool>()
{
	return false;
}

template <class T> nlohmann::json internalGet(nlohmann::json current, T key)
{
	return nlohmann::json::parse("{}");
}

template <> nlohmann::json JSON::internalGet<int>(nlohmann::json current, int key)
{
	if (key < current.size())
	{
		return current[key];
	}
	else
	{
		JSONSingletonErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
		throw 1;
	}
}

template <> nlohmann::json JSON::internalGet<const char *>(nlohmann::json current, const char *key)
{
	if (current.find(key) != current.end())
	{
		return current[key];
	}
	else
	{
		JSONSingletonErrorHandler::getInstance().handle(JSONError::branchError, __FILE__, __LINE__);
		throw 1;
	}
}

template <> nlohmann::json JSON::internalGet<std::string>(nlohmann::json current, std::string key)
{
	return internalGet<const char *>(current, key.c_str());
}
