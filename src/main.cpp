#include "server.hpp"
#include <stdexcept>
#include <iostream>

int main() {
    try {
        Config config("config/server.conf");
        Server server(config);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}