#include <iostream>
#include <thread>
#include <vector>
#include <exception>

using namespace std;

void dummyTask() {
    this_thread::sleep_for(chrono::seconds(10)); // Simulate work
}

int main() {
    vector<thread> threads; // Store created threads
    int count = 0;

    try {
        while (true) {
            threads.emplace_back(dummyTask); // Create a new thread
            count++;
            cout << "Thread " << count << " created successfully." << endl;
        }
    } catch (const exception& e) {
        cout << "Failed to create thread " << count + 1 << ": " << e.what() << endl;
    }

    // Clean up all threads
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    cout << "Maximum threads that could be created: " << count << endl;
    return 0;
}
