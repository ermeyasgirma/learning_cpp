#include <iostream>
using namespace std;

int main() {
    string Day {"Thursday"};
    int dayNumber {4};

    switch (dayNumber) {
        case 1:
            cout << "Monday";
            break;
        case 2:
            cout << "Tuesday";
            break;
        case 3:
            cout << "skipping";
            break;
        case 4:
            cout << "Thirsty Thursday \n";
            break;
        case 5:
            [[fallthrough]];
        case 6:
        case 7:
            cout << "Weekend";
            break;
        default:
            cout << "Please enter a valid day of the week";
    }
    return 0;
}