cmake_minimum_required(VERSION 3.16)
project(TBotSimulator VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default compiler flags
include(CheckCXXCompilerFlag)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#Add -Werror to debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")
enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
add_executable(tbot_runner main.cpp)
target_link_libraries(tbot_runner PRIVATE tbot_core)



