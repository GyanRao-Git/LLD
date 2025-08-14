#include <iostream>
#include <cmath>
using namespace std;


//forcing method volume on both 2d and 3d shape breaks the rule
//therefore make different interfaces

// Base interface: only area()
class Shape {
public:
    virtual double area() = 0;
    virtual ~Shape() {}
};

//  Extended interface: adds volume()
class ThreeDShape : public Shape {
public:
    virtual double volume() = 0;
};

//  2D shape: Square
class Square : public Shape {
private:
    double side;

public:
    Square(double side) {
        this->side = side;
    }

    double area() override {
        return side * side;
    }
};

//  2D shape: Circle
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double radius) {
        this->radius = radius;
    }

    double area() override {
        return 3.14 * radius * radius;
    }
};

//  3D shape: Cube
class Cube : public ThreeDShape {
private:
    double side;

public:
    Cube(double side) {
        this->side = side;
    }

    double area() override {
        return 6 * side * side; // Surface area
    }

    double volume() override {
        return side * side * side;
    }
};

int main() {
    Shape* s1 = new Square(4);
    Shape* s2 = new Circle(3);
    ThreeDShape* s3 = new Cube(2);

    cout << "Square area: " << s1->area() << endl;
    cout << "Circle area: " << s2->area() << endl;
    cout << "Cube area: " << s3->area() << endl;
    cout << "Cube volume: " << s3->volume() << endl;

    delete s1;
    delete s2;
    delete s3;

    return 0;
}
