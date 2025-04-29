#include "logger.hpp"
#include <iostream>
#include <ctime>

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto now = std::time(nullptr);
    std::cout << "[" << std::ctime(&now) << "] " << message << std::endl;
}