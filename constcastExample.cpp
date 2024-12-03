#include <iostream>
void modifyValue(const int& x)  //int& x = val; pass by ref
 {
    int& modifiable = const_cast<int&>(x);
    modifiable = 42; // Modifies the original value (undefined behavior if x is const)
}

int main() {
    int val = 10;
    modifyValue(val);
    std::cout << val << '\n'; // Output: 42

    //const cast example
    const int val2 = 40;
    //val2 = 50; //error 
    int* modi = const_cast<int*> (&val2);
    *modi = 50;
    std::cout <<"const cast example- >"<<*modi <<std::endl;
    return 0;
}