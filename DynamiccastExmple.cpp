#include <iostream>
class Base {
   virtual void dummy() {std::cout << "base dummy function\n";} // Makes the class polymorphic
};

class Derived : public Base {
public:
    void specificFunction() { std::cout << "Derived specific function\n"; }
     void dummy() {std::cout << "derrived dummy function\n";}
};

class Derrived2 : public Base {
    public :
        void dummy() {std::cout << "derrived2 dummy function\n";}
};

int main() {
    Base* basePtr = new Base(); // Base pointer to a Base object
    Derived* derivedPtr =  dynamic_cast<Derived*>(basePtr);   //like  Derived* nn= new Base(); 
    
    //  Derived* dPtr = new Derived();
    //  Base* bptr = dynamic_cast<Base*>(dPtr); //working case
    
    //check if derivedPtr is nullptr
    if (derivedPtr) {
        derivedPtr->specificFunction();
    } else {
        std::cout << "dynamic_cast failed\n"; // Output: dynamic_cast failed
    }

   //derivedPtr->dummy(); //wrong Segmentation fault (core dumped) without check nullpr calling function

    //Derrived2  class code below
    Derived* ptr1 = new Derived();
    Base* ptr2 = dynamic_cast<Base*> (ptr1); //upcasting correct way

    ;
    ;
    ;
    Derrived2* ptr3 = dynamic_cast<Derrived2*> (ptr2); //compils fine but logically wrong downcast 
    if(ptr3 == nullptr)
    {
        std::cout << "dynamic_cast failed\n";
    }

   delete basePtr;
    return 0;
}
