/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once
enum class githubAPIResponse
{
	OK,
	JSONError,
	badCredentials,
	rateLimitExceeded,
	forbidden,
	badGateway,
	urlNotFound,
	unknownError,
	count // Should always be last.
};

enum class JSONError
{
	branchError,
	parseError,
	typeError,
	fieldEmptyError,
	outOfRangeError,
	count
};
