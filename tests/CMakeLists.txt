# This program has been developed by students from the bachelor Computer Science at
# Utrecht University within the Software Project course.
# © Copyright Utrecht University (Department of Information and Computing Sciences)

# Required by FetchContent_MakeAvailable
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project(crawler_tests)

add_subdirectory(../libSearchSECOCrawler ./Crawler)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_GetProperties(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

set(CMAKE_CXX_STANDARD 20)
set(TEST_NAME crawler_tests)
add_executable(${TEST_NAME} GithubCrawler_test.cpp JSON_test.cpp IndividualErrorHandler_test.cpp GithubInterfaceMock.cpp)
target_include_directories(${TEST_NAME} PUBLIC "${PROJECT_BINARY_DIR}" ../libSearchSECOCrawler)
target_link_libraries(${TEST_NAME} gtest_main libSearchSECOCrawler)


enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})