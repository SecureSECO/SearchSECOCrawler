#pragma once
enum class githubAPIResponse
{
    OK,
    JSONError,
    badCredentials,
    forbidden,
    badGateway,
    urlNotFound,
    unknownError,
};
enum class genericError
{
    basicError,
};

enum class JSONError
{
    branchError,
    parseError,
};