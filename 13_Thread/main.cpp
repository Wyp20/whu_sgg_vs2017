#include <iostream>
#include <thread>

void f1(int n)
{
    for (int i = 0; i < 5; ++i) 
    {
        std::cout << "Thread 1 executing" << std::endl;
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i) 
    {
        std::cout << "Thread 2 executing" << std::endl;
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo
{
public:
    int n;
    static int s;

public:
    foo() : n(0) {}

    void bar()
    {
        for (int i = 0; i < 5; ++i) 
        {
            std::cout << "Thread 3 executing" << std::endl;
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    static void staticBar()
    {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "Thread 4 executing" << std::endl;
            ++s;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

int foo::s = 0;

int main(void)
{
    int n = 0;
    foo f;

    std::thread t1(f1, n + 1); // 按值传递: void f1(int n)
    std::thread t2(f2, std::ref(n)); // 按引用传递: void f2(int& n)
    std::thread t3(&foo::bar, &f); // t3在对象f上运行foo::bar()--->f.bar()
    std::thread t4(foo::staticBar); // t4运行foo的静态成员函数foo::staticBar()

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of f::n is " << f.n << '\n';
    std::cout << "Final value of foo::s is " << foo::s << '\n';

    return 0;
}
