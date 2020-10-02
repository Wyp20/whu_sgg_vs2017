#include "Circle.h"
#include <memory>
#include <iomanip>

int *m;

int* pA[8];

void copy(const Circle *src, Circle *dst)
{
    dst->setR(src->getR());
}

void difference()
{
    int array[8] = { 2, 56, 12, 6, 30, 19, 20, 25 };

    std::cout << std::setw(20) << "array = " << array << std::endl;
    std::cout << std::setw(20) << "&array[0] = " << &array[0] << std::endl;
    std::cout << std::setw(20) << "&array = " << &array << std::endl;
    std::cout << std::setw(20) << "array + 1 = " << array + 1 << std::endl;
    std::cout << std::setw(20) << "&array[0] + 1 = " << &array[0] + 1 << std::endl;
    std::cout << std::setw(20) << "&array + 1 = " << &array + 1 << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(20) << "sizeof(array) = " << sizeof(array) << std::endl;
    std::cout << std::setw(20) << "sizeof(array[0]) = " << sizeof(array[0]) << std::endl;
    std::cout << std::setw(20) << "sizeof(&array) = " << sizeof(&array) << std::endl;
}

void bubbleSort(int a[], int len)
//void bubbleSort(int *a, int len)
{
    std::cout << sizeof(a) << std::endl;
    for (int i = 0; i < len - 1; ++i)
    {
        for (int j = i + 1; j < len; ++j)
        {
            if (a[j-1] > a[j])
            {
                int tmp = a[j-1];
                a[j-1] = a[j];
                a[j] = tmp;
            }
        }
    }
}

int add(int a, int b)
{
    return a + b;
}

typedef int(*FUNC)(int, int);

int main(void)
{
    int i(10), a(5);
    int* p = &i;
    int& ri = i;

    a = i;
    a = *p;
    a = ri;

    char *buffer = new char[sizeof(Circle) * 10];
    Circle *c1 = new(buffer) Circle(2.0);
    c1->area();
    c1->~Circle();
    delete[] buffer;

    //int *p1, *p2;
    //*p1 = 10;

    //int *p1 = new int(2);
    //*p1 = 10;
    //delete p1;
    //p1 = nullptr;

    //int *p2 = new int(2);
    //delete p2;
    //p2 = nullptr;

    int array[8] = {2, 56, 12, 6, 30, 19, 20, 25};
    std::cout << sizeof(array) << std::endl;
    bubbleSort(array, 8);

    int(*pArray)[8] = &array;

    /*int* pA[8];*/

    //int(*pFunc)(int, int) = add;
    //// FUNC pFunc = add;
    //std::cout << pFunc(10, 2) << std::endl;
 
    return 0;
}