#ifndef SERVER_HPP
#define SERVER_HPP

#include "config.hpp"
#include "thread_pool.hpp"
#include "logger.hpp"
#include "file_handler.hpp"
#include "http_parser.hpp"
#include "cache.hpp"

class Server {
public:
    Server(const Config& config);
    void start();
    void stop();

private:
    void handle_client(int client_socket);
    Config config_;
    ThreadPool thread_pool_;
    Logger logger_;
    FileHandler file_handler_;
    HttpParser parser_;
    Cache cache_;
    int server_socket_;
};

#endif // SERVER_HPP