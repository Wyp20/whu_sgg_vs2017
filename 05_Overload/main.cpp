#include "Circle.h"

int main(void)
{
    Circle c1(2.0), c3;

    Circle c2(c1);

    c2 = c1;

    c3 = c3 + 0.2;

    std::cout << c3 << std::endl;
    // <<(std::cout, c3);

    std::cin >> c3;
    std::cout << c3 << std::endl;

    return 0;
}