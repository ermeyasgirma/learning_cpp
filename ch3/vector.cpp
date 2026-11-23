#include <iostream>
using namespace std;

struct Vector3D {
    float x;
    float y;
    float z;


    // Member function for multiplying two vectors
    // eg v1 * otherV
    Vector3D operator*(Vector3D &other) {
        return Vector3D{
            this->x * other.x,
            this->y * other.y,
            this->z * other.z
        };
    }
};

// Addition is a commmuative opetation so the order of the operands does not matter
Vector3D operator+(Vector3D &a, Vector3D &b) {
    return Vector3D{
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

int main () {
    Vector3D a{1.0f, 2.0f, 3.0f};
    Vector3D b{4.0f, 5.0f, 6.0f};
    Vector3D c = a + b; 

    cout << "c.x: " << c.x << endl;
    cout << "c.y: " << c.y << endl;
    cout << "c.z: " << c.z << endl;

    return 0;
}