#include "Circle.h"

std::ostream& operator<<(std::ostream& out, const Circle& c)
{
    out << "r: " << c._r;
    return out;
}

std::istream& operator>>(std::istream& in, Circle& c)
{
    in >> c._r;

    return in;
}

Circle::Circle() : _r(0.0)
{
}

Circle::Circle(const Circle& other) : _r(other._r)
{
}

Circle::Circle(double r) : _r(r)
{
}

Circle& Circle::operator=(const Circle& other)
{
    if (this != &other)
    {
        _r = other._r;
    }

    return *this;
}

Circle Circle::operator+(double d)
{
    return Circle(_r + d);
}

//Circle& Circle::operator+(double d)
//{
//    Circle t(_r + d);
//    Circle& rt = t;
//
//    return t;
//}
