#include <iostream>
#include <iomanip>

int main(void)
{
    int array[8] = { 2, 56, 12, 6, 30, 19, 20, 25 };

    // ����array��Ԫ��2���ڴ��׵�ַ
    std::cout << std::setw(20) << "array = " << array << std::endl;

    // ����array��Ԫ��2���ڴ��׵�ַ
    std::cout << std::setw(20) << "&array[0] = " << &array[0] << std::endl;

    // ����array���׵�ַ
    std::cout << std::setw(20) << "&array = " << &array << std::endl;

    // array����Ԫ���׵�ַ��array+1ҪԽ��һ��Ԫ�أ�����Ԫ�ص���һ��Ԫ�ص��׵�ַ
    // ���Ժ�array��ֵ���4
    std::cout << std::setw(20) << "array + 1 = " << array + 1 << std::endl;

    // &array[0]����Ԫ���׵�ַ��&array[0]+1ҪԽ��һ��Ԫ�أ�����Ԫ�ص���һ��Ԫ�ص��׵�ַ
    std::cout << std::setw(20) << "&array[0] + 1 = " << &array[0] + 1 << std::endl;

    // &array�������׵�ַ��&array+1ҪԽ��һ�����飬����һ������ĵ�ַ����Ȼ�����в�û������һ�����飩
    // ���Ժ�&array��ֵ���32
    std::cout << std::setw(20) << "&array + 1 = " << &array + 1 << std::endl;
    std::cout << std::endl;

    // ����ĳ���
    std::cout << std::setw(20) << "sizeof(array) = " << sizeof(array) << std::endl;
    
    // array��Ԫ�صĳ���
    std::cout << std::setw(20) << "sizeof(array[0]) = " << sizeof(array[0]) << std::endl;
    
    // array��ַ�ĳ���
    std::cout << std::setw(20) << "sizeof(&array) = " << sizeof(&array) << std::endl;

    return 0;
}