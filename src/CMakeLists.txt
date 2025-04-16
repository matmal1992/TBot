# Add sources
set(SOURCES
    BotSimulator.cpp
    LoadCsvData.cpp
)

# Create the main executable
add_executable(TBotSimulator ${SOURCES} ../main.cpp)
target_compile_options(TBotSimulator PRIVATE -g)

# Include headers
target_include_directories(TBotSimulator PRIVATE ../headers)