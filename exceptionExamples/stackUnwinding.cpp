#include <iostream>
using namespace std;

class Resource {
public:
    Resource() { cout << "Resource acquired" << endl; }
    ~Resource() { cout << "Resource released" << endl; }
};

int main() {
    try {
        Resource r;
        throw "An error occurred!";
    }
     catch (const char* e) 
    {
        cout << "Exception: " << e << endl;
    }
    return 0;
}
