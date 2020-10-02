#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <iostream>

class Circle
{
    friend std::ostream& operator<<(std::ostream& out, const Circle& c);
    friend std::istream& operator>>(std::istream& in, Circle& c);

private:
    double _r;

public:
    Circle();
    Circle(const Circle& other);
    Circle(double r);

    Circle& operator=(const Circle& other);
    Circle operator+(double d);
    //Circle& operator+(double d);
};

std::ostream& operator<<(std::ostream& out, const Circle& c);
std::istream& operator>>(std::istream& in, Circle& c);

#endif
