cmake_minimum_required(VERSION 3.10)
project(HttpWebServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
        src/main.cpp
        src/config.cpp
        src/http_parser.cpp
        src/logger.cpp
        src/server.cpp
        src/file_handler.cpp
        src/thread_pool.cpp
        src/cache.cpp
        src/signal_handler.cpp
)

# Include directories
include_directories(include)

# Executable
add_executable(http_server ${SOURCES})

# Link libraries
find_package(Threads REQUIRED)
target_link_libraries(http_server PRIVATE Threads::Threads)