set(CRAWLER_HEADER_LIST
  Crawler.h
  GithubCrawler.h
  Networking.h
  ProjectMetadata.h
  Runcrawler.h
  JSON.h
  RepositoryCrawler.h
  Utility.h
  GithubInterface.h
)


add_library(crawler
  Crawler.cpp
  GithubCrawler.cpp
  Networking.cpp
  Runcrawler.cpp
  JSON.cpp
  RepositoryCrawler.cpp
  Utility.cpp
  GithubInterface.cpp
  ${CRAWLER_HEADER_LIST}
)

