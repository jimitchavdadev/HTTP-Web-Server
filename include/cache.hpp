#ifndef CACHE_HPP
#define CACHE_HPP

#include <string>
#include <unordered_map>
#include <mutex>

class Cache {
public:
    Cache(size_t max_size_mb);
    bool get(const std::string& key, std::string& value);
    void put(const std::string& key, const std::string& value);

private:
    std::unordered_map<std::string, std::string> cache_;
    std::mutex mutex_;
    size_t max_size_bytes_;
    size_t current_size_bytes_;
};

#endif // CACHE_HPP