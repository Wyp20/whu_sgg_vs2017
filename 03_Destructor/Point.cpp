#include <iostream>
#include <iomanip>
#include "Point.h"  

PointHelper::PointHelper(const char* fileName)
{
    _out.open(fileName, std::ios::app | std::ios::out);
}

bool PointHelper::save(const Point& point)
{
    if (!_out.is_open())
    {
        std::cout << "The file is not open." << std::endl;
        return false;
    }

    _out.setf(std::ios::fixed); // 定点表示

    _out << std::setprecision(3) << "x: " << point._x << ", y: " << point._y << std::endl;
    return true;
}

PointHelper::~PointHelper()
{
    std::cout << "PointHelper::~PointHelper()" << std::endl;
    _out.close();
}