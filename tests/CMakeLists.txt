enable_testing()

# Google Test
add_subdirectory(../googletest-src googletest-build)

#Test sources
set(TEST_SOURCES
    PatternsTest.cpp
)

# Test executable
add_executable(TBotTests ${TEST_SOURCES})

# Link Google Test and project files
target_link_libraries(TBotTests PRIVATE gtest)

# Include headers
target_include_directories(TBotTests PRIVATE ../headers)

# Register the tests
add_test(NAME TBotTests COMMAND TBotTests)
