#ifndef MYTEMPLATE_H_
#define MYTEMPLATE_H_

template <typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T1, typename T2>
class Pair
{
public:
    T1 _key;
    T2 _value;

public:
    Pair(T1 k, T2 v) : _key(k), _value(v) {}
    bool operator<(const Pair<T1, T2>& other)
    {
        return _key < other._key;
    }
};

#endif // !MYTEMPLATE_H_
