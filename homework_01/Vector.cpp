#include "Vector.h"

#include <cmath>
#include <iomanip>

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(2);

    out << "P(" << v._polar._r << ", " << (v._polar._angle * 180 / PIE) << "°), ";
    out << "R(" << v._rect._x << ", " << v._rect._y << ")";
    return out;
}

void PolarCoordinate::updateFromRect(const RectCoordinate& rect)
{
    // 极径 = 开根号(x的平方 + y的平方)
    _r = std::sqrt(rect._x * rect._x + rect._y * rect._y);

    // 通过argtan()计算弧度
    _angle = atan(rect._y / rect._x);
}

void RectCoordinate::updateFromPolar(const PolarCoordinate& polar)
{
    _x = polar._r * std::cos(polar._angle);
    _y = polar._r * std::sin(polar._angle);
}

Vector::Vector() : _rect(0.0, 0.0), _polar(0.0, 0.0)
{
}

Vector::Vector(double x, double y) : _rect(x, y)
{
    _polar.updateFromRect(_rect);
}

Vector::~Vector()
{
}

double Vector::len()
{
    return _polar._r;
}

void Vector::setPolar(double r, double angel)
{
    _polar._r = r;
    _polar._angle = angel;

    // 同步更新直角坐标
    _rect.updateFromPolar(_polar);
}

void Vector::setRect(double x, double y)
{
    _rect._x = x;
    _rect._y = y;

    // 同步更新极坐标
    _polar.updateFromRect(_rect);
}
