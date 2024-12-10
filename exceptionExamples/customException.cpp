#include <iostream>
#include <exception>
using namespace std;

class MyException : public exception {
public:
    MyException() {cout<<"default constrctor\n"<<endl;}
    const char* what() const noexcept override {
        return "Custom exception occurred!";
    }
};

int main() {
    try {
        throw MyException();   
    } catch (const MyException& e) {  // MyException& e= MyException();
        cout << e.what() << endl;
    }
    return 0;
}
