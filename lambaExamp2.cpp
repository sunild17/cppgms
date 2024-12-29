
#include <iostream>
#include <thread>
#include <functional> // For std::function

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
    slave(std::function<int(std::string)> func)
    {
        someFunc();
        int res=func("My function executed!!");
        std::cout<<res<<std::endl;
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
    int a = 10;
    int b = 20;
    auto func = [&obj1,a,b](std::string str) { std::cout<<str<<std::endl; obj1.add(a,b); return 1;  };

    slave obj2(func);
    
    return 0;
}