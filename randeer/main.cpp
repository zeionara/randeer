#include <iostream>

using namespace std;

extern "C"
void sample(long number = 0) {
    cout << number << endl;
}

