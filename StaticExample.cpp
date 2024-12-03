#include <iostream>
class Base {
public:
   virtual void print() { std::cout << "Base\n"; }
};

class Derived : public Base {
public:
    void print() override { std::cout << "Derived\n"; }
};

int main() {
    Base* basePtr = new Derived();
    Derived* derivedPtr = static_cast<Derived*>(basePtr); // Safe since basePtr actually points to a Derived
    derivedPtr->print(); // Output: Derived
    basePtr->print();
    delete basePtr;


    
    std::cout << "\n"<<std::endl;;
    int a=10;
    int b=20;
    float c = static_cast<float>(a+b)/4;
    //float c =(float)(a+b)/4;
    std::cout<<"c->"<<c<<std::endl;
    return 0;
}