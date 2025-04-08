cmake_minimum_required(VERSION 3.10)

project(TBotSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Includes
include_directories(headers)

# Subdirectories
# add_subdirectory(tests)
add_subdirectory(src)
