#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    try {
        string s = "Hello";
        cout << s.at(10) << endl;  // Access out of range
    } catch (const out_of_range& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}


//standard exception types header files  <stdexcept> and <exception>.
// std::logic_error
// std::runtime_error
// std::bad_alloc
// std::out_of_range