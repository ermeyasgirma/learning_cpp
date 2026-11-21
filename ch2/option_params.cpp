#include <iostream>
using namespace std;

float sum(float a, float b = 5.0f) {
    return a + b;
}

int main() {

    cout << sum((sum(2)), 7.0f) << endl;
    return 0;
}