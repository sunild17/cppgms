#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

// Shared variables for synchronization
int number = 1;                      // The number to print
const int MAX_NUMBER = 100;          // The limit up to which numbers will be printed
mutex mtx;                           // Mutex to protect shared data
condition_variable cv;               // Condition variable to coordinate threads
bool isOddTurn = true;               // Flag to indicate whose turn it is (odd starts first)

// Function to print odd numbers
void printOdd() {
    while (number <= MAX_NUMBER) {
        unique_lock<mutex> lock(mtx);  // Acquire the lock
        cv.wait(lock, [] { return isOddTurn; });  // Wait until it's the odd thread's turn

        if (number > MAX_NUMBER) break;  // Exit if the number exceeds the limit
        cout << "Odd: " << number << endl;
        number++;                       // Increment the number
        isOddTurn = false;              // Switch turn to the even thread
        cv.notify_all();                // Notify the even thread
    }
}

// Function to print even numbers
void printEven() {
    while (number <= MAX_NUMBER) {
        unique_lock<mutex> lock(mtx);  // Acquire the lock
        cv.wait(lock, [] { return !isOddTurn; });  // Wait until it's the even thread's turn

        if (number > MAX_NUMBER) break;  // Exit if the number exceeds the limit
        cout << "Even: " << number << endl;
        number++;                       // Increment the number
        isOddTurn = true;               // Switch turn to the odd thread
        cv.notify_all();                // Notify the odd thread
    }
}

int main() {
    // Create two threads
    thread oddThread(printOdd);
   // thread evenThread(printEven);

    // Wait for both threads to finish
    oddThread.join();
  //  evenThread.join();

    cout << "Printing completed!" << endl;
    return 0;
}
