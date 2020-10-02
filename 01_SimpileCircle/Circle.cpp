#include <iostream>
#include "Circle.h"

int Circle::_count = 0;

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

int Circle::getCount()
{
    return _count;
}

void Circle::setCount(int c)
{
    _count = c;
}

