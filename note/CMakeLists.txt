# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 2.8)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11   -pthread" )
add_definitions(-std=c++11)
# Set the project name
project (test)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    test.cpp
    )

INCLUDE_DIRECTORIES(.)
# Add an executable
add_executable(more_effective_c++  more_effective_c++.cpp)
add_executable(test ${SOURCES})
#target_link_libraries(test pthread rt)
#
# Binaries
install (TARGETS more_effective_c++  DESTINATION bin)

