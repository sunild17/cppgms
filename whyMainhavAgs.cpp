#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    cout <<"1st" <<argc <<endl;

    for(int i=0;i<argc;i++)
    {
        cout <<argv [i] <<endl;
    }

}