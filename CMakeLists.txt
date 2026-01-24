cmake_minimum_required(VERSION 3.13)

project(NetSim)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------
# Biblioteka projektu
# --------------------
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(netsim_lib ${SOURCE_FILES})

target_include_directories(netsim_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# --------------------
# Główna aplikacja
# --------------------
add_executable(SimulationMain main.cpp)
target_link_libraries(SimulationMain PRIVATE netsim_lib)

# --------------------
# GoogleTest
# --------------------
add_subdirectory(googletest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp)

add_executable(NetSimTests ${TEST_SOURCES})

target_link_libraries(NetSimTests
    PRIVATE
        netsim_lib
        GTest::gtest
        GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(NetSimTests)
