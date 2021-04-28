set(CRAWLER_HEADER_LIST
  Crawler.h
  GithubCrawler.h
  Networking.h
  ProjectMetadata.h
  Runcrawler.h
  JSON.h
  ReposityCrawler.h
  Utility.h
  GithubInterface.h
)


add_library(crawler
  Crawler.cpp
  GithubCrawler.cpp
  Networking.cpp
  Runcrawler.cpp
  JSON.cpp
  ReposityCrawler.cpp
  Utility.cpp
  GithubInterface.cpp
  ${CRAWLER_HEADER_LIST}
)

