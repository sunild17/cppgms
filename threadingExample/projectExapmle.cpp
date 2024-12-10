#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <functional>

using namespace std;

// Task Manager Class
class TaskManager {
private:
    queue<function<void()>> tasks;  // Task queue to hold jobs
    mutex taskMutex;               // Mutex to protect task queue
    condition_variable taskCV;     // Condition variable for task notification
    atomic<bool> stopFlag;         // Flag to stop threads //Thread-safe data structures using atomic
    vector<thread> threadPool;     // Thread pool

public:
    // Constructor: Create a thread pool
    TaskManager(size_t numThreads) : stopFlag(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            threadPool.emplace_back([this]() { this->workerThread(); });
        }
    }

    // Destructor: Stop all threads
    ~TaskManager() {
        stopFlag.store(true);  // Set the stop flag
        taskCV.notify_all();   // Wake up all threads
        for (thread& t : threadPool) {
            if (t.joinable()) {
                t.join();       // Wait for all threads to finish
            }
        }
    }

    // Add a task to the queue
    void addTask(function<void()> task) {
        {
            lock_guard<mutex> lock(taskMutex);
            tasks.push(task);  // Add task to the queue
        }
        taskCV.notify_one();  // Notify one thread
    }

private:
    // Worker thread function
    void workerThread() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(taskMutex);
                taskCV.wait(lock, [this]() { return stopFlag.load() || !tasks.empty(); });

                if (stopFlag.load() && tasks.empty()) {
                    return;  // Exit the thread if stop is requested and tasks are empty
                }

                task = tasks.front();  // Get the next task
                tasks.pop();           // Remove it from the queue
            }
            task();  // Execute the task
        }
    }
};

// Simulate a job
void simulateJob(int jobId, int duration) {
    cout << "Job " << jobId << " started on thread " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::seconds(duration));  // Simulate work
    cout << "Job " << jobId << " finished on thread " << this_thread::get_id() << endl;
}

// Log writer function
void writeLog(const string& message) {
    static mutex logMutex;  // Separate mutex for logging
    lock_guard<mutex> lock(logMutex);
    cout << "Log: " << message << " [Thread: " << this_thread::get_id() << "]" << endl;
}

// Data generator function
void generateData(int dataId) {
    cout << "Data generated: " << dataId << " on thread " << this_thread::get_id() << endl;
}

int main() {
    const size_t numThreads = 4;  // Number of threads in the pool
    TaskManager taskManager(numThreads);

    // Add tasks to the task manager
    for (int i = 1; i <= 10; ++i) {
        taskManager.addTask([i]() { simulateJob(i, i % 3 + 1); });  // Add job tasks
        taskManager.addTask([i]() { writeLog("Task " + to_string(i) + " logged"); });  // Add log tasks
        taskManager.addTask([i]() { generateData(i); });  // Add data generation tasks
    }

    this_thread::sleep_for(chrono::seconds(15));  // Allow threads to process tasks
    cout << "Main thread exiting." << endl;
    return 0;
}
