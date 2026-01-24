cmake_minimum_required(VERSION 3.13)

project(NetSim)

set(CMAKE_CXX_STANDARD 23)

set(PROJECT_ID NETSIM)


file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

include_directories(include)

file(GLOB_RECURSE SOURCES_FILES_TEST "test/*.cpp")

add_library(LIB ${SOURCE_FILES})


add_executable(SimulationMain main.cpp)
target_link_libraries(SimulationMain PRIVATE LIB)
