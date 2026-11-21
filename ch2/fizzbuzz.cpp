#include <iostream>
using namespace std;

void fizzBuzz(int n);

int main() {
    fizzBuzz(30);
    return 0;
}

void fizzBuzz(int n) {
    for (int i = 0; i <= n; i++) {
        if (i % 15 == 0) {
            cout << "FizzBuzz" << endl;
        } else if (i % 3 == 0) {
            cout << "Fizz" << endl;
        } else if (i % 5 == 0) {
            cout << "Buzz" << endl;
        } else {
            cout << i << endl;
        }
    }
}