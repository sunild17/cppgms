#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5; // Maximum size of the shared buffer
queue<int> buffer;         // Shared buffer
mutex mtx;                 // Mutex to protect the shared buffer
condition_variable cv;     // Condition variable to signal threads
bool done = false;         // Flag to stop the producer and consumer threads

// Producer function
void producer(int id) {
    int value = 0; // Value to produce
    while (!done) {
        // Simulate production delay
        this_thread::sleep_for(chrono::milliseconds(100));

        unique_lock<mutex> lock(mtx); // Lock the mutex
        // Wait if the buffer is full
        cv.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        // Add a new item to the buffer
        buffer.push(value);
        cout << "Producer " << id << " produced: " << value << endl;
        value++;

        // Notify consumers
        cv.notify_all();
    }
}

// Consumer function
void consumer(int id) {
    while (!done) {
        unique_lock<mutex> lock(mtx); // Lock the mutex

        // Wait if the buffer is empty
        cv.wait(lock, [] { return !buffer.empty(); }); //condition variable true->it will not wait
                                                        //condition variable false->it will wait

        // Consume an item from the buffer
        int value = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed: " << value << endl;

        // Notify producers
        cv.notify_all();

        // Simulate consumption delay
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main() {
    thread prod1(producer, 1);
    thread prod2(producer, 2);
    thread cons1(consumer, 1);
    thread cons2(consumer, 2);

    // Let the threads run for a while
    this_thread::sleep_for(chrono::seconds(5));

    // Signal threads to stop
    done = true;
    cv.notify_all();

    // Join threads
    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();

    cout << "Producer-Consumer simulation finished!" << endl;

    return 0;
}
