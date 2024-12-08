#include "threadScheduler.h"
#include <iostream>
#include <chrono>

void exampleTask(int id) {
    std::cout << "Task " << id << " is running on thread " 
              << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
}



int main() {
    ThreadScheduler scheduler(4); // Create a scheduler with 4 threads


   //Add tasks to the scheduler
    for (int i = 0; i < 10; ++i) {
        scheduler.addTask([i]() { exampleTask(i); });
    }
    
    //scheduler.addTask( std::bind(exampleTask, 10)); std:bind working

    std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait to see all tasks complete
    scheduler.stop(); // Stop the scheduler

    return 0;
}
