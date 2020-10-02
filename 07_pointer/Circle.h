#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <iostream>

class Circle
{
private:
    double _r;

public:
    Circle();
    Circle(double r) : _r(r) { std::cout << "Circle::Circle()" << std::endl; }
    ~Circle() { std::cout << "Circle::Circle()" << std::endl; }

public:
    bool setR(double r);
    double getR() const { return _r; };
    inline double area();
};

inline double Circle::area()
{
    return _r * _r * 3.14;
}

#endif // !CIRCLE_H_


