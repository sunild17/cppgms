#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>
using namespace std;


mutex m;
condition_variable cond;
int i=0;


void printEven(int range)
{
    while(i < range)

    {
         unique_lock lock(m);
    cond.wait(lock,[](){if (i%2 != 0) return false; else return true;   });

    cout<<i<<"\n";
    i++;
    cond.notify_all();
    }
   
}

void printOdd(int range)
{
     while(i < range)

    {
         unique_lock lock(m);
    cond.wait(lock,[](){if (i%2 != 0) {return true;} else return false; });

    cout<<i<<"\n";
    i++;
    cond.notify_all();
    }
}

int main()
{
    int value =10;
    thread t1(printEven,value);
    thread t2(printOdd,value);

    t1.join();
    t2.join();
    cout<<"successfully endded"<<endl;
}