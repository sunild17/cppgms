#include<iostream>
using namespace std;

class Base
{
    int var;
    public:
    Base(){}
     Base(int data):var(data){}

    void print()
    {
        cout<<"data"<<var<<endl;
    }
};

void fun(Base b)
{
    b.print();
}

int main()
{
    Base b(10);
   // Base b2 = 20;

    fun(b);

    fun(30);
    // fun(b2);

    Base b3 = Base(50);  
     fun(b3);
    
}