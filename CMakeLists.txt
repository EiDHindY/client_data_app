cmake_minimum_required(VERSION 3.10)

project(safecoin)

# Use C++ 23 Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Where to look for .h files
include_directories(include)

# Find all .cpp files in src and subfolders
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the final executable
add_executable(Safecoin ${SOURCES})
