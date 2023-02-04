# Crawler
![Testing](https://github.com/SecureSECO/SearchSECOCrawler/actions/workflows/testing.yml/badge.svg)

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

# License

This project is licensed under the GNU Affero General Public License v3.0. See [LICENSE](LICENSE) for more info.

This program has been developed by students from the bachelor Computer Science at Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)

## Licenses for code from other projects
* [Curl](https://curl.se/). The license for Curl can be found in [external/curl/COPYING](external/curl/COPYING) and is applicable to everything in the [external/curl](external/curl) folder, and any subfolders.
* [Curlcpp](https://github.com/JosephP91/curlcpp). The license for curlcpp can be found in [external/curlcpp/LICENSE](external/curlcpp/LICENSE) and is applicable to everything in the [external/curlcpp](external/curlcpp) folder, and any subfolders.
* [GoogleTest](https://github.com/google/googletest). The license for GoogleTest can be found in the GoogleTest [GitHub repository](https://github.com/google/googletest/blob/355d57d90d9744c41ac7c99f1e960778f1c63040/LICENSE), and is applicable to the [pch.h and pch.cpp files](tests/) in the tests directory.
