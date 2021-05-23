cmake_minimum_required(VERSION 3.10)

# https://cmake.org/cmake/help/latest/guide/tutorial/index.html

# set the project name
project(htmltdcnt VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# to make config.h reachable
configure_file("${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")
include_directories("${PROJECT_BINARY_DIR}")

# add the executable
add_executable(htmltdcnt htmltdcnt.cpp)

