#include "server.hpp"
#include "signal_handler.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Add this for inet_ntoa
#include <unistd.h>
#include <stdexcept>
#include <sstream>

Server::Server(const Config& config)
    : config_(config),
      thread_pool_(config.get_thread_pool_size()),
      file_handler_(config.get_root_dir()),
      cache_(config.get_cache_size_mb()) {}

void Server::start() {
    // Setup signal handler for graceful shutdown
    setup_signal_handler();

    // Create socket
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_ < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    // Bind socket
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(config_.get_port());
    if (bind(server_socket_, (sockaddr*)&addr, sizeof(addr)) < 0) {
        throw std::runtime_error("Failed to bind socket");
    }

    // Listen
    if (listen(server_socket_, 10) < 0) {
        throw std::runtime_error("Failed to listen");
    }

    logger_.log("Server started on port " + std::to_string(config_.get_port()));

    // Accept connections
    while (running) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket_, (sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            if (!running) break;
            logger_.log("Failed to accept connection");
            continue;
        }

        // Log client connection
        std::string client_ip = inet_ntoa(client_addr.sin_addr);
        logger_.log("New connection from " + client_ip);

        // Enqueue client handling task
        thread_pool_.enqueue([this, client_socket] { handle_client(client_socket); });
    }

    stop();
}

void Server::stop() {
    close(server_socket_);
    logger_.log("Server stopped");
}

void Server::handle_client(int client_socket) {
    // Read request
    char buffer[1024];
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0';

    HttpResponse response;
    try {
        // Parse request
        HttpRequest request = parser_.parse_request(buffer);
        logger_.log("Request: " + request.method + " " + request.path);

        // Check cache
        std::string content;
        std::string content_type; // Store content type here
        if (cache_.get(request.path, content)) {
            response.status_code = 200;
            response.status_text = "OK";
            response.content_type = file_handler_.get_file_content(request.path, content_type); // Get content type
            response.content_type = content_type; // Use the returned content type
            response.body = content;
        } else {
            // Serve file
            response.body = file_handler_.get_file_content(request.path, content_type);
            response.content_type = content_type; // Use the returned content type
            response.status_code = 200;
            response.status_text = "OK";
            cache_.put(request.path, response.body); // Cache the response
        }
    } catch (const std::runtime_error& e) {
        response.status_code = 404;
        response.status_text = "Not Found";
        response.content_type = "text/plain";
        response.body = e.what();
    } catch (...) {
        response.status_code = 500;
        response.status_text = "Internal Server Error";
        response.content_type = "text/plain";
        response.body = "Server error";
    }

    // Send response
    std::string response_str = parser_.build_response(response);
    write(client_socket, response_str.c_str(), response_str.size());

    // Close client socket
    close(client_socket);
}