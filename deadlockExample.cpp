#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Two mutexes representing shared resources
mutex resourceA;
mutex resourceB;

void thread1() {
    lock_guard<mutex> lock1(resourceA); // Lock Resource A
    cout << "Thread 1: Locked Resource A" << endl;

    // Simulate some work
    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> lock2(resourceB); // Wait for Resource B
    cout << "Thread 1: Locked Resource B" << endl;
}

void thread2() {
    lock_guard<mutex> lock1(resourceB); // Lock Resource B
    cout << "Thread 2: Locked Resource B" << endl;

    // Simulate some work
    this_thread::sleep_for(chrono::milliseconds(100));

    lock_guard<mutex> lock2(resourceA); // Wait for Resource A
    cout << "Thread 2: Locked Resource A" << endl;
}

int main() {
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    cout << "Threads finished execution" << endl;
    return 0;
}
