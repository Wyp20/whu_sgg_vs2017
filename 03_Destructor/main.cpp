#include "Point.h"

void savePoint(const Point& p)
{
    PointHelper ph("point_test.txt");

    ph.save(p);
}

int main(void)
{
    Point p1;
    
    p1._x = p1._y = 1.0;

    savePoint(p1);

    return 0;
}