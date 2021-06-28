# Crawler

The Crawler is responsible for finding projects to process, scouring different code sources and returning found URLs. 
These URLs are then processed by the Spider. Another important function of the Crawler is to retrieve project-specific metadata, like the name and email of the owner of the project.

# Installation

## Dependencies
* c++17 (std::optional is used).
* nlohmann.json from the nuget package manager needs to be installed.
The crawler has been confirmed to work on Windows 10, and works via the controller also on Ubuntu 18.04+.

## Building

### Library

#### CMake
Make sure [CMake](https://cmake.org/download) is installed.
- In the root of the project, run
```
> mkdir build && cd build
> cmake ../libSearchSECOCrawler
> cmake --build .
```

#### Visual Studio
Open the solution and build the libSearchSECOCrawler project.

### Stand-alone
Building and running the stand-alone only works on Windows, and as such we will only give instructions to build the stand-alone in Visual Studio.

#### Visual Studio

Open the solution and build the SearchSECOCrawler project.

# Usage

## Library

The Crawler has two entry points. The function `crawlRepositories` returns a list of URLs given a crawlable source (only GitHub at the moment), 
while the `findMetadata` function returns project metadata of a given project URL to a GitHub repository. Include `RunCrawler.h` to use them.

## Stand-alone
Set the SearchSECOCrawler as startup project and run that project. Do note that this project has no real purpose outside of testing whether the project actually works.

# Copyright

This program has been developed by students from the bachelor Computer Science at Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)