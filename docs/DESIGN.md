# Design Document

## Architecture
- **Server**: Initializes socket, binds to port, and listens for connections. Uses a thread pool to handle clients.
- **Thread Pool**: Manages worker threads to process client requests concurrently.
- **HTTP Parser**: Parses incoming GET requests and builds HTTP responses.
- **File Handler**: Serves static files from the `www/` directory.
- **Cache**: In-memory cache for recently accessed files (basic LRU-like eviction).
- **Logger**: Thread-safe logging of requests and server events.
- **Config**: Reads settings from `server.conf`.
- **Signal Handler**: Handles SIGINT/SIGTERM for graceful shutdown.

## Request Flow
1. Client connects to server socket.
2. Server accepts connection and enqueues client handling task to thread pool.
3. Worker thread reads request, parses it, and checks cache.
4. If cache miss, file handler reads file from disk.
5. Response is built and sent to client.
6. Client socket is closed.

## Thread Safety
- Logger and cache use mutexes for thread-safe access.
- Thread pool ensures tasks are executed concurrently without race conditions.