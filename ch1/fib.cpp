#include <iostream>
using namespace std;

int fib(int n) {
    if (n == 0) {return 0;}

    if (n == 1) {return 1;}

    return fib(n-1) + fib(n-2);
}

int main() {
    int fib10 = fib(10);
    cout << "The tenth number in the fibonacci sequence is " << fib10 << "\n";

    int8_t signedInt = 100; // 8 bits so allows values from -127 to +127
    uint8_t unsignedInt = 200; // unsigned 8 bits so allows values from 0 to 255

    float f1 = 3.14; // uses 32 bits of memory
    double d1 = 2.71828; // uses 64 bits of memory
    return 0;
}