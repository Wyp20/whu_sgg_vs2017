#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <iostream>

// 作用：为了让24行的代码能够编译通过，提前告知编译器有RectCoordinate类
// 原因：因为在该行出现了RectCoordinate的引用，而RectCoordinate类却是在这一行之后才定义
// 的，在此之前编译器不知道RectCoordinate类。而RectCoordinate类里也用到了PolarCoordinate类，
// 所以互换位置解决不了问题
// 其他说明：类的成员变量或成员函数的形参，如果是指针或者引用，在编译阶段只要知道有对应的类型存在即
// 可通过，这条语句就是声明一下类的存在，而非定义，可以多次出现在头文件中用以解决这类情况，但链接阶
// 段就必须知道这个类长什么样子了
class RectCoordinate; 

// 极坐标类
class PolarCoordinate
{
public:
    PolarCoordinate() : _r(0.0), _angle(0.0) {}
    PolarCoordinate(double r, double angle) : _r(r), _angle(angle) {}

    // 给定直角坐标，更新极径和极角
    void updateFromRect(const RectCoordinate& rect);

public:
    double _r;      // 极径
    double _angle;  // 极角（单位：弧度）
};

class RectCoordinate
{
public:
    RectCoordinate() : _x(0.0), _y(0.0) {}
    RectCoordinate(double x, double y) : _x(x), _y(y) {}

    // 给定极坐标，更新x和y
    void updateFromPolar(const PolarCoordinate& polar);

public:
    double _x;  // x坐标
    double _y;  // y坐标
};

class Vector
{
    friend std::ostream& operator<<(std::ostream& out, const Vector& v);

public:
    Vector();
    Vector(double x, double y);
    ~Vector();

    double len();   // 取向量的长度

    void setPolar(double r, double angel);  // 设置极坐标
    void setRect(double x, double y);  // 设置直角坐标

    double getX() const { return _rect._x; }
    double getY() const { return _rect._y; }

private:
    PolarCoordinate _polar;
    RectCoordinate _rect;
};

std::ostream& operator<<(std::ostream& out, const Vector& v);

const double PIE = 3.1415926;

#endif // !VECTOR_H_



