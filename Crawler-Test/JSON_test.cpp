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
	std::string result = json->repeatedGet<std::string, std::string>({"commit", "commit", "tree", "sha"});
	EXPECT_EQ(result, "testsha");
}

TEST(TestJSONGet, DifferentPaths)
{
	std::unique_ptr<JSON> json(JSON::parse(
		R"({"commit": {"commit": {"tree": {"sha": "testsha"}}}, "test": {"test1": "test2"}, "test3": {"test4": {"test5": "test6"}}})"));
	std::string result = json->branch("test").get<std::string, std::string>("test1");
	EXPECT_EQ(result, "test2");
}
TEST(TestJSONGet, LongPath)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"a": {"b": {"c": {"d": {"e": {"f": {"g": {"h": {"i": "j"}}}}}}}}})"));
	std::string result = json->repeatedGet<std::string, std::string>({"a", "b", "c", "d", "e", "f", "g", "h", "i"});
	EXPECT_EQ(result, "j");
}

TEST(TestJSONGet, InvalidJSONGet)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {"commit": {"tree": {"sha": "testsha"}}}})"));
	EXPECT_ANY_THROW((json->get<std::string, int>("commit/test|;tes2")));
}

TEST(TestJSONGet, JSONGetEmpty)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {}})"));
	EXPECT_EQ((json->get<std::string, std::string>("commit")), "");
	EXPECT_TRUE(json->isEmpty("commit"));
}

TEST(TestJSONGet, JSONGetEmptyInt)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {}})"));
	EXPECT_EQ((json->get<std::string, int>("commit")), 0);
}

TEST(TestJSONGet, JSONGetEmptyThrow)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": {}})"));
	EXPECT_ANY_THROW((json->get<std::string, bool>("commit", true)));
}

TEST(TestJSONGet, JSONArrayGet)
{
	std::unique_ptr<JSON> json(JSON::parse("[{\"test1\": \"test\"}]"));
	EXPECT_EQ((json->branch(0).get<std::string, std::string>("test1")), "test");
}

TEST(TestJSONGet, InvalidJSONArrayGet)
{
	std::unique_ptr<JSON> json(JSON::parse("[{\"test1\": \"test\"}]"));
	EXPECT_ANY_THROW((json->get<std::string, std::string>("a/test")));
}

TEST(TestJSONParse, InvalidJSON)
{
	EXPECT_ANY_THROW(JSON::parse(R"(invalid)"));
}

TEST(TestJSONExist, JSONNull)
{
	std::unique_ptr<JSON> json(JSON::parse("{\"test1\": null}"));
	EXPECT_EQ((json->get<std::string, std::string>("test1")), "");
	EXPECT_TRUE(json->isNull("test1"));
}

TEST(TestJSONExist, JSONContains)
{
	std::unique_ptr<JSON> json(JSON::parse("{\"test1\": null}"));
	EXPECT_FALSE(json->contains("test2"));
}

TEST(TestJSONExist, JSONExists)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"test1": null, "commit": {}})"));
	EXPECT_FALSE(json->exists("test1"));
	EXPECT_FALSE(json->exists("commit"));
	EXPECT_FALSE(json->exists("doesNotExist"));
}

TEST(TestJSONProperty, JSONLength)
{
	std::unique_ptr<JSON> json(JSON::parse(R"({"test1": null, "commit": {}})"));
	EXPECT_EQ(json->length(), 2);
}

TEST(TestJSONGet, JSONGetIndex)
{
	std::vector<std::string> vec;
	std::unique_ptr<JSON> json(JSON::parse(R"({"commit": "testvalue", "commit3": "testvalue3"})"));
	for (int i = 0; i < json->length(); i++)
	{
		vec.push_back(json->getIndex<std::string>(i));
	}
	bool b1 = (std::find(vec.begin(), vec.end(), "testvalue") != vec.end());
	bool b2 = (std::find(vec.begin(), vec.end(), "testvalue3") != vec.end());
	EXPECT_TRUE(b1);
	EXPECT_TRUE(b2);

}