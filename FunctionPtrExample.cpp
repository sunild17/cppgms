
#include <iostream>
#include <thread>

class master{
  
  public:
    void add(int a,int b)
    {
         std::cout << a+b << std::endl;
    }
};


class slave
{
   public:
    slave(void (master::*funPtr) (int,int), master& obj)
    {
        someFunc();
        (obj.*funPtr)(10,20);
    }
    
    void someFunc()
    {
        ;
        ;
        ;
        std::cout<<"somefunction executed!!!"<<std::endl;
    }
};


int main()
{
    master obj1;
    
    void (master::*addFucnPtr) (int,int);
    addFucnPtr = &master::add;
    slave obj2(addFucnPtr,obj1);
    
    return 0;
}