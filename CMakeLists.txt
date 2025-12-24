cmake_minimum_required(VERSION 3.10)

project(safecoin)

# Use C++ 23 Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Where to look for .h files
include_directories(include)

# 1. Gather all Core Logic (Everything in src/*.cpp)
file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")

# 2. Filter out the App's Main (So tests don't get confused)
list(REMOVE_ITEM CORE_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

# 3. Gather all Test Files
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# 4. Define the Catch2 Engine path clearly
set(CATCH_ENGINE "include/catch_amalgamated.cpp")

# TARGET A: The Main Application
# (Core Logic + The App's Main)
add_executable(Safecoin 
${CORE_SOURCES} 
"src/main.cpp")

# TARGET B: The Test Suite
# (Core Logic + The Test's Main + The Catch2 Engine)
add_executable(SafecoinTests 
${TEST_SOURCES}
${CORE_SOURCES}
${CATCH_ENGINE})

