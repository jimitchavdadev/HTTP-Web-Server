#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
};

#endif // THREAD_POOL_HPP