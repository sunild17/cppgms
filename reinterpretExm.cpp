#include <iostream>
int main() {
    int a = 300;
    char* charPtr = reinterpret_cast<char*>(&a); //unsafe
    std::cout << charPtr << '\n'; // Output: 'A' (interpreted as ASCII value)

    int* ptr2 = new int[20]; //heap
   
    int* ptr3 = new int(30); //heap
    
    int var = 30;
    int* ptr4 = &var; //satck


    std::cout << *ptr2 << '\n';

    char b = 'B';
    int c = b;

    return 0;
}
