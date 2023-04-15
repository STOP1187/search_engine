cmake_minimum_required(VERSION 3.21)

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
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

include_directories(include)
include_directories(src)
add_subdirectory(Tests)



add_executable(search_engine
        src/main.cpp
        include/ConverterJSON.h
        src/ConverterJSON.cpp
        include/InvertedIndex.h
        src/InvertedIndex.cpp
        include/SearchServer.h
        src/SearchServer.cpp
        include/exeptionClass.h
        src/exeptionClass.cpp
        include/RequestNotFoundExeption.h
        src/RequestNotFoundExeption.cpp
        include/AnswersNotFoundExeption.h
        src/AnswersNotFoundExeption.cpp)

add_custom_command(TARGET search_engine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/config/ $<TARGET_FILE_DIR:search_engine>)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

