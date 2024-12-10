//catching all exceptions

#include <iostream>
using namespace std;

// int main() {
//     try {
//         throw 3.14;
//     } catch (...) {
//         cout << "Caught an exception of unknown type!" << endl;
//     }
//     return 0;
// }

//nested try-catch block


int main() {
    try {
        try {
            throw "Inner exception"; //only throw; not allowed here we need to give msg also or datatype
        } catch (const char* e) {
            cout << "Handled in inner catch: " << e << endl;
            int a =777;
            throw &a ;  // Re-throwing exception
            //throw; // this is allowed here 
        }
    } catch (const int* a) {
        cout << "Handled in outer catch: " << *a << endl;
    }
    return 0;
}

