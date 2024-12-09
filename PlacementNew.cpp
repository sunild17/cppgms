#include<iostream>
using namespace std;

class base
{
    int a;
    public:
    base(){
        cout<<"Construcrtor"<<endl;
    }
    void  setA(double d) {this->a=d;}
    void printA() {cout << this->a <<endl;};
    ~base(){
        cout<<"Destructor"<<endl;
    }

};

int main()
{
    cout<<"normal class"<<endl;
    base *ptr = new base();
    delete ptr;

    char *mem = new char[5*sizeof(int)];

    //cout<<"size:"<< sizeof(double) <<endl;

    base *obj1 = new(&mem[0]) base();
     base *obj2 = new(&mem[4]) base();
    base *obj3 = new(&mem[8]) base();

    // cout<<"size:"<< sizeof(obj1) <<endl;
    // cout<<"size:"<< sizeof(obj2) <<endl;
    // cout<<"size:"<< sizeof(obj3) <<endl;


    obj1->setA(9.45);
    obj1->printA();

    // obj2->setA(10.45);
    // obj2->printA();

    // obj3->setA(11.45);
    // obj3->printA();

    obj1 -> ~base();
    obj2 -> ~base();
    obj3 -> ~base();

    delete[] mem;

    }