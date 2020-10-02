#ifndef POINT_H_
#define POINT_H_

#include <iostream>

class Point
{
    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    friend std::istream& operator>>(std::istream& in, Point& p);

public:
    double _x;
    double _y;

public:
    Point() : _x(0.0), _y(0.0) {}

    Point& operator=(const Point& other);
};

std::ostream& operator<<(std::ostream& out, const Point& p);
std::istream& operator>>(std::istream& in, Point& p);

#endif // !POINT_H_

