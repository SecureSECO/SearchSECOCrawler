# This program has been developed by students from the bachelor Computer Science at
# Utrecht University within the Software Project course.
# © Copyright Utrecht University (Department of Information and Computing Sciences)

cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

message("Building the crawler...")
if(NOT DEFINED LOGURU_INCLUDED)
   set(LOGURU_FILES
   loguru/loguru.hpp
   loguru/loguru.cpp
   )
   set(LOGURU_INCLUDED true PARENT_SCOPE)
   message("Including loguru files...")
endif()

if (WIN32)
  add_definitions(-DCURL_STATICLIB)

  include(FetchContent)
  FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.7.3)

  FetchContent_GetProperties(json)
  if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
else()
  find_package(nlohmann_json REQUIRED)
endif()

add_subdirectory(../curlcpp/src ./curlcpp)


set(CRAWLER_HEADER_LIST
  CrawlData.h
  GithubCrawler.h
  Networking.h
  ProjectMetadata.h
  RunCrawler.h
  JSON.h
  Utility.h
  GithubInterface.h
  ErrorHandler.h
  ErrorList.h
  GithubClientErrorConverter.h
  IndividualErrorHandler.h
  LoggerCrawler.h
)

add_library(crawler
  Crawler.cpp
  GithubCrawler.cpp
  Networking.cpp
  RunCrawler.cpp
  JSON.cpp
  Utility.cpp
  GithubInterface.cpp
  EmptyHandler.cpp
  ErrorHandler.cpp
  GithubClientErrorConverter.cpp
  LoggerCrawler.cpp
  LogHandler.cpp
  LogThrowHandler.cpp
  ${CRAWLER_HEADER_LIST}
  ${LOGURU_FILES}
)

target_link_libraries(crawler curlcpp nlohmann_json::nlohmann_json)
target_include_directories(crawler PUBLIC "${PROJECT_BINARY_DIR}" ../curlcpp/include)

if(CMAKE_DL_LIBS)
    target_link_libraries(crawler ${CMAKE_DL_LIBS})
endif()
