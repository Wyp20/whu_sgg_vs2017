#include "Vector.h"
#include "Point.h"

#include <random>
#include <ctime>
#include <list>

void drunkardToLamp()
{
    // light：醉汉距离灯的距离（单位：厘米）
    // distance：醉汉当前距离原点的距离
    double light(1000.0), distance(0.0);

    double x(0.0), y(0.0); // x、y：计算当前位置时使用
    Vector v;
    std::list<Vector> stepList; // 存放每一个落脚点的位置

    int count(0); // 计数用

    // 以下四句用来产生随机数
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disStep(45, 80); // 产生[45,80]内的随机步长（单位：厘米）
    std::uniform_int_distribution<> disAngle(0, 179); // 产生[0,179]内的随机角度

    // distance < light：还没走到
    while (distance < light)
    {
        ++count;

        // 用随机产生的角度和步长设置v，由于随机的是角度，换算成弧度传进去
        v.setPolar((double)disStep(gen), (double)disAngle(gen) * PIE / 180);
        std::cout << "New step: " << v << std::endl;

        if (stepList.empty())
        {
            stepList.push_back(v);
        }
        else
        {
            // last：上一次的落脚点位置
            const Vector last = stepList.back();

            // x：新落脚点的x坐标，y：新落脚点的y坐标
            x = last.getX() + v.getX();
            y = last.getY() + v.getY();
            v.setRect(x, y);        // v本来存的是随机向量，setRect后存的是新落脚点信息
            stepList.push_back(v);  // 将新落脚点保存在list中   
        }

        distance = v.len(); // 当前位置距离原点的距离
        std::cout << "Current pos: " << v << " ---- To original point: " << distance << std::endl;
    }

    std::cout << "Total steps: " << count << std::endl;
    std::cout << "Average step lenght: " << (light / count) << "cm" << std::endl;
}

void pointOverload()
{
    Point p1, p2;

    std::cout << "Please input x and y：";
    std::cin >> p1;

    p2 = p1;
    std::cout << p2 << std::endl;
}

int main(void)
{
    // 第一次课后练习（2）：醉汉行走
    //drunkardToLamp();

    // 第一次课后练习（3）：重载练习
    pointOverload();
  
    return 0;
}
