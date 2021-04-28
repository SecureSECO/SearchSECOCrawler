set(CRAWLER_HEADER_LIST
  Crawler.h
  GithubCrawler.h
  Networking.h
  ProjectMetadata.h
  Runcrawler.h
)


add_library(crawler
  Crawler.cpp
  GithubCrawler.cpp
  Networking.cpp
  Runcrawler.cpp
  ${CRAWLER_HEADER_LIST}
)

