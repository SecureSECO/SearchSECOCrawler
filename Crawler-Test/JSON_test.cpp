/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "pch.h"
#include "JSON.h"
TEST(TestJSONGet, ShortPath) 
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {"commit": {"tree": {"sha": "testsha"}}}})"));
	EXPECT_EQ(json->get("commit/commit/tree/sha"), "testsha");
}

TEST(TestJSONGet, DifferentPaths) 
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {"commit": {"tree": {"sha": "testsha"}}}, "test": {"test1": "test2"}, "test3": {"test4": {"test5": "test6"}}})"));
	EXPECT_EQ(json->get("test/test1"), "test2");
}
TEST(TestJSONGet, LongPath) 
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"a": {"b": {"c": {"d": {"e": {"f": {"g": {"h": {"i": "j"}}}}}}}}})"));
	EXPECT_EQ(json->get("a/b/c/d/e/f/g/h/i"), "j");
}

TEST(TestJSONGet, InvalidJSONGet)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {"commit": {"tree": {"sha": "testsha"}}}})"));
	EXPECT_ANY_THROW(json->get("commit/test|;tes2"));
}

TEST(TestJSONGet, JSONGetEmpty)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {}})"));
	EXPECT_EQ(json->get("commit"), "");
}

TEST(TestJSONGet, JSONArrayGet)
{
	std::unique_ptr<JSON> json(JSON::parse("[{\"test1\": \"test\"}]"));
	EXPECT_EQ(json->get("0/test1"), "test");
}

TEST(TestJSONGet, InvalidJSONArrayGet)
{
	std::unique_ptr<JSON> json(JSON::parse("[{\"test1\": \"test\"}]"));
	EXPECT_ANY_THROW(json->get("a/test"));
}

TEST(TestJSONParse, InvalidJSON)
{
	EXPECT_ANY_THROW(JSON::parse(R"(invalid)"));
}

