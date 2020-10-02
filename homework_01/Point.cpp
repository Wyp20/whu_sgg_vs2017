#include "Point.h"

#include <string>
#include <sstream>
#include <iomanip>

std::ostream& operator<<(std::ostream& out, const Point& p)
{
    std::cout.setf(std::ios::fixed);

    out << std::setprecision(3) << "Point(" << p._x << ", " << p._y << ")";
    return out;
}

// �����ʽ��X����, Y����
// ʾ����1.3589, 2.5583
// ע��������û����֤����������Ƿ���ϼȶ��ĸ�ʽ
std::istream& operator>>(std::istream& in, Point& p)
{
    std::string tmp;
    getline(in, tmp);

    size_t pos = tmp.find(',');
    if (pos != std::string::npos)
    {
        tmp.erase(pos, 1);

        std::stringstream ss;
        ss << tmp;
        ss >> p._x >> p._y;
    }

    return in;
}

Point& Point::operator=(const Point& other)
{
    if (this != &other)
    {
        _x = other._x;
        _y = other._y;
    }
    
    return *this;
}