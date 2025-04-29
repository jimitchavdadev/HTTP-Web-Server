#include "config.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

Config::Config(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + filename);
    }

    // Default values
    port_ = 8080;
    root_dir_ = "./www";
    thread_pool_size_ = 4;
    cache_size_mb_ = 10;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "port") port_ = std::stoi(value);
            else if (key == "root_dir") root_dir_ = value;
            else if (key == "thread_pool_size") thread_pool_size_ = std::stoi(value);
            else if (key == "cache_size_mb") cache_size_mb_ = std::stoul(value);
        }
    }
}