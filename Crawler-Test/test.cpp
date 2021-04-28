/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "pch.h"
#include "JSON.h"
TEST(TestJSONParse, ShortPath) {
	JSON *json = JSON::parse(R"({"commit": {"commit": {"tree": {"sha": "testsha"}}}})");
	EXPECT_EQ(json->get("commit/commit/tree/sha"), "testsha");
}

TEST(TestJSONParse, DifferentPaths) {
	JSON* json = JSON::parse(R"({"commit": {"commit": {"tree": {"sha": "testsha"}}}, "test": {"test1": "test2"}, "test3": {"test4": {"test5": "test6"}}})");
	EXPECT_EQ(json->get("test/test1"), "test2");
}
TEST(TestJSONParse, LongPath) {
	JSON* json = JSON::parse(R"({"a": {"b": {"c": {"d": {"e": {"f": {"g": {"h": {"i": "j"}}}}}}}}})");
	EXPECT_EQ(json->get("a/b/c/d/e/f/g/h/i"), "j");
}