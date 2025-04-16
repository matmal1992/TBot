cmake_minimum_required(VERSION 3.10)

project(TBotSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("$<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall;-Werror;-Wno-attributes;-g;-Og;>")

# Includes
include_directories(headers)

# Subdirectories
# add_subdirectory(tests)
add_subdirectory(src)
