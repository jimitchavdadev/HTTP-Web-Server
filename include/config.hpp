#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config {
public:
    Config(const std::string& filename);
    int get_port() const { return port_; }
    std::string get_root_dir() const { return root_dir_; }
    int get_thread_pool_size() const { return thread_pool_size_; }
    size_t get_cache_size_mb() const { return cache_size_mb_; }

private:
    int port_;
    std::string root_dir_;
    int thread_pool_size_;
    size_t cache_size_mb_;
};

#endif // CONFIG_HPP