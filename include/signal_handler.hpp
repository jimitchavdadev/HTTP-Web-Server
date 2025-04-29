#ifndef SIGNAL_HANDLER_HPP
#define SIGNAL_HANDLER_HPP

#include <atomic>

void setup_signal_handler();
extern std::atomic<bool> running;

#endif // SIGNAL_HANDLER_HPP