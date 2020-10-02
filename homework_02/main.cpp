#include <iostream>
#include <iomanip>

int main(void)
{
    int array[8] = { 2, 56, 12, 6, 30, 19, 20, 25 };

    // 数组array首元素2的内存首地址
    std::cout << std::setw(20) << "array = " << array << std::endl;

    // 数组array首元素2的内存首地址
    std::cout << std::setw(20) << "&array[0] = " << &array[0] << std::endl;

    // 数组array的首地址
    std::cout << std::setw(20) << "&array = " << &array << std::endl;

    // array是首元素首地址，array+1要越过一个元素，即首元素的下一个元素的首地址
    // 所以和array的值相差4
    std::cout << std::setw(20) << "array + 1 = " << array + 1 << std::endl;

    // &array[0]是首元素首地址，&array[0]+1要越过一个元素，即首元素的下一个元素的首地址
    std::cout << std::setw(20) << "&array[0] + 1 = " << &array[0] + 1 << std::endl;

    // &array是数组首地址，&array+1要越过一个数组，即下一个数组的地址（虽然本例中并没有这样一个数组）
    // 所以和&array的值相差32
    std::cout << std::setw(20) << "&array + 1 = " << &array + 1 << std::endl;
    std::cout << std::endl;

    // 数组的长度
    std::cout << std::setw(20) << "sizeof(array) = " << sizeof(array) << std::endl;
    
    // array首元素的长度
    std::cout << std::setw(20) << "sizeof(array[0]) = " << sizeof(array[0]) << std::endl;
    
    // array地址的长度
    std::cout << std::setw(20) << "sizeof(&array) = " << sizeof(&array) << std::endl;

    return 0;
}