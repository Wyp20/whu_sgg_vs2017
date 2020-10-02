#include <iostream>

//void Swap(int a, int b)
//{
//    int tmp = a;
//    a = b;
//    b = tmp;
//
//    std::cout << "a_addr: " << &a << ", b_addr: " << &b << std::endl;
//}

void Swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;

    std::cout << "a_addr: " << &a << ", b_addr: " << &b << std::endl;
}

int main(void)
{
    int i = 0;
    int& ri = i;
    std::cout << &i << std::endl;
    std::cout << &ri << std::endl;
    i = 10;
    std::cout << "ri: " << ri << std::endl;

    int x(5), y(10);
    std::cout << "x_addr: " << &x << ", y_addr: " << &y << std::endl;
    Swap(x, y);
    std::cout << "x: " << x << ", y: " << y << std::endl;

    return 0;
}
