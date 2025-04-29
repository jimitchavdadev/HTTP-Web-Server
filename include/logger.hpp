#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>

class Logger {
public:
    Logger() = default;
    void log(const std::string& message);

private:
    std::mutex mutex_;
};

#endif // LOGGER_HPP