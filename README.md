# Crawler

The Crawler is responsible for finding projects to process, scouring different code sources and returning found URLs.
 These URLs are then processed by the Spider. Another important function of the Crawler is to retrieve project-specific metadata, like the name and email of the owner of the project.

# Installation

Download the .zip containing the source files and extract the files.
Then you need to build and run the standalone project. 
The project has been tested on Windows 10 and works with visual studio 2019.
## Dependencies

* c++17 (uses std::optional)
* nlohmann.json from the nuget package manager needs to be installed.
## Building

The project can be build by opening the solution file and building via Visual Studio 2019.
# Usage

## Library

The Crawler has two entry points. The function _crawlRepositories_ returns a list of URLs given a crawlable source (only GitHub at the moment), 
while the _findMetadata_ function returns project metadata of a given project URL to a GitHub repository.
# Copyright

This program has been developed by students from the bachelor Computer Science at Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)


