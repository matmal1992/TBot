

# Google Test
add_subdirectory(${CMAKE_SOURCE_DIR}/googletest-src ${CMAKE_SOURCE_DIR}/googletest-build)

#Test sources
set(TEST_SOURCES
        PatternsTest.cpp
        BotSimulatorTest.cpp
)

# Test executable
add_executable(TBotTests ${TEST_SOURCES})

# Link Google Test and project files
target_link_libraries(TBotTests PRIVATE 
                        gtest_main 
                        tbot_core)

# Include headers
target_include_directories(TBotTests PRIVATE ../headers)

# Register the tests
add_test(NAME TBotTests COMMAND TBotTests)
