cmake_minimum_required(VERSION 3.22)

project(search_engine)

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

FetchContent_MakeAvailable(googletest)

enable_testing()



set(CMAKE_CXX_STANDARD 23)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)


add_executable(search_engine main.cpp ConverterJSON.h ConverterJSON.cpp InvertedIndex.h InvertedIndex.cpp SearchServer.h SearchServer.cpp)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(search_engine PRIVATE gtest_main)


gtest_discover_tests(search_engine)