#include "Vector.h"
#include "Point.h"

#include <random>
#include <ctime>
#include <list>

void drunkardToLamp()
{
    // light��������Ƶľ��루��λ�����ף�
    // distance������ǰ����ԭ��ľ���
    double light(1000.0), distance(0.0);

    double x(0.0), y(0.0); // x��y�����㵱ǰλ��ʱʹ��
    Vector v;
    std::list<Vector> stepList; // ���ÿһ����ŵ��λ��

    int count(0); // ������

    // �����ľ��������������
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disStep(45, 80); // ����[45,80]�ڵ������������λ�����ף�
    std::uniform_int_distribution<> disAngle(0, 179); // ����[0,179]�ڵ�����Ƕ�

    // distance < light����û�ߵ�
    while (distance < light)
    {
        ++count;

        // ����������ĽǶȺͲ�������v������������ǽǶȣ�����ɻ��ȴ���ȥ
        v.setPolar((double)disStep(gen), (double)disAngle(gen) * PIE / 180);
        std::cout << "New step: " << v << std::endl;

        if (stepList.empty())
        {
            stepList.push_back(v);
        }
        else
        {
            // last����һ�ε���ŵ�λ��
            const Vector last = stepList.back();

            // x������ŵ��x���꣬y������ŵ��y����
            x = last.getX() + v.getX();
            y = last.getY() + v.getY();
            v.setRect(x, y);        // v������������������setRect����������ŵ���Ϣ
            stepList.push_back(v);  // ������ŵ㱣����list��   
        }

        distance = v.len(); // ��ǰλ�þ���ԭ��ľ���
        std::cout << "Current pos: " << v << " ---- To original point: " << distance << std::endl;
    }

    std::cout << "Total steps: " << count << std::endl;
    std::cout << "Average step lenght: " << (light / count) << "cm" << std::endl;
}

void pointOverload()
{
    Point p1, p2;

    std::cout << "Please input x and y��";
    std::cin >> p1;

    p2 = p1;
    std::cout << p2 << std::endl;
}

int main(void)
{
    // ��һ�οκ���ϰ��2����������
    //drunkardToLamp();

    // ��һ�οκ���ϰ��3����������ϰ
    pointOverload();
  
    return 0;
}
