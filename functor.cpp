#include<iostream>

class Funct
{
    int val;
    public:
    Funct(){}
    Funct(int data):val(data){std::cout <<"Constructor !!"<<std::endl;}

    int operator ()(int data)
    {
        std::cout <<"oprator overloading executed!!"<<std::endl;
        return val*data;
    }
};

int main()
{
    Funct obj(10);
    std::cout<<obj(23)<<std::endl;
    std::cout<<obj(10)<<std::endl;

}
