#include "cache.hpp"
#include <stdexcept>

Cache::Cache(size_t max_size_mb) : max_size_bytes_(max_size_mb * 1024 * 1024), current_size_bytes_(0) {}

bool Cache::get(const std::string& key, std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = cache_.find(key);
    if (it == cache_.end()) return false;
    value = it->second;
    return true;
}

void Cache::put(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    size_t new_size = key.size() + value.size();
    if (new_size > max_size_bytes_) return; // Simple size check
    if (current_size_bytes_ + new_size > max_size_bytes_) {
        cache_.clear(); // Simple eviction (replace with LRU for production)
        current_size_bytes_ = 0;
    }
    cache_[key] = value;
    current_size_bytes_ += new_size;
}