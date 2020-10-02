#include <thread>
#include <iostream>
#include <list>

std::list<int> l;
int k = 0;

void testGlobal()
{
    std::thread::id id = std::this_thread::get_id();

    for (; k<20; ++k)
    {
        l.push_back(k);

        std::cout << id << ": " << k << std::endl;
    }
}

void testLocal()
{
    std::thread::id id = std::this_thread::get_id();

    static int a = 100;

    std::list<int> l;
    for (int i(0); i < 20; ++i)
    {
        l.push_back(i);
        ++a;
    }

    for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        std::cout << id << ": " << *it << std::endl;
    }

    std::cout << "a: " << a << std::endl;
}

int main(void)
{
    std::thread t1(testLocal), t2(testLocal);

    //std::thread t1(testGlobal), t2(testGlobal);

    t1.join();
    t2.join();

    /*std::cout << "size(l): " << l.size() << std::endl;

    for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << " ";
    }*/

    return 0;
}