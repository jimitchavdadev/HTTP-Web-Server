#include "signal_handler.hpp"
#include <csignal>

std::atomic<bool> running(true);

void signal_handler(int) {
    running = false;
}

void setup_signal_handler() {
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);
}