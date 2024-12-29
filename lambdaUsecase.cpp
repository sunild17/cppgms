
#include <iostream>
#include <thread>

class myThread{
  
  public:
    void add(int a,int b)
    {
         std::cout << a+b << std::endl;
    }
};


// void add(int a,int b)
// {
//      std::cout << a+b << std::endl;
// }


int main()
{
    // auto add = [](int a, int b) { return a + b; };
    // std::cout << add(1, 2); // Works with any type
    myThread obj;
    int a=10;
    int b=20;
    std::thread t1([&obj,a,b](){obj.add(a,b);});
    t1.join();
    return 0;
}