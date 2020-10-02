#ifndef POINT_H_
#define POINT_H_

#include <fstream>

class Point
{
public:
    double _x;
    double _y;
};

class PointHelper
{
public:
    PointHelper(const char* fileName);
    ~PointHelper();
    bool save(const Point& point);

private:
    std::ofstream _out;
};

#endif
