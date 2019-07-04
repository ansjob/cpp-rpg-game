cmake_minimum_required(VERSION 2.8)

FILE(GLOB cpp_files src/*.cpp)

add_definitions(-Wall --std=c++0x -pg)
SET(CMAKE_BUILD_TYPE Debug)

add_executable(game ${cpp_files})

find_package(Boost 1.50 REQUIRED COMPONENTS regex)
if(Boost_FOUND)
    target_link_libraries(game boost_regex)
    target_include_directories(game PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_directories(game PRIVATE /usr/local/Cellar/boost/1.62.0/lib)
endif(Boost_FOUND)
