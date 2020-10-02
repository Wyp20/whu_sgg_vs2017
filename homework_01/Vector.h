#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <iostream>

// ���ã�Ϊ����24�еĴ����ܹ�����ͨ������ǰ��֪��������RectCoordinate��
// ԭ����Ϊ�ڸ��г�����RectCoordinate�����ã���RectCoordinate��ȴ������һ��֮��Ŷ���
// �ģ��ڴ�֮ǰ��������֪��RectCoordinate�ࡣ��RectCoordinate����Ҳ�õ���PolarCoordinate�࣬
// ���Ի���λ�ý����������
// ����˵������ĳ�Ա�������Ա�������βΣ������ָ��������ã��ڱ���׶�ֻҪ֪���ж�Ӧ�����ʹ��ڼ�
// ��ͨ������������������һ����Ĵ��ڣ����Ƕ��壬���Զ�γ�����ͷ�ļ������Խ����������������ӽ�
// �ξͱ���֪������೤ʲô������
class RectCoordinate; 

// ��������
class PolarCoordinate
{
public:
    PolarCoordinate() : _r(0.0), _angle(0.0) {}
    PolarCoordinate(double r, double angle) : _r(r), _angle(angle) {}

    // ����ֱ�����꣬���¼����ͼ���
    void updateFromRect(const RectCoordinate& rect);

public:
    double _r;      // ����
    double _angle;  // ���ǣ���λ�����ȣ�
};

class RectCoordinate
{
public:
    RectCoordinate() : _x(0.0), _y(0.0) {}
    RectCoordinate(double x, double y) : _x(x), _y(y) {}

    // ���������꣬����x��y
    void updateFromPolar(const PolarCoordinate& polar);

public:
    double _x;  // x����
    double _y;  // y����
};

class Vector
{
    friend std::ostream& operator<<(std::ostream& out, const Vector& v);

public:
    Vector();
    Vector(double x, double y);
    ~Vector();

    double len();   // ȡ�����ĳ���

    void setPolar(double r, double angel);  // ���ü�����
    void setRect(double x, double y);  // ����ֱ������

    double getX() const { return _rect._x; }
    double getY() const { return _rect._y; }

private:
    PolarCoordinate _polar;
    RectCoordinate _rect;
};

std::ostream& operator<<(std::ostream& out, const Vector& v);

const double PIE = 3.1415926;

#endif // !VECTOR_H_



