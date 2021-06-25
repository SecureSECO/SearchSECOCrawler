/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "GithubCrawler.h"
#include "LoggerCrawler.h"
CrawlData GithubCrawler::crawlRepositories(int start)
{
	auto strStart = std::to_string(start);
	GithubErrorThrowHandler *handler = getCorrectGithubHandler();
	LoggerCrawler::logDebug("Starting crawling at index " + strStart, __FILE__, __LINE__);
	int currentId;

	// Create an unique_ptr from a GitHub request asking for a list of repositories, and use that to get the CrawlData.
	std::unique_ptr<JSON> json(githubInterface->getRequest("https://api.github.com/repositories?since=" + strStart));
	CrawlData crawlData = getCrawlData(json, handler, currentId);

	LoggerCrawler::logInfo("100% done, finished crawling one page (" + std::to_string(MAXRESULTS) +
							   " repositories)",
						   __FILE__, __LINE__);
	crawlData.finalProjectId = currentId;
	delete handler;
	return crawlData;
}

CrawlData GithubCrawler::getCrawlData(std::unique_ptr<JSON> &json, GithubErrorThrowHandler *handler, int &currentId)
{
	CrawlData crawlData;
	// The maximum amount of URLs we can crawl.
	int bound = std::min(json->length(), MAXRESULTS);

	for (int i = 0; i < bound; i++)
	{
		logProgress(i, bound);

		JSON branch = json->branch(i);
		currentId = branch.get<std::string, int>("id", true);

		// Add URL if possible, if we get a 0 skip this URL, if we get a 1 we have a fatal error.
		try
		{
			addURL(branch, crawlData, handler);
		}
		catch (int e)
		{
			if (e == 0)
			{
				continue;
			}
			else if (e == 1)
			{
				throw 1;
			}
		}
	}
	return crawlData;
}

void GithubCrawler::addURL(JSON &branch, CrawlData &crawlData, GithubErrorThrowHandler *handler)
{
	std::string repoUrl = branch.get<std::string, std::string>("url", true);
	std::pair<float, int> parseable = getParseableRatio(repoUrl, handler);

	// Only add URLs which contain data that we can parse.
	if (std::get<1>(parseable) != 0)
	{
		int stars = getStars(repoUrl, handler);
		std::string url = branch.get<std::string, std::string>("html_url", true);
		crawlData.urlImportanceList.push_back(std::make_pair(url, getImportanceMeasure(stars, parseable)));
	}
}

void GithubCrawler::logProgress(int step, int max, int stepSize)
{
	double progressPerStep = 100.0 / ((double)max);
	double progress = step * progressPerStep;
	double previousProgress = progress - progressPerStep;
	int k = std::floor(progress / ((double)stepSize));

	// Log the percentage of work we have done every time we have completed k times procentLog work.
	if (progress > k * stepSize && previousProgress <= k * stepSize && k > 0)
	{
		LoggerCrawler::logInfo(std::to_string(k * stepSize) + "% done...", __FILE__, __LINE__);
	}
}

GithubErrorThrowHandler *GithubCrawler::getCorrectGithubHandler()
{
	GithubErrorThrowHandler *handler = new GithubErrorThrowHandler();
	IndividualErrorHandler *individualHandler1 = new LogThrowHandler(
		"Found URL was inaccessible, skipping...", LogLevel::WARN, Utility::getCode(githubAPIResponse::forbidden));
	IndividualErrorHandler *individualHandler2 = new LogThrowHandler(
		"Found URL was inaccessible, skipping...", LogLevel::WARN, Utility::getCode(githubAPIResponse::urlNotFound));
	handler->replaceSingleHandler(githubAPIResponse::forbidden, individualHandler1);
	handler->replaceSingleHandler(githubAPIResponse::urlNotFound, individualHandler2);
	return handler;
}

JSONErrorHandler *GithubCrawler::getCorrectJSONHandler()
{
	JSONErrorHandler *handler = new JSONErrorHandler();
	IndividualErrorHandler *individualHandler = new LogThrowHandler(
		"Trying to parse the JSON structure returned by the given URL returned a parse error, skipping...",
		LogLevel::WARN, Utility::getCode(JSONError::parseError));
	handler->replaceSingleHandler(JSONError::parseError, individualHandler);
	return handler;
}

GithubErrorThrowHandler *GithubCrawler::getGithubHandlerForJSONError()
{
	GithubErrorThrowHandler *githubHandler = new GithubErrorThrowHandler();
	IndividualErrorHandler *individualHandler =
		new LogThrowHandler("Github returned a JSON error, skipping this url...", LogLevel::WARN,
							Utility::getCode(githubAPIResponse::JSONError));
	githubHandler->replaceSingleHandler(githubAPIResponse::JSONError, individualHandler);
	return githubHandler;
}

