/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubClientErrorConverter.h"

githubAPIResponse GithubClientErrorConverter::convertResponse(long code)
{
    switch ((int)code)
    {
        case 100: // Continue.
        case 200: // OK.
            return githubAPIResponse::OK;
        case 400: // Bad JSON format.
        case 422: // Invalid fields in JSON.
            return githubAPIResponse::JSONError;
        case 401: // Wrong credentials
            return githubAPIResponse::badCredentials;
        case 403: // Max login attempts exceeded.
            return githubAPIResponse::forbidden;
        case 404: // Url not found.
            return githubAPIResponse::urlNotFound;
        case 502: // Bad gateway (can happen when executing too many queries at once).
            return githubAPIResponse::badGateway;
        default: // We don't know what the error is.
            return githubAPIResponse::unknownError;
    }
}
