#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    long numProcessors = sysconf(_SC_NPROCESSORS_ONLN); // Get the number of online logical processors
    if (numProcessors == -1) {
        perror("sysconf");
        return 1;
    }

    cout << "Number of logical processors: " << numProcessors << endl;
    return 0;
}

