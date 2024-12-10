#include <iostream>
using namespace std;

//Basic Syntax of Exception Handling

// int main() {
//     try {
//         int a = 10, b = 0;
//         if (b == 0)
//             throw "Division by zero error!";
//         cout << a / b << endl;
//     } catch (const char* e) {
//         cout << "Caught an exception: " << e << endl;
//     }
//     return 0;
// }

//multiple catch blocks


int main() {
    try {
        throw 404; // Throwing an integer
        cout<<"after try block"<<endl;        
        throw 3.14;        // Throwing a double
        throw "Error!";    // Throwing a string literal
    } catch (int e) {
        cout << "Caught integer exception: " << e << endl;
    } catch (double e) {
        cout << "Caught double exception: " << e << endl;
    } catch (const char* e) {
        cout << "Caught string exception: " << e << endl;
    }
    return 0;
}



