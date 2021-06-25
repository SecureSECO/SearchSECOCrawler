# Crawler

The Crawler is responsible for finding projects to process, scouring different code sources and returning found URLs. 
These URLs are then processed by the Spider. Another important function of the Crawler is to retrieve project-specific metadata, like the name and email of the owner of the project.

# Installation

## Dependencies

* c++17 (uses std::optional)
* nlohmann.json from the nuget package manager needs to be installed.
## Building

The project can be built by opening the solution file and building via Visual Studio 2019.
Building the project this way has been confirmed to work on Windows 10.
# Usage

##Stand-alone

The standalone project that can be run can be found in the "Standalone" folder. However, as the data that is returned from crawling will not be displayed to the user,
we advise to use this project as a library instead.

## Library

The Crawler has two entry points. The function `crawlRepositories` returns a list of URLs given a crawlable source (only GitHub at the moment), 
while the `findMetadata` function returns project metadata of a given project URL to a GitHub repository. Include `RunCrawler.h` to use them.
# Copyright

This program has been developed by students from the bachelor Computer Science at Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)