std::tuple<std::string, std::string> GithubCrawler::getOwnerAndRepo(std::string const &url)
{
	std::vector<std::string> split = Utility::split(url, '/');
	int segCount = split.size();

	std::string ownername = split[segCount - 2];
	std::string reponame = split[segCount - 1];

	return std::tuple<std::string, std::string>{ownername, reponame};
}

std::string GithubCrawler::getRepoUrl(std::string url)
{
	LoggerCrawler::logDebug("Finding owner and repository...", __FILE__, __LINE__);
	std::tuple<std::string, std::string> ownerAndRepo = getOwnerAndRepo(url);
	std::string ownername = std::get<0>(ownerAndRepo);
	std::string reponame = std::get<1>(ownerAndRepo);

	return "https://api.github.com/repos/" + ownername + "/" + reponame;
}

ProjectMetadata GithubCrawler::getProjectMetadata(std::string url)
{
	std::string repoUrl = getRepoUrl(url);
	LoggerCrawler::logDebug("Getting information about the repository...", __FILE__, __LINE__);
	JSONErrorHandler *handler = getCorrectJSONHandler();
	GithubErrorThrowHandler *githubHandler = getGithubHandlerForJSONError();
	JSON *json = NULL;

	try
	{
		json = githubInterface->getRequest(repoUrl, githubHandler, handler);
	}
	catch (int e)
	{
		if (e == 0)
		{
			return ProjectMetadata();
		}
		else if (e == 1)
		{
			throw 1;
		}
	}
	// Construct projectMetadata using the owner and repo and the JSON variable we just found.
	ProjectMetadata projectMetadata = constructProjectMetadata(json, getOwnerAndRepo(url));

	LoggerCrawler::logInfo("Successfully found all relevant metadata, returning.", __FILE__, __LINE__);
	delete json;
	delete handler;
	delete githubHandler;
	return projectMetadata;
}

ProjectMetadata GithubCrawler::constructProjectMetadata(JSON *json, std::tuple<std::string, std::string> ownerAndRepo)
{
	JSON branch = json->branch("owner");
	JSON *ownerData = githubInterface->getRequest(branch.get<std::string, std::string>("url"));
	ProjectMetadata projectMetadata;

	LoggerCrawler::logDebug("Getting information about the owner...", __FILE__, __LINE__);
	std::string email = ownerData->get<std::string, std::string>("email");

	// Add known information.
	projectMetadata.authorName = std::get<0>(ownerAndRepo);
	projectMetadata.authorMail = email;
	projectMetadata.name = std::get<1>(ownerAndRepo);

	// We always need an URL.
	projectMetadata.url = json->get<std::string, std::string>("html_url", true);

	// However, these other fields are not as important and as such we do not require them to be filled in.
	projectMetadata.version = json->get<std::string, std::string>("pushed_at");
	projectMetadata.defaultBranch = json->get<std::string, std::string>("default_branch");

	// We may not be able to branch on the license field, so make sure it exists first.
	if (json->exists<std::string>("license"))
	{
		projectMetadata.license = json->branch("license").get<std::string, std::string>("name");
	}
	else
	{
		projectMetadata.license = "";
	}

	delete ownerData;
	return projectMetadata;
}

int GithubCrawler::getImportanceMeasure(int stars, std::pair<float, int> percentageAndBytes)
{
	float percentage = std::get<0>(percentageAndBytes);
	int bytes = std::get<1>(percentageAndBytes);
	return 20000000 * percentage * std::log(stars + 1) * std::log(std::log(bytes + 1) + 1);
}

int GithubCrawler::getStars(std::string repoUrl, GithubErrorThrowHandler *handler)
{
	std::unique_ptr<JSON> json(githubInterface->getRequest(repoUrl, handler));
	int stars = json->get<std::string, int>("stargazers_count");
	return stars;
}

std::pair<float, int> GithubCrawler::getParseableRatio(std::string repoUrl, GithubErrorThrowHandler *handler)
{
	std::string languagesUrl = repoUrl + "/languages";
	std::unique_ptr<JSON> json(githubInterface->getRequest(languagesUrl, handler));
	int total = 0;
	int parseable = 0;
	int length = json->length();

	// Loop through all the languages in the JSON variable, and retrieve the amount of bytes of code in that language.
	for (int i = 0; i < length; i++)
	{
		total += json->getIndex<int>(i);
	}
	// Loop through the list of languages we can actually parse and retrieve the amount of parseable bytes.
	for (std::string language : PARSEABLELANGUAGES)
	{
		if (json->exists(language))
		{
			parseable += json->get<std::string, int>(language);
		}
	}
	if (total != 0)
	{
		return std::pair((float)((float)(parseable) / (float)(total)), parseable);
	}
	return std::pair(0.0, 0);
}
