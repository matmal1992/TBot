cmake_minimum_required(VERSION 3.10)

project(TBotSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers directory
include_directories(headers)
add_subdirectory(tests)

# Add executable (main.cpp + all .cpp files in src/)
file(GLOB SRC_FILES "src/*.cpp")
add_executable(TBotSimulator main.cpp ${SRC_FILES})
