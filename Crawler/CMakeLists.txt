find_package(nlohmann-json REQUIRED)

set(CRAWLER_HEADER_LIST
  Crawler.h
  GithubCrawler.h
  Networking.h
  ProjectMetadata.h
  RunCrawler.h
  JSON.h
  RepositoryCrawler.h
  Utility.h
  GithubInterface.h
)


add_library(crawler
  Crawler.cpp
  GithubCrawler.cpp
  Networking.cpp
  RunCrawler.cpp
  JSON.cpp
  RepositoryCrawler.cpp
  Utility.cpp
  GithubInterface.cpp
  ${CRAWLER_HEADER_LIST}
)

