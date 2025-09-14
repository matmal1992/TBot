# Set sources
set(TBOT_CORE_SOURCES
    BotSimulator.cpp
    LoadCsvData.cpp
    Patterns.cpp
    Graph.cpp
)

# Create the static library
add_library(tbot_core STATIC ${TBOT_CORE_SOURCES})

# Include headers directory
target_include_directories(tbot_core 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/headers)