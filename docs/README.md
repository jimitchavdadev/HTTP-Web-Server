# Multithreaded HTTP Web Server

A lightweight, multithreaded HTTP web server implemented in C++ that serves static files and supports concurrent client connections.

## Features
- Handles HTTP GET requests
- Serves static HTML, CSS, JS, and image files
- Multithreaded with a thread pool
- In-memory caching
- Graceful shutdown on SIGINT/SIGTERM
- Configurable via `config/server.conf`

## Prerequisites
- CMake 3.10+
- C++17-compatible compiler (e.g., g++)
- POSIX system (Linux/macOS)
- Catch2 for testing (optional)

## Build Instructions
1. Run `./scripts/build.sh` to build the project.
2. Run `./scripts/run.sh` to start the server.

## Testing
1. Install Catch2 (`sudo apt install catch2` or equivalent).
2. Run `./scripts/test.sh` to execute unit tests.

## Configuration
Edit `config/server.conf` to set:
- `port`: Server port (default: 8080)
- `root_dir`: Static files directory (default: `./www`)
- `thread_pool_size`: Number of worker threads (default: 4)
- `cache_size_mb`: Cache size in MB (default: 10)

## Usage
Access the server at `http://localhost:8080` in a browser.