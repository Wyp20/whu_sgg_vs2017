#include <iostream>
#include "Circle.h"

Circle::Circle()
{
    std::cout << "Circle::Circle()" << std::endl;
    _r = 1.0;
}

bool Circle::setR(double r)
{
    bool ret = true;
    if (r > 0)
    {
        _r = r;
    }
    else
    {
        std::cout << "Error input!";
        ret = false;
    }
    return ret;
}