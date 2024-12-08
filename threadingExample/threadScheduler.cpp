#include "threadScheduler.h"
#include <iostream>

ThreadScheduler::ThreadScheduler(size_t numThreads) : stopFlag(false) {
    // Create worker threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(&ThreadScheduler::workerThread, this);
    }
}

ThreadScheduler::~ThreadScheduler() {
    stop();
}

void ThreadScheduler::addTask(const std::function<void()>& task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push(task);
    }
    condition.notify_one(); // Notify a worker thread
}

void ThreadScheduler::stop() {
    stopFlag = true; // Set stop flag
    condition.notify_all(); // Wake up all threads

    for (std::thread& thread : threads) {
        if (thread.joinable()) {
            thread.join(); // Wait for threads to finish
        }
    }
}

void ThreadScheduler::workerThread() {
    while (!stopFlag) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this]() { return stopFlag || !taskQueue.empty(); });

            if (stopFlag && taskQueue.empty()) {
                return; // Exit thread
            }

            task = taskQueue.front(); // Get task
            taskQueue.pop();          // Remove it from the queue
        }

        try {
            task(); // Execute task
        } catch (const std::exception& ex) {
            std::cerr << "Task execution error: " << ex.what() << std::endl;
        }
    }
}
