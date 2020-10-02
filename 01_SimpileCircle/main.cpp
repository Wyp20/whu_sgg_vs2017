#include <iostream>
#include "Circle.h"

Circle gc;

int main(void)
{
    Circle c1, c2;
    c1.setCount(1);
    std::cout << "class call: " << Circle::getCount() << std::endl;
    std::cout << "object call: " << c2.getCount() << std::endl;

    c1.setR(2.0);
    c2.setR(1.0);
    std::cout << c1.area() << std::endl;

    int i = 0;

    return 0;
}
