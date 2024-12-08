#ifndef THREADSCHEDULER_H
#define THREADSCHEDULER_H

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadScheduler {
public:
    explicit ThreadScheduler(size_t numThreads);
    ~ThreadScheduler();

    // Add a task to the scheduler
    void addTask(const std::function<void()>& task);

    // Stop the scheduler gracefully
    void stop();

private:
    void workerThread(); // Worker thread function

    std::vector<std::thread> threads;             // Thread pool
    std::queue<std::function<void()>> taskQueue;  // Task queue
    std::mutex queueMutex;                        // Mutex for task queue
    std::condition_variable condition;           // Condition variable for synchronization
    std::atomic<bool> stopFlag;                  // Stop flag
};

#endif // THREADSCHEDULER_H
