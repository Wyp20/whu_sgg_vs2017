#ifndef CIRCLE_H_
#define CIRCLE_H_

class Circle
{
private:
    double _r;

public:
    Circle();

public:
    bool setR(double r);
    double getR() { return _r; };
    inline double area();
};

inline double Circle::area()
{
    return _r * _r * 3.14;
}

#endif // !CIRCLE_H_

