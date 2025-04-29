## 📌 Objective

The primary goal of this project is to implement a **lightweight multithreaded HTTP web server** in C++ capable of:
- Serving static files like HTML, CSS, JavaScript, and images.
- Handling multiple client requests concurrently using a thread pool.
- Supporting configuration-based customization and efficient file delivery with an in-memory caching mechanism.

This project aims to demonstrate foundational server architecture concepts including socket programming, HTTP parsing, thread synchronization, and caching.


## 📁 Project Structure

```plaintext
.
├── build/                  # Build output directory (ignored by VCS)
├── config/
│   └── server.conf         # Configuration file for the server
├── docs/                   # Documentation (API, design, README)
├── include/                # Header files for all modules
│   ├── cache.hpp
│   ├── config.hpp
│   ├── file_handler.hpp
│   ├── http_parser.hpp
│   ├── logger.hpp
│   ├── server.hpp
│   ├── signal_handler.hpp
│   └── thread_pool.hpp
├── scripts/                # Build/test/run helper scripts
│   ├── build.sh
│   ├── run.sh
│   └── test.sh
├── src/                    # Source code implementation
│   ├── cache.cpp
│   ├── config.cpp
│   ├── file_handler.cpp
│   ├── http_parser.cpp
│   ├── logger.cpp
│   ├── main.cpp
│   ├── server.cpp
│   ├── signal_handler.cpp
│   └── thread_pool.cpp
└── www/                    # Static content served (HTML, CSS, JS, images)
```


## ⚙️ How It Works

### 1. Server Initialization
- Reads configuration from `config/server.conf` (port, thread pool size, cache size, etc.).
- Creates a socket, binds it to the configured port, and listens for incoming TCP connections.

### 2. Thread Pool & Request Handling
- Incoming connections are accepted and assigned to worker threads from the thread pool.
- Each worker reads the HTTP request, parses it, and responds accordingly.

### 3. File Handling & Caching
- Checks if the requested file is in the in-memory cache.
- If present (cache hit), returns the cached content.
- If not (cache miss), reads the file from the `www/` directory, stores it in cache, and returns it.

### 4. HTTP Parsing & Response
- A lightweight HTTP parser extracts method, path, and version.
- A valid response is constructed (with appropriate `Content-Type` and `Content-Length`) and sent back to the client.

### 5. Logging & Shutdown
- All connections and events are logged in a thread-safe manner.
- Handles SIGINT/SIGTERM signals for graceful server shutdown.

