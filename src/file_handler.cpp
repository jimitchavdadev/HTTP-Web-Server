#include "file_handler.hpp"
#include <fstream>
#include <stdexcept>
#include <algorithm>

FileHandler::FileHandler(const std::string& root_dir) : root_dir_(root_dir) {
    if (root_dir_.back() != '/') root_dir_ += '/';
}

std::string FileHandler::get_file_content(const std::string& path, std::string& content_type) {
    std::string full_path = root_dir_ + (path == "/" ? "index.html" : path.substr(1));
    std::ifstream file(full_path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("File not found: " + full_path);
    }

    content_type = get_content_type(full_path);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

std::string FileHandler::get_content_type(const std::string& path) {
    // Helper function to check if string ends with a suffix
    auto ends_with = [](const std::string& str, const std::string& suffix) {
        if (str.length() < suffix.length()) return false;
        return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
    };

    if (ends_with(path, ".html")) return "text/html";
    if (ends_with(path, ".css")) return "text/css";
    if (ends_with(path, ".js")) return "application/javascript";
    if (ends_with(path, ".png")) return "image/png";
    return "application/octet-stream";
}