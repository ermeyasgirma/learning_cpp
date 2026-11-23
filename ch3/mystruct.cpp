#include <iostream>
using namespace std;

class MyClass {
    int myInt; // this is private by default
};


// Structs are intended for objects that carry data
// and are basically just for setting and getting
struct MyStruct {
    int myInt; // this is public by default
};

int main() {
    return 0;
}